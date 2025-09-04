#include "GameManager.h"
#include<QDebug>
#include "AIPlayer.h"
#include <limits>
#include <random>

GameManager::GameManager(Board* b, QObject *parent)
    : QObject{parent}, board(b)
{
    if (board) {
        m_board_table = toVariantBoard(board->getBoard());
        emit boardChanged();
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

void GameManager::setGameMode(GameMode gm)
{
    game_mode = gm;
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

bool GameManager::checkPlayerMove(QVariantList position)
{
    if(board->isEmptyAt(position[0].toInt(), position[1].toInt(), board->getBoard())) {
        return true;
    }
    return false;
}

QVariantList GameManager::getAiMove(int depth)
{
    QVariantList result;

    if(is_easy_mode) {
        QVariantList available_positions;

        available_positions = toVariantList2D(board->getAvailablePositions());

        // Define range
        int min = 0;
        int max = available_positions.size() - 1;

        // Initialize a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(min, max);

        // Generate random number in the range [min, max]
        int randomValue = distrib(gen);
        result = available_positions[randomValue].toList();
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
    QVariantList position_2d = toVariantList(board->get2DPos(position_1d));
    // Game loop
    if(board->getState() == GameState::Continue){
        if(game_mode == GameMode::OnePlayer && (current_player == Player::AIX || current_player == Player::AIO)) {
            position_2d = getAiMove();
        }
        else {
            if(!checkPlayerMove(position_2d)) return;
        }

        // Game logic
        board->makeMove(toVectorInt(position_2d), current_player);
        board->setState(board->evaluateState(current_player, board->getBoard()));

        // Update UI
        setBoardTable(toVariantBoard(board->getBoard()));
    }
    if(board->getState() == GameState::Continue){
        advanceTurn();
    }
    else {
        //Show result
        qWarning() << "Game Over !!!!";
    }

    //showResult();
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

    for (const auto& inner : vec2d) {
        QVariantList inner_list;

        for (int v : inner) {
            inner_list.append(v);
        }
        outer_list.append(inner_list);
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
