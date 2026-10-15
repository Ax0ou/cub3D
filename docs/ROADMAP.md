# Roadmap — qui fait quoi, dans quel ordre

> **Axel = parsing** (`src/parsing/`, `src/utils/`, maps de test) — **Davi = moteur** (`src/render/`, `src/game/`, `src/platform/`).
> Chaque issue porte un code : `AX-xx` (Axel), `DV-xx` (Davi), `DUO-xx` (ensemble). On les fait **dans l'ordre des numéros**.
> Pourquoi ce partage : choix d'Axel, qui reprend le parsing comme sur minishell ; Davi prend le moteur. Les deux doivent quand même savoir expliquer le raycasting à l'éval (DUO-02 + reviews croisées).

## Le principe : on ne s'attend jamais

1. **Le contrat est figé dès le jour 1** : `includes/cub3d.h` + les garanties de `t_scene` (`docs/ARCHITECTURE.md` §3). Tant que personne ne le change sans prévenir, chacun code contre le contrat, pas contre le code de l'autre.
2. **Tous les stubs compilent déjà** : appeler une fonction de l'autre qui n'est pas encore écrite ne casse rien (elle renvoie une valeur neutre).
3. **Davi n'attend pas le parsing** : jusqu'à `DUO-05`, il remplit `game.scene` à la main dans une fonction temporaire sur sa branche (jamais mergée sur `dev`).
4. **Axel n'attend pas le rendu** : le parsing se teste entièrement avec `./tests/run_tests.sh`, sans fenêtre.
5. **Un seul fichier partagé** : `src/utils/cleanup.c` (Axel : `free_*` / Davi : `destroy_game`). Axel merge `AX-03` tôt, Davi fait `DV-04` après.
6. **Tâche tampon** : si l'un est en avance ou bloqué, Axel → `AX-11` (maps de test), Davi → relire les PR d'Axel / préparer le thème.

## Planning

```
          AXEL (parsing)                         DAVI (moteur)
          ─────────────                          ─────────────
S1   ┌─ DUO-01 Kickoff ─ DUO-02 Tuto raycasting ─ DUO-03 Board + 1re PR ─ DUO-04 Thème ─┐
     │  AX-01 erreurs + strings                  DV-01 fenêtre + put_pixel             │
     │  AX-02 extension + lecture fichier        DV-02 hooks clavier / croix           │
     │  AX-03 free_* (cleanup.c) ──┐             DV-03 ciel / sol (scène en dur)       │
     │                             └────────────▶DV-04 destroy_game (cleanup.c)        │
S2   │  AX-04 identifiants / éléments            DV-05 init_player (spawn en dur)      │
     │  AX-05 couleurs                           DV-06 DDA (map en dur)                │
     │  AX-06 textures                           DV-07 hauteur des murs, couleurs      │
     │  AX-07 parse_map                                                                │
     │  AX-08 caractères + joueur                                                      │
     │  AX-09 parse_scene ──────────┐                                                  │
     │  AX-10 map fermée            │                                                  │
     └──────────────────────────────┴─▶ DUO-05 INTÉGRATION (synchro n°1) ◀─────────────┘
S3      AX-11 maps de test                       DV-08 chargement textures
        AX-12 job Tests obligatoire              DV-09 murs texturés
                                                 DV-10 WASD
                                                 DV-11 rotation
S4      AX-13 crash tests                        DV-12 fluidité fenêtre
        ─────── DUO-06 leaks ─ DUO-07 README ─ DUO-08 éval blanche (synchro n°2) ───────
        ─────────────── DUO-09 RELEASE mandatory → main (synchro n°3) ──────────────────
S5      ─────────────── DUO-10 organisation bonus ──────────────────────────────────────
        AX-14 collisions                         DV-13 minimap
        AX-15 portes (avec Davi pour le DDA)     DV-14 souris
                                                 DV-15 sprite animé
        ─────────────── DUO-11 thème final → rendu ─────────────────────────────────────
```

## Tableau détaillé

| Code | Issue | Qui | A besoin de | Débloque |
|---|---|---|---|---|
| DUO-01 | #1 Kickoff | duo | — | tout |
| DUO-02 | #4 Tuto raycasting | duo | #1 | #19 |
| DUO-03 | #2 Board + 1re PR | duo | #1 | — |
| DUO-04 | #3 Thème (brouillon) | duo | #1 | #41 |
| AX-01 | #5 erreurs + strings | Axel | #1 | #7, #11 |
| AX-02 | #7 extension + lecture | Axel | #5 | #11 |
| AX-03 | #6 free_* | Axel | — | #10 |
| AX-04 | #11 éléments | Axel | #7 | #12, #13 |
| AX-05 | #13 couleurs | Axel | #11 | #17 |
| AX-06 | #12 textures | Axel | #11 | #17 |
| AX-07 | #14 parse_map | Axel | #11 | #15, #16 |
| AX-08 | #15 caractères + joueur | Axel | #14 | #17 |
| AX-09 | #17 parse_scene | Axel | #12, #13, #15 | **#22** |
| AX-10 | #16 map fermée | Axel | #17 | — |
| AX-11 | #27 maps de test | Axel | — | #28 |
| AX-12 | #28 Tests obligatoire | Axel | #22 | — |
| AX-13 | #30 crash tests | Axel | #16 | #33 |
| AX-14 | #36 collisions | Axel | #25, #35 | — |
| AX-15 | #37 portes | Axel | #19, #35 | — |
| DV-01 | #8 fenêtre + put_pixel | Davi | #1 | #9, #18 |
| DV-02 | #9 hooks | Davi | #8 | #25, #26 |
| DV-03 | #18 ciel / sol | Davi | #8 | #20 |
| DV-04 | #10 destroy_game | Davi | #6 | #29 |
| DV-05 | #21 init_player | Davi | #8 | #19 |
| DV-06 | #19 DDA | Davi | #4, #21 | #20 |
| DV-07 | #20 hauteur murs | Davi | #19, #18 | **#22** |
| DV-08 | #23 load_textures | Davi | #8 | #24 |
| DV-09 | #24 murs texturés | Davi | #20, #23 | #29, #41 |
| DV-10 | #25 WASD | Davi | #9, #21 | #26, #36 |
| DV-11 | #26 rotation | Davi | #25 | #29 |
| DV-12 | #31 fluidité | Davi | #24 | #33 |
| DV-13 | #38 minimap | Davi | #35 | — |
| DV-14 | #39 souris | Davi | #35 | — |
| DV-15 | #40 sprite | Davi | #35, #24 | — |
| DUO-05 | #22 Intégration | duo | #17, #20, #21 | S3 |
| DUO-06 | #29 leaks | duo | #10, #24, #26 | #33 |
| DUO-07 | #32 README | duo | — | #34 |
| DUO-08 | #33 éval blanche | duo | #29, #30, #31 | #34 |
| DUO-09 | #34 release | duo | #32, #33 | bonus |
| DUO-10 | #35 organisation bonus | duo | #34 | #36 → #40 |
| DUO-11 | #41 thème final | duo | #3, #24 | rendu |

## Reviews

- Les PR d'Axel sont relues par Davi, et inversement → c'est comme ça que chacun apprend la moitié qu'il n'a pas codée (indispensable pour l'éval).
- Priorité : **relire une PR passe avant de commencer l'issue suivante**. Une PR qui attend bloque l'autre.
