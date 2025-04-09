/**
 * @file King.h
 * @brief Class representing a king chess piece
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Piece.h"

class ChessBoard;

/**
 * @class King
 * @brief Represents a king piece in chess
 *
 * The king can move one square in any direction (horizontally, vertically, or diagonally).
 * It also has a special move called castling, which involves the rook.
 * The king cannot move to a square that is under attack by an opponent's piece.
 */
class King : public Piece {
public:
    /**
     * @brief Constructor
     * @param color The color of the king (WHITE or BLACK)
     */
    King(PieceColor color);

    /**
     * @brief Gets all possible moves for this king
     * @param row Current row position of the king
     * @param col Current column position of the king
     * @param board Reference to the chess board
     * @return Vector of possible destination coordinates
     *
     * Calculates all valid moves for the king from the current position,
     * including one square in any direction and castling moves if available.
     * Squares under attack by opponent pieces are excluded from the results.
     */
    std::vector<sf::Vector2i> getPossibleMoves(int row, int col, const ChessBoard& board) const override;
};