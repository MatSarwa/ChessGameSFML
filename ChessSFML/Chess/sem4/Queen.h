/**
 * @file queen.h
 * @brief Contains the Queen class definition for a chess game
 * @author Mateusz Sarwa
 * @date 2024-04-07
 * This header defines the Queen piece, which inherits from the base Piece class
 * and implements its specific movement rules.
 */
#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Piece.h"

 // Forward declaration
class ChessBoard;

/**
 * @class Queen
 * @brief Represents a Queen piece in a chess game
 *
 * The Queen can move any number of squares along a rank, file, or diagonal,
 * combining the movement capabilities of a rook and a bishop.
 */
class Queen : public Piece {
public:
    /**
     * @brief Constructor for a Queen piece
     * @param color The color of the Queen (WHITE or BLACK)
     *
     * Initializes a Queen with the specified color and sets its type to QUEEN
     */
    Queen(PieceColor color);

    /**
     * @brief Calculate all possible moves for the Queen
     *
     * Determines all valid moves the Queen can make from its current position
     * on the chess board, considering:
     * - Movement along ranks (horizontal)
     * - Movement along files (vertical)
     * - Movement along diagonals
     * - Blocking by other pieces
     * - Board boundaries
     *
     * @param row Current row of the Queen
     * @param col Current column of the Queen
     * @param board Reference to the current chess board state
     * @return std::vector<sf::Vector2i> List of possible move coordinates
     */
    std::vector<sf::Vector2i> getPossibleMoves(int row, int col, const ChessBoard& board) const override;
};