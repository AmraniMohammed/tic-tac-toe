#include <Board.h>


Board::Board() : state(GameState::Continue), board_size(3), board(createBoard(3)) {}

const std::vector<std::vector<BoardValue> >& Board::getBoard() const noexcept
{
    return board;
}

GameState Board::getState() const noexcept {return state;};

int Board::getBoardSize() const noexcept {
    if(board_size < 3) return 3;
    return board_size;
};

void Board::setState(GameState new_state) noexcept {state = new_state;}

void Board::setBoardSize(int new_board_size) noexcept
{
    board_size = new_board_size;
    board = createBoard(board_size);
}

void Board::reset() noexcept
{
    board = createBoard(board_size);
}

std::vector<std::vector<BoardValue>> Board::createBoard(int dim)
{
    std::vector<std::vector<BoardValue>> new_board;
    for(int i = 0; i < dim; i++) {
        std::vector<BoardValue> line;
        for(int j = 0; j < dim; j++) {
            line.push_back(BoardValue::Empty);
        }
        new_board.push_back(line);
    }
    return new_board;
};

void Board::makeMove(std::vector<int> position_2d, Player player) {
    board[position_2d[0]][position_2d[1]] = getPlayerSymbol(player);
};

GameState Board::evaluateState(Player current_player, const std::vector<std::vector<BoardValue>>& board) {
    switch (evaluateWinner(board))
    {
        case Winner::X:
            return GameState::PlayerXWin;
            break;
        case Winner::O:
            return GameState::PlayerOWin;
            break;
        case Winner::Draw:
            return GameState::Draw;
            break;
        default:
            return GameState::Continue;
            break;
    }
};


Winner Board::evaluateWinner(const std::vector<std::vector<BoardValue>>& in_board) {
    int board_dim = in_board.size();
    // Row win case check
    for(auto row: in_board) {
        BoardValue check_value = row[0];
        int cnt = std::count_if(row.begin(), row.end(), [check_value](BoardValue val){return (check_value == val && val != BoardValue::Empty);});
        if(cnt == board_dim && check_value == BoardValue::X) return Winner::X;
        else if(cnt == board_dim && check_value == BoardValue::O) return Winner::O;
    }

    // Column win case check
    for(int i = 0; i < board_dim; i++) {
        BoardValue check_value = in_board[0][i];
        int cnt = 0;
        if(check_value == BoardValue::Empty) continue;
        for(int j = 0; j < board_dim; j++) {
            if(in_board[j][i] == check_value) cnt++;
        }
        if(cnt == board_dim && check_value == BoardValue::X) return Winner::X;
        else if(cnt == board_dim && check_value == BoardValue::O) return Winner::O;
    }

    // Diagonal win case check
    std::vector<BoardValue> diag_left;
    std::vector<BoardValue> diag_right;
    
    
    for(int i = 0; i < board_dim; i++) {
        diag_left.push_back(in_board[i][i]);
        diag_right.push_back(in_board[i][board_dim - 1 - i]); //right column index = left + (n - 1)
    }

    int cnt_left = std::count_if(diag_left.begin(), diag_left.end(), [diag_left](BoardValue val){return (diag_left[0] == val && val != BoardValue::Empty);});
    int cnt_right = std::count_if(diag_right.begin(), diag_right.end(), [diag_right](BoardValue val){return (diag_right[0] == val && val != BoardValue::Empty);});

    // Left-to-right diagonal
    if (cnt_left == board_dim) {
        if (diag_left[0] == BoardValue::X) return Winner::X;
        else if (diag_left[0] == BoardValue::O) return Winner::O;
    }

    // Right-to-left diagonal
    if (cnt_right == board_dim) {
        if (diag_right[0] == BoardValue::X) return Winner::X;
        else if (diag_right[0] == BoardValue::O) return Winner::O;
    }

    if(isFull(in_board)) return Winner::Draw;

    return Winner::None;
}


BoardValue Board::getPlayerSymbol(Player player) {
    switch (player) {
        case Player::X: return BoardValue::X;
        case Player::O: return BoardValue::O;
        case Player::AIO: return BoardValue::O;
        case Player::AIX: return BoardValue::X;
    }
    return BoardValue::Empty;
}


std::string Board::getBoardSymbol(std::vector<int> ids, std::string index) const {
    switch (board[ids[0]][ids[1]]) {
        case BoardValue::X: return "X";
        case BoardValue::O: return "O";
        default: return "";
    }
}


std::string Board::getBoardSymbol(Player player) const {
    if(player == Player::X || player == Player::AIX) return "X";
    else if(player == Player::O || player == Player::AIO) return "O";
    return ".";
}


std::vector<int> Board::get2DPos(int pos1D) {
    return { pos1D / getBoardSize(), pos1D % getBoardSize() };
}


bool Board::isEmptyAt(int row, int col, const std::vector<std::vector<BoardValue>>& in_board) const {
    return in_board[row][col] == BoardValue::Empty;
}


std::vector<std::vector<int>> Board::getAvailablePositions() const {
    std::vector<std::vector<int>> positions;
    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            if (isEmptyAt(i, j, board)) {
                positions.push_back({i, j});
            }
        }
    }
    return positions;
}

bool Board::checkIfWin(const std::vector<std::vector<BoardValue>>& board_table) {
    // Row win case check
    for(auto row: board_table) {
        BoardValue check_value = row[0];
        int result = std::count_if(row.begin(), row.end(), [check_value](BoardValue val){return (check_value == val && val != BoardValue::Empty);});
        if(result == board_size) return true;
    }

    // Column win case check
    for(int i = 0; i < board_size; i++) {
        BoardValue check_value = board_table[0][i];
        int cnt = 0;
        if(check_value == BoardValue::Empty) continue;
        for(int j = 0; j < board_size; j++) {
            if(board_table[j][i] == check_value) cnt++;
        }
        if(cnt == board_size) return true;
    }

    // Diagonal win case check
    std::vector<BoardValue> diag_left;
    std::vector<BoardValue> diag_right;
    
    int right = board_size - 1;
    for(int i = 0; i < board_size; i++) {
        diag_left.push_back(board_table[i][i]);
        diag_right.push_back(board_table[i][board_size - 1 - i]); //right column index = left + (n - 1)
    }

    int result_left = std::count_if(diag_left.begin(), diag_left.end(), [diag_left](BoardValue val){return (diag_left[0] == val && val != BoardValue::Empty);});
    int result_right = std::count_if(diag_right.begin(), diag_right.end(), [diag_right](BoardValue val){return (diag_right[0] == val && val != BoardValue::Empty);});
    if(result_right == board_size || result_left == board_size) return true;

    return false;
}

bool Board::isFull(const std::vector<std::vector<BoardValue>>& in_board) {
    for(int i = 0; i < board_size; i++) {
        for(int j = 0; j < board_size; j++) {
            if(in_board[i][j] == BoardValue::Empty) return false;
        }
    }
    return true;
}
