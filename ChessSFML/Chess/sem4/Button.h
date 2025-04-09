#pragma once
#include <SFML/Graphics.hpp>
#include <string>
/**
 * The Button class represents an interactive button in the user interface.
 * It allows displaying text, responding to mouse hover and clicks.
 */
class Button {
private:
    sf::RectangleShape shape;     // Button shape
    sf::Text text;                // Button text
    sf::Font font;                // Text font
    bool isHovered;               // Whether the mouse is over the button
    sf::Color idleColor;          // Button color in idle state
    sf::Color hoverColor;         // Button color when hovered
public:
    /**
     * Button constructor.
     * @param x X position of the button
     * @param y Y position of the button
     * @param width Button width
     * @param height Button height
     * @param buttonText Text displayed on the button
     * @param fontSize Font size (default 18)
     */
    Button(float x, float y, float width, float height, const std::string& buttonText, unsigned int fontSize = 18);
    /**
     * Sets the font for the button text.
     * @param newFont Font to set
     */
    void setFont(const sf::Font& newFont);
    /**
     * Sets the button position.
     * @param x New X position
     * @param y New Y position
     */
    void setPosition(float x, float y);
    /**
     * Sets the button colors.
     * @param idle Color in idle state
     * @param hover Color when hovered
     */
    void setColors(const sf::Color& idle, const sf::Color& hover);
    /**
     * Sets the button text color.
     * @param color Text color to set
     */
    void setTextColor(const sf::Color& color);
    /**
     * Checks if a point is inside the button.
     * @param point Point to check
     * @return true if the point is inside the button, false otherwise
     */
    bool contains(const sf::Vector2f& point) const;
    /**
     * Checks if the button was clicked.
     * @param mousePos Mouse click position
     * @return true if the button was clicked, false otherwise
     */
    bool isClicked(const sf::Vector2i& mousePos) const;
    /**
     * Updates the button state based on mouse position.
     * @param mousePos Current mouse position
     */
    void update(const sf::Vector2i& mousePos);
    /**
     * Renders the button in the window.
     * @param window Window in which to render the button
     */
    void render(sf::RenderWindow& window);
    /**
     * Sets new text on the button.
     * @param newText New text to display
     */
    void setText(const std::string& newText);
    /**
     * Sets the text style.
     * @param style Text style (e.g., sf::Text::Bold, sf::Text::Italic)
     */
    void setTextStyle(sf::Uint32 style) {
        text.setStyle(style);
    }
};