add_library(GameManagerWrapper STATIC
    GameManagerWrapper.h GameManagerWrapper.cpp )

target_include_directories(GameManagerWrapper
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(GameManagerWrapper PRIVATE Qt6::Core GameManager)
