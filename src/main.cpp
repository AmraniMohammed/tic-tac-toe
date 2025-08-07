#include <GameManager.h>
#include <Board.h>


int main() {   
    Board board;
    GameManager game_manager(board); 
    
    game_manager.setup();
    
    game_manager.run();

    return 0;
}