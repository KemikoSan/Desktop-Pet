# Desktop-Pet

Desktop companion with random behaviour.

### Features:
- Idle
- Sleeping
- Walking in random direction

### Setup:
To setup pet you need to include flipbook files in assets directory:
- idle_x_y.png
- sleep_x_y.png
- walk_x_y.png

where `x` is number of animation frames and `y` is number of frames per second.

privided files must be in png format with 400x400 pixels per animation frame

### Keyboard bindings:
| Key      | Action  |
| -------- | ------- |
| ESC | Close application    |
| F11 | Toggle window border |

### Dependencies:
- SDL3
- SDL3_image
### Compiling:
If compiling for Linux SDL Wayland support must be turned off, otherwise pet can't walk.
