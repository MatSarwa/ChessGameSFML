#include "Knight.h"
#include "ChessBoard.h"

Knight::Knight(PieceColor color) : Piece(PieceType::KNIGHT, color) {
}

std::vector<sf::Vector2i> Knight::getPossibleMoves(int row, int col, const ChessBoard& board) const {
    std::vector<sf::Vector2i> moves;

    const int knightMoves[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    for (auto& move : knightMoves) {
        int r = row + move[0];
        int c = col + move[1];

        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            const Piece* target = board.getPieceAt(r, c);
            if (target->isEmpty() || target->getColor() != color) {
                moves.push_back(sf::Vector2i(r, c));
            }
        }
    }

    return moves;
}