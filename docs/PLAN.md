# Plan — 5 semaines (15 oct. → 19 nov. 2026)

> Chaque semaine = un **milestone** GitHub avec ses issues. On ne passe à la semaine suivante que si le **critère de passage** est atteint (sinon on décale, on ne bâcle pas).
> Rythme visé : ~15-20 h / semaine / personne. Objectif réel : mandatory fini fin semaine 4, la semaine 5 sert de marge + bonus.

| Semaine | Dates | Thème | A — Parsing | B — Moteur |
|---|---|---|---|---|
| S1 | 15 → 22 oct. | Fondations | utils, erreurs, lecture du fichier | fenêtre, image, touches, fermeture propre |
| S2 | 23 → 29 oct. | Parsing complet + premier rendu | éléments, couleurs, map, validation | DDA, murs unis, ciel/sol |
| S3 | 30 oct. → 5 nov. | Intégration | maps de test, CI tests obligatoire | textures, WASD, rotation |
| S4 | 6 → 12 nov. | Robustesse + éval blanche | crash tests | fluidité, leaks |
| S5 | 13 → 19 nov. | Bonus + thème | collisions, portes | minimap, souris, sprites |

---

## S1 — Fondations

**Ensemble** : kickoff (rôles, `cub3d.h`, thème), board Projects, tuto lodev partie 1 lu par les deux.

- A : `print_error`, `exit_error`, `string_utils`, `free_*`, `has_extension`, `read_file_lines`
- B : `init_graphics`, `put_pixel`, hooks (ESC, croix, press/release), `destroy_game`

**Critère de passage**
- `./cub3D` sans argument / mauvaise extension / fichier absent → `Error` + message (3 premiers tests du tester verts)
- B ouvre une fenêtre noire qui se ferme proprement avec ESC **et** la croix, 0 leak (valgrind)
- Une première PR de chacun mergée sur `dev` avec la CI verte (norme + build)

## S2 — Parsing complet + premier rendu

- A : `parse_elements`, `parse_texture`, `parse_color`, `parse_map`, `check_map_chars`, `check_map_closed`, `parse_scene`
- B : ciel/sol, DDA (`init_ray`, `run_dda`, `compute_wall_distance`), `compute_wall_slice`, murs en couleur unie par face, `init_player` — sur une map écrite en dur

**Critère de passage**
- `./tests/run_tests.sh` : **toutes** les maps invalides → `Error` (tous les tests parsing verts)
- `valgrind` propre sur tous les cas d'erreur (`./tests/run_tests.sh --leaks` sur Linux)
- B affiche des murs en 3D (couleurs unies) cohérents depuis les 4 orientations de départ

## S3 — Intégration

- Ensemble : brancher parsing → rendu sur `dev`, toutes les maps valides s'ouvrent
- A : nouvelles maps de test (limites), rendre le job **Tests** obligatoire dans la protection de `main` et `dev`
- B : `load_textures`, `get_texture_pixel`, murs texturés, `move_player`, `rotate_player`, `update_player`

**Critère de passage**
- CI 100 % verte, job Tests compris (`--valid --leaks`)
- On se balade dans `maps/valid/subject.cub` : 4 textures différentes, pas inversées, mouvements fluides, flèches dans le bon sens

## S4 — Robustesse + éval blanche (mandatory = FINI)

- A : crash tests (map géante, ligne vide en fin de fichier, fichier binaire, `/dev/null`, xpm cassé, droits de lecture retirés)
- B : fenêtre minimisée / recouverte / déplacée, perf sur grande map, aucun leak à la fermeture
- Ensemble : README final, `docs/CHECKLIST.md` entièrement cochée, test sur une machine de l'école, **chacun explique le module de l'autre**, merge `dev` → `main`

**Critère de passage**
- Éval blanche entre nous deux avec la checklist : 0 point perdu
- `main` = version rendable

## S5 — Bonus + thème

> Les bonus ne comptent **que si le mandatory est parfait**. Si S4 n'est pas validée, la S5 sert à finir S4.

- Ensemble : organisation des fichiers `*_bonus.c`, intégration du thème (textures, maps signature)
- A : collisions (glissement le long des murs), portes (`D` dans la map, ouverture avec une touche)
- B : minimap, rotation souris, sprite animé

**Critère de passage** : `make bonus` OK, norme OK, 0 leak, mandatory toujours parfait → rendu.
