/**
 * @file ChessBoard.h
 * @brief Class representing a chess board and managing chess game logic
 * @author Mateusz Sarwa
 * @date 2025-04-07
 */

#pragma once
#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Piece.h"

 /**
  * @class ChessBoard
  * @brief Manages the chess board state, piece positions, and chess game rules
  *
  * This class implements chess game logic, handles piece movements, validates moves,
  * and supports special rules like castling, en passant, and pawn promotion.
  */
class ChessBoard {
public:
    // Delete default copy constructor
    /**
     * @brief Copy constructor is deleted due to the use of unique_ptr
     */
    ChessBoard(const ChessBoard&) = delete;

    /**
     * @brief Assignment operator is deleted due to the use of unique_ptr
     */
    ChessBoard& operator=(const ChessBoard&) = delete;
private:
    /**
     * @brief Two-dimensional array storing chess pieces on the board
     *
     * Each position on the board can contain a pointer to a piece or nullptr
     * if the square is empty.
     */
    std::unique_ptr<Piece> board[8][8];

    // Additional game states
    /**
     * @brief Flag indicating whether the white king has moved (relevant for castling)
     */
    bool whiteKingMoved;

    /**
     * @brief Flag indicating whether the black king has moved (relevant for castling)
     */
    bool blackKingMoved;

    /**
     * @brief Flag indicating whether the left white rook has moved (relevant for castling)
     */
    bool whiteRook1Moved;

    /**
     * @brief Flag indicating whether the right white rook has moved (relevant for castling)
     */
    bool whiteRook2Moved;

    /**
     * @brief Flag indicating whether the left black rook has moved (relevant for castling)
     */
    bool blackRook1Moved;

    /**
     * @brief Flag indicating whether the right black rook has moved (relevant for castling)
     */
    bool blackRook2Moved;

    /**
     * @brief Column for en passant capture (-1 if unavailable)
     */
    int enPassantCol;

    /**
     * @brief Row for en passant capture
     */
    int enPassantRow;

    // Helper methods
    /**
     * @brief Checks if the given position is within the board boundaries
     * @param row Row number (0-7)
     * @param col Column number (0-7)
     * @return true if the position is valid, false otherwise
     */
    bool isValidPosition(int row, int col) const;

    /**
     * @brief Checks if the piece at the given position belongs to the current player
     * @param row Row number
     * @param col Column number
     * @param isWhiteTurn Whether it's white's turn
     * @return true if the piece belongs to the current player, false otherwise
     */
    bool isPieceOfCurrentPlayer(int row, int col, bool isWhiteTurn) const;

    // Check-related verifications
    /**
     * @brief Checks if the king of the given color is in check
     * @param color Color of the king to check
     * @return true if the king is in check, false otherwise
     */
    bool isKingInCheck(PieceColor color) const;

    /**
     * @brief Checks if a move would expose the king to attack
     * @param fromRow Starting row
     * @param fromCol Starting column
     * @param toRow Target row
     * @param toCol Target column
     * @param isWhiteTurn Whether it's white's turn
     * @return true if the move would expose the king, false otherwise
     */
    bool wouldMoveExposeKing(int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn) const;

    /**
     * @brief Checks if the king can castle kingside (short castling)
     * @param isWhite Whether we're checking for the white king
     * @return true if castling is possible, false otherwise
     */
    bool canCastleKingside(bool isWhite) const;

    /**
     * @brief Checks if the king can castle queenside (long castling)
     * @param isWhite Whether we're checking for the white king
     * @return true if castling is possible, false otherwise
     */
    bool canCastleQueenside(bool isWhite) const;

    /**
     * @brief Checks if the path between two positions is clear of pieces
     * @param startRow Starting row
     * @param startCol Starting column
     * @param endRow Ending row
     * @param endCol Ending column
     * @return true if the path is clear, false otherwise
     */
    bool isPathClear(int startRow, int startCol, int endRow, int endCol) const;

    /**
     * @brief Checks if a path is under attack by opponent pieces
     * @param row Row of the path
     * @param startCol Starting column of the path
     * @param endCol Ending column of the path
     * @param kingColor Color of the king
     * @return true if the path is under attack, false otherwise
     */
    bool isPathUnderAttack(int row, int startCol, int endCol, PieceColor kingColor) const;
public:
    /**
     * @brief Default constructor, initializes an empty chess board
     */
    ChessBoard();

    /**
     * @brief Resets the board to the initial piece arrangement
     */
    void resetBoard();

    /**
     * @brief Returns a const pointer to the piece at the given position
     * @param row Row number
     * @param col Column number
     * @return Const pointer to the piece or nullptr if the square is empty
     */
    const Piece* getPieceAt(int row, int col) const;

    /**
     * @brief Returns a pointer to the piece at the given position
     * @param row Row number
     * @param col Column number
     * @return Pointer to the piece or nullptr if the square is empty
     */
    Piece* getPieceAt(int row, int col);

    /**
     * @brief Places a piece at the given position
     * @param row Row number
     * @param col Column number
     * @param piece Pointer to the piece to be placed
     */
    void setPieceAt(int row, int col, std::unique_ptr<Piece> piece);

    /**
     * @brief Removes a piece from the given position and returns it
     * @param row Row number
     * @param col Column number
     * @return Pointer to the removed piece or nullptr if the square was empty
     */
    std::unique_ptr<Piece> removePieceAt(int row, int col);

    /**
     * @brief Returns a list of possible moves for the piece at the given position
     * @param row Row number
     * @param col Column number
     * @return Vector of positions where the piece can move
     */
    std::vector<sf::Vector2i> getPossibleMoves(int row, int col) const;

    /**
     * @brief Executes a piece movement
     * @param fromRow Starting row
     * @param fromCol Starting column
     * @param toRow Target row
     * @param toCol Target column
     * @return true if the move was executed, false if the move is invalid
     */
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);

    /**
     * @brief Promotes a pawn to another piece type
     * @param row Pawn's row
     * @param col Pawn's column
     * @param newType New piece type
     */
    void promotePawn(int row, int col, PieceType newType);

    /**
     * @brief Checks if there is a checkmate
     * @param isWhiteTurn Whether we're checking for the white player
     * @return true if there is a checkmate, false otherwise
     */
    bool isCheckmate(bool isWhiteTurn) const;

    /**
     * @brief Checks if there is a stalemate
     * @param isWhiteTurn Whether we're checking for the white player
     * @return true if there is a stalemate, false otherwise
     */
    bool isStalemate(bool isWhiteTurn) const;

    /**
     * @brief Checks if the player's king is in check
     * @param isWhitePlayer Whether we're checking for the white player
     * @return true if the king is in check, false otherwise
     */
    bool isInCheck(bool isWhitePlayer) const;

    /**
     * @brief Returns the column where en passant capture is possible
     * @return Column number or -1 if en passant is unavailable
     */
    int getEnPassantCol() const { return enPassantCol; };

    /**
     * @brief Returns the row where en passant capture is possible
     * @return Row number
     */
    int getEnPassantRow() const { return enPassantRow; };
};