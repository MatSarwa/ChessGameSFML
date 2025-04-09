#include "BoardView.h"

BoardView::BoardView(sf::RenderWindow& window, const ChessBoard& board)
    : window(&window), board(board), squareSize(75), boardPosition(0, 0),
    possibleMoves() {

    if (!boardTexture.loadFromFile("resources/images/board.png")) {
    }

    float scale = 600.0f / static_cast<float>(boardTexture.getSize().x);
    boardSprite.setTexture(boardTexture);
    boardSprite.setScale(scale, scale);
    boardSprite.setPosition(boardPosition);

    squareSize = 600 / 8;

    if (!piecesTextures[0].loadFromFile("resources/images/king_w.png")) {
    }
    if (!piecesTextures[1].loadFromFile("resources/images/queen_w.png")) {
    }
    if (!piecesTextures[2].loadFromFile("resources/images/rook_w.png")) {
    }
    if (!piecesTextures[3].loadFromFile("resources/images/bishop_w.png")) {
    }
    if (!piecesTextures[4].loadFromFile("resources/images/knight_w.png")) {
    }
    if (!piecesTextures[5].loadFromFile("resources/images/pawn_w.png")) {
    }

    if (!piecesTextures[6].loadFromFile("resources/images/king_b.png")) {
    }
    if (!piecesTextures[7].loadFromFile("resources/images/queen_b.png")) {
    }
    if (!piecesTextures[8].loadFromFile("resources/images/rook_b.png")) {
    }
    if (!piecesTextures[9].loadFromFile("resources/images/bishop_b.png")) {
    }
    if (!piecesTextures[10].loadFromFile("resources/images/knight_b.png")) {
    }
    if (!piecesTextures[11].loadFromFile("resources/images/pawn_b.png")) {
    }

    for (int i = 0; i < 12; i++) {
        sf::Vector2u textureSize = piecesTextures[i].getSize();
        float pieceScale = static_cast<float>(squareSize) / static_cast<float>(textureSize.x);
        pieceScales[i] = pieceScale;
    }

    selectedPieceHighlight.setSize(sf::Vector2f(squareSize, squareSize));
    selectedPieceHighlight.setFillColor(sf::Color(255, 255, 0, 128));

    possibleMoveHighlight.setSize(sf::Vector2f(squareSize, squareSize));
    possibleMoveHighlight.setFillColor(sf::Color(0, 255, 0, 128));
}

void BoardView::render() {
    window->draw(boardSprite);

    for (const auto& move : possibleMoves) {
        possibleMoveHighlight.setPosition(getScreenPosition(move.x, move.y));
        window->draw(possibleMoveHighlight);
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Piece* piece = board.getPieceAt(row, col);
            if (piece && !piece->isEmpty()) {
                int pieceValue = piece->toInt();
                sf::Sprite pieceSprite;

                int textureIndex = -1;
                if (pieceValue > 0) {
                    switch (pieceValue) {
                    case 4: textureIndex = 0; break;
                    case 5: textureIndex = 1; break;
                    case 1: textureIndex = 2; break;
                    case 3: textureIndex = 3; break;
                    case 2: textureIndex = 4; break;
                    case 6: textureIndex = 5; break;
                    }
                }
                else if (pieceValue < 0) {
                    switch (pieceValue) {
                    case -4: textureIndex = 6; break;
                    case -5: textureIndex = 7; break;
                    case -1: textureIndex = 8; break;
                    case -3: textureIndex = 9; break;
                    case -2: textureIndex = 10; break;
                    case -6: textureIndex = 11; break;
                    }
                }

                if (textureIndex >= 0) {
                    pieceSprite.setTexture(piecesTextures[textureIndex]);
                    pieceSprite.setScale(pieceScales[textureIndex], pieceScales[textureIndex]);

                    sf::FloatRect bounds = pieceSprite.getLocalBounds();
                    sf::Vector2f fieldPos = getScreenPosition(row, col);
                    pieceSprite.setPosition(
                        fieldPos.x + (squareSize - bounds.width * pieceScales[textureIndex]) / 2.0f,
                        fieldPos.y + (squareSize - bounds.height * pieceScales[textureIndex]) / 2.0f
                    );

                    window->draw(pieceSprite);
                }
            }
        }
    }
}

sf::Vector2i BoardView::getBoardPosition(const sf::Vector2i& screenPos) const {
    float x = screenPos.x - boardPosition.x;
    float y = screenPos.y - boardPosition.y;

    if (x < 0 || x >= 8 * squareSize || y < 0 || y >= 8 * squareSize) {
        return sf::Vector2i(-1, -1);
    }

    return sf::Vector2i(static_cast<int>(y / squareSize), static_cast<int>(x / squareSize));
}

sf::Vector2f BoardView::getScreenPosition(int row, int col) const {
    return sf::Vector2f(boardPosition.x + col * squareSize, boardPosition.y + row * squareSize);
}

void BoardView::highlightSelectedPiece(int row, int col) {
    selectedPieceHighlight.setPosition(getScreenPosition(row, col));
}

void BoardView::clearHighlights() {
    possibleMoves.clear();
}

void BoardView::setPossibleMoves(const std::vector<sf::Vector2i>& moves) {
    possibleMoves = moves;
}

sf::Vector2f BoardView::getBoardCenter() const {
    return sf::Vector2f(boardPosition.x + 4 * squareSize, boardPosition.y + 4 * squareSize);
}

float BoardView::getBoardWidth() const {
    return 8 * squareSize;
}

float BoardView::getBoardHeight() const {
    return 8 * squareSize;
}

const sf::Texture& BoardView::getPieceTexture(int index) const {
    return piecesTextures[index];
}