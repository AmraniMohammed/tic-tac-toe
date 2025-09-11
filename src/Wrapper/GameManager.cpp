#include "GameManager.h"
#include<QDebug>
#include "AIPlayer.h"
#include <QRandomGenerator>
#include <QVector>
#include <QTimer>

GameManager::GameManager(Board* b, QObject *parent)
    : QObject{parent}, board(b)
{
    if (board) {
        setBoardTable(toVariantBoard(board->getBoard()));
    }
}

QVariantList GameManager::board_table() const
{
    return m_board_table;
}

void GameManager::setBoardTable(QVariantList bt)
{
    if (m_board_table != bt) {
        m_board_table = bt;
        emit boardChanged();
    }
}

void GameManager::setGameMode(bool is_two_player)
{
    if(is_two_player) game_mode = GameMode::TwoPlayers;

    else game_mode = GameMode::OnePlayer;
}

void GameManager::setPlayersSymbols(Player first, Player second)
{
    first_player = first;
    second_player = second;
}

void GameManager::setDifficultyMode(bool is_easy)
{
    is_easy_mode = is_easy;
}

void GameManager::makeMove(QVariantList position_2d)
{
    // Game logic
    board->makeMove(toVectorInt(position_2d), current_player);
    board->setState(board->evaluateState(current_player, board->getBoard()));

    // Update UI
    setBoardTable(toVariantBoard(board->getBoard()));
}

void GameManager::setup(int new_board_size, int new_ai_depth_value, bool is_two_player, bool is_x, bool is_easy)
{
    if(new_board_size != board_size) setBoardSize(new_board_size);

    if(new_ai_depth_value != depth) setDepth(new_ai_depth_value);

    setGameMode(is_two_player);

    setFirstSecondPlayer(is_x);

    is_easy_mode = is_easy;
}

bool GameManager::checkPlayerMove(QVariantList position)
{
    return board->isEmptyAt(position[0].toInt(), position[1].toInt(), board->getBoard());
}

QVariantList GameManager::getAiMove(int depth)
{
    QVariantList result;

    if(is_easy_mode) {
        QVector<QVector<int>> available_positions = toQVector2D(board->getAvailablePositions());

        // Define range
        int min = 0;
        int max = available_positions.size() - 1;

        if (max >= 0) {
            // Generate random index in the range [min, max]
            int randomIndex = QRandomGenerator::global()->bounded(min, max + 1);

            int row = available_positions[randomIndex][0];
            int col = available_positions[randomIndex][1];

            result.append(row);
            result.append(col);
        }
    }
    else {
        AIPlayer ai_player(*board);

        result = toVariantList(ai_player.getBestMove(board->getBoard(), second_player, first_player, second_player, depth));
    }
    return result;
}

void GameManager::advanceTurn() noexcept
{
    if(game_mode == GameMode::OnePlayer) {
        switch(current_player) {
        case Player::X:
            current_player = Player::AIO;
            break;
        case Player::O:
            current_player = Player::AIX;
            break;
        case Player::AIX:
            current_player = Player::O;
            break;
        case Player::AIO:
            current_player = Player::X;
            break;
        }
    }
    else {
        current_player = (current_player == Player::X ? Player::O : Player::X);
    }
}

void GameManager::update(int position_1d)
{
    QVariantList position_2d;

    if(position_1d >= 0) {
        position_2d = toVariantList(board->get2DPos(position_1d));
    }

    // Game loop
    if(board->getState() == GameState::Continue){
        if(game_mode == GameMode::OnePlayer && (current_player == Player::AIX || current_player == Player::AIO)) {
            position_2d = getAiMove(depth);
        }
        else {
            if(!checkPlayerMove(position_2d)) return;
        }
        makeMove(position_2d);
    }
    if(board->getState() == GameState::Continue){
        advanceTurn();

        if(game_mode == GameMode::OnePlayer && (current_player == Player::AIX || current_player == Player::AIO)) {
            QTimer::singleShot(1000, [this]() {
                update(-1); // Ai compute his move in getAiMove line
            });
        }
    }
    else {
        QString result;

        if(board->getState() == GameState::Draw) {
            result = "Draw";
        } else if(board->getState() == GameState::PlayerXWin) {
            result = "Player X Won";
        }
        else if(board->getState() == GameState::PlayerOWin) {
            result = "Player O Won";
        }
        emit gameOver("Game Over: " + result);
    }

    //showResult();
}

