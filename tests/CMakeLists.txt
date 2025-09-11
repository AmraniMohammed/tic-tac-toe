set(CMAKE_TLS_VERIFY OFF)
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)


# Prevent GoogleTest from installing itself
set(INSTALL_GTEST OFF)
set(BUILD_GMOCK OFF)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(TestMain test_main.cpp)


target_link_libraries(TestMain
    PRIVATE
      Board
      AIPlayer
      gtest_main
)

# Include directories
target_include_directories(TestMain PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(TestMain)
