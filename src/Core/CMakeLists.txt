add_library(Board STATIC Board.cpp)
target_include_directories(Board
    PUBLIC
      ${PROJECT_SOURCE_DIR}/src/core/include
)

add_library(GameManager STATIC GameManager.cpp)
target_include_directories(GameManager
    PUBLIC
      ${PROJECT_SOURCE_DIR}/src/core/include
)

add_library(AIPlayer STATIC AIPlayer.cpp)
target_include_directories(AIPlayer
    PUBLIC
      ${PROJECT_SOURCE_DIR}/src/core/include
)


#add_executable(TicTacToe main.cpp)
#target_link_libraries(TicTacToe
#    PRIVATE
#      Board
#      GameManager
#      AIPlayer
#)
