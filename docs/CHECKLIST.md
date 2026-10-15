# Checklist avant rendu

> À dérouler ensemble en S4 (éval blanche) puis juste avant de cliquer « rendu ». Tout doit être coché.

## Repo & Makefile

- [ ] `git clone` dans un dossier vide sur une machine de l'école → `make` compile
- [ ] Règles `$(NAME) all clean fclean re bonus` présentes, `cc -Wall -Wextra -Werror`
- [ ] 2e `make` → « Nothing to be done » (pas de relink), idem `make bonus`
- [ ] `make fclean` supprime binaire + objets + `libft.a`
- [ ] Pas de binaire, `.o`, `.a`, `.DS_Store` commités
- [ ] Bonus dans des fichiers `*_bonus.c` / `*_bonus.h`

## Norme

- [ ] `norminette src includes libft` → 0 erreur (bonus compris)
- [ ] Header 42 avec un vrai login sur chaque fichier

## Fonctions autorisées

- [ ] `nm -u cub3D` : uniquement open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday, math, mlx / X11 / OpenGL

## Arguments & erreurs

- [ ] Pas d'argument, 2 arguments → `Error`
- [ ] Fichier inexistant, sans droits, dossier nommé `x.cub`, extension `.cubx`, `.cub.txt`, `.cub` seul → `Error`
- [ ] Toutes les maps de `maps/invalid/` → `Error\n` + message explicite, code de sortie ≠ 0
- [ ] Aucun crash, aucune fuite sur **tous** ces cas (valgrind)

## Fichier .cub

- [ ] Éléments dans n'importe quel ordre, séparés par plusieurs lignes vides
- [ ] Plusieurs espaces entre identifiant et valeur
- [ ] Élément manquant / en double / inconnu → `Error`
- [ ] Couleur : 3 composantes, chiffres uniquement, [0,255], sinon `Error`
- [ ] Texture inexistante ou xpm invalide → `Error` (sans leak MLX)
- [ ] Map : en dernier, caractères `01NSEW` + espaces, un seul joueur, fermée
- [ ] Map avec des espaces à l'intérieur, lignes de longueurs différentes → OK si fermée
- [ ] Ligne vide au milieu de la map → `Error`

## Rendu

- [ ] 4 textures différentes selon la face (N/S/E/W), pas inversées en miroir
- [ ] Sol et plafond de couleurs différentes, celles du fichier
- [ ] Pas d'effet fish-eye
- [ ] Spawn N, S, E, W : on regarde dans la bonne direction
- [ ] Coller le nez à un mur : pas de crash, pas de ralentissement énorme

## Contrôles & fenêtre

- [ ] `W A S D` déplacent, `← →` tournent, dans le bon sens
- [ ] Plusieurs touches en même temps
- [ ] Impossible de sortir de la map (pas de segfault)
- [ ] `ESC` et croix rouge → fermeture propre, 0 leak
- [ ] Minimiser / masquer / déplacer la fenêtre → l'image revient correctement

## README

- [ ] 1re ligne en italique : *This project has been created as part of the 42 curriculum by login1, login2.*
- [ ] Sections Description, Instructions, Resources (+ usage de l'IA), en anglais

## Défense (chacun doit savoir répondre)

- [ ] Expliquer le DDA sur un schéma papier
- [ ] Pourquoi la distance perpendiculaire (fish-eye) ?
- [ ] Rôle de `dir` et `plane`, comment change le FOV
- [ ] Comment on choisit la colonne de texture (`wall_x`) et la ligne (`step`)
- [ ] Comment on vérifie qu'une map est fermée
- [ ] Pourquoi dessiner dans une image et pas `mlx_pixel_put`
- [ ] Être capable de faire une petite modif en direct (changer la vitesse, le FOV, une couleur, ajouter une touche)
