#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <limits>
#include <random>

enum class GameState { PlayerXWin, PlayerOWin, Draw, Continue };
enum class Player {X, O, AI};
enum class GameMode { TwoPlayers, OnePlayer };
enum class BoardValue {Empty, X, O};

class Board {

    private:
        Player current_player = Player::X;
        Player first_player = Player::X;
        Player second_player = Player::O;
        GameState state = GameState::Continue;
        GameMode game_mode = GameMode::TwoPlayers;
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

        Player getPlayer() const noexcept {return current_player;};
        const auto& getBoard() const {return board;};
        GameState getState() const noexcept {return state;};
        GameMode getGameMode() const noexcept {return game_mode;};

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
                        second_player = Player::AI;
                        break;
                    }
                    else if(game_mode == GameMode::OnePlayer  && (starting_player == "O" || starting_player == "o")) {
                        current_player = Player::O;
                        first_player = current_player;
                        second_player = Player::AI;
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

        void fillSquareAtPosition(std::vector<int> position_2d) {
            board[position_2d[0]][position_2d[1]] = getPlayerSymbol(current_player);
        };
        
        void advanceTurn() noexcept {
            if(game_mode == GameMode::OnePlayer) {
                current_player = (current_player == Player::X || current_player == Player::O ? Player::AI : first_player);
            }
            else {
                current_player = (current_player == Player::X ? Player::O : Player::X);
            }
        }

        bool readPlayerMove(std::vector<int>& out_2d_position) {
            std::cout << "\n" << "Player (" << getBoardSymbol(current_player) << ") role, please type the position you want to fill: ";
            
            int pos;
            std::cin >> pos;
            if(std::cin.fail() || pos < 0 || pos > 8) {
                std::cout << "Please give a valid number between 0 and 8\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return false;
            }
            std::vector<int> pos_2d = get2DPos(pos);
            if(board[pos_2d[0]][pos_2d[1]] == BoardValue::X || board[pos_2d[0]][pos_2d[1]] == BoardValue::O) {
                std::cout << "Position [" << pos << "] already filled, please choose another one\n";
                return false;
            }
            out_2d_position = pos_2d;
            return true;
        }

        GameState evaluateState() {
            if(checkIfWin()) {
                state = (current_player == Player::X ? GameState::PlayerXWin : GameState::PlayerOWin);
                return state;
            }
            int cnt = 0;
            for(auto row: board) {
                cnt += std::count_if(row.begin(), row.end(), [](BoardValue value){return(value == BoardValue::X || value == BoardValue::O);});
            }
            if(cnt == board_size * board_size) {
                state = GameState::Draw;
            }
            else {
                state = GameState::Continue;
            }
            return state;
        };

        void updateBoardUI() const noexcept {
            std::cout <<"\n";
            for(int i = 0; i < board_size; i++) {

                for(int j = 0; j < board_size; j++) {
                    std::cout << "|" << " " << getBoardSymbol({i, j}, std::to_string(i * board_size + j)) << " ";
                }
                std::cout << "|\n";
                drawDivider();
            }
        };

        void drawDivider() const {
            std::cout << std::string(board_size * 4 + (board_size-1)*1, '_') << "\n";
        }
        
        void showResult() const noexcept{
            if(state == GameState::Draw) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Draw ==========\n";
            } else if(state == GameState::PlayerXWin) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Player X won ==========\n";
            }
            else if(state == GameState::PlayerOWin) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Player O won ==========\n";
            }
        }

        void run() {
            // Get Position to fill from player
            std::vector<int> position_2d;
            
            // Game loop
            while(getState() == GameState::Continue){ 

                if(getGameMode() == GameMode::OnePlayer && getPlayer() == Player::AI) {
                    //std::cout << "One player mode vs AI coming soon ... \n";
                    position_2d = getAiMove();
                    //break;
                }
                else {
                    // Get input
                    if(!readPlayerMove(position_2d)) continue;
                }

                // Game logic
                fillSquareAtPosition(position_2d);
                evaluateState();

                // Draw 
                updateBoardUI();

                if(getState() == GameState::Continue) 
                    advanceTurn();

            };

            showResult();
        }

        BoardValue getPlayerSymbol(Player player) {
            switch (player) {
                case Player::X: return BoardValue::X;
                case Player::O: return BoardValue::O;
                case Player::AI: {
                    if(first_player == Player::X) return BoardValue::O;
                    else return BoardValue::X;
                };
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
            switch (player) {
                case Player::X: return "X";
                case Player::O: return "O";
            }
            return ".";
        }


        std::vector<int> get2DPos(int pos1D) {
            return { pos1D / board_size, pos1D % board_size };
        }

        std::vector<int> getAiMove() {

            std::vector<std::vector<int>> available_positions;

            for(int i = 0; i < board.size(); i++) {
                for(int j = 0; j < board.size(); j++) {
                    if(board[i][j] != BoardValue::X && board[i][j] != BoardValue::O) {
                        available_positions.push_back({i, j});
                    }
                }
            }

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

        bool checkIfWin() {
            // Row win case check
            for(auto row: board) {
                BoardValue check_value = row[0];
                int result = std::count_if(row.begin(), row.end(), [check_value](BoardValue val){return (check_value == val && val != BoardValue::Empty);});
                if(result == board_size) return true;
            }

            // Column win case check
            for(int i = 0; i < board_size; i++) {
                BoardValue check_value = board[0][i];
                int cnt = 0;
                if(check_value == BoardValue::Empty) continue;
                for(int j = 0; j < board_size; j++) {
                    if(board[j][i] == check_value) cnt++;
                }
                if(cnt == board_size) return true;
            }

            // Diagonal win case check
            std::vector<BoardValue> diag_left;
            std::vector<BoardValue> diag_right;
            
            int right = board_size - 1;
            for(int i = 0; i < board_size; i++) {
                diag_left.push_back(board[i][i]);
                diag_right.push_back(board[i][i + board_size - 1]); //right column index = left + (n - 1)
            }

            int result_left = std::count_if(diag_left.begin(), diag_left.end(), [diag_left](BoardValue val){return (diag_left[0] == val && val != BoardValue::Empty);});
            int result_right = std::count_if(diag_right.begin(), diag_right.end(), [diag_right](BoardValue val){return (diag_right[0] == val && val != BoardValue::Empty);});
            if(result_right == board_size || result_left == board_size) return true;

            return false;
        }
    };


int main() {    
    Board board;

    board.setup();

    board.run();
    
    return 0;
}