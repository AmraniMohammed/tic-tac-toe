# Tic Tac Toe with AI (Sprint 1)

A C++ console-based Tic Tac Toe game featuring:

- Two-player mode
- One-player mode against an AI (random moves now; Minimax to be added)
- Flexible board representation (3×3 for now; ready for N×N)
- Clean separation of concerns: `Board`, `GameManager`, `AIPlayer`, shared types

---

## 🏗️ Project Structure

```
TicTacToe/
├── include/
│   ├── AIPlayer.h           # AI logic interface
│   ├── Board.h              # Board representation & winner detection
│   ├── GameManager.h        # Game flow & user interaction
│   └── GameTypes.h          # Shared enums: Player, BoardValue, GameState, Winner, GameMode
│
├── src/
│   ├── AIPlayer.cpp         # AIPlayer implementation
│   ├── Board.cpp            # Board methods implementation
│   ├── GameManager.cpp      # GameManager implementation
│   ├── main.cpp             # Entry point
│   └── CMakeLists.txt       # Per-folder build rules
│
└── CMakeLists.txt           # Top-level CMake configuration
```

---

## ⚙️ Build & Run

```bash
mkdir build && cd build
cmake ..
cmake --build .
.\src\TicTacToe.exe      # On Windows
```

**Requirements:**

- C++17 compiler
- CMake 3.15+

---

## 📝 Usage

1. **Choose mode**

   - Type `2` for Two-Players
   - Type `1` for One-Player vs AI

2. **Select starting symbol** (X or O)
3. **Play**

   - Enter a cell number (0–8) to make your move
   - AI plays immediately after you in One-Player mode

4. **Game ends** when someone wins or board is full

---

## 🚀 Sprint 1 Goals

- **Implement Minimax AI**

  - Unbeatable AI (hard mode)
  - Alpha-Beta pruning optimization
  - Configurable difficulty (Random vs Minimax)

- **Refactor**

  - Move AI logic entirely into `AIPlayer`
  - Keep `GameManager` only for turn sequencing & I/O

- **Write Unit Tests** for board evaluation and Minimax outcomes

---

## 🛠️ Next Steps

1. Start using `AIPlayer::miniMaxAlgo()` with core game.
2. Expose difficulty levels in `GameManager`.
3. Add unit tests (GoogleTest) for:

   - `Board::evaluateWinner` on various boards
   - `AIPlayer` produces optimal moves

---

_Thanks for checking out my Tic Tac Toe project!_
