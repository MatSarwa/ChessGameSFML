/**
 * @file Bishop.h
 * @brief Class representing a bishop chess piece
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Piece.h"

class ChessBoard;

/**
 * @class Bishop
 * @brief Represents a bishop piece in chess
 *
 * The bishop moves any number of vacant squares diagonally in a straight line.
 * It cannot jump over other pieces.
 */
class Bishop : public Piece {
public:
    /**
     * @brief Constructor
     * @param color The color of the bishop (WHITE or BLACK)
     */
    Bishop(PieceColor color);

    /**
     * @brief Gets all possible moves for this bishop
     * @param row Current row position of the bishop
     * @param col Current column position of the bishop
     * @param board Reference to the chess board
     * @return Vector of possible destination coordinates
     *
     * Calculates all valid diagonal moves for the bishop from the current position,
     * taking into account the board boundaries and other pieces.
     */
    std::vector<sf::Vector2i> getPossibleMoves(int row, int col, const ChessBoard& board) const override;
};