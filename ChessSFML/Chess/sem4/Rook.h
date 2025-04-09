/**
 * @file rook.h
 * @brief Contains the Rook class definition for a chess game
 * @author Mateusz Sarwa
 * @date 2024-04-07
 * This header defines the Rook piece, which inherits from the base Piece class
 * and implements its specific movement rules.
 */
#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Piece.h"

 // Forward declaration
class ChessBoard;

/**
 * @class Rook
 * @brief Represents a Rook piece in a chess game
 *
 * The Rook can move any number of squares along a rank (horizontal) or file (vertical),
 * but cannot move diagonally. It plays a crucial role in castling.
 */
class Rook : public Piece {
public:
    /**
     * @brief Constructor for a Rook piece
     * @param color The color of the Rook (WHITE or BLACK)
     *
     * Initializes a Rook with the specified color and sets its type to ROOK
     */
    Rook(PieceColor color);

    /**
     * @brief Calculate all possible moves for the Rook
     *
     * Determines all valid moves the Rook can make from its current position
     * on the chess board, considering:
     * - Movement along ranks (horizontal)
     * - Movement along files (vertical)
     * - Blocking by other pieces
     * - Board boundaries
     *
     * @param row Current row of the Rook
     * @param col Current column of the Rook
     * @param board Reference to the current chess board state
     * @return std::vector<sf::Vector2i> List of possible move coordinates
     */
    std::vector<sf::Vector2i> getPossibleMoves(int row, int col, const ChessBoard& board) const override;
};