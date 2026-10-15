# Travailler à deux sur cub3D

> **Pour qui** : Axel + binôme. **À lire en entier (15 min) avant de toucher au code.**
> Le but : coder en parallèle sans jamais casser le code de l'autre, et arriver à l'éval en sachant expliquer **tout** le projet, pas seulement sa moitié.

---

## 1. Le concept en une ligne

```
1 ISSUE  =  1 BRANCHE  =  1 PULL REQUEST  =  1 REVIEW PAR L'AUTRE  =  1 MERGE
```

Rien n'arrive sur `dev` ou `main` sans être passé par une PR relue par l'autre et validée par la CI.

---

## 2. Qui fait quoi

Deux rôles, à choisir au kickoff. Chacun **possède** ses dossiers (c'est lui qui code dedans), mais **relit** tout ce que l'autre fait.

| | Personne A — **Parsing & robustesse** | Personne B — **Moteur & jeu** |
|---|---|---|
| Dossiers | `src/parsing/`, `src/utils/` | `src/render/`, `src/game/`, `src/platform/` |
| Livre | une `t_scene` remplie et **garantie valide** | une fenêtre qui affiche et réagit aux touches |
| Tests | `maps/invalid/*`, `tests/run_tests.sh` | `maps/valid/*`, test visuel, leaks à la fermeture |
| Bonus | collisions, portes (parsing du `D`) | minimap, souris, sprites animés |

**Le contrat entre les deux = `includes/cub3d.h`.** Tant que la `t_scene` respecte ce qui est écrit en commentaire au-dessus de la struct, A et B peuvent avancer sans s'attendre.

> [!IMPORTANT]
> À l'éval, chacun peut être interrogé sur **n'importe quelle** partie (le raycasting surtout). D'où la règle : on relit 100 % des PR de l'autre et on pose des questions jusqu'à comprendre. Une PR qu'on ne comprend pas, on ne l'approuve pas.

### Comment tester sans attendre l'autre

- **B n'attend pas le parsing** : en semaine 1-2, B écrit en dur une petite map dans une fonction de test locale (branche à lui, pas commitée sur `dev`) ou utilise une `t_scene` remplie à la main.
- **A n'attend pas le rendu** : le parsing se teste entièrement avec `tests/run_tests.sh` (pas besoin de fenêtre).

---

## 3. Les branches

```
main  ← version rendable, protégée (PR + 1 review + CI verte obligatoires)
 └── dev  ← intégration, on merge ici tous les jours
      ├── feat/parse-colors       (issue #12)
      ├── feat/raycast-dda        (issue #20)
      └── fix/leak-texture-path   (issue #41)
```

| Préfixe | Pour |
|---|---|
| `feat/` | nouvelle fonctionnalité |
| `fix/` | correction de bug |
| `test/` | ajout de maps ou de tests |
| `docs/` | documentation |
| `chore/` | Makefile, CI, ménage |

`dev` → `main` : uniquement à la fin de chaque semaine, quand la CI est verte et que le critère de la semaine (cf. `docs/PLAN.md`) est atteint.

---

## 4. Le cycle complet, commande par commande

```bash
# 1. Partir de dev à jour
git checkout dev
git pull

# 2. Créer sa branche (le numéro = l'issue)
git checkout -b feat/parse-colors

# 3. Coder, tester, committer souvent
make && make norm && ./tests/run_tests.sh
git add src/parsing/parse_color.c
git commit -m "feat(parsing): parse F and C colors (#12)"

# 4. Avant de pousser : récupérer ce que l'autre a mergé entre-temps
git fetch origin
git rebase origin/dev        # en cas de conflit : voir §7

# 5. Pousser et ouvrir la PR vers dev
git push -u origin feat/parse-colors
gh pr create --base dev --fill
```

Dans la description de la PR, écrire `Closes #12` → l'issue se ferme toute seule au merge.

### Messages de commit

```
<type>(<module>): <ce qui change, en anglais, à l'impératif> (#issue)

feat(parsing): reject colors outside [0,255] (#12)
fix(render): clamp draw_end to WIN_HEIGHT - 1 (#22)
test(maps): add map with hole next to a space (#15)
```

### Review

- Le reviewer a **24 h** max pour relire (sinon on bloque l'autre).
- On commente le code, pas la personne. On pose des questions plutôt que d'affirmer.
- Merge par **celui qui a ouvert la PR**, une fois approuvée et la CI verte → bouton *Squash and merge*.
- Après le merge : supprimer la branche (bouton GitHub) et `git checkout dev && git pull`.

---

## 5. La norme (non négociable)

Une seule erreur de norme = **0** au projet, bonus compris. La CI la vérifie à chaque push, mais vérifie **avant** de pousser :

```bash
make norm
```

| Règle | Piège classique sur cub3D |
|---|---|
| 25 lignes max par fonction | la boucle DDA et le dessin d'une colonne : découper tôt |
| 5 fonctions max par fichier | on a prévu des fichiers par thème, en créer d'autres plutôt que de tasser |
| 4 paramètres max, 5 variables max | passer `t_game *` ou `t_ray *` au lieu de 6 doubles |
| pas de `for`, `switch`, `do while`, ternaire | `while` + `if/else` |
| pas de variable globale | tout passe par `t_game` |
| pas de commentaire **dans** une fonction | commenter au-dessus, comme dans le squelette |
| header 42 sur chaque `.c` / `.h` | mettre son login dans le header des fichiers qu'on crée |

Ajouter un nouveau `.c` ? → l'ajouter dans `SRC_FILES` du `Makefile` (pas de wildcard).

### Fonctions autorisées

`open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday`, toute la lib math (`-lm`), toutes les fonctions MiniLibX, notre libft.
**Rien d'autre.** Pas de `memset` de la libc (→ `ft_memset`), pas de `strcmp`, pas de `fprintf`.

---

## 6. La CI (GitHub Actions)

À chaque push / PR, GitHub lance automatiquement (onglet **Actions**) :

| Job | Vérifie | Bloque le merge ? |
|---|---|---|
| Norminette | `src/ includes/ libft/` | ✅ oui |
| Build (Linux) | `make`, pas de relink, `make bonus`, `make re` | ✅ oui |
| Build (macOS) | `make` sur Mac | ✅ oui |
| Tests | toutes les maps invalides → `Error`, maps valides qui tournent, valgrind | ⚠️ rouge au début (le code n'est pas écrit), **obligatoire à partir de la fin de semaine 3** |

Une croix rouge sur ta PR ? Clique sur *Details* → lis le log → corrige → re-push sur la même branche. La PR se met à jour toute seule.

---

## 7. Conflits git

Ça arrive surtout sur `Makefile` et `includes/cub3d.h` (les deux fichiers partagés).

```bash
git rebase origin/dev
# git affiche CONFLICT dans un fichier → l'ouvrir, garder les DEUX lignes en général
# (ex : chacun a ajouté un fichier dans SRC_FILES)
git add Makefile
git rebase --continue
git push --force-with-lease     # seulement sur TA branche, jamais sur dev/main
```

**Règle d'or** : toute modification d'une struct ou d'un prototype dans `cub3d.h` = on se prévient **avant** (message), et on met à jour `docs/ARCHITECTURE.md` dans la même PR.

---

## 8. Le board et les issues

- Toutes les tâches sont déjà créées en issues, classées par **milestone** (= semaine) et par **label** (`area:parsing`, `area:render`, …).
- Board Kanban : onglet **Projects** du repo (à créer au kickoff, cf. §10).
- Je prends une issue → je me l'**assigne** (`gh issue edit 12 --add-assignee @me`) → je la passe *In Progress*.
- Bloqué plus de 2 h sur une issue ? On en parle, on ne reste pas seul.

---

## 9. Rituels

| Quand | Quoi | Durée |
|---|---|---|
| Chaque jour de code | message rapide : *hier / aujourd'hui / bloqué ?* | 2 min |
| Lundi | point semaine : où on en est vs `docs/PLAN.md`, on s'assigne les issues | 20 min |
| Vendredi | merge `dev` → `main` si le critère de la semaine est atteint | 15 min |
| Chaque fin de semaine | **chacun explique à l'autre** une partie qu'il n'a pas codée | 30 min |

---

## 10. Kickoff (première séance ensemble, ~2 h)

- [ ] Le binôme accepte l'invitation GitHub et clone le repo
- [ ] Lire ensemble le sujet (`docs/subject.pdf`) et ce fichier
- [ ] Choisir les rôles A / B
- [ ] Relire `includes/cub3d.h` ensemble : renommer ce qui n'est pas clair **maintenant**, après c'est trop tard
- [ ] Lire ensemble la partie 1 du tuto [lodev raycasting](https://lodev.org/cgtutor/raycasting.html) (le moteur repose dessus)
- [ ] **Discuter du thème** (cf. §11)
- [ ] Créer le board Projects : *Projects → New project → Board*, colonnes `Todo / In Progress / In Review / Done`, ajouter toutes les issues
- [ ] Chacun s'assigne ses issues de la semaine 1

---

## 11. Le thème (à décider ensemble)

Le sujet laisse libres les textures, les couleurs et les bonus. C'est **la** discussion à avoir au kickoff :

- Univers : donjon médiéval ? station spatiale ? backrooms ? l'école 42 elle-même ?
- 4 textures murales en `.xpm` (64×64 ou 128×128, même taille pour les 4 c'est plus simple) — conversion : `magick image.png -resize 64x64 textures/north.xpm`
- Couleurs sol / plafond qui vont avec
- Une ou deux maps « signature » dans `maps/valid/`
- Quels bonus (cf. `docs/PLAN.md` semaine 5) servent le thème ? (portes pour un donjon, sprite animé pour une ambiance…)

Les textures actuelles dans `textures/` sont des **placeholders** pour pouvoir coder tout de suite.

---

## 12. IA

Le sujet est clair (chapitre IV) : on peut utiliser l'IA pour **comprendre** et pour les tâches répétitives, mais **chaque ligne rendue doit être comprise et expliquée par nous deux**. Copier une fonction générée qu'on ne sait pas expliquer = échec à l'éval. On le décrit honnêtement dans la section *AI usage* du README.
