#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# Creates labels, the 5 weekly milestones and every issue of the project.
# Run ONCE from the repo root, after the GitHub repo exists:
#     ./scripts/bootstrap_issues.sh
# Needs: gh (logged in), the repo as "origin".
# ---------------------------------------------------------------------------
set -euo pipefail

REPO=$(gh repo view --json nameWithOwner -q .nameWithOwner)
echo "Repo: $REPO"

# ------------------------------- labels ------------------------------------
label() { gh label create "$1" --color "$2" --description "$3" --force >/dev/null; }

label "area:parsing" "1d76db" "src/parsing — lecture et validation du .cub"
label "area:render"  "5319e7" "src/render — fenêtre, raycasting, textures"
label "area:game"    "0e8a16" "src/game — joueur, touches, mouvements"
label "area:utils"   "c5def5" "src/utils — erreurs, free, chaînes"
label "area:infra"   "666666" "Makefile, CI, repo, organisation"
label "area:test"    "fbca04" "maps de test, tester, leaks"
label "area:docs"    "0075ca" "README, docs/, défense"
label "role:A"       "d4c5f9" "Personne A — Parsing & robustesse"
label "role:B"       "bfdadc" "Personne B — Moteur & jeu"
label "role:both"    "fef2c0" "À faire ensemble"
label "bonus"        "e99695" "Partie bonus (seulement si mandatory parfait)"
label "theme"        "f9d0c4" "Thème / direction artistique"
label "type:bug"     "d73a4a" "Quelque chose ne marche pas"

# ----------------------------- milestones ----------------------------------
milestone() {
	gh api "repos/$REPO/milestones" -f title="$1" -f due_on="$2T23:59:59Z" \
		-f description="$3" >/dev/null 2>&1 || true
}

M1="S1 — Fondations"
M2="S2 — Parsing complet + premier rendu"
M3="S3 — Intégration"
M4="S4 — Robustesse + éval blanche"
M5="S5 — Bonus + thème"
milestone "$M1" "2026-10-22" "Fenêtre qui s'ouvre/se ferme proprement, erreurs d'arguments gérées. Voir docs/PLAN.md"
milestone "$M2" "2026-10-29" "Toutes les maps invalides refusées sans leak, murs 3D en couleur unie. Voir docs/PLAN.md"
milestone "$M3" "2026-11-05" "Parsing branché au rendu, textures, WASD + flèches, CI 100% verte. Voir docs/PLAN.md"
milestone "$M4" "2026-11-12" "Mandatory parfait, checklist cochée, merge sur main. Voir docs/PLAN.md"
milestone "$M5" "2026-11-19" "Bonus + thème, rendu. Voir docs/PLAN.md"

# ------------------------------- issues ------------------------------------
# issue "<title>" "<milestone>" "<label1,label2>"   (body on stdin)
issue() {
	gh issue create --title "$1" --milestone "$2" --label "$3" --body-file - >/dev/null
	echo "  + $1"
}

echo "Creating issues..."

# =============================== S1 ========================================
issue "Kickoff : rôles, sujet, relecture de cub3d.h" "$M1" "area:infra,role:both" <<'EOF'
Première séance ensemble (~2 h). Déroulé complet : `TEAM_WORK.md` §10.

- [ ] Le binôme accepte l'invitation et clone le repo
- [ ] Lire `docs/subject.pdf` + `TEAM_WORK.md` ensemble
- [ ] Choisir qui est **A (parsing)** et qui est **B (moteur)**
- [ ] Relire `includes/cub3d.h` : renommer maintenant ce qui n'est pas clair
- [ ] Trancher la décision D10 de `docs/ARCHITECTURE.md` (tabulations acceptées ?)
- [ ] Chacun s'assigne ses issues S1

**Fini quand** : rôles décidés, chacun s'est assigné les issues `role:A` ou `role:B` de la S1.
EOF

issue "Créer le board GitHub Projects + première PR de test" "$M1" "area:infra,role:both" <<'EOF'
- [ ] Onglet **Projects** → New project → *Board* → nom « cub3D »
- [ ] Colonnes : `Todo` / `In Progress` / `In Review` / `Done`
- [ ] Ajouter toutes les issues du repo au board
- [ ] Workflows du board : *Item closed → Done*, *Pull request merged → Done*
- [ ] Chacun ouvre une mini PR (ex : son login dans le README) pour vérifier que la CI tourne et que la review fonctionne

