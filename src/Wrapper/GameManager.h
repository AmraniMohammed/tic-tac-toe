#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QVariantList>
#include "GameTypesWrapper.h"
#include "Board.h"

class GameManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList board_table READ board_table WRITE setBoardTable NOTIFY boardChanged)
    Q_PROPERTY(int game_state READ game_state WRITE setGameState NOTIFY gameStateChanged)
public:
    explicit GameManager(Board* b = nullptr, QObject *parent = nullptr);

    Player current_player = Player::X; // Tracks whose turn it currently is
    Player first_player = Player::X; // Player who starts the game
    Player second_player = Player::O; // The other player
    GameMode game_mode = GameMode::TwoPlayers; // Player vs Player or Player vs AI
    bool is_easy_mode = false; // AI difficulty (true = random moves, false = minimax)
    int depth = 10; // AI search depth for minimax
    int board_size = 3; // Current board size (NxN)

    // Flattened board state as a QVariantList
    QVariantList board_table() const;

    // The current game state (continue, win, draw)
    int game_state() const;

    // Updates the board state.
    void setBoardTable(QVariantList bt);

    // Updates the game state.
    void setGameState(int new_game_state);

    // Sets whether the mode is 2-player or 1-player (vs AI).
    void setGameMode(bool is_two_player);

    // Defines symbols for the first and second player.
    void setPlayersSymbols(Player first, Player second);

    // Enables or disables "easy mode" (random AI moves).
    void setDifficultyMode (bool is_easy);

    // Places a move on the board at the given [row, col].
    void makeMove(QVariantList position_2d);

    /**
         * @brief Configures the game parameters.
         * @param new_board_size Size of the board (N x N)
         * @param new_ai_depth_value Depth for AI minimax search
         * @param is_two_player True = Player vs Player, False = Player vs AI
         * @param is_x True if the first player should be 'X', False if 'O'
         * @param is_easy True = easy AI (random moves), False = minimax AI
    */
    Q_INVOKABLE void setup(int new_board_size, int new_ai_depth_value, bool is_two_player, bool is_x, bool is_easy);


    /**
         * @brief Validates the move from a human player.
         * @return true if the move is valid, false otherwise.
    */
    bool checkPlayerMove(QVariantList position);

    /**
         * @brief Gets the move for the AI player (random or minimax-based).
         * @return The AI's chosen position in [row, col] format.
    */
    QVariantList getAiMove(int depth = 10);

    /**
         * @brief Switches to the next player's turn.
    */
    void advanceTurn() noexcept;

    /**
         * @brief Main game loop entry point.
         * @param position_1d Cell index chosen (flattened board index).
         *
         * - If position_1d >= 0, converts to (row, col).
         * - If in AI mode, automatically calls getAiMove().
         * - Makes the move, updates board, checks win/draw, switches turns.
         * - If AI's turn, schedules next move with QTimer.
    */
    Q_INVOKABLE void update(int position_1d);

    // Resets the game to the initial state.
    Q_INVOKABLE void reset();

    // Updates the AI depth value.
    Q_INVOKABLE void setBoardSize(int new_board_size = 3) noexcept;

    // Configures first and second players depending on who starts.
    Q_INVOKABLE void setDepth(int new_depth);

    // Logs the current player (for debugging).
    Q_INVOKABLE void setFirstSecondPlayer(bool is_x);

    // Return The current board size.
    Q_INVOKABLE void logCurrentPlayer() const;

    // Converts a 1D position into [row, col].
    Q_INVOKABLE int getBoardSize() const;

    // Gets the cell value ("X", "O", "").
    Q_INVOKABLE QVariantList get2DPos(int pos1D) const;

    // Return String description of the current game mode.
    Q_INVOKABLE QString getGame_mode() const;

    // Return String representation of the current player.
    Q_INVOKABLE QString getCurrent_player() const;

    // Converts a std::vector<int> to a QVariantList of ints (usable in QML)
    QVariantList toVariantList(const std::vector<int>& vec);

    // Converts a std::vector<std::vector<int>> to a QVariantList of QVariantList of ints
    QVariantList toVariantList2D(const std::vector<std::vector<int>>& vec2d);

    // Converts a QVariantList (containing ints) into std::vector<int>
    std::vector<int> toVectorInt(const QVariantList &list);

    // Return flattens board (1D)
    QVariantList toVariantBoard(std::vector<std::vector<BoardValue>> in_board);

    // Return 2d Qvector of int
    QVector<QVector<int>> toQVector2D(const std::vector<std::vector<int>>& vec2d);

signals:
    void boardChanged(); // Emitted whenever the board UI should update
    void gameStateChanged(); // Emitted when the internal game state integer changes
    void gameOver(QString message); // Emitted at the end of a game with result message

private:
    // Pointer to the board instance
    Board* board = nullptr;
    QVariantList m_board_table;
    int m_game_state;
};

#endif // GAMEMANAGER_H
