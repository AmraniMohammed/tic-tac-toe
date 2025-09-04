add_library(GameManager STATIC
    GameManager.h GameManager.cpp
    GameTypesWrapper.h  )

target_include_directories(GameManager
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(GameManager PRIVATE Qt6::Core Board)

target_link_libraries(GameManager
    PRIVATE
      Board
      AIPlayer
)
