/**
 * @file game_screen.h
 * @brief Contains the GameScreen class definition
 * @author Mateusz Sarwa
 * @date 2024-04-07
 * This header defines the main game screen for a chess application,
 * managing game state, UI, and game logic.
 */
#pragma once

#include "Screen.h"
#include "Button.h"
#include "ChessTimer.h"
#include "PromotionPopup.h"
#include "MoveHistoryPanel.h"
#include "ChessBoard.h"
#include "BoardView.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ApplicationManager.h"

 /**
  * @class GameScreen
  * @brief Manages the main game screen and chess game logic
  *
  * Responsible for:
  * - Rendering the chess board and UI elements
  * - Handling player interactions
  * - Managing game state
  * - Tracking move history and game progression
  */
class GameScreen : public Screen {
private:
    // UI Components
    sf::Font font;  ///< Font used for rendering text
    sf::RectangleShape background;  ///< Background of the game screen
    Button backButton;  ///< Button to return to previous screen
    Button resetButton;  ///< Button to reset the game
    Button undoButton;  ///< Button to undo the last move

    // Game Components
    ChessBoard chessBoard;        ///< Game board model
    BoardView boardView;          ///< Visual representation of the board
    ChessTimer whiteTimer;        ///< Timer for white player
    ChessTimer blackTimer;        ///< Timer for black player
    MoveHistoryPanel historyPanel; ///< Panel showing move history

    // Game State
    bool isPieceSelected;         ///< Flag indicating if a piece is currently selected
    sf::Vector2i selectedPiecePos; ///< Position of the selected piece
    bool gameOver;                ///< Flag indicating if the game has ended
    bool currentPlayer;           ///< Current player (true = white, false = black)

    int whitePlayerTime;  ///< Remaining time for white player
    int blackPlayerTime;  ///< Remaining time for black player

    PromotionPopup promotionPopup;  ///< Popup for piece promotion
    sf::Vector2i promotionSquare;   ///< Coordinates of promotion square

    // Last move tracking
    int lastMoveFromRow;  ///< Row of the piece before last move
    int lastMoveFromCol;  ///< Column of the piece before last move

    /**
     * @struct CapturedPieceInfo
     * @brief Stores information about a captured piece
     */
    struct CapturedPieceInfo {
        PieceType capturedType;  ///< Type of the captured piece
        PieceColor capturedColor;  ///< Color of the captured piece
    };
    CapturedPieceInfo capturedPieceInfo;  ///< Information about the most recently captured piece

    ApplicationManager* appManager;  ///< Pointer to the application manager

    // Popup-related members
    bool showPopup;  ///< Flag to show/hide popup
    sf::RectangleShape popupBackground;  ///< Background for popup
    sf::Text popupText;  ///< Text displayed in popup
    Button popupOkButton;  ///< OK button for popup
    std::string popupMessage;  ///< Message to display in popup
    sf::Color popupColor;  ///< Color of the popup

    /**
     * @brief Handles click events on the chess board
     * @param mousePos Position of the mouse click
     */
    void handleBoardClick(const sf::Vector2i& mousePos);

    /**
     * @brief Executes a move on the chess board
     * @param fromRow Source row of the piece
     * @param fromCol Source column of the piece
     * @param toRow Destination row
     * @param toCol Destination column
     */
    void makeMove(int fromRow, int fromCol, int toRow, int toCol);

    /**
     * @brief Checks if a piece needs promotion
     * @param row Row of the piece
     * @param col Column of the piece
     * @return bool True if promotion is needed, false otherwise
     */
    bool needsPromotion(int row, int col);

    /**
     * @brief Generates algebraic notation for a move
     * @param fromRow Source row of the piece
     * @param fromCol Source column of the piece
     * @param toRow Destination row
     * @param toCol Destination column
     * @return std::string Algebraic notation of the move
     */
    std::string generateMoveNotation(int fromRow, int fromCol, int toRow, int toCol);

    /**
     * @brief Generates algebraic notation for a promotion move
     * @param fromRow Source row of the piece
     * @param fromCol Source column of the piece
     * @param toRow Destination row
     * @param toCol Destination column
     * @param promotedTo Type of piece promoted to
     * @return std::string Algebraic notation of the promotion move
     */
    std::string generatePromotionNotation(int fromRow, int fromCol, int toRow, int toCol, PieceType promotedTo);

    /**
     * @brief Checks and updates the current game state
     */
    void checkGameState();

    /**
     * @brief Undoes the last move
     */
    void undoLastMove();

    /**
     * @brief Updates the background size based on window dimensions
     */
    void updateBackgroundSize();

    /**
     * @brief Displays a popup window indicating game result
     * @param message Message to display in the popup
     * @param color Color of the popup
     */
    void showPopupWin(const std::string& message, sf::Color color);

    /**
     * @brief Hides the game result popup
     */
    void hidePopup();

public:
    /**
     * @brief Constructor for GameScreen
     * @param win Reference to the application render window
     * @param manager Pointer to the ApplicationManager (optional)
     */
    GameScreen(sf::RenderWindow& win, ApplicationManager* manager = nullptr);

    /**
     * @brief Called when entering the game screen
     * Initializes game state and resources
     */
    virtual void onEnter() override;

    /**
     * @brief Called when exiting the game screen
     * Cleans up resources and saves game state
     */
    virtual void onExit() override;

    /**
     * @brief Handles input events for the game screen
     * @param event SFML event to process
     * @return std::string Name of the next screen (if screen change is needed)
     */
    virtual std::string handleEvent(const sf::Event& event) override;

    /**
     * @brief Updates game state
     * Called every frame to update game logic
     */
    virtual void update() override;

    /**
     * @brief Renders the game screen
     * Draws all game elements and UI
     */
    virtual void render() override;

    /**
     * @brief Resets the game to its initial state
     */
    void resetGame();

    /**
     * @brief Sets the initial time for both players
     * @param whiteTime Initial time for white player in seconds
     * @param blackTime Initial time for black player in seconds
     */
    void setPlayerTimes(int whiteTime, int blackTime);
};