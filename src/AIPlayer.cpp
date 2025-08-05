#include <AIPlayer.h>
#include <Board.h>

AIPlayer::AIPlayer(Board& b) : board(b){ };

int AIPlayer::miniMaxAlgo(const std::vector<std::vector<BoardValue>>& board_table, int depth, Player current_player, Player human_player, Player ai_player) {
    if(isTerminal(board_table) || depth == 0) {
        return getUtility(board_table, ai_player);
    }
    if(current_player == ai_player) {
        int max_eval = -2; //utility values are -1, 0, 1
        for(std::vector<int> action: getActions(board_table)){
            int eval = miniMaxAlgo(getResult(board_table, action, current_player), depth - 1, human_player, human_player, ai_player);
            max_eval = std::max(max_eval, eval);
        }
        return max_eval;
    }
    else {
        int min_eval = 2; //utility values are -1, 0, 1
        for(std::vector<int> action: getActions(board_table)){
            int eval = miniMaxAlgo(getResult(board_table, action, current_player), depth - 1, ai_player, human_player, ai_player);
            min_eval = std::min(min_eval, eval);
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