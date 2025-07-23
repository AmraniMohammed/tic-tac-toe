#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <string>

enum class GameState { PlayerXWin, PlayerOWin, Draw, Continue };
enum class Player {X, O};

class Board {

    private:
        Player current_player = Player::X;
        GameState state = GameState::Continue;
        std::vector<std::string> board = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};
        inline static const std::vector<std::vector<int>> wins_cases = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
                                                                                {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
                                                                                {0, 4, 8}, {2, 4, 6}
                                                                                };


    public:
        Player getPlayer() const noexcept {return current_player;};
        const std::vector<std::string>& getBoard() const {return board;};
        GameState getState() const noexcept {return state;};

        void fillSquareAtPosition(int pos) {
            if(current_player == Player::X) {
                board[pos] = "X";
            }
            else {
                board[pos] = "O";
            }
        };
         void advanceTurn() noexcept {
            current_player = (current_player == Player::X ? Player::O : Player::X);
        }

        void setStartPlayer() {
            std::cout<< "Choose starting player symbol by typing X or O\n";
            while (true)
            {
                std::string starting_player;
                std::cin >> starting_player;

                if(starting_player == "X" || starting_player == "x") {
                    current_player = Player::X;
                    break;
                }
                else if(starting_player == "O" || starting_player == "o") {
                    current_player = Player::O;
                    break;
                }
                else {
                    std::cout<< "Please type a valid player symbol (X or O)\n";
                }
            }
            
        }

        int readMove() {
            std::cout << "\n" << ((current_player == Player::X) ? "Player 1 (X)" : "Player 2(O)") << " role, please type the psotion you want to fill: ";
            std::string string_input; 
            std::cin >> string_input;
            
            int pos;
            
            try
            {
                pos = std::stoi(string_input);
            }
            catch (std::exception& e)
            {
                return -1;
            }
            return pos;
        };
        bool checkIfValidInput(int pos) {
            if(pos < 0 || pos > 8) {
                std::cout << "Please give a valid number between 0 and 8\n";
                return false;
            }
            else if(board[pos] == "X" || board[pos] == "O") {
                std::cout << "Position [" << pos << "] already filled, please choose another one\n";
                return false;
            }
            return true;
        };

        GameState updateGameState() {
            bool is_win = false;

            for(auto win_case: wins_cases) {
                if(board[win_case[0]] == board[win_case[1]] && board[win_case[1]] == board[win_case[2]]) {
                    is_win = true;
                    break;
                }
            };

            if(is_win) {
                state = (current_player == Player::X ? GameState::PlayerXWin : GameState::PlayerOWin);
            }
            else if(std::count_if(board.begin(), board.end(), [](std::string value){return(value == "X" || value == "O");}) == 9) {
                state = GameState::Draw;
            }
            else {
                state = GameState::Continue;
            }
            return state;
        };

        void updateBoardUI() const noexcept {
            std::cout <<"\n";

            std::cout << " " << board[0]  << " " << "|" << " " << board[1] << " " << "|" << " " << board[2] << " " << "\n";
            std::cout << "___ ___ ___" << "\n";

            std::cout << " " << board[3]  << " " << "|" << " " << board[4] << " " << "|" << " " << board[5] << " " << "\n";
            std::cout << "___ ___ ___" << "\n";
            
            std::cout << " " << board[6]  << " " << "|" << " " << board[7] << " " << "|" << " " << board[8] << " " << "\n";
        };

        void showResult() const noexcept{
            if(state == GameState::Draw) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Draw ==========\n";
            } else if(state == GameState::PlayerXWin) {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Player X won ==========\n";
            }
            else {
                std::cout << "\n========== Game Over ==========\n";
                std::cout << "\n========== Player O won ==========\n";
            }
        }
};


int main() {

    std::cout << "========== Tic Tac Toe Game ==========\n";

    Board board;

    board.setStartPlayer();

    board.updateBoardUI();

    //Get Position to fill from player
    int position = - 1;
    GameState game_state = board.getState();

    do{ 
        //Check if valid input
        position = board.readMove();
        if(!board.checkIfValidInput(position)) continue;

        // Fill with symbol of the current player & update the board
        board.fillSquareAtPosition(position);
    
        //Update UI
        board.updateBoardUI();
        game_state = board.updateGameState();

        if(game_state == GameState::Continue) 
            board.advanceTurn();
    }while(game_state == GameState::Continue);

    board.showResult();
    
    return 0;
}