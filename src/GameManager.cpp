#include <GameManager.h>
#include <AIPlayer.h>

GameManager::GameManager(Board& b) : board(b){ };


void GameManager::setup() {
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
                std::cout<< "Easy mode ? (y/n)\n";
                std::string play_mode;
                std::cin >> play_mode;
                if(play_mode == "y" || play_mode == "Y") {
                    is_easy_mode = true;
                }
                else if(play_mode == "n" || play_mode == "N") {
                    is_easy_mode = false;
                }
                else {
                    continue;
                }
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

void GameManager::updateBoardUI() const noexcept {
    std::cout <<"\n";
    for(int i = 0; i < board.getBoardSize(); i++) {

        for(int j = 0; j < board.getBoardSize(); j++) {
            std::cout << "|" << " " << board.getBoardSymbol({i, j}, std::to_string(i * board.getBoardSize() + j)) << " ";
        }
        std::cout << "|\n";
        drawDivider();
    }
};


void GameManager::drawDivider() const {
    std::cout << std::string(board.getBoardSize() * 4 + (board.getBoardSize()-1)*1, '_') << "\n";
}

void GameManager::update() {
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


bool GameManager::readPlayerMove(std::vector<int>& out_2d_position) {
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


std::vector<int> GameManager::getAiMove() {
    std::vector<int> result;
    
    if(is_easy_mode) {
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
        result = available_positions[randomValue];
    }
    else {
        AIPlayer ai_player(board);

        result = ai_player.getBestMove(board.getBoard(), second_player, first_player, second_player, 10);
    }

    

    return result;
}


void GameManager::showResult() const noexcept{
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
}


void GameManager::advanceTurn() noexcept {
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
