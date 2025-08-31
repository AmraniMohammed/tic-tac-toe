add_subdirectory(Core)
add_subdirectory(UI)

add_executable(appTicTacToe main.cpp)

target_link_libraries(appTicTacToe
      PRIVATE Qt6::Core
      PRIVATE Qt6::Quick
)

target_link_libraries(appTicTacToe PRIVATE UIModule)

target_link_libraries(appTicTacToe
    PRIVATE
      Board
      GameManager
      AIPlayer

)