**Fini quand** : les 2 PR sont mergées sur `dev` avec la CI verte.
EOF

issue "Thème : choisir l'univers du jeu (brouillon)" "$M1" "theme,role:both" <<'EOF'
Discussion du kickoff, cf. `TEAM_WORK.md` §11.

- [ ] Univers choisi (donjon ? station spatiale ? backrooms ? 42 ?)
- [ ] 4 textures murales repérées (libres de droits) — 64×64 ou 128×128, même taille
- [ ] Couleurs sol / plafond
- [ ] Idée de bonus qui sert le thème (portes, sprite…)

Les textures actuelles (`textures/*.xpm`) restent des placeholders jusqu'à la S5.
Conversion : `magick image.png -resize 64x64 textures/north.xpm`

**Fini quand** : le choix est écrit dans un commentaire de cette issue.
EOF

issue "Tous les deux : comprendre le raycasting (tuto lodev partie 1)" "$M1" "area:render,role:both" <<'EOF'
Le moteur repose sur https://lodev.org/cgtutor/raycasting.html (partie « The Basic Idea » à « Textured Raycaster »).
**Les deux** doivent savoir l'expliquer à l'éval, pas seulement B.

- [ ] Lire le tuto
- [ ] Refaire sur papier : un joueur, `dir`, `plane`, 3 rayons, le DDA sur une grille 5×5
- [ ] Comprendre pourquoi on prend la distance **perpendiculaire** (fish-eye)
- [ ] Relire les commentaires de `src/render/raycast.c` et `draw_wall.c`

**Fini quand** : chacun a expliqué le DDA à l'autre avec le schéma.
EOF

issue "utils : print_error, exit_error, string_utils" "$M1" "area:utils,role:A" <<'EOF'
Fichiers : `src/utils/error.c`, `src/utils/string_utils.c`

- [ ] `print_error` : `Error\n<message>\n` sur **stderr**, retourne 1
- [ ] `exit_error` : print + `destroy_game` + `exit(1)`
- [ ] `is_space`, `skip_spaces`, `is_blank_line`

**Fini quand** : `./cub3D` (sans argument) et `./cub3D map.ber` affichent `Error` + message → les 2 premiers tests de `./tests/run_tests.sh` passent.
EOF

issue "utils : free_string_array, free_scene" "$M1" "area:utils,role:A" <<'EOF'
Fichier : `src/utils/cleanup.c`

- [ ] `free_string_array` : accepte `NULL`
- [ ] `free_scene` : les 4 `texture_paths` + `map`, accepte une scène à moitié remplie, remet les pointeurs à `NULL`

**Fini quand** : appelable 2 fois de suite sans double free.
EOF

issue "parsing : has_extension + read_file_lines" "$M1" "area:parsing,role:A" <<'EOF'
Fichiers : `src/parsing/parse_scene.c` (`has_extension`), `src/parsing/read_file.c`

- [ ] `has_extension` : `map.cub` ✅ — `.cub`, `map.cub.txt`, `map.CUB`, `mapcub` ❌
- [ ] `read_file_lines` avec `get_next_line` : tableau de lignes sans `\n`, terminé par `NULL`
- [ ] Toujours lire jusqu'à `NULL` (buffer statique de GNL = leak sinon)
- [ ] Fichier vide, inexistant, dossier → erreur explicite
- [ ] Garder les lignes vides (utile pour détecter une ligne vide dans la map)

**Fini quand** : tests « file does not exist », « directory named .cub », `file_empty.cub` verts + 0 leak.
EOF

issue "render : fenêtre + image frame + put_pixel" "$M1" "area:render,role:B" <<'EOF'
Fichiers : `src/render/init_graphics.c` (`init_graphics`), `src/render/pixel.c` (`put_pixel`)

- [ ] `mlx_init`, `mlx_new_window(WIN_WIDTH, WIN_HEIGHT)`, `mlx_new_image`, `mlx_get_data_addr`
- [ ] `put_pixel` qui écrit dans le buffer (ignore les coordonnées hors image)
- [ ] Test : remplir l'image d'un dégradé et l'afficher avec `mlx_put_image_to_window`

**Fini quand** : une fenêtre affiche une image remplie par `put_pixel`, sur Mac **et** sur Linux.
EOF

