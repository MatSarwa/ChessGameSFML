#include "Pawn.h"
#include "ChessBoard.h"

Pawn::Pawn(PieceColor color) : Piece(PieceType::PAWN, color) {
}

std::vector<sf::Vector2i> Pawn::getPossibleMoves(int row, int col, const ChessBoard& board) const {
    std::vector<sf::Vector2i> moves;
    int direction = isWhite() ? -1 : 1;

    if (board.getPieceAt(row + direction, col)->isEmpty()) {
        moves.push_back(sf::Vector2i(row + direction, col));
        if ((isWhite() && row == 6) || (isBlack() && row == 1)) {
            if (board.getPieceAt(row + 2 * direction, col)->isEmpty()) {
                moves.push_back(sf::Vector2i(row + 2 * direction, col));
            }
        }
    }

    for (int offset : {-1, 1}) {
        int newCol = col + offset;
        if (newCol >= 0 && newCol < 8) {
            const Piece* target = board.getPieceAt(row + direction, newCol);
            if (!target->isEmpty() && target->getColor() != color) {
                moves.push_back(sf::Vector2i(row + direction, newCol));
            }
        }
    }

    int enPassantCol = board.getEnPassantCol();
    int enPassantRow = board.getEnPassantRow();
    if (enPassantCol != -1) {
        if ((isWhite() && row == 3) || (isBlack() && row == 4)) {
            if (abs(col - enPassantCol) == 1) {
                int targetRow = row + direction;
                moves.push_back(sf::Vector2i(targetRow, enPassantCol));
            }
        }
    }

    return moves;
}