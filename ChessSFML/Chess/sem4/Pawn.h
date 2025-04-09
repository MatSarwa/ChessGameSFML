/**
 * @file Pawn.h
 * @brief Class representing a pawn chess piece
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Piece.h"

class ChessBoard;

/**
 * @class Pawn
 * @brief Represents a pawn piece in chess
 *
 * The pawn is unique in several ways: it moves forward but captures diagonally,
 * it can move two squares on its first move, it can capture en passant under
 * specific conditions, and it can be promoted to another piece when it reaches
 * the opposite end of the board.
 */
class Pawn : public Piece {
public:
    /**
     * @brief Constructor
     * @param color The color of the pawn (WHITE or BLACK)
     */
    Pawn(PieceColor color);

    /**
     * @brief Gets all possible moves for this pawn
     * @param row Current row position of the pawn
     * @param col Current column position of the pawn
     * @param board Reference to the chess board
     * @return Vector of possible destination coordinates
     *
     * Calculates all valid moves for the pawn from the current position,
     * including:
     * - Moving one square forward (if unblocked)
     * - Moving two squares forward from starting position (if unblocked)
     * - Capturing diagonally (if opponent piece is present)
     * - En passant captures (if available)
     *
     * Note: The promotion of a pawn is handled separately in the game logic
     * when a pawn reaches the opposite end of the board.
     */
    std::vector<sf::Vector2i> getPossibleMoves(int row, int col, const ChessBoard& board) const override;
};