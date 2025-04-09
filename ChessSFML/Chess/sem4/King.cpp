#include "King.h"
#include "ChessBoard.h"

King::King(PieceColor color) : Piece(PieceType::KING, color) {
}

std::vector<sf::Vector2i> King::getPossibleMoves(int row, int col, const ChessBoard& board) const {
    std::vector<sf::Vector2i> moves;

    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            if (r == 0 && c == 0) continue;
            int newRow = row + r;
            int newCol = col + c;
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                const Piece* target = board.getPieceAt(newRow, newCol);

                if (target->isEmpty() || target->getColor() != color) {
                    moves.push_back(sf::Vector2i(newRow, newCol));
                }
            }
        }
    }

    if (!hasMoved) {
        bool isWhite = (color == PieceColor::WHITE);
        int kingRow = isWhite ? 7 : 0;
        if (row == kingRow && col == 4) {

            bool shortCastlePossible = true;
            for (int c = 5; c < 7; c++) {
                if (!board.getPieceAt(kingRow, c)->isEmpty()) {
                    shortCastlePossible = false;
                    break;
                }
            }
            const Piece* rookShort = board.getPieceAt(kingRow, 7);
            if (shortCastlePossible && rookShort &&
                rookShort->getType() == PieceType::ROOK &&
                rookShort->getColor() == color &&
                !rookShort->getHasMoved()) {
                moves.push_back(sf::Vector2i(kingRow, 6));
            }

            bool longCastlePossible = true;
            for (int c = 1; c < 4; c++) {
                if (!board.getPieceAt(kingRow, c)->isEmpty()) {
                    longCastlePossible = false;
                    break;
                }
            }
            const Piece* rookLong = board.getPieceAt(kingRow, 0);
            if (longCastlePossible && rookLong &&
                rookLong->getType() == PieceType::ROOK &&
                rookLong->getColor() == color &&
                !rookLong->getHasMoved()) {
                moves.push_back(sf::Vector2i(kingRow, 2));
            }
        }
    }

    return moves;
}