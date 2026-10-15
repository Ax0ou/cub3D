*This project has been created as part of the 42 curriculum by aalvarad, dbomfim-.*

# cub3D

> **TODO (week 4):** check the logins above, fill the theme / features / screenshots,
> and complete the "AI usage" section. The first line MUST stay in italics (subject, chapter VI).

## Description

cub3D is a small ray-casting engine written in C with the MiniLibX, inspired by
*Wolfenstein 3D* (id Software, 1992). It reads a scene description file (`.cub`)
and renders a first-person 3D view of a maze in which the player can walk and look around.

- Textured walls, with a different texture for each face (North, South, East, West)
- Configurable floor and ceiling colors
- Smooth movement (`W` `A` `S` `D`) and rotation (`←` `→`)
- Strict validation of the scene file: any error prints `Error` followed by an explicit message

<!-- TODO (week 5): theme, bonus features, screenshot -->

## Instructions

### Requirements

| OS | Needed |
|----|--------|
| Linux (42 machines) | `cc`, `make`, `libx11-dev`, `libxext-dev`, `libbsd-dev` |
| macOS | Xcode command line tools (`xcode-select --install`) |

The MiniLibX sources for both systems are included (`mlx_linux/`, `mlx_macos/`);
the Makefile picks the right one automatically.

### Build & run

```bash
make            # builds ./cub3D
make bonus      # builds ./cub3D_bonus
./cub3D maps/valid/subject.cub
```

### Controls

| Key | Action |
|-----|--------|
| `W` / `S` | move forward / backward |
| `A` / `D` | strafe left / right |
| `←` / `→` | look left / right |
| `ESC` or red cross | quit |

### Scene file (`.cub`)

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

- `NO` `SO` `WE` `EA`: path to an `.xpm` texture for each wall face
- `F` / `C`: floor / ceiling color, `R,G,B` in `[0,255]`
- map: `1` wall, `0` floor, `N` `S` `E` `W` player spawn + orientation, spaces allowed;
  the map must be closed by walls and must be the last element of the file

### Tests

```bash
make test                          # parsing tests (invalid maps, arguments)
./tests/run_tests.sh --valid       # + every valid map opens without crashing
./tests/run_tests.sh --leaks       # + valgrind on every error path (Linux)
```

## Resources

- [Lode Vandevenne — Raycasting tutorial](https://lodev.org/cgtutor/raycasting.html) — the DDA algorithm used here
- [Permadi — Ray-Casting Tutorial For Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [MiniLibX documentation (42 Docs)](https://harm-smits.github.io/42docs/libs/minilibx)
- [Wolfenstein 3D — play online](http://users.atw.hu/wolf3d/)
- [KrolPolski/cube3d](https://github.com/KrolPolski/cube3d) — studied as a reference for project organisation

### AI usage

<!-- TODO (week 4): be honest and specific. Example below, adapt it. -->
- AI was used to set up the repository organisation (CI workflow, test script, issue list, documentation skeleton).
- AI was used to explain concepts (DDA, camera plane, texture mapping) that we then re-derived on paper.
- All the C code of the project was written, reviewed and tested by us; every line can be explained during the defense.
