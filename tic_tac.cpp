#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <limits>
#include <random>

enum class GameState { PlayerXWin, PlayerOWin, AIWin, Draw, Continue };
enum class Player {X, O, AIO, AIX}; // AIX = AI playing with symbol X, AIO = AI playing with symbol O
enum class GameMode { TwoPlayers, OnePlayer };
enum class BoardValue {Empty, X, O};

class Board {

    private:
        GameState state = GameState::Continue;
        int board_size = 3;
        std::vector<std::vector<BoardValue>> board;
    
    public:
        Board()
        {
             board = std::vector<std::vector<BoardValue>>(
            board_size,
            std::vector<BoardValue>(board_size, BoardValue::Empty)
        );
        }

        const std::vector<std::vector<BoardValue>>& getBoard() const noexcept {return board;};
        GameState getState() const noexcept {return state;};
        int getBoardSize() const noexcept {return board_size;};

        void setState(GameState new_state) noexcept {state = new_state;};

        void makeMove(std::vector<int> position_2d, Player player) {
            board[position_2d[0]][position_2d[1]] = getPlayerSymbol(player);
        };
        
        
        GameState evaluateState(Player current_player, const std::vector<std::vector<BoardValue>>& board) {
            GameState result_state;
            if(checkIfWin(board)) {
                switch (current_player)
                {
                case Player::X:
                    result_state = GameState::PlayerXWin;
                    break;
                case Player::O:
                    result_state = GameState::PlayerOWin;
                    break;
                case Player::AIO:
                    result_state = GameState::AIWin;
                    break;
                case Player::AIX:
                    result_state = GameState::AIWin;
                    break;
                }
                return result_state;
            }
            int cnt = 0;
            for(auto row: board) {
                cnt += std::count_if(row.begin(), row.end(), [](BoardValue value){return(value == BoardValue::X || value == BoardValue::O);});
            }
            if(cnt == board_size * board_size) {
                result_state = GameState::Draw;
            }
            else {
                result_state = GameState::Continue;
            }
            return result_state;
        };

        BoardValue getPlayerSymbol(Player player) {
            switch (player) {
                case Player::X: return BoardValue::X;
                case Player::O: return BoardValue::O;
                case Player::AIO: return BoardValue::O;
                case Player::AIX: return BoardValue::X;
            }
            return BoardValue::Empty;
        }
        
        std::string getBoardSymbol(std::vector<int> ids, std::string index) const {
            switch (board[ids[0]][ids[1]]) {
                case BoardValue::X: return "X";
                case BoardValue::O: return "O";
            }
            return index;
        }

        std::string getBoardSymbol(Player player) const {
            if(player == Player::X || player == Player::AIX) return "X";
            else if(player == Player::O || player == Player::AIO) return "O";
            return ".";
        }

        std::vector<int> get2DPos(int pos1D) {
            return { pos1D / board_size, pos1D % board_size };
        }

        bool isEmptyAt(int row, int col, std::vector<std::vector<BoardValue>> board) const {
            return board[row][col] == BoardValue::Empty;
        }

