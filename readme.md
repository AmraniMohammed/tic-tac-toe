# Tic Tac Toe with AI (Sprint 2)

A C++ Tic Tac Toe project with Qt/QML UI and AI player.
**Sprint 1 (console + AI basics)** is complete — work continues on **Sprint 2 (UI/UX improvements, wrapper, more tests, CI)**.

---

## Project overview

- Two-player (local) mode
- One-player vs AI (easy = random, hard = minimax)
- Qt/QML UI for interactive play
- Core game logic (`Board`, `AIPlayer`) separated from UI
- `GameManager` wrapper exposes Core to QML
- Console version snapshot maintained in branch `console`

---

## Repository layout

```
TicTacToe/
├── src/
│   ├── main.cpp
│   ├── resources.qrc
│   ├── Core/                     # Pure C++ game logic
│   │   ├── include/
│   │   │   ├── AIPlayer.h
│   │   │   ├── Board.h
│   │   │   └── GameTypes.h
│   │   ├── AIPlayer.cpp
│   │   └── Board.cpp
│   ├── Wrapper/                  # QObject wrapper for QML
│   │   ├── GameManager.h
│   │   ├── GameManager.cpp
│   │   └── GameTypesWrapper.h
│   └── UI/                       # QML interface
│       └── Main.qml
├── tests/
│   ├── test_main.cpp
│   └── CMakeLists.txt
└── CMakeLists.txt                # Top-level CMake
```

---

## Quick Build & Run (Qt6 QML UI)

1. Make sure Qt 6 is installed with your preferred compiler (MSVC or MinGW).
2. Open a terminal (cmd/PowerShell) or Developer Command Prompt for your compiler.
3. Create and enter a build folder:

```bash
mkdir build
cd build
```

4. Run CMake and provide the Qt6 path (adjust for your Qt version and compiler):

```bash
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.X.X/mingw_64/lib/cmake"
cmake --build .
```

If you use MSVC 2022, set CMAKE_PREFIX_PATH="C:/Qt/6.9.1/msvc2022_64_64/lib/cmake" instead.

5. Run the app:

```bash
./src/appTicTacToe.exe
```

**Requirements**

- C++17-compatible compiler
- CMake 3.31.5+
- Qt 6+ (with QML support)
- (Optional) GoogleTest for unit tests

---

## Running tests (GoogleTest + CTest)

Tests are configured under `tests/`:

```bash
cd build
cmake --build .
ctest --test-dir .
```

---

## ✅ Sprint 1 — Completed

- Console game with core components: `Board`, `GameManager`, `AIPlayer`
- Minimax implemented in `AIPlayer` (hard mode); random easy mode implemented
- `Board::evaluateWinner()` with row/column/diagonal checks and draw detection
- Basic unit test for `Board::evaluateWinner` (in `tests/`)

---

## ⏭️ Sprint 2 – Qt UI, Wrapper & Tests (1–2 weeks)

### Goals

- Add a Qt/QML GUI
- Create a `GameManager` QObject wrapper
- Increase test coverage & add CI
- Stabilize and document public interfaces

### Planned features

- GUI: tiles/buttons, click-to-play

- Highlight winning lines

- Restart button & simple menu

- Difficulty selector (easy / hard)

- Unit tests for:

  - All winner cases
  - AI immediate win/block scenarios
  - Integration tests

- CI: build and run tests on push

---

## Development & branching recommendation

- Keep `main` for active development (Sprint 2+)
- Use `console` branch as a stable snapshot with the playable console release

---

## Notes & TODOs

- Consider adding alpha–beta pruning to `AIPlayer::miniMaxAlgo` for performance
- Add more unit tests for `AIPlayer` (best-move correctness in common scenarios)
- Add CI (GitHub Actions/GitLab CI) to build and run tests automatically
