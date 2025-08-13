# Tic Tac Toe with AI (Sprint 1 → Sprint 2)

A C++ Tic Tac Toe project with a console playable game and an AI player.
**Sprint 1 (console + AI basics)** is complete — work continues on **Sprint 2 (UI/UX improvements, more tests, CI)**.

---

## Project overview

- Two-player (local) mode
- One-player vs AI (easy = random, hard = minimax)
- Clean separation of concerns: `Board`, `GameManager`, `AIPlayer`, `GameTypes`
- Console playable snapshot kept in branch `console`; use `main` for Sprint 2 work

---

## Repository layout

```
TicTacToe/
├── include/
│   ├── AIPlayer.h
│   ├── Board.h
│   ├── GameManager.h
│   └── GameTypes.h
├── src/
│   ├── AIPlayer.cpp
│   ├── Board.cpp
│   ├── GameManager.cpp
│   ├── main.cpp
│   └── CMakeLists.txt
├── tests/
│   ├── test_main.cpp
│   └── CMakeLists.txt
└── CMakeLists.txt
```

---

## Quick build & run (console)

```bash
# from repo root
mkdir -p build
cd build
cmake ..
cmake --build .

# run the executable
./src/TicTacToe

# Windows (PowerShell or cmd)
.\src\TicTacToe.exe
```

**Requirements**

- C++17-compatible compiler
- CMake 3.31.5+
- (Optional) GoogleTest for unit tests

---

## Running tests (GoogleTest + CTest)

Tests are configured under `tests/`:

```bash
cd build
cmake --build .
ctest --test-dir .
```

## ✅ Sprint 1 — Completed

- Console game with core components: `Board`, `GameManager`, `AIPlayer`
- Minimax implemented in `AIPlayer` (hard mode); random easy mode implemented
- `Board::evaluateWinner()` with row/column/diagonal checks and draw detection
- Basic unit test for `Board::evaluateWinner` (in `tests/`)

---

## ⏭️ Sprint 2 – UI / Tests / CI (1–2 weeks)

### Goals

- Add a GUI (prototype)
- Increase test coverage & add CI (GitHub Actions)
- Stabilize and document public interfaces

### Planned features

- Replace console UI with GUI (tiles/buttons, click-to-play)
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

- Keep `main` for active development (Sprint 2+).
- Use `console` branch as a stable snapshot with the playable console release.

---

## Notes & TODOs

- Consider adding alpha–beta pruning to `AIPlayer::miniMaxAlgo` for performance.
- Add more unit tests for `AIPlayer` (best-move correctness in common scenarios).
- Add CI (GitHub Actions/GitLab CI) to build and run tests automatically.

---
