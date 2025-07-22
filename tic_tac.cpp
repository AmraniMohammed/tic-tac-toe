#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

std::vector<std::string> board = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};
int bIsPlayer1 = true;
int bIsDraw = false;

//Update Board UI
void updateBoard() {
    std::cout << std::endl;
    std::cout << " " << board[0]  << " " << "|" << " " << board[1] << " " << "|" << " " << board[2] << " " << std::endl;
    std::cout << "___ ___ ___" << std::endl;
    std::cout << " " << board[3]  << " " << "|" << " " << board[4] << " " << "|" << " " << board[5] << " " << std::endl;
    std::cout << "___ ___ ___" << std::endl;
    std::cout << " " << board[6]  << " " << "|" << " " << board[7] << " " << "|" << " " << board[8] << " " << std::endl;
}

// 1 => Game Over & 0 => Draw & -1 => Go Next
int checkState() {
    if(board[0] == board[1] && board[1] == board[2]) {
        return 1;
    }
    else if(board[3] == board[4] && board[4] == board[5]) {
        return 1;
    }
    else if(board[6] == board[7] && board[7] == board[8]) {
        return 1;
    }
    else if(board[0] == board[3] && board[3] == board[6]) {
        return 1;
    }
    else if(board[1] == board[4] && board[4] == board[7]) {
        return 1;
    }
    else if(board[2] == board[5] && board[5] == board[8]) {
        return 1;
    }
    else if(board[0] == board[4] && board[4] == board[8]) {
        return 1;
    }
    else if(board[2] == board[4] && board[4] == board[6]) {
        return 1;
    }
    else if(std::count_if(board.begin(), board.end(), [](std::string value){return(value == "X" || value == "O");}) == 9) {
        return 0;
    }
    return -1;
}

bool checkIfPositionFilled(int pos) {
    if(board[pos] == "X" || board[pos] == "O"){
        return true;
    }
    else {
        return false;
    }
}


class Board {

    private:
        bool bIsDraw = false; // False => draw & True => Win
        bool bIsPlayer1 = true;
        std::vector<std::string> board = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};

    public:
        int GetPlayerInput() {
            std::cout << "\n" << (bIsPlayer1 ? "Player 1 (X)" : "Player 2(O)") << " role, please type the psotion you want to fill: ";
            std::string string_input; 
            std::cin >> string_input;
            return std::stoi(string_input);
        }
        bool CheckIfValidInput(int pos) {
            if(std::cin.fail() || pos < 0 || pos > 8) {
                std::cout << "Please give a valid input between 0 and 8" << std::endl;
                return false;
            }
            else if(board[pos] == "X" || board[pos] == "O") {
                std::cout << "Position already filled, please choose another one" << std::endl;
                return false;
            }
            return true;
        }
        bool IsDraw() {return bIsDraw;};
        bool IsPlayer1() {return bIsPlayer1;};
        std::vector<std::string> GetBoard() {return board;};
        void FillSquareAtPosition(int pos) {
            if(IsPlayer1()) {
                board[pos] = "X";
            }
            else {
                board[pos] = "O";
            }
            bIsPlayer1 = !bIsPlayer1;
        };
        void SetBoardSquareAtPosition(int pos, std::string symb) {
            board[pos] = symb;
        };

        void UpdateBoardUI() {
            std::cout << std::endl;

            std::cout << " " << board[0]  << " " << "|" << " " << board[1] << " " << "|" << " " << board[2] << " " << std::endl;
            std::cout << "___ ___ ___" << std::endl;

            std::cout << " " << board[3]  << " " << "|" << " " << board[4] << " " << "|" << " " << board[5] << " " << std::endl;
            std::cout << "___ ___ ___" << std::endl;
            
            std::cout << " " << board[6]  << " " << "|" << " " << board[7] << " " << "|" << " " << board[8] << " " << std::endl;
        };

        // 1 => Game Over & 0 => Draw & -1 => Go Next
        int CheckState() {
            if(board[0] == board[1] && board[1] == board[2]) {
                return 1;
            }
            else if(board[3] == board[4] && board[4] == board[5]) {
                return 1;
            }
            else if(board[6] == board[7] && board[7] == board[8]) {
                return 1;
            }
            else if(board[0] == board[3] && board[3] == board[6]) {
                return 1;
            }
            else if(board[1] == board[4] && board[4] == board[7]) {
                return 1;
            }
            else if(board[2] == board[5] && board[5] == board[8]) {
                return 1;
            }
            else if(board[0] == board[4] && board[4] == board[8]) {
                return 1;
            }
            else if(board[2] == board[4] && board[4] == board[6]) {
                return 1;
            }
            else if(std::count_if(board.begin(), board.end(), [](std::string value){return(value == "X" || value == "O");}) == 9) {
                return 0;
            }
            return -1;
        }

};


int main() {

    std::cout << "========== Tic Tac Toe Game ==========" << std::endl;

    std::shared_ptr<Board> TicTacToeBoard = std::make_shared<Board>();

    TicTacToeBoard->UpdateBoardUI();

    //updateBoard();
    do{ 

        //Get Position to fill from player

        std::cout << TicTacToeBoard->IsPlayer1() ? "Player 1 role \n" : "Player 2 role \n";

        int position = TicTacToeBoard->GetPlayerInput();

        // std::cout << "\n" << (bIsPlayer1 ? "Player 1 (X)" : "Player 2(O)") << " role, please type the psotion you want to fill: ";
        // int pos; 
        // std::string string_input; 
        // std::cin >> string_input;
        // pos = std::stoi(string_input);
    

        //Check if valid input
        if(TicTacToeBoard->CheckIfValidInput(position))
        {
            // Fill with symbol of the current player & update the board
            TicTacToeBoard->FillSquareAtPosition(position);

            //Update UI
            TicTacToeBoard->UpdateBoardUI();
        }

        // if(std::cin.fail() || pos < 0 || pos > 8) {
        //     std::cout << "Please give a valid input between 0 and 8" << std::endl;
        // }
        // else if(checkIfPositionFilled(pos)) {
        //     std::cout << "Position already filled, please choose another one" << std::endl;
        // }
        // else {
        //     // Fill with symbol of the current player & update the board
        //     if(bIsPlayer1) {
        //         board[pos] = "X";
        //     }
        //     else {
        //         board[pos] = "O";
        //     }
        //     bIsPlayer1 = !bIsPlayer1;

        //     //Update UI
        //     updateBoard();

        // }
        if(checkState() == 0) {
            bIsDraw = true;
            break;
        }
    }while(checkState() != 1);

    if(bIsDraw) {
        std::cout << "Draw" << std::endl;
    } else if(bIsPlayer1) {
        std::cout << "Player 2 won" << std::endl;
    }
    else {
        std::cout << "Player 1 won" << std::endl;
    }
    
    return 0;
}