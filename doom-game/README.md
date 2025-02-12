# Doom Game

## Overview
Doom Game is a simple implementation of a classic first-person shooter. This project serves as an educational example of game development using C programming language. The game is structured to provide a clear separation of concerns, with distinct modules for game logic, player management, and utility functions.

## Project Structure
The project is organized as follows:

```
doom-game
├── src
│   ├── main.c        # Entry point of the game
│   ├── game.c        # Game logic implementation
│   ├── player.c      # Player functionalities
│   └── utils.c       # Utility functions
├── inc
│   ├── game.h        # Header for game logic
│   ├── player.h      # Header for player management
│   └── utils.h       # Header for utility functions
├── Makefile          # Build instructions
└── README.md         # Project documentation
```

## Requirements
- The game is developed to run on Ubuntu 20.04 LTS.
- The project is compiled using `gcc` with the following flags:
  - `-Wall`
  - `-Werror`
  - `-Wextra`
  - `-std=gnu89`
  - `-pedantic`

## Setup Instructions
1. Clone the repository:
   ```
   git clone https://github.com/yourusername/doom-game.git
   ```
2. Navigate to the project directory:
   ```
   cd doom-game
   ```
3. Build the project using the Makefile:
   ```
   make
   ```

## Gameplay
- The player navigates through a simple environment, avoiding obstacles and interacting with various elements.
- The game features basic movement controls and health management.

## Contribution
Feel free to contribute to the project by submitting issues or pull requests. Ensure that your code adheres to the coding standards and guidelines outlined in the project specifications.

## License
This project is licensed under the MIT License - see the LICENSE file for details.