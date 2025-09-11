add_library(Board STATIC Board.cpp)
target_include_directories(Board
    PUBLIC
      ${PROJECT_SOURCE_DIR}/src/Core/include
)

add_library(AIPlayer STATIC AIPlayer.cpp)
target_include_directories(AIPlayer
    PUBLIC
      ${PROJECT_SOURCE_DIR}/src/Core/include
)
