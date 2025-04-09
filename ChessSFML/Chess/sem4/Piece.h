/**
 * @file chess_pieces.h
 * @brief Contains definitions for chess pieces and related enumerations
 * @author Mateusz Sarwa
 * @date 2024-04-07
 * This header defines the base structure for chess pieces, including
 * piece types, colors, and a base Piece class for chess game implementation.
 */
#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

 // Forward declarations
class ChessBoard;

/**
 * @enum PieceType
 * @brief Enumeration of possible chess piece types
 */
enum class PieceType {
    NONE,   ///< Represents an empty or unspecified piece
    ROOK,   ///< Rook piece
    KNIGHT, ///< Knight piece
    BISHOP, ///< Bishop piece
    KING,   ///< King piece
    QUEEN,  ///< Queen piece
    PAWN    ///< Pawn piece
};

/**
 * @enum PieceColor
 * @brief Enumeration of possible piece colors
 */
enum class PieceColor {
    NONE,   ///< Represents an unspecified color
    WHITE,  ///< White pieces
    BLACK   ///< Black pieces
};

/**
 * @class Piece
 * @brief Abstract base class for chess pieces
 *
 * Provides common functionality and interface for all chess pieces
 */
class Piece {
protected:
    PieceType type;    ///< Type of the chess piece
    PieceColor color;  ///< Color of the chess piece
    bool hasMoved;     ///< Flag to track if the piece has moved

public:
    /**
     * @brief Default constructor
     * Creates an empty piece with no type or color
     */
    Piece() : type(PieceType::NONE), color(PieceColor::NONE), hasMoved(false) {}

    /**
     * @brief Parameterized constructor
     * @param type Type of the chess piece
     * @param color Color of the chess piece
     */
    Piece(PieceType type, PieceColor color) : type(type), color(color), hasMoved(false) {}

    /**
     * @brief Virtual destructor
     * Allows proper destruction of derived classes
     */
    virtual ~Piece() = default;

    /**
     * @brief Get the type of the piece
     * @return PieceType Current piece type
     */
    PieceType getType() const { return type; }

    /**
     * @brief Get the color of the piece
     * @return PieceColor Current piece color
     */
    PieceColor getColor() const { return color; }

    /**
     * @brief Check if the piece has moved
     * @return bool True if the piece has moved, false otherwise
     */
    bool getHasMoved() const { return hasMoved; }

    /**
     * @brief Set the moved status of the piece
     * @param moved New moved status
     */
    void setHasMoved(bool moved) { hasMoved = moved; }

    /**
     * @brief Check if the piece is white
     * @return bool True if the piece is white
     */
    bool isWhite() const { return color == PieceColor::WHITE; }

    /**
     * @brief Check if the piece is black
     * @return bool True if the piece is black
     */
    bool isBlack() const { return color == PieceColor::BLACK; }

    /**
     * @brief Check if the piece is empty
     * @return bool True if the piece type is NONE
     */
    bool isEmpty() const { return type == PieceType::NONE; }

    /**
     * @brief Convert piece to an integer representation
     *
     * Provides a numeric value for the piece, with sign indicating color
     * Positive values for white pieces, negative for black pieces
     *
     * @return int Numeric representation of the piece
     */
    int toInt() const {
        int value = 0;
        switch (type) {
        case PieceType::ROOK:   value = 1; break;
        case PieceType::KNIGHT: value = 2; break;
        case PieceType::BISHOP: value = 3; break;
        case PieceType::KING:   value = 4; break;
        case PieceType::QUEEN:  value = 5; break;
        case PieceType::PAWN:   value = 6; break;
        default:                value = 0; break;
        }
        return isWhite() ? value : -value;
    }

    /**
     * @brief Get all possible moves for this piece
     *
     * Pure virtual method to be implemented by derived classes
     *
     * @param row Current row of the piece
     * @param col Current column of the piece
     * @param board Reference to the chess board
     * @return std::vector<sf::Vector2i> List of possible move coordinates
     */
    virtual std::vector<sf::Vector2i> getPossibleMoves(int row, int col, const ChessBoard& board) const = 0;
};

/**
 * @class EmptyPiece
 * @brief Represents an empty square on the chess board
 *
 * Derives from Piece, but has no possible moves
 */
class EmptyPiece : public Piece {
public:
    /**
     * @brief Default constructor
     * Creates an empty piece with no type or color
     */
    EmptyPiece() : Piece(PieceType::NONE, PieceColor::NONE) {}

    /**
     * @brief Get possible moves
     *
     * Always returns an empty vector as an empty piece cannot move
     *
     * @param row Current row (unused)
     * @param col Current column (unused)
     * @param board Chess board reference (unused)
     * @return std::vector<sf::Vector2i> Empty vector
     */
    std::vector<sf::Vector2i> getPossibleMoves(int row, int col, const ChessBoard& board) const override {
        return {}; // Empty square has no moves
    }
};

// Forward declarations for specific piece classes
class Pawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;