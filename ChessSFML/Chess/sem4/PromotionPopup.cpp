#include "PromotionPopup.h"

PromotionPopup::PromotionPopup(sf::RenderWindow& window, sf::Font& font, BoardView& boardView)
    : window(window), font(font), isActive(false), selectedPiece(-1) {

    background.setSize(sf::Vector2f(300, 400));
    background.setFillColor(sf::Color(20, 30, 70, 230));
    background.setOutlineThickness(3);
    background.setOutlineColor(sf::Color::White);

    pieceHighlight.setSize(sf::Vector2f(75, 75));
    pieceHighlight.setFillColor(sf::Color(255, 255, 0, 128));

    title.setFont(font);
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::White);
    title.setString("Choose piece for promotion:");

    okButton.setSize(sf::Vector2f(100, 40));
    okButton.setFillColor(sf::Color(50, 80, 150));
    okButton.setOutlineThickness(2);
    okButton.setOutlineColor(sf::Color::White);

    okText.setFont(font);
    okText.setCharacterSize(18);
    okText.setFillColor(sf::Color::White);
    okText.setString("OK");

    whiteTextures[0] = &boardView.getPieceTexture(1);
    whiteTextures[1] = &boardView.getPieceTexture(2);
    whiteTextures[2] = &boardView.getPieceTexture(3);
    whiteTextures[3] = &boardView.getPieceTexture(4);

    blackTextures[0] = &boardView.getPieceTexture(7);
    blackTextures[1] = &boardView.getPieceTexture(8);
    blackTextures[2] = &boardView.getPieceTexture(9);
    blackTextures[3] = &boardView.getPieceTexture(10);
}

void PromotionPopup::show(bool forWhitePiece) {
    isActive = true;
    isWhite = forWhitePiece;
    selectedPiece = -1;

    sf::Vector2u windowSize = window.getSize();
    float popupWidth = 300.0f;
    float popupHeight = 400.0f;

    background.setPosition((windowSize.x - popupWidth) / 2, (windowSize.y - popupHeight) / 2);

    sf::FloatRect textBounds = title.getLocalBounds();
    title.setPosition(
        (windowSize.x - textBounds.width) / 2,
        (windowSize.y - popupHeight) / 2 + 20
    );

    sf::Vector2f popupPos = background.getPosition();

    const sf::Texture** textures = isWhite ? whiteTextures : blackTextures;

    float xPosition = popupPos.x + 150.0f - 32.5f;

    for (int i = 0; i < 4; i++) {
        pieceSprites[i].setTexture(*textures[i]);
        float scale = 65.0f / static_cast<float>(textures[i]->getSize().x);
        pieceSprites[i].setScale(scale, scale);
        pieceSprites[i].setPosition(xPosition, popupPos.y + 100 + i * 65);
    }

    okButton.setPosition(
        (windowSize.x - 100) / 2,
        popupPos.y + popupHeight - 40
    );

    sf::FloatRect okBounds = okButton.getGlobalBounds();
    sf::FloatRect okTextBounds = okText.getLocalBounds();
    okText.setPosition(
        okBounds.left + (okBounds.width - okTextBounds.width) / 2,
        okBounds.top + (okBounds.height - okTextBounds.height) / 2 - 5
    );
}

PieceType PromotionPopup::handleEvent(const sf::Event& event) {
    if (!isActive) return PieceType::NONE;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

        for (int i = 0; i < 4; i++) {
            sf::FloatRect pieceBounds = pieceSprites[i].getGlobalBounds();
            pieceBounds.left -= 40;
            pieceBounds.width += 80;

            if (pieceBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                selectedPiece = i;
                break;
            }
        }

        sf::FloatRect okBounds = okButton.getGlobalBounds();
        if (okBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            if (selectedPiece != -1) {
                PieceType chosenType;
                switch (selectedPiece) {
                case 0: chosenType = PieceType::QUEEN; break;
                case 1: chosenType = PieceType::ROOK; break;
                case 2: chosenType = PieceType::BISHOP; break;
                case 3: chosenType = PieceType::KNIGHT; break;
                default: chosenType = PieceType::QUEEN; break;
                }

                hide();

                return chosenType;
            }
        }
    }

    return PieceType::NONE;
}

void PromotionPopup::render() {
    if (!isActive) return;

    window.draw(background);
    window.draw(title);

    for (int i = 0; i < 4; i++) {
        window.draw(pieceSprites[i]);
    }

    if (selectedPiece != -1) {
        sf::FloatRect bounds = pieceSprites[selectedPiece].getGlobalBounds();

        pieceHighlight.setSize(sf::Vector2f(bounds.width + 20, bounds.height + 20));
        pieceHighlight.setPosition(bounds.left - 10, bounds.top - 10);
        pieceHighlight.setFillColor(sf::Color::Transparent);
        pieceHighlight.setOutlineThickness(4.0f);
        pieceHighlight.setOutlineColor(sf::Color(255, 255, 0, 220));

        window.draw(pieceHighlight);
    }

    window.draw(okButton);
    window.draw(okText);
}

void PromotionPopup::setPieceTextures(const sf::Texture& queenTexture, const sf::Texture& rookTexture,
    const sf::Texture& bishopTexture, const sf::Texture& knightTexture) {
    pieceSprites[0].setTexture(queenTexture);
    float scale = 75.0f / static_cast<float>(queenTexture.getSize().x);
    pieceSprites[0].setScale(scale, scale);

    pieceSprites[1].setTexture(rookTexture);
    scale = 75.0f / static_cast<float>(rookTexture.getSize().x);
    pieceSprites[1].setScale(scale, scale);

    pieceSprites[2].setTexture(bishopTexture);
    scale = 75.0f / static_cast<float>(bishopTexture.getSize().x);
    pieceSprites[2].setScale(scale, scale);

    pieceSprites[3].setTexture(knightTexture);
    scale = 75.0f / static_cast<float>(knightTexture.getSize().x);
    pieceSprites[3].setScale(scale, scale);
}

void PromotionPopup::hide() {
    isActive = false;
    selectedPiece = -1;
}