        std::vector<std::vector<int>> getAvailablePositions() const {
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

        bool checkIfWin(std::vector<std::vector<BoardValue>> board_table) {
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

        bool isFull(std::vector<std::vector<BoardValue>> board) {
            for(int i = 0; i < board_size; i++) {
                for(int j = 0; j < board_size; j++) {
                    if(board[i][j] == BoardValue::Empty) return false;
                }
            }
            return true;
        }
};


class GameManager {
    private:
        Board& board;
        Player current_player = Player::X;
        Player first_player = Player::X;
        Player second_player = Player::O;
        GameMode game_mode = GameMode::TwoPlayers;
    public:
        GameManager(Board& b) : board(b){ };

        void setup() {
            std::cout << "============================== Tic Tac Toe Game ==============================\n";

            std::cout << "Please choose the game mode that you want, for two player game mode type 2, and for one player vs AI game mode type 1. \n";
            int play_mode;
            bool play_mode_seted = false;
            while(true) {
                if(!play_mode_seted) {
                    std::cin >> play_mode;
                    if(std::cin.fail() || (play_mode != 1 && play_mode != 2)) {
                        std::cout << "Please type a valid choice (1 or 2). \n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else {
                        if(play_mode == 2) game_mode = GameMode::TwoPlayers;
                        else game_mode = GameMode::OnePlayer;
                        play_mode_seted = true;
                    }
                }
                else {
                    if(game_mode == GameMode::TwoPlayers) {
                        std::cout<< "Please choose a valid starting player symbol by typing X or O\n";
                    }
                    else {
                        std::cout<< "Please choose a playing symbol by typing X or O\n";
                    }
                    std::string starting_player;
                    std::cin >> starting_player;

                    if(game_mode == GameMode::OnePlayer  && (starting_player == "X" || starting_player == "x")) {
                        current_player = Player::X;
                        first_player = current_player;
                        second_player = Player::AIO;
                        break;
                    }
                    else if(game_mode == GameMode::OnePlayer  && (starting_player == "O" || starting_player == "o")) {
                        current_player = Player::O;
                        first_player = current_player;
                        second_player = Player::AIX;
                        break;
                    }
                    else if(starting_player == "X" || starting_player == "x") {
                        current_player = Player::X;
                        first_player = current_player;
                        second_player = Player::O;
                        break;
                    }
                    else if(starting_player == "O" || starting_player == "o") {
                        current_player = Player::O;
                        first_player = current_player;
                        second_player = Player::X;
                        break;
                    }
                }
            };
            updateBoardUI();
        }

        void updateBoardUI() const noexcept {
            std::cout <<"\n";
            for(int i = 0; i < board.getBoardSize(); i++) {

                for(int j = 0; j < board.getBoardSize(); j++) {
                    std::cout << "|" << " " << board.getBoardSymbol({i, j}, std::to_string(i * board.getBoardSize() + j)) << " ";
                }
                std::cout << "|\n";
                drawDivider();
            }
        };
        
        void drawDivider() const {
            std::cout << std::string(board.getBoardSize() * 4 + (board.getBoardSize()-1)*1, '_') << "\n";
        }

        void run() {
            // Get Position to fill from player
            std::vector<int> position_2d;
            
            // Game loop
            while(board.getState() == GameState::Continue){ 
                if(game_mode == GameMode::OnePlayer && (current_player == Player::AIX || current_player == Player::AIO)) {
                    position_2d = getAiMove();
                }
                else {
                    // Get input
                    if(!readPlayerMove(position_2d)) continue;
                }

                // Game logic
                board.makeMove(position_2d, current_player);
                board.setState(board.evaluateState(current_player, board.getBoard()));

                // Draw
                updateBoardUI();

                if(board.getState() == GameState::Continue) 
                    advanceTurn();

            };

            showResult();
        }
        
        bool readPlayerMove(std::vector<int>& out_2d_position) {
            std::cout << "\n" << "Player (" << board.getBoardSymbol(current_player) << ") role, please type the position you want to fill: ";
            
            int pos;
            std::cin >> pos;
            if(std::cin.fail() || pos < 0 || pos > 8) {
                std::cout << "Please give a valid number between 0 and 8\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return false;
            }
            std::vector<int> pos_2d = board.get2DPos(pos);
            if(!board.isEmptyAt(pos_2d[0], pos_2d[1], board.getBoard())) {
                std::cout << "Position [" << pos << "] already filled, please choose another one\n";
                return false;
            }
            out_2d_position = pos_2d;
            return true;
        }

        std::vector<int> getAiMove() {

            std::vector<std::vector<int>> available_positions;

            available_positions = board.getAvailablePositions();

            // Define range
            int min = 0;
            int max = available_positions.size() - 1;

            // Initialize a random number generator
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(min, max);

            // Generate random number in the range [min, max]
            int randomValue = distrib(gen);

            return available_positions[randomValue];
        }

        void showResult() const noexcept{
            if(board.getState() == GameState::Draw) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Draw ==========\n";
            } else if(board.getState() == GameState::PlayerXWin) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Player X won ==========\n";
            }
            else if(board.getState() == GameState::PlayerOWin) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Player O won ==========\n";
            }
            else if(board.getState() == GameState::AIWin) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== AI won ==========\n";
            }
        }
        
        void advanceTurn() noexcept {
            if(game_mode == GameMode::OnePlayer) {
                if(current_player == Player::X) current_player = Player::AIO;
                else if(current_player == Player::O) current_player = Player::AIX;
                else if(current_player == Player::AIX) current_player = Player::O;
                else current_player = Player::X;
            }
            else {
                current_player = (current_player == Player::X ? Player::O : Player::X);
            }
        }

        int miniMaxAlgo(std::vector<std::vector<BoardValue>>& board_table, int depth, Player current_player, Player human_player, Player ai_player) {
            if(isTerminal(board_table) || depth == 0) {
                return getUtility(board_table, current_player);
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

        bool isTerminal(std::vector<std::vector<BoardValue>>& board_table) {
            return board.isFull(board_table);
        }

        int getUtility(std::vector<std::vector<BoardValue>>& board_table, Player current_player) {
            GameState state =  board.evaluateState(current_player, board_table);
            if(state == GameState::AIWin) return 1;
            else if(state == GameState::PlayerXWin || state == GameState::PlayerOWin) return -1;
            else if(state == GameState::Draw) return 0;
            return 0;
        }
        std::vector<std::vector<int>> getActions(std::vector<std::vector<BoardValue>>& board_table) {
            std::vector<std::vector<int>> result;
            for(int i = 0; i < board_table.size(); i++) {
                for(int j = 0; j < board_table.size(); j++) {
                    if(board.isEmptyAt(i, j, board_table)) result.push_back({i, j});
                }
            }
            return result;
        }
        std::vector<std::vector<BoardValue>> getResult(std::vector<std::vector<BoardValue>>& board_table, std::vector<int> action, Player player) {
            board_table[action[0]][action[1]] = (player == Player::X || player == Player::AIX ? BoardValue::X : BoardValue::O);
            return board_table;
        }
};


class AIPlayer {

};

int main() {   
    Board board;
    GameManager game_manager(board); 
    
    game_manager.setup();
    
    game_manager.run();

    return 0;
}