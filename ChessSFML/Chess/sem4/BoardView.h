/**
 * @file BoardView.h
 * @brief Class for rendering and handling the chess board view
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "ChessBoard.h"
#include <functional>
#include <vector>

 /**
  * @class BoardView
  * @brief Manages the visual representation of the chess board and pieces
  *
  * This class is responsible for rendering the chess board, pieces,
  * handling highlighting of selected pieces and possible moves,
  * and converting between screen and board coordinates.
  */
class BoardView {
private:
    /**
     * @brief Pointer to the rendering window
     */
    sf::RenderWindow* window;

    /**
     * @brief Texture for the chess board
     */
    sf::Texture boardTexture;

    /**
     * @brief Sprite for rendering the chess board
     */
    sf::Sprite boardSprite;

    /**
     * @brief Array of textures for all chess pieces
     */
    sf::Texture piecesTextures[12];

    /**
     * @brief Scale factors for each piece
     */
    float pieceScales[12];

    /**
     * @brief Highlight shape for the selected piece
     */
    sf::RectangleShape selectedPieceHighlight;

    /**
     * @brief Highlight shape for possible moves
     */
    sf::RectangleShape possibleMoveHighlight;

    /**
     * @brief List of possible moves for the currently selected piece
     */
    std::vector<sf::Vector2i> possibleMoves;

    /**
     * @brief Reference to the chess board model
     */
    const ChessBoard& board;

    /**
     * @brief Size of a single square on the board
     */
    int squareSize;

    /**
     * @brief Position of the board on the screen
     */
    sf::Vector2f boardPosition;

public:
    /**
     * @brief Constructor
     * @param window Reference to the rendering window
     * @param board Reference to the chess board model
     */
    BoardView(sf::RenderWindow& window, const ChessBoard& board);

    /**
     * @brief Renders the chess board and pieces to the window
     */
    void render();

    /**
     * @brief Converts screen coordinates to board coordinates
     * @param screenPos Position on the screen
     * @return Position on the chess board (row, column)
     */
    sf::Vector2i getBoardPosition(const sf::Vector2i& screenPos) const;

    /**
     * @brief Converts board coordinates to screen coordinates
     * @param row Row on the chess board
     * @param col Column on the chess board
     * @return Position on the screen
     */
    sf::Vector2f getScreenPosition(int row, int col) const;

    /**
     * @brief Highlights the selected piece
     * @param row Row of the selected piece
     * @param col Column of the selected piece
     */
    void highlightSelectedPiece(int row, int col);

    /**
     * @brief Clears all highlights from the board
     */
    void clearHighlights();

    /**
     * @brief Sets and highlights possible moves for the selected piece
     * @param moves Vector of possible move positions
     */
    void setPossibleMoves(const std::vector<sf::Vector2i>& moves);

    /**
     * @brief Gets the width of the board
     * @return Width of the board in pixels
     */
    float getBoardWidth() const;

    /**
     * @brief Gets the height of the board
     * @return Height of the board in pixels
     */
    float getBoardHeight() const;

    /**
     * @brief Gets the center position of the board
     * @return Center position of the board
     */
    sf::Vector2f getBoardCenter() const;

    /**
     * @brief Gets the texture for a specific piece
     * @param index Index of the piece texture
     * @return Reference to the piece texture
     */
    const sf::Texture& getPieceTexture(int index) const;
};