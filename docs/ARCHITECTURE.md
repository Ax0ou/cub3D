# Architecture

> Toute modification d'une struct ou d'un prototype de `includes/cub3d.h` se reporte ici, dans la même PR.

## 1. Vue d'ensemble

```
./cub3D map.cub
      │
      ▼
 ┌──────────────┐  t_scene (garantie valide)   ┌──────────────┐       ┌──────────────────┐
 │   PARSING    │ ───────────────────────────▶ │  init_player │ ────▶ │ init_graphics    │
 │ src/parsing/ │  textures, couleurs, map,     │  src/game/   │       │ load_textures    │
 └──────────────┘  spawn                        └──────────────┘       └────────┬─────────┘
      │ erreur → "Error\n<message>" + exit 1                                    │
                                                                               ▼
                         ┌────────────────────── mlx_loop ──────────────────────┐
                         │  game_loop()  (à chaque frame)                        │
                         │     update_player()   ← flags t_keys (press/release)  │
                         │     render_frame()                                    │
                         │        ciel + sol                                     │
                         │        pour chaque colonne x : init_ray → run_dda →   │
                         │          compute_wall_distance → compute_wall_slice → │
                         │          draw_wall_column                             │
                         │        mlx_put_image_to_window                         │
                         └───────────────────────────────────────────────────────┘
                                         ESC / croix rouge → on_close → destroy_game → exit 0
```

## 2. Arborescence

```
Cube3d/
├── Makefile               all clean fclean re bonus  (+ norm, test)
├── includes/
│   ├── cub3d.h            LE contrat : structs + prototypes
│   └── keys.h             keycodes Mac / Linux
├── src/
│   ├── main.c
│   ├── parsing/           [A] lecture et validation du .cub
│   ├── render/            [B] fenêtre, raycasting, textures
│   ├── game/              [B] joueur, touches, déplacements
│   ├── utils/             [A] erreurs, free, chaînes
│   └── platform/          display_linux.c / display_macos.c (choisi par le Makefile)
├── libft/                 notre libft (+ get_next_line, ft_printf)
├── mlx_linux/ mlx_macos/  MiniLibX (sources)
├── maps/valid/ maps/invalid/
├── textures/              .xpm (placeholders en attendant le thème)
├── tests/run_tests.sh
└── docs/
```

## 3. Les structures

| Struct | Rôle | Rempli par | Lu par |
|---|---|---|---|
| `t_vec` | vecteur 2D `{x, y}` en `double` | — | partout |
| `t_image` | image MLX + accès direct aux pixels (`addr`, `line_length`…) | `init_graphics`, `load_textures` | `put_pixel`, `get_texture_pixel` |
| `t_scene` | tout le contenu du `.cub` | **parsing uniquement** | init_player, load_textures, raycast, render |
| `t_player` | `pos`, `dir`, `plane` (plan caméra) | `init_player`, `movement.c` | raycast |
| `t_ray` | les calculs d'**un** rayon (une colonne) | `raycast.c`, `draw_wall.c` | `draw_wall.c` |
| `t_keys` | touches enfoncées (0/1) | `hooks.c` | `update_player` |
| `t_game` | la racine : mlx, fenêtre, frame, textures, scene, player, keys | `main` | tout le monde (`t_game *`) |

| Enum | Valeurs |
|---|---|
| `t_side` | `NORTH SOUTH WEST EAST` (+ `SIDE_COUNT`) — index de `texture_paths[]` et `textures[]` |
| `t_element` | `ELEM_NO … ELEM_CEILING` (+ `ELEM_COUNT`, `ELEM_UNKNOWN`) — index de `scene.found[]` |

### Garanties de `t_scene` après un `parse_scene` réussi

C'est ce que la personne B a le droit de supposer sans vérifier :

1. Les 4 `texture_paths` existent, finissent par `.xpm`, et le fichier s'ouvre.
2. `floor_color` / `ceiling_color` sont au format `0xRRGGBB`.
3. `map` est un **rectangle** : `map_height` lignes de `map_width` caractères exactement (complétées par des espaces), terminé par `NULL`.
4. La map ne contient que `0 1 ' '` : la lettre du joueur a été remplacée par `0`.
5. `spawn_x` (colonne), `spawn_y` (ligne), `spawn_dir` (`N S E W`) sont remplis.
6. La map est fermée → un rayon finit **toujours** par toucher un `1`.

### Repère

- `map[y][x]` : `y` = ligne (0 = haut du fichier = **nord**), `x` = colonne (0 = gauche = **ouest**).
- `y` augmente vers le **sud**. D'où `N → dir = (0, -1)`.

## 4. Le raycasting choisi : DDA (Lode Vandevenne)

