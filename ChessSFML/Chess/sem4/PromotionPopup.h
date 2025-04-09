/**
 * @file PromotionPopup.h
 * @brief Class for displaying and handling pawn promotion UI
 * @author Mateusz Sarwa
 * @date 2024-04-07
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include <functional>
#include "BoardView.h"

 /**
  * @class PromotionPopup
  * @brief Popup UI for selecting a piece during pawn promotion
  *
  * This class manages the display and interaction for pawn promotion,
  * allowing players to select which piece they want to promote their
  * pawn to (Queen, Rook, Bishop, or Knight).
  */
class PromotionPopup {
private:
    /**
     * @brief Reference to the rendering window
     */
    sf::RenderWindow& window;

    /**
     * @brief Reference to the font used for text display
     */
    sf::Font& font;

    /**
     * @brief Background shape for the popup
     */
    sf::RectangleShape background;

    /**
     * @brief Highlight shape for the selected piece
     */
    sf::RectangleShape pieceHighlight;

    /**
     * @brief Sprites for the four promotion options (Queen, Rook, Bishop, Knight)
     */
    sf::Sprite pieceSprites[4];

    /**
     * @brief Title text for the popup
     */
    sf::Text title;

    /**
     * @brief Currently selected piece (-1 = none, 0 = Queen, 1 = Rook, 2 = Bishop, 3 = Knight)
     */
    int selectedPiece;

    /**
     * @brief Shape for the OK/confirm button
     */
    sf::RectangleShape okButton;

    /**
     * @brief Text for the OK/confirm button
     */
    sf::Text okText;

    /**
     * @brief Flag indicating if the popup is currently active/visible
     */
    bool isActive;

    /**
     * @brief Flag indicating if the promotion is for a white pawn
     */
    bool isWhite;

    /**
     * @brief Array of textures for white promotion pieces
     */
    const sf::Texture* whiteTextures[4];

    /**
     * @brief Array of textures for black promotion pieces
     */
    const sf::Texture* blackTextures[4];

public:
    /**
     * @brief Constructor
     * @param window Reference to the rendering window
     * @param font Reference to the font for text display
     * @param boardView Reference to the board view
     */
    PromotionPopup(sf::RenderWindow& window, sf::Font& font, BoardView& boardView);

    /**
     * @brief Shows the promotion popup
     * @param forWhitePiece Whether the promotion is for a white pawn
     *
     * Displays the popup with the appropriate piece textures based on the pawn's color.
     */
    void show(bool forWhitePiece);

    /**
     * @brief Hides the promotion popup
     */
    void hide();

    /**
     * @brief Handles UI events for the popup
     * @param event The SFML event to handle
     * @return The selected piece type, or NONE if selection is not confirmed
     *
     * Processes mouse clicks for selecting pieces and confirming the selection.
     */
    PieceType handleEvent(const sf::Event& event);

    /**
     * @brief Renders the promotion popup to the window
     *
     * Should be called in the game's rendering loop when the popup is active.
     */
    void render();

    /**
     * @brief Checks if the popup is currently visible
     * @return true if the popup is active, false otherwise
     */
    bool isVisible() const { return isActive; }

    /**
     * @brief Sets the textures for the promotion pieces
     * @param queenTexture Texture for the queen
     * @param rookTexture Texture for the rook
     * @param bishopTexture Texture for the bishop
     * @param knightTexture Texture for the knight
     *
     * These textures will be used for displaying the promotion options.
     */
    void setPieceTextures(const sf::Texture& queenTexture, const sf::Texture& rookTexture,
        const sf::Texture& bishopTexture, const sf::Texture& knightTexture);
};