# Roadmap — qui fait quoi, dans quel ordre

> **Davi = parsing** (`src/parsing/`, `src/utils/`, maps de test) — **Axel = moteur** (`src/render/`, `src/game/`, `src/platform/`).
> Chaque issue porte un code : `DV-xx` (Davi), `AX-xx` (Axel), `DUO-xx` (ensemble). On les fait **dans l'ordre des numéros**.
> Pourquoi ce partage : sur minishell Axel faisait le parsing et Davi l'exécution → on inverse pour que chacun apprenne quelque chose de nouveau. Le moteur colle aussi au profil « visuel » d'Axel pour le thème.

## Le principe : on ne s'attend jamais

1. **Le contrat est figé dès le jour 1** : `includes/cub3d.h` + les garanties de `t_scene` (`docs/ARCHITECTURE.md` §3). Tant que personne ne le change sans prévenir, chacun code contre le contrat, pas contre le code de l'autre.
2. **Tous les stubs compilent déjà** : appeler une fonction de l'autre qui n'est pas encore écrite ne casse rien (elle renvoie une valeur neutre).
3. **Axel n'attend pas le parsing** : jusqu'à `DUO-05`, il remplit `game.scene` à la main dans une fonction temporaire sur sa branche (jamais mergée sur `dev`).
4. **Davi n'attend pas le rendu** : le parsing se teste entièrement avec `./tests/run_tests.sh`, sans fenêtre.
5. **Un seul fichier partagé** : `src/utils/cleanup.c` (Davi : `free_*` / Axel : `destroy_game`). Davi merge `DV-03` tôt, Axel fait `AX-04` après.
6. **Tâche tampon** : si l'un est en avance ou bloqué, Davi → `DV-11` (maps de test), Axel → relire les PR de Davi / préparer le thème.

## Planning

```
          DAVI (parsing)                         AXEL (moteur)
          ─────────────                          ─────────────
S1   ┌─ DUO-01 Kickoff ─ DUO-02 Tuto raycasting ─ DUO-03 Board + 1re PR ─ DUO-04 Thème ─┐
     │  DV-01 erreurs + strings                  AX-01 fenêtre + put_pixel             │
     │  DV-02 extension + lecture fichier        AX-02 hooks clavier / croix           │
     │  DV-03 free_* (cleanup.c) ───────────────▶AX-03 ciel / sol (scène en dur)       │
     │                                           AX-04 destroy_game (cleanup.c)        │
S2   │  DV-04 identifiants / éléments            AX-05 init_player (spawn en dur)      │
     │  DV-05 couleurs                           AX-06 DDA (map en dur)                │
     │  DV-06 textures                           AX-07 hauteur des murs, couleurs      │
     │  DV-07 parse_map                                                                │
     │  DV-08 caractères + joueur                                                      │
     │  DV-09 parse_scene ──────────┐                                                  │
     │  DV-10 map fermée            │                                                  │
     └──────────────────────────────┴─▶ DUO-05 INTÉGRATION (synchro n°1) ◀─────────────┘
S3      DV-11 maps de test                       AX-08 chargement textures
        DV-12 job Tests obligatoire              AX-09 murs texturés
                                                 AX-10 WASD
                                                 AX-11 rotation
S4      DV-13 crash tests                        AX-12 fluidité fenêtre
        ─────── DUO-06 leaks ─ DUO-07 README ─ DUO-08 éval blanche (synchro n°2) ───────
        ─────────────── DUO-09 RELEASE mandatory → main (synchro n°3) ──────────────────
S5      ─────────────── DUO-10 organisation bonus ──────────────────────────────────────
        DV-14 collisions                         AX-13 minimap
        DV-15 portes (avec Axel pour le DDA)     AX-14 souris
                                                 AX-15 sprite animé
        ─────────────── DUO-11 thème final → rendu ─────────────────────────────────────
```

## Tableau détaillé

| Code | Issue | Qui | A besoin de | Débloque |
|---|---|---|---|---|
| DUO-01 | #1 Kickoff | duo | — | tout |
| DUO-02 | #4 Tuto raycasting | duo | #1 | #19 |
| DUO-03 | #2 Board + 1re PR | duo | #1 | — |
| DUO-04 | #3 Thème (brouillon) | duo | #1 | #41 |
| DV-01 | #5 erreurs + strings | Davi | #1 | #7, #11 |
| DV-02 | #7 extension + lecture | Davi | #5 | #11 |
| DV-03 | #6 free_* | Davi | — | #10 |
| DV-04 | #11 éléments | Davi | #7 | #12, #13 |
| DV-05 | #13 couleurs | Davi | #11 | #17 |
| DV-06 | #12 textures | Davi | #11 | #17 |
| DV-07 | #14 parse_map | Davi | #11 | #15, #16 |
| DV-08 | #15 caractères + joueur | Davi | #14 | #17 |
| DV-09 | #17 parse_scene | Davi | #12, #13, #15 | **#22** |
| DV-10 | #16 map fermée | Davi | #17 | — |
| DV-11 | #27 maps de test | Davi | — | #28 |
| DV-12 | #28 Tests obligatoire | Davi | #22 | — |
| DV-13 | #30 crash tests | Davi | #16 | #33 |
| DV-14 | #36 collisions | Davi | #25, #35 | — |
| DV-15 | #37 portes | Davi | #19, #35 | — |
| AX-01 | #8 fenêtre + put_pixel | Axel | #1 | #9, #18 |
| AX-02 | #9 hooks | Axel | #8 | #25, #26 |
| AX-03 | #18 ciel / sol | Axel | #8 | #20 |
| AX-04 | #10 destroy_game | Axel | #6 | #29 |
| AX-05 | #21 init_player | Axel | #8 | #19 |
| AX-06 | #19 DDA | Axel | #4, #21 | #20 |
| AX-07 | #20 hauteur murs | Axel | #19, #18 | **#22** |
| AX-08 | #23 load_textures | Axel | #8 | #24 |
| AX-09 | #24 murs texturés | Axel | #20, #23 | #29, #41 |
| AX-10 | #25 WASD | Axel | #9, #21 | #26, #36 |
| AX-11 | #26 rotation | Axel | #25 | #29 |
| AX-12 | #31 fluidité | Axel | #24 | #33 |
| AX-13 | #38 minimap | Axel | #35 | — |
| AX-14 | #39 souris | Axel | #35 | — |
| AX-15 | #40 sprite | Axel | #35, #24 | — |
| DUO-05 | #22 Intégration | duo | #17, #20, #21 | S3 |
| DUO-06 | #29 leaks | duo | #10, #24, #26 | #33 |
| DUO-07 | #32 README | duo | — | #34 |
| DUO-08 | #33 éval blanche | duo | #29, #30, #31 | #34 |
| DUO-09 | #34 release | duo | #32, #33 | bonus |
| DUO-10 | #35 organisation bonus | duo | #34 | #36 → #40 |
| DUO-11 | #41 thème final | duo | #3, #24 | rendu |

## Reviews

- Les PR de Davi sont relues par Axel, et inversement → c'est comme ça que chacun apprend la moitié qu'il n'a pas codée (indispensable pour l'éval).
- Priorité : **relire une PR passe avant de commencer l'issue suivante**. Une PR qui attend bloque l'autre.
