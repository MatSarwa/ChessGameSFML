/**
 * @file Knight.h
 * @brief Class representing a knight chess piece
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Piece.h"

class ChessBoard;

/**
 * @class Knight
 * @brief Represents a knight piece in chess
 *
 * The knight moves in an L-shape pattern: two squares in one direction and then
 * one square perpendicular to that direction. It is the only piece that can jump
 * over other pieces on the board.
 */
class Knight : public Piece {
public:
    /**
     * @brief Constructor
     * @param color The color of the knight (WHITE or BLACK)
     */
    Knight(PieceColor color);

    /**
     * @brief Gets all possible moves for this knight
     * @param row Current row position of the knight
     * @param col Current column position of the knight
     * @param board Reference to the chess board
     * @return Vector of possible destination coordinates
     *
     * Calculates all valid L-shaped moves for the knight from the current position.
     * The knight can jump over other pieces, so only the destination square needs
     * to be checked for availability (empty or occupied by an opponent's piece).
     */
    std::vector<sf::Vector2i> getPossibleMoves(int row, int col, const ChessBoard& board) const override;
};