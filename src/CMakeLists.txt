add_subdirectory(Core)
add_subdirectory(UI)
add_subdirectory(Wrapper)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(appTicTacToe main.cpp
      resources.qrc
)

target_link_libraries(appTicTacToe
      PRIVATE Qt6::Core
      PRIVATE Qt6::Quick
)

target_link_libraries(appTicTacToe PRIVATE UIModule)

target_link_libraries(appTicTacToe PRIVATE GameManagerWrapper)

target_link_libraries(appTicTacToe
    PRIVATE
      Board
      GameManager
      AIPlayer
)
