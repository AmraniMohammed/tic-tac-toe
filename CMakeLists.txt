cmake_minimum_required(VERSION 3.16)

project(TicTacToe VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_subdirectory(src)
# add_subdirectory(tests)

# enable_testing()

qt_standard_project_setup(REQUIRES 6.8)

# qt_add_executable(appTicTacToe
#     main.cpp
# )

# qt_add_qml_module(appTicTacToe
#     URI TicTacToe
#     VERSION 1.0
#     QML_FILES
#         src/UI/Main.qml
#         SOURCES include/GameManager.h src/GameManager.cpp
# )


# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# set_target_properties(appTicTacToe PROPERTIES
# #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTicTacToe
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# target_link_libraries(appTicTacToe
#     PRIVATE Qt6::Quick
# )
# target_link_libraries(appTicTacToe PRIVATE Qt6::Core)

# include(GNUInstallDirs)
# install(TARGETS appTicTacToe
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