void GameManager::reset()
{
    board->setState(GameState::Continue);
    board->reset();
    setBoardTable(toVariantBoard(board->getBoard()));
    current_player = first_player;
}

void GameManager::setBoardSize(int new_board_size) noexcept
{
    board->setBoardSize(new_board_size);
    board_size = new_board_size;
    setBoardTable(toVariantBoard(board->getBoard()));
}

void GameManager::setDepth(int new_depth)
{
    depth = new_depth;
}

void GameManager::setFirstSecondPlayer(bool is_x)
{
    if(is_x) {
        if(game_mode == GameMode::OnePlayer) {
            first_player = Player::X;
            second_player = Player::AIO;
            current_player = first_player;
        }
        else {
            first_player = Player::X;
            second_player = Player::O;
            current_player = first_player;
        }
    }
    else {
        if(game_mode == GameMode::OnePlayer) {
            first_player = Player::O;
            second_player = Player::AIX;
            current_player = first_player;
        }
        else {
            first_player = Player::O;
            second_player = Player::X;
            current_player = first_player;
        }
    }
}

void GameManager::logCurrentPlayer() const
{
    if(current_player == Player::X) {
        qWarning() << "Current player is X";
    }
    else if(current_player == Player::O) {
        qWarning() << "Current player is O";
    }
    else if(current_player == Player::AIO) {
        qWarning() << "Current player is AIO";
    }
    else if(current_player == Player::AIX) {
        qWarning() << "Current player is AIX";
    }
}

int GameManager::getBoardSize() const
{
    return board_size;
}

QVariantList GameManager::get2DPos(int pos1D) const
{
    QVariantList pos2D;

    for(int pos: board->get2DPos(pos1D))
        pos2D.append(pos);

    return pos2D;
}

QString GameManager::getCellValue(int position_1d) const
{
    std::vector<int> position_2d = board->get2DPos(position_1d);
    std::vector<std::vector<BoardValue>> board_tb = board->getBoard();
    BoardValue board_value = board_tb[position_2d.at(0)][position_2d.at(1)];

    if(board_value == BoardValue::X) return "X";
    else if(board_value == BoardValue::O) return "O";
    return "";
}

QVariantList GameManager::toVariantList(const std::vector<int> &vec)
{
    QVariantList list;

    for (int v : vec) {
        list.append(v);
    }
    return list;
}

QVariantList GameManager::toVariantList2D(const std::vector<std::vector<int> > &vec2d)
{
    QVariantList outer_list;

    qWarning() << "Vec2 size is " << vec2d.size();

    for (const auto& inner : vec2d) {
        QVariantList line;

        for (int v : inner) {
            line.append(v);
        }
        outer_list.append(line.toList());
    }

    return outer_list;
}

std::vector<int> GameManager::toVectorInt(const QVariantList &list)
{
    std::vector<int> result;

    for (const QVariant &v : list) {
        result.push_back(v.toInt());
    }
    return result;
}

QVariantList GameManager::toVariantBoard(std::vector<std::vector<BoardValue> > in_board)
{
    QVariantList outer_board;

    for (const auto& inner : in_board) {
        //QVariantList line;

        for (BoardValue v : inner) {
            QString value;
            switch(v) {
            case BoardValue::X:
                value = "X";
                break;
            case BoardValue::O:
                value = "O";
                break;
            default:
                value = "";
            }
            // line.append(value);
            outer_board.append(value);
        }
        //outer_board.append(line);
    }

    return outer_board;

}

QVector<QVector<int> > GameManager::toQVector2D(const std::vector<std::vector<int> > &vec2d)
{
    QVector<QVector<int>> result;

    for (const auto& inner : vec2d) {
        if (inner.size() != 2) {
            qWarning() << "Inner vector does not have 2 elements!";
            continue;
        }
        QVector<int> row;
        row.append(inner[0]);
        row.append(inner[1]);
        result.append(row);
    }

    return result;
}
