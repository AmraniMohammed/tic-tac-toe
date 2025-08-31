#pragma once

enum class GameState { PlayerXWin, PlayerOWin, Draw, Continue };
enum class Winner { X, O, Draw, None };
enum class Player {X, O, AIO, AIX}; // AIX = AI playing with symbol X, AIO = AI playing with symbol O
enum class GameMode { TwoPlayers, OnePlayer };
enum class BoardValue {Empty, X, O};