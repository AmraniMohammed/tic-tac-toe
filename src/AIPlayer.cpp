#include <AIPlayer.h>
#include <Board.h>
#include <iostream>

AIPlayer::AIPlayer(Board& b) : board(b){ };

int AIPlayer::miniMaxAlgo(const std::vector<std::vector<BoardValue>>& board_table, int depth, Player current_player, Player human_player, Player ai_player) {
    if(isTerminal(board_table) || depth == 0) {
        auto winner = board.evaluateWinner(board_table);
        std::cout << "Terminal: winner=" << (winner == Winner::X ? "X"
             : winner == Winner::O ? "O"
             : winner == Winner::Draw ? "Draw"
             : "None")
          << " utility=" << getUtility(board_table, ai_player)
          << " depth=" << depth << "\n";
        return getUtility(board_table, ai_player);
    }
    Player opponent = (current_player == ai_player)
                    ? human_player
                    : ai_player;
    if(current_player == ai_player) {
        int max_eval = -2; //utility values are -1, 0, 1
        for(std::vector<int> action: getActions(board_table)){
            int eval = miniMaxAlgo(getResult(board_table, action, current_player), depth - 1, opponent, human_player, ai_player);
            max_eval = std::max(max_eval, eval);
            if(max_eval == 1) break;
        }
        return max_eval;
    }
    else {
        int min_eval = 2; //utility values are -1, 0, 1
        for(std::vector<int> action: getActions(board_table)){
            int eval = miniMaxAlgo(getResult(board_table, action, current_player), depth - 1, opponent, human_player, ai_player);
            min_eval = std::min(min_eval, eval);
            if(min_eval == -1) break;
        }
        return min_eval;
    }
    return 0;
}


bool AIPlayer::isTerminal(const std::vector<std::vector<BoardValue>>& board_table) {
    return (board.evaluateWinner(board_table) != Winner::None);
}

int AIPlayer::getUtility(const std::vector<std::vector<BoardValue>>& board_table, Player ai_player) {
    Winner winner =  board.evaluateWinner(board_table);
    if((winner == Winner::X && ai_player == Player::AIX )|| (winner == Winner::O && ai_player == Player::AIO)) return 1;
    else if(winner == Winner::Draw) return 0;
    return -1;
}


std::vector<std::vector<int>> AIPlayer::getActions(const std::vector<std::vector<BoardValue>>& board_table) {
    std::vector<std::vector<int>> result;
    for(int i = 0; i < board_table.size(); i++) {
        for(int j = 0; j < board_table.size(); j++) {
            if(board.isEmptyAt(i, j, board_table)) result.push_back({i, j});
        }
    }
    return result;
}


std::vector<std::vector<BoardValue>> AIPlayer::getResult(const std::vector<std::vector<BoardValue>>& board_table, std::vector<int>& action, Player player) {
    auto next_board = board_table; 
    next_board[action[0]][action[1]] = (player == Player::X || player == Player::AIX ? BoardValue::X : BoardValue::O);
    return next_board;
}


std::vector<int> AIPlayer::getBestMove(const std::vector<std::vector<BoardValue>>& board_table, Player current_player, Player human_player, Player ai_player, int depth) {
    int best_score = -2;
    std::vector<int> best_action;

    for(auto action: getActions(board_table)) {
        auto new_board = getResult(board_table, action, ai_player);

        Player next_player = (ai_player == Player::AIX || ai_player == Player::AIO)
                     ? human_player
                     : ai_player;

        int score = miniMaxAlgo(new_board, depth - 1, next_player, human_player, ai_player);

        if(score > best_score) {
            best_score = score;
            best_action = action;
        }
    }
    return best_action;
}