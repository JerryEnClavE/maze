# Maze Project

## Overview
The Maze Project is a 3D game developed using raycasting techniques. The game allows players to navigate through a maze, interact with walls, and experience a dynamic environment. This project utilizes the SDL2 library for graphics and input handling.

## Project Structure
```
maze-project
├── src
│   ├── main.c          # Entry point of the application
│   ├── raycasting.c    # Raycasting logic and wall rendering
│   ├── rendering.c      # Rendering functions for walls, ground, and ceiling
│   ├── input.c         # User input handling
│   ├── map.c           # Map loading and parsing
│   └── utils.c         # Utility functions
├── inc
│   ├── raycasting.h     # Header for raycasting functions
│   ├── rendering.h      # Header for rendering functions
│   ├── input.h          # Header for input handling functions
│   ├── map.h            # Header for map management functions
│   └── utils.h          # Header for utility functions
├── assets
│   ├── textures
│   │   ├── wall_texture.png      # Texture for walls
│   │   ├── ground_texture.png     # Texture for ground
│   │   └── ceiling_texture.png    # Texture for ceiling
│   └── maps
│       └── map1.txt              # Map data file
├── Makefile                      # Build instructions
└── README.md                     # Project documentation
```

## Setup Instructions
1. **Install SDL2**: Ensure that SDL2 is installed on your system. You can follow the installation instructions provided in the SDL2 documentation.
2. **Clone the Repository**: Clone this repository to your local machine.
3. **Build the Project**: Navigate to the project directory and run `make` to compile the project.
4. **Run the Game**: After building, execute the generated binary to start the game.

## Features
- **Raycasting**: The game uses raycasting to render a 3D perspective of the maze.
- **User Input**: Players can move and rotate the camera using keyboard and mouse inputs.
- **Collision Detection**: The player cannot walk through walls, and can slide along them.
- **Map Loading**: Maps can be loaded from text files, allowing for easy modifications.
- **Texturing**: Walls, ground, and ceiling can be textured for a more immersive experience.

## Future Enhancements
- Implement additional features such as enemies, weapons, and environmental effects like rain.
- Improve the rendering engine to support more complex textures and lighting effects.

## License
This project is licensed under the MIT License - see the LICENSE file for details.