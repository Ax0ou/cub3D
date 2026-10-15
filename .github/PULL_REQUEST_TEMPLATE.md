## Ce que fait cette PR

<!-- 1 à 3 phrases. Exemple : "Parse les lignes F et C et refuse les couleurs invalides." -->

Closes #

## Comment tester

```bash
make re
./cub3D maps/valid/minimal.cub
./tests/run_tests.sh
```

## Checklist (cocher AVANT de demander une review)

- [ ] `make` compile sans warning, `make` une 2e fois → "Nothing to be done" (pas de relink)
- [ ] `make norm` → 0 erreur
- [ ] `./tests/run_tests.sh` → pas de régression (les tests qui passaient passent encore)
- [ ] Pas de leak sur ce que j'ai touché (valgrind sur Linux / `leaks` sur Mac)
- [ ] Seulement des fonctions autorisées (open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday, math, mlx_*, libft)
- [ ] J'ai mis à jour `docs/ARCHITECTURE.md` si j'ai changé une struct ou un prototype
- [ ] Je peux expliquer chaque ligne de cette PR à l'oral (règle IA du sujet)

## Pour le reviewer

<!-- Où regarder en priorité ? Un doute sur un choix ? -->
