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
public:
    explicit GameManager(Board* b = nullptr, QObject *parent = nullptr);

    Player current_player = Player::X;
    Player first_player = Player::X;
    Player second_player = Player::O;
    GameMode game_mode = GameMode::TwoPlayers;
    // GameState state = GameState::Continue;
    bool is_easy_mode = false;
    int depth = 10;
    int board_size = 3;

    QVariantList board_table() const;
    void setBoardTable(QVariantList bt);

    void setGameMode(bool is_two_player);
    void setPlayersSymbols(Player first, Player second);
    void setDifficultyMode (bool is_easy);

    void makeMove(QVariantList position_2d);


    /**
         * @brief Set up params
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
         * @brief Runs the main game loop.
    */
    Q_INVOKABLE void update(int position_1d);

    Q_INVOKABLE void reset();

    Q_INVOKABLE void setBoardSize(int new_board_size = 3) noexcept;

    Q_INVOKABLE void setDepth(int new_depth);

    Q_INVOKABLE void setFirstSecondPlayer(bool is_x);

    Q_INVOKABLE void logCurrentPlayer() const;

    Q_INVOKABLE int getBoardSize() const;

    Q_INVOKABLE QVariantList get2DPos(int pos1D) const;

    Q_INVOKABLE QString getCellValue(int position_1d) const;

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
    void boardChanged();
    void gameOver(QString message);

private:
    Board* board = nullptr;
    QVariantList m_board_table;
};

#endif // GAMEMANAGER_H
