/**
 * @file MoveHistoryPanel.h
 * @brief Classes for managing chess move history and display
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Piece.h" // Include for access to PieceType and PieceColor

 /**
  * @struct ChessMove
  * @brief Represents a chess move with all its properties
  *
  * This structure stores all information about a chess move, including
  * its algebraic notation, source and destination coordinates, captured pieces,
  * special moves like castling, en passant, and promotion.
  */
struct ChessMove {
    /**
     * @brief Algebraic notation of the move (e.g., "e4", "Nxf3+")
     */
    std::string notation;

    /**
     * @brief Flag indicating if this is a white player's move
     */
    bool isWhiteMove;

    /**
     * @brief Flag indicating if the move puts the opponent in check
     */
    bool isCheck;

    /**
     * @brief Flag indicating if the move results in checkmate
     */
    bool isCheckmate;

    /**
     * @brief Type of the captured piece (NONE if no capture)
     */
    PieceType capturedPieceType;

    /**
     * @brief Color of the captured piece
     */
    PieceColor capturedPieceColor;

    /**
     * @brief Flag indicating if a piece was captured during this move
     */
    bool wasPieceCaptured;

    /**
     * @brief Flag indicating if this move included a pawn promotion
     */
    bool wasPromotion;

    /**
     * @brief Source row of the moved piece
     */
    int sourceRow;

    /**
     * @brief Source column of the moved piece
     */
    int sourceCol;

    /**
     * @brief Destination row of the moved piece
     */
    int destRow;

    /**
     * @brief Destination column of the moved piece
     */
    int destCol;

    /**
     * @brief Flag indicating if the move was an en passant capture
     */
    bool wasEnPassant;

    /**
     * @brief Row of the pawn captured via en passant
     */
    int enPassantCapturedRow;

    /**
     * @brief Column of the pawn captured via en passant
     */
    int enPassantCapturedCol;

    /**
     * @brief Flag indicating if the move was a castling move
     */
    bool wasCastling;

    /**
     * @brief Flag indicating if the castling was kingside (true) or queenside (false)
     */
    bool wasKingsideCastling;

    /**
     * @brief Initial column of the rook during castling
     */
    int rookFromCol;

    /**
     * @brief Final column of the rook after castling
     */
    int rookToCol;

    /**
     * @brief Constructor
     * @param note Algebraic notation of the move
     * @param white Whether it's a white player's move
     * @param check Whether the move puts the opponent in check
     * @param mate Whether the move results in checkmate
     * @param capturedType Type of the captured piece (if any)
     * @param capturedColor Color of the captured piece (if any)
     * @param promotion Whether the move includes a pawn promotion
     */
    ChessMove(const std::string& note, bool white, bool check = false, bool mate = false,
        PieceType capturedType = PieceType::NONE,
        PieceColor capturedColor = PieceColor::NONE,
        bool promotion = false)
        : notation(note), isWhiteMove(white), isCheck(check), isCheckmate(mate),
        capturedPieceType(capturedType), capturedPieceColor(capturedColor),
        wasPieceCaptured(capturedType != PieceType::NONE), wasPromotion(promotion),
        sourceRow(-1), sourceCol(-1), destRow(-1), destCol(-1),
        wasEnPassant(false), enPassantCapturedRow(-1), enPassantCapturedCol(-1),
        wasCastling(false), wasKingsideCastling(false), rookFromCol(-1), rookToCol(-1)
    {
    }

    /**
     * @brief Sets the source coordinates of the moved piece
     * @param row Source row
     * @param col Source column
     */
    void setSourceCoords(int row, int col) {
        sourceRow = row;
        sourceCol = col;
    }

    /**
     * @brief Sets the destination coordinates of the moved piece
     * @param row Destination row
     * @param col Destination column
     */
    void setDestCoords(int row, int col) {
        destRow = row;
        destCol = col;
    }

    /**
     * @brief Sets information about an en passant capture
     * @param wasEnPassant Whether the move was an en passant capture
     * @param row Row of the captured pawn
     * @param col Column of the captured pawn
     */
    void setEnPassantCapture(bool wasEnPassant, int row, int col) {
        this->wasEnPassant = wasEnPassant;
        this->enPassantCapturedRow = row;
        this->enPassantCapturedCol = col;
    }

    /**
     * @brief Gets whether the move was an en passant capture
     * @return true if the move was an en passant capture, false otherwise
     */
    bool getWasEnPassant() const { return wasEnPassant; }