Pour chaque colonne `x` de l'écran :

```
camera_x = 2 * x / WIN_WIDTH - 1                       // -1 (gauche) … +1 (droite)
ray.dir  = player.dir + player.plane * camera_x
```

On avance de case en case (DDA) en choisissant toujours la prochaine ligne de grille la plus proche (verticale ou horizontale) jusqu'à tomber sur un mur. La **distance perpendiculaire** au plan caméra (et non la distance réelle) évite l'effet fish-eye. La hauteur du mur à l'écran vaut `WIN_HEIGHT / wall_dist`.

Pourquoi DDA et pas la méthode angles + intersections horizontales/verticales du repo de référence : moins de trigonométrie, pas de cas particuliers à 90°/270°, pas de fish-eye à corriger, et c'est la méthode la plus documentée → plus facile à défendre.

Tout est détaillé en commentaire au-dessus des fonctions de `src/render/raycast.c` et `draw_wall.c`.

## 5. Décisions techniques (figées sauf accord des deux)

| # | Décision | Pourquoi |
|---|---|---|
| D1 | **MiniLibX classique** (`mlx_linux` / `mlx_macos`), pas MLX42 | le sujet impose « the miniLibX » ; MLX42 (utilisée par le repo de référence) est une autre lib, risqué à l'éval |
| D2 | Textures en **`.xpm`** | seul format chargé nativement par `mlx_xpm_file_to_image` sur les deux OS |
| D3 | On dessine dans **une image** (`t_image frame`) puis un seul `mlx_put_image_to_window` par frame | `mlx_pixel_put` est beaucoup trop lent |
| D4 | Touches gérées par **flags press/release** (`t_keys`) + mouvement dans `game_loop` | mouvement fluide, plusieurs touches à la fois |
| D5 | Map stockée en **rectangle** complété par des espaces | plus jamais de lecture hors d'une ligne |
| D6 | Map fermée = aucune case marchable voisine d'un espace ou du bord | simple, sans récursion (pas de stack overflow sur grandes maps) |
| D7 | Toute erreur : `Error\n<message>\n` sur **stderr**, code de sortie `1` | exigé par le sujet + testable automatiquement |
| D8 | Un seul `t_game` dans `main`, pas de globale | norme |
| D9 | `mlx_destroy_display` n'existe que sur Linux → fonction `destroy_display()` dans `src/platform/`, le Makefile compile la bonne version | pas de `#ifdef` dans les `.c` |
| D10 | *(à décider au kickoff)* tabulations acceptées comme séparateurs dans les éléments ? | à trancher, puis l'écrire ici |

## 6. Correspondance avec le repo de référence (KrolPolski/cube3d)

Utile pour aller lire comment ils ont fait — **sans copier** (les APIs MLX42 sont différentes de toute façon).

| Référence | Chez nous | Remarque |
|---|---|---|
| `t_map` (`map`, `no`, `so`, `ea`, `we`, `floor`, `f`, `c`, `start_i`…) | `t_scene` | `texture_paths[4]` indexé par `t_side`, couleurs déjà converties en int, `spawn_x/y/dir` |
| `t_info` (`p_x`, `p_y`, `p_orient`, `ray_*`, `horiz_vec`…) | `t_player` + `t_ray` + `t_game` | on sépare joueur / rayon / état global |
| `t_images` (`txt_no`, `no`, `world`…) | `t_image textures[4]` + `t_image frame` | |
| `t_cw` (cast wall) | champs de `t_ray` | `line_height`, `draw_start`, `wall_x`… |
| `t_sq` (minimap) | bonus semaine 5 | |
| `enum e_dir {north, east, south, west, error}` | `t_side` | |
| `parsing.c` … `parsing4.c`, `validation*.c` | `src/parsing/*` | un fichier par responsabilité |
| `raycaster*.c`, `cast_wall.c`, `walls.c` | `src/render/*` | DDA au lieu d'angles |
| `move_hooks*.c` | `src/game/*` | |
| `draw_2d_map.c`, `draw_squares.c` | bonus minimap | |

## 7. macOS vs Linux

| | macOS | Linux (écoles + CI) |
|---|---|---|
| MLX | `mlx_macos/` | `mlx_linux/` |
| Keycodes | `keys.h` branche `__APPLE__` | `keys.h` branche X11 |
| `mlx_destroy_display` | n'existe pas | à appeler + `free(mlx)` |
| Leaks | `leaks --atExit -- ./cub3D map.cub` | `valgrind --leak-check=full ./cub3D map.cub` |

Les correcteurs testent souvent sur les machines de l'école : **tester sur une machine Linux de l'école au moins une fois par semaine**, la CI Linux ne remplace pas ce test.
