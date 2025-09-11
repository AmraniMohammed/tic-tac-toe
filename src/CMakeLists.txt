add_subdirectory(Core)
add_subdirectory(UI)
add_subdirectory(Wrapper)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(appTicTacToe main.cpp
      resources.qrc
)

set_target_properties(appTicTacToe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(appTicTacToe
      PRIVATE Qt6::Core
      PRIVATE Qt6::Quick
)

target_link_libraries(appTicTacToe PRIVATE UIModule)

target_link_libraries(appTicTacToe PRIVATE GameManager)

target_link_libraries(appTicTacToe
    PRIVATE
      Board
      AIPlayer
)