    /**
     * @brief Gets whether the move was a castling
     * @return true if the move was a castling, false otherwise
     */
    bool getWasCastling() const { return wasCastling; }

    /**
     * @brief Gets whether the castling was kingside
     * @return true if kingside castling, false if queenside
     */
    bool getWasKingsideCastling() const { return wasKingsideCastling; }

    /**
     * @brief Gets the initial column of the rook during castling
     * @return Initial column of the rook
     */
    int getRookFromCol() const { return rookFromCol; }

    /**
     * @brief Gets the final column of the rook after castling
     * @return Final column of the rook
     */
    int getRookToCol() const { return rookToCol; }

    /**
     * @brief Sets castling information
     * @param kingsideCastling Whether it was a kingside castling
     * @param fromCol Initial column of the rook
     * @param toCol Final column of the rook
     */
    void setCastling(bool kingsideCastling, int fromCol, int toCol) {
        this->wasCastling = true;
        this->wasKingsideCastling = kingsideCastling;
        this->rookFromCol = fromCol;
        this->rookToCol = toCol;
    }

    /**
     * @brief Gets the type of the captured piece
     * @return Type of the captured piece, or NONE if no piece was captured
     */
    PieceType getCapturedPieceType() const { return capturedPieceType; }

    /**
     * @brief Gets the color of the captured piece
     * @return Color of the captured piece
     */
    PieceColor getCapturedPieceColor() const { return capturedPieceColor; }

    /**
     * @brief Gets whether a piece was captured
     * @return true if a piece was captured, false otherwise
     */
    bool getWasPieceCaptured() const { return wasPieceCaptured; }

    /**
     * @brief Gets whether the move included a pawn promotion
     * @return true if the move included a promotion, false otherwise
     */
    bool getWasPromotion() const { return wasPromotion; }
};

/**
 * @class MoveHistoryPanel
 * @brief UI panel for displaying chess move history
 *
 * This class manages the visual display of chess move history,
 * including scrolling functionality to navigate through long games.
 */
class MoveHistoryPanel {
private:
    /**
     * @brief Pointer to the rendering window
     */
    sf::RenderWindow* window;

    /**
     * @brief Background shape for the panel
     */
    sf::RectangleShape background;

    /**
     * @brief Font used for text display
     */
    sf::Font font;

    /**
     * @brief Title text for the panel
     */
    sf::Text titleText;

    /**
     * @brief Position of the panel on the screen
     */
    sf::Vector2f position;

    /**
     * @brief Size of the panel
     */
    sf::Vector2f size;

    /**
     * @brief List of all moves in the game
     */
    std::vector<ChessMove> moves;

    /**
     * @brief Scrollbar background
     */
    sf::RectangleShape scrollbar;

    /**
     * @brief Scrollbar thumb (the draggable part)
     */
    sf::RectangleShape scrollbarThumb;

    /**
     * @brief Current scroll offset (for displaying moves)
     */
    int scrollOffset;

    /**
     * @brief Maximum number of moves visible at once
     */
    int maxVisibleMoves;

    /**
     * @brief Flag indicating if the scrollbar is being dragged
     */
    bool isDraggingScrollbar;

public:
    /**
     * @brief Constructor
     * @param win Reference to the rendering window
     * @param pos Position of the panel on the screen
     * @param sz Size of the panel
     */
    MoveHistoryPanel(sf::RenderWindow& win, const sf::Vector2f& pos, const sf::Vector2f& sz);

    /**
     * @brief Renders the move history panel to the window
     */
    void render();

    /**
     * @brief Adds a new move to the history
     * @param move The chess move to add
     */
    void addMove(const ChessMove& move);

    /**
     * @brief Clears the move history
     */
    void clear();

    /**
     * @brief Handles UI events (e.g., scrolling, clicking)
     * @param event The SFML event to handle
     */
    void handleEvent(const sf::Event& event);

    /**
     * @brief Gets the list of all moves
     * @return Constant reference to the move list
     */
    const std::vector<ChessMove>& getMoves() const;

    /**
     * @brief Gets the last move made
     * @return Constant reference to the last move
     */
    const ChessMove& getLastMove() const;

    /**
     * @brief Removes the last move from history
     *
     * Useful for implementing undo functionality.
     */
    void removeLastMove();

private:
    /**
     * @brief Scrolls the move history by the specified amount
     * @param delta Amount to scroll by (positive for down, negative for up)
     */
    void scroll(int delta);
};