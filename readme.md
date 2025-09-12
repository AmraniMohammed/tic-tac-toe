# Tic Tac Toe with AI (Sprint 3 – Planning)

A C++ Tic Tac Toe project with Qt/QML UI and AI player.
**Sprint 2 (UI/UX, GameManager wrapper, CI, unit tests)** is complete — work continues in **Sprint 3 (enhancements & optional features)**.

---

## Project overview

- Two-player (local) mode
- One-player vs AI (easy = random, hard = minimax)
- Qt/QML UI for interactive play
- Core game logic (`Board`, `AIPlayer`) separated from UI
- `GameManager` wrapper exposes Core to QML
- Console version snapshot maintained in branch `console`
- CI/CD pipeline automatically builds, tests, and packages the app

---

## Repository layout

```
TicTacToe/
├── src/
│   ├── main.cpp
│   ├── resources.qrc
│   ├── Core/
│   │   ├── include/
│   │   │   ├── AIPlayer.h
│   │   │   ├── Board.h
│   │   │   └── GameTypes.h
│   │   ├── AIPlayer.cpp
│   │   └── Board.cpp
│   ├── Wrapper/
│   │   ├── GameManager.h
│   │   ├── GameManager.cpp
│   │   └── GameTypesWrapper.h
│   └── UI/
│       └── Main.qml
│       └── Startup.qml
│       └── Game.qml
├── tests/
│   ├── test_main.cpp
│   └── CMakeLists.txt
└── CMakeLists.txt
```

---

## Quick Build & Run (Qt6 QML UI)

1. Ensure Qt 6 is installed with your preferred compiler (MSVC or MinGW).
2. Open terminal or Developer Command Prompt.
3. Create and enter a build folder:

```bash
mkdir build
cd build
```

4. Run CMake and provide the Qt6 path:

```bash
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.X.X/mingw_64/lib/cmake"
cmake --build .
```

5. Run the app:

```bash
./src/appTicTacToe.exe
```

**Requirements:** C++17 compiler, CMake 3.31+, Qt 6+, (Optional) GoogleTest.

---

## Running tests (GoogleTest + CTest)

```bash
cd build
cmake --build .
ctest --test-dir .
```

---

## ✅ Sprint 1 — Completed

- Console version: core components (`Board`, `GameManager`, `AIPlayer`)
- Minimax AI implemented (hard mode); random AI (easy mode)
- Winner evaluation with draw detection
- Basic unit test for `Board::evaluateWinner()`

---

## ✅ Sprint 2 — Completed

- Qt/QML GUI fully implemented
- `GameManager` QObject wrapper for QML
- Increased test coverage (all winner cases + AI scenarios)
- CI/CD: automatic build, test, and packaging
- Executable packaged as `.zip` artifact

**New features in Sprint 2:**

- GUI: interactive tiles/buttons, restart button, menu
- Difficulty selector (easy/hard)
- Highlight winning line (UI)
- Unit tests & integration tests
- CI/CD pipeline (GitHub Actions)

---

## ⏭️ Sprint 3 — Enhancements & Optional Features

**Goals / planned features:**

- Add screenshots/video demo to README
- Refine UI for end-of-game highlight and UX improvements
- Optional: Add alpha–beta pruning to `AIPlayer::miniMaxAlgo` for optimization
- Optional: visual polish, animations, or sounds

---

## Future TODOs / Nice-to-Have Features

- Networking support for two-player mode over LAN or Internet
- Score tracking or game replay system

---