issue "game : hooks clavier + croix rouge + game_loop" "$M1" "area:game,role:B" <<'EOF'
Fichier : `src/game/hooks.c`

- [ ] `setup_hooks` : key press, key release, destroy (croix), `mlx_loop_hook(game_loop)`
- [ ] `on_key_press` / `on_key_release` : remplissent `t_keys` (utiliser `keys.h`, jamais un nombre en dur)
- [ ] ESC et croix → `on_close`
- [ ] `game_loop` : pour l'instant appelle juste `render_frame`

**Fini quand** : ESC et la croix ferment la fenêtre ; un `printf` temporaire montre que les flags passent à 1 puis 0.
EOF

issue "game : destroy_game, fermeture sans leak" "$M1" "area:game,role:B" <<'EOF'
Fichier : `src/utils/cleanup.c` (`destroy_game`), voir aussi `src/platform/`

- [ ] Détruire textures, frame, fenêtre, puis `destroy_display(game->mlx)`
- [ ] `free_scene`
- [ ] Chaque pointeur testé avant destruction (fermeture possible à n'importe quelle étape)

**Fini quand** : `valgrind --leak-check=full ./cub3D maps/valid/minimal.cub` puis ESC → « All heap blocks were freed » (hors bruit X11 éventuel, à noter dans la PR).
EOF

# =============================== S2 ========================================
issue "parsing : identifiants + parse_elements" "$M2" "area:parsing,role:A" <<'EOF'
Fichier : `src/parsing/parse_elements.c` (`get_element_type`, `parse_elements`)

- [ ] `NO SO WE EA F C` suivis d'au moins un espace
- [ ] Ordre libre, lignes vides entre les éléments
- [ ] Doublon → erreur, identifiant inconnu → erreur, map avant la fin des 6 éléments → erreur
- [ ] Remplit `scene->found[]`

**Fini quand** : `element_duplicate.cub`, `element_missing.cub`, `map_not_last_1.cub`, `map_not_last_2.cub` → `Error`.
EOF

issue "parsing : textures (parse_texture)" "$M2" "area:parsing,role:A" <<'EOF'
Fichier : `src/parsing/parse_elements.c` (`parse_texture`)

- [ ] Valeur vide → erreur ; espaces en fin de ligne ignorés
- [ ] Doit finir par `.xpm`
- [ ] Le fichier doit s'ouvrir (`open` puis `close`)
- [ ] Stocké dans `texture_paths[NORTH…EAST]` (pas de leak si erreur juste après)

**Fini quand** : `texture_bad_extension.cub`, `texture_not_found.cub` → `Error`.
EOF

issue "parsing : couleurs (parse_color, rgb_to_int)" "$M2" "area:parsing,role:A" <<'EOF'
Fichier : `src/parsing/parse_color.c`

- [ ] Exactement 3 composantes, chiffres uniquement, [0, 255]
- [ ] Pas de `ft_atoi` à l'aveugle (accepte `12abc`, déborde)
- [ ] `rgb_to_int` → `0xRRGGBB`

**Fini quand** : les 6 maps `color_*.cub` → `Error`, et `F 0,0,0` / `C 255,255,255` passent.
EOF

issue "parsing : parse_map (rectangle, lignes vides)" "$M2" "area:parsing,role:A" <<'EOF'
Fichier : `src/parsing/parse_map.c`

- [ ] `is_map_line`
- [ ] Ligne vide au milieu de la map → erreur
- [ ] Pas de map → erreur
- [ ] Map stockée en **rectangle** complété par des espaces (`map_width`, `map_height`)

**Fini quand** : `map_empty_line_inside.cub`, `map_missing.cub` → `Error` ; un `print` de debug montre un rectangle parfait sur `subject.cub`.
EOF

issue "parsing : check_map_chars (caractères + joueur unique)" "$M2" "area:parsing,role:A" <<'EOF'
Fichier : `src/parsing/check_map.c` (`check_map_chars`)

- [ ] Seulement `0 1 N S E W` et espace
- [ ] Exactement un joueur → `spawn_x`, `spawn_y`, `spawn_dir`, lettre remplacée par `0`

**Fini quand** : `map_invalid_char.cub`, `map_no_player.cub`, `map_two_players.cub` → `Error`.
EOF

issue "parsing : check_map_closed (map fermée)" "$M2" "area:parsing,role:A" <<'EOF'
Fichier : `src/parsing/check_map.c` (`check_map_closed`) — décision D6 de `docs/ARCHITECTURE.md`

- [ ] Chaque case marchable : ses 4 voisins existent et ne sont pas des espaces
- [ ] Bords de la map
- [ ] Joueur au bord

**Fini quand** : `map_open_wall.cub`, `map_space_hole.cub`, `map_player_on_border.cub` → `Error` et **toutes** les maps de `maps/valid/` passent.
EOF

issue "parsing : parse_scene + 0 leak sur tous les chemins d'erreur" "$M2" "area:parsing,role:A" <<'EOF'
Fichier : `src/parsing/parse_scene.c` (`parse_scene`)

- [ ] Enchaîne lecture → éléments → map → vérifications
- [ ] `free_string_array(lines)` dans tous les cas
- [ ] `./tests/run_tests.sh --leaks` sur Linux (ou la CI) → 0 leak

**Fini quand** : `./tests/run_tests.sh` → **tous** les tests parsing verts.
EOF

issue "render : ciel et sol" "$M2" "area:render,role:B" <<'EOF'
Fichier : `src/render/render_frame.c` (`draw_ceiling_and_floor`)

- [ ] Moitié haute = `ceiling_color`, moitié basse = `floor_color`
- [ ] Pour tester sans parsing : remplir `game.scene` à la main sur ta branche

**Fini quand** : la fenêtre affiche deux couleurs.
EOF

issue "render : DDA (init_ray, run_dda, compute_wall_distance)" "$M2" "area:render,role:B" <<'EOF'
Fichier : `src/render/raycast.c` — tout l'algo est en commentaire au-dessus des fonctions.

- [ ] `init_ray` : `camera_x`, `dir`, `delta_dist`, `step`, `side_dist`
- [ ] `run_dda` : avancer jusqu'au mur
- [ ] `compute_wall_distance` : distance perpendiculaire, `side` (N/S/E/W), `wall_x`
- [ ] Map en dur sur ta branche tant que le parsing n'est pas mergé

**Fini quand** : `printf` de debug cohérents pour la colonne du milieu (distance = nombre de cases jusqu'au mur en face).
EOF

issue "render : hauteur des murs + couleur unie par face" "$M2" "area:render,role:B" <<'EOF'
Fichiers : `src/render/draw_wall.c`, `src/render/render_frame.c`

- [ ] `compute_wall_slice` : `line_height`, `draw_start`, `draw_end` (bornés)
- [ ] Version 1 de `draw_wall_column` : une couleur par `t_side`
- [ ] `render_frame` : boucle sur toutes les colonnes + `mlx_put_image_to_window`

**Fini quand** : on voit des murs 3D, chaque face d'une couleur différente, pas de fish-eye.
EOF

issue "game : init_player depuis le spawn" "$M2" "area:game,role:B" <<'EOF'
Fichier : `src/game/init_player.c`

- [ ] `pos` = centre de la case
- [ ] `dir` / `plane` pour N, S, E, W (tableau dans le commentaire)

**Fini quand** : avec 4 maps identiques sauf la lettre, on regarde bien dans les 4 directions (et pas en miroir).
EOF

# =============================== S3 ========================================
issue "Intégration : parsing → rendu sur dev" "$M3" "area:infra,role:both" <<'EOF'
- [ ] Supprimer toute map / scène en dur
- [ ] `./cub3D` sur **chaque** map de `maps/valid/` → s'ouvre, s'affiche
- [ ] `./tests/run_tests.sh --valid` vert (Linux : `xvfb-run` ou machine de l'école)

**Fini quand** : job **Tests** vert sur `dev`.
EOF

issue "render : load_textures + get_texture_pixel" "$M3" "area:render,role:B" <<'EOF'
Fichiers : `src/render/init_graphics.c` (`load_textures`), `src/render/pixel.c` (`get_texture_pixel`)

- [ ] `mlx_xpm_file_to_image` pour les 4 faces + `mlx_get_data_addr`
- [ ] xpm invalide → `Error` sans leak (ajouter une map de test avec un faux .xpm)

**Fini quand** : les 4 textures sont chargées, une xpm cassée est refusée proprement.
EOF

issue "render : murs texturés (draw_wall_column)" "$M3" "area:render,role:B" <<'EOF'
Fichier : `src/render/draw_wall.c`

- [ ] `tex_x` depuis `wall_x`, inversion pour 2 faces
- [ ] `step` / `tex_pos` pour la colonne
- [ ] Vérifier avec des textures asymétriques (lettres, flèches) que rien n'est en miroir

**Fini quand** : `maps/valid/subject.cub` affiche 4 textures différentes, dans le bon sens.
EOF

issue "game : déplacements WASD (move_player, update_player)" "$M3" "area:game,role:B" <<'EOF'
Fichier : `src/game/movement.c`

- [ ] Avancer / reculer selon `dir`, strafe selon la perpendiculaire
- [ ] Ne jamais entrer dans un mur ni sortir de la map (x et y testés séparément)
- [ ] Plusieurs touches en même temps

**Fini quand** : impossible de traverser un mur ou de segfault en fonçant dans un coin.
EOF

issue "game : rotation flèches (rotate_player)" "$M3" "area:game,role:B" <<'EOF'
Fichier : `src/game/movement.c` (`rotate_player`)

- [ ] Matrice de rotation sur `dir` **et** `plane`
- [ ] Flèche gauche tourne vers la gauche (vérifier les signes)

**Fini quand** : rotation fluide dans le bon sens, le FOV ne se déforme pas après 50 tours.
EOF

issue "test : compléter maps/invalid et maps/valid" "$M3" "area:test,role:A" <<'EOF'
- [ ] Valides : map avec espaces à l'intérieur, map non rectangulaire, map 1 case, éléments dans le désordre avec plein de lignes vides, lignes vides en fin de fichier
- [ ] Invalides : `F` en double, `NO` sans chemin, `NO` avec 2 chemins, xpm cassé, caractère `2`, `.cub` vide de map mais avec espaces
- [ ] Chaque nouvelle map invalide est automatiquement testée par `run_tests.sh`

**Fini quand** : ≥ 30 maps invalides, ≥ 15 valides, tout est vert.
EOF

issue "infra : rendre le job Tests obligatoire" "$M3" "area:infra,role:A" <<'EOF'
Une fois le job **Tests** vert sur `dev` :

- [ ] Settings → Branches → `main` et `dev` → *Require status checks* → cocher « Tests (parsing + valid maps + leaks) »
- [ ] Mettre à jour le tableau CI de `TEAM_WORK.md` §6

**Fini quand** : une PR avec un test rouge ne peut plus être mergée.
EOF

# =============================== S4 ========================================
issue "test : chasse aux leaks (toutes les maps + fermeture)" "$M4" "area:test,role:both" <<'EOF'
- [ ] `./tests/run_tests.sh --leaks` vert
- [ ] Chaque map valide : ouvrir, bouger, ESC → valgrind propre
- [ ] Idem avec la croix rouge
- [ ] Erreur de chargement d'une texture **après** `mlx_init` → pas de leak

**Fini quand** : 0 leak sur tous les chemins, testé sur une machine de l'école.
EOF

issue "test : crash tests (fichiers tordus)" "$M4" "area:test,role:A" <<'EOF'
Essayer de casser le programme comme un correcteur :

- [ ] `/dev/null`, `/dev/random` renommé en `.cub`, un binaire renommé en `.cub`
- [ ] Fichier sans droits de lecture (`chmod 000`)
- [ ] Map de 500×500
- [ ] Ligne de 10 000 caractères
- [ ] Texture qui est un dossier, texture vide, xpm de taille différente
- [ ] `F 255,255,255,` / `F ,255,255` / `F 0255,0,0` (décider ce qu'on accepte et l'écrire dans ARCHITECTURE.md)

**Fini quand** : aucun crash, aucun leak, chaque cas ajouté dans `maps/invalid/` si pertinent.
EOF

issue "render : fluidité de la fenêtre + perf" "$M4" "area:render,role:B" <<'EOF'
Le sujet : « The management of your window must remain smooth ».

- [ ] Minimiser / restaurer, passer une autre fenêtre devant, déplacer → l'image revient
- [ ] Grande map : pas de lag visible
- [ ] Le nez collé contre un mur : pas de ralentissement (`line_height` énorme → bien borner la boucle de dessin)

**Fini quand** : testé sur Mac et sur une machine Linux de l'école.
EOF

issue "docs : README final" "$M4" "area:docs,role:both" <<'EOF'
Exigences du sujet, chapitre VI.

- [ ] 1re ligne en italique avec **les deux logins**
- [ ] Description, Instructions, Resources
- [ ] Section *AI usage* honnête et précise
- [ ] Captures d'écran (optionnel mais apprécié)

**Fini quand** : relu par les deux.
EOF

issue "Défense : éval blanche croisée + CHECKLIST" "$M4" "area:docs,role:both" <<'EOF'
- [ ] Dérouler `docs/CHECKLIST.md` ensemble, tout cocher
- [ ] A explique le raycasting à B, B explique le parsing à A (sans regarder le code)
- [ ] Chacun fait une « petite modif en direct » choisie par l'autre (vitesse, FOV, nouvelle touche, nouvelle erreur)

**Fini quand** : checklist 100 % cochée.
EOF

issue "Release mandatory : test école + merge dev → main" "$M4" "area:infra,role:both" <<'EOF'
- [ ] `git clone` frais sur une machine de l'école → `make` → tester 3 maps
- [ ] `norminette` sur la machine de l'école
- [ ] PR `dev` → `main`, CI verte, review des deux
- [ ] Tag `v1.0-mandatory`

**Fini quand** : `main` est rendable tel quel.
EOF

# =============================== S5 ========================================
issue "bonus : organisation des fichiers *_bonus" "$M5" "bonus,area:infra,role:both" <<'EOF'
Le sujet : les bonus vont dans des fichiers `_bonus.{c,h}`, évalués séparément.

- [ ] Décider : copie de `src/` en `src_bonus/` avec suffixe `_bonus`, ou seulement les fichiers qui changent
- [ ] Remplir `SRC_BONUS_FILES` dans le Makefile
- [ ] `make bonus` sans relink, norme OK

**Fini quand** : `./cub3D_bonus` tourne et le mandatory n'a pas bougé.
EOF

issue "bonus : collisions avec les murs" "$M5" "bonus,area:game,role:A" <<'EOF'
- [ ] Marge autour du joueur (rayon ~0.2 case) : la caméra ne rentre jamais dans un mur
- [ ] Glissement le long des murs en diagonale

**Fini quand** : on longe un mur sans être bloqué ni voir à travers.
EOF

issue "bonus : portes qui s'ouvrent et se ferment" "$M5" "bonus,area:parsing,area:render,role:A" <<'EOF'
- [ ] Nouveau caractère `D` dans la map (parsing bonus) + texture de porte (élément `DO` ?)
- [ ] Une touche (ex : `E`) ouvre / ferme la porte en face du joueur
- [ ] Le DDA traite une porte fermée comme un mur

**Fini quand** : porte fonctionnelle sur une map de démo dans `maps/bonus/`.
EOF

issue "bonus : minimap" "$M5" "bonus,area:render,role:B" <<'EOF'
- [ ] Carré en haut à gauche : murs, sol, joueur, direction
- [ ] Optionnel : rayons du FOV, touche `M` pour l'afficher / la masquer

**Fini quand** : la minimap suit le joueur sans ralentir le rendu.
EOF

issue "bonus : rotation à la souris" "$M5" "bonus,area:game,role:B" <<'EOF'
- [ ] Hook mouvement souris (`mlx_hook` event 6, MotionNotify)
- [ ] Rotation proportionnelle au déplacement horizontal, souris recentrée (`mlx_mouse_move`) / cachée
- [ ] Attention : prototypes `mlx_mouse_*` différents Mac / Linux → `src/platform/`

**Fini quand** : on vise à la souris de façon fluide, sur les deux OS.
EOF

issue "bonus : sprite animé" "$M5" "bonus,area:render,role:B" <<'EOF'
- [ ] Nouveau caractère dans la map pour placer un sprite
- [ ] Plusieurs frames xpm, changement de frame avec `gettimeofday`
- [ ] Z-buffer (distance de chaque colonne) pour cacher le sprite derrière les murs

**Fini quand** : sprite animé visible, correctement caché par les murs.
EOF

issue "Thème : intégration finale" "$M5" "theme,role:both" <<'EOF'
- [ ] Textures définitives dans `textures/` (xpm, même taille)
- [ ] Couleurs sol / plafond
- [ ] 1 ou 2 maps « signature » dans `maps/valid/`
- [ ] Capture d'écran dans le README

**Fini quand** : le jeu a une identité, et les maps de test fonctionnent toujours.
EOF

echo "Done."
