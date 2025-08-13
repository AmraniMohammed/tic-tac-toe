#include <gtest/gtest.h>
#include "Board.h"

// Helper function to generate row win boards for X
std::vector<std::vector<std::vector<BoardValue>>> generateXWins() {
    int N = 3;
    std::vector<std::vector<std::vector<BoardValue>>> wins;

    // Row wins
    for (int r = 0; r < N; ++r) {
        std::vector<std::vector<BoardValue>> board(N, std::vector<BoardValue>(N, BoardValue::Empty));
        for (int c = 0; c < N; ++c) board[r][c] = BoardValue::X;
        wins.push_back(board);
    }

    // Column wins
    for (int c = 0; c < N; ++c) {
        std::vector<std::vector<BoardValue>> board(N, std::vector<BoardValue>(N, BoardValue::Empty));
        for (int r = 0; r < N; ++r) board[r][c] = BoardValue::X;
        wins.push_back(board);
    }

    // Diagonal wins
    std::vector<std::vector<BoardValue>> diag1(N, std::vector<BoardValue>(N, BoardValue::Empty));
    std::vector<std::vector<BoardValue>> diag2(N, std::vector<BoardValue>(N, BoardValue::Empty));
    for (int i = 0; i < N; ++i) {
        diag1[i][i] = BoardValue::X;
        diag2[i][N - 1 - i] = BoardValue::X;
    }
    wins.push_back(diag1);
    wins.push_back(diag2);

    return wins;
}

TEST(BoardLib, EvaluateWinnerTest) {
    Board board;
    auto allWins = generateXWins();
    for (auto& board_table : allWins) {
        EXPECT_EQ(board.evaluateWinner(board_table), Winner::X);
    }
}

