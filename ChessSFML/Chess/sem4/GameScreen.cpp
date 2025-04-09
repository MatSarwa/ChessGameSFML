#include "GameScreen.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

GameScreen::GameScreen(sf::RenderWindow& win, ApplicationManager* manager) : Screen(win),
boardView(win, chessBoard),
backButton(10, boardView.getBoardHeight() + 650, 150, 40, "Return to menu", 16),
resetButton(170, boardView.getBoardHeight() + 650, 150, 40, "Reset game", 16),
undoButton(330, boardView.getBoardHeight() + 650, 150, 40, "Undo move", 16),
whiteTimer(win, sf::Vector2f(boardView.getBoardWidth() + 100, 100), sf::Vector2f(200, 80), true),
blackTimer(win, sf::Vector2f(boardView.getBoardWidth() + 100, 200), sf::Vector2f(200, 80), false),
historyPanel(win, sf::Vector2f(boardView.getBoardWidth() + 100, 300), sf::Vector2f(200, 300)),
isPieceSelected(false),
selectedPiecePos(-1, -1),
gameOver(false),
currentPlayer(true),
showPopup(false),
popupOkButton(0, 0, 100, 40, "OK", 18),
appManager(manager),
promotionPopup(win, font, boardView),
promotionSquare(-1, -1) {


    font.loadFromFile("resources/fonts/arial.ttf");
    
    popupText.setFont(font);
    popupText.setCharacterSize(24);
    popupText.setFillColor(sf::Color::White);

    sf::Color buttonColor(50, 80, 150);
    sf::Color hoverColor(100, 160, 255);

    sf::Color textColor = sf::Color::White;

    sf::Uint32 textStyle = sf::Text::Bold;
    backButton.setTextStyle(textStyle);
    resetButton.setTextStyle(textStyle);
    undoButton.setTextStyle(textStyle);

    backButton.setColors(buttonColor, hoverColor);
    backButton.setFont(font);
    backButton.setTextColor(textColor);

    resetButton.setColors(buttonColor, hoverColor);
    resetButton.setFont(font);
    resetButton.setTextColor(textColor);

    undoButton.setColors(buttonColor, hoverColor);
    undoButton.setFont(font);
    undoButton.setTextColor(textColor);

    popupOkButton.setColors(buttonColor, hoverColor);


    background.setSize(sf::Vector2f(win.getSize().x, win.getSize().y));
    background.setFillColor(sf::Color(0x11, 0x2c, 0x49));


    resetGame();
}

void GameScreen::onEnter() {
    if (appManager) {
        int whiteTime = appManager->getWhitePlayerTime();
        int blackTime = appManager->getBlackPlayerTime();


        whiteTimer.setRemainingTime(whiteTime);
        blackTimer.setRemainingTime(blackTime);
    }

    updateBackgroundSize();
}

void GameScreen::onExit() {}

std::string GameScreen::handleEvent(const sf::Event& event) {

    if (showPopup) {

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            if (popupOkButton.isClicked(mousePos)) {
                hidePopup();
                resetGame();
            }
        }
        else if (event.type == sf::Event::MouseMoved) {

            sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
            popupOkButton.update(mousePos);
        }


        return "";
    }

    if (promotionPopup.isVisible()) {
        PieceType chosenType = promotionPopup.handleEvent(event);

        if (chosenType != PieceType::NONE) {

            int fromRow = lastMoveFromRow;
            int fromCol = lastMoveFromCol;
            int toRow = promotionSquare.x;
            int toCol = promotionSquare.y;

            chessBoard.promotePawn(toRow, toCol, chosenType);


            std::string moveNotation = generatePromotionNotation(fromRow, fromCol, toRow, toCol, chosenType);

            currentPlayer = !currentPlayer;
            bool isCheck = chessBoard.isInCheck(currentPlayer);
            bool isCheckmate = chessBoard.isCheckmate(currentPlayer);
            currentPlayer = !currentPlayer;

            ChessMove move(moveNotation, !currentPlayer, isCheck, isCheckmate,
                capturedPieceInfo.capturedType, capturedPieceInfo.capturedColor, true);

            move.setSourceCoords(fromRow, fromCol);
            move.setDestCoords(toRow, toCol);

            historyPanel.addMove(move);

            isPieceSelected = false;
            boardView.clearHighlights();

            if (currentPlayer) {
                whiteTimer.stop();
                blackTimer.start();
            }
            else {
                blackTimer.stop();
                whiteTimer.start();
            }

            currentPlayer = !currentPlayer;
            checkGameState();
        }

        return "";
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

            if (backButton.isClicked(mousePos)) {
                return "menu";
            }

            if (resetButton.isClicked(mousePos)) {
                resetGame();
                return "";
            }

            if (undoButton.isClicked(mousePos)) {
                undoLastMove();
                return "";
            }

            if (!gameOver) {
                handleBoardClick(mousePos);
            }
        }
    }

    historyPanel.handleEvent(event);

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
        backButton.update(mousePos);
        resetButton.update(mousePos);
        undoButton.update(mousePos);
    }

    return "";
}

void GameScreen::update() {
    static int updateCounter = 0;
    updateCounter++;

    if (updateCounter >= 60) {
        updateCounter = 0;
    }

    whiteTimer.update();
    blackTimer.update();

    if (!gameOver) {
        if (currentPlayer) {
            if (whiteTimer.getRemainingTime() <= 0) {
                gameOver = true;
                std::string message = "Time's up! Black wins!";
                showPopupWin(message, sf::Color::Black);
               
            }
        }
        else {
            if (blackTimer.getRemainingTime() <= 0) {
                gameOver = true;
                std::string message = "Time's up! White wins!";
                showPopupWin(message, sf::Color::White);
        
            }
        }
    }
}

void GameScreen::render() {
    window.draw(background);
    boardView.render();

    backButton.render(window);
    resetButton.render(window);
    undoButton.render(window);

    whiteTimer.render();
    blackTimer.render();

    historyPanel.render();

    if (showPopup) {
        window.draw(popupBackground);
        window.draw(popupText);
        popupOkButton.render(window);
    }

    if (showPopup) {
        window.draw(popupBackground);
        window.draw(popupText);
        popupOkButton.render(window);
    }

    promotionPopup.render();
}

void GameScreen::resetGame() {
    chessBoard.resetBoard();

    isPieceSelected = false;
    selectedPiecePos = sf::Vector2i(-1, -1);
    gameOver = false;
    currentPlayer = true;

    whiteTimer.reset(whitePlayerTime);
    blackTimer.reset(blackPlayerTime);

    whiteTimer.stop();
    blackTimer.stop();

    historyPanel.clear();
    boardView.clearHighlights();
}

void GameScreen::handleBoardClick(const sf::Vector2i& mousePos) {
    sf::Vector2i boardPos = boardView.getBoardPosition(mousePos);

    if (boardPos.x == -1 || boardPos.y == -1) {
        return;
    }

    const Piece* clickedPiece = chessBoard.getPieceAt(boardPos.x, boardPos.y);
    bool isCurrentPlayerPiece = false;

    if (clickedPiece) {
        isCurrentPlayerPiece = !clickedPiece->isEmpty() &&
            ((currentPlayer && clickedPiece->isWhite()) ||
                (!currentPlayer && clickedPiece->isBlack()));
    }

    if (!isPieceSelected) {
        if (isCurrentPlayerPiece) {
            isPieceSelected = true;
            selectedPiecePos = boardPos;
            boardView.highlightSelectedPiece(boardPos.x, boardPos.y);

            auto moves = chessBoard.getPossibleMoves(boardPos.x, boardPos.y);
            boardView.setPossibleMoves(moves);
        }
    }
    else {
        if (boardPos.x == selectedPiecePos.x && boardPos.y == selectedPiecePos.y) {
            isPieceSelected = false;
            boardView.clearHighlights();
        }
        else if (isCurrentPlayerPiece) {
            selectedPiecePos = boardPos;
            boardView.highlightSelectedPiece(boardPos.x, boardPos.y);

            auto moves = chessBoard.getPossibleMoves(boardPos.x, boardPos.y);
            boardView.setPossibleMoves(moves);
        }
        else {
            auto moves = chessBoard.getPossibleMoves(selectedPiecePos.x, selectedPiecePos.y);
            bool validMove = false;

            for (const auto& move : moves) {
                if (move.x == boardPos.x && move.y == boardPos.y) {
                    validMove = true;
                    break;
                }
            }

            if (validMove) {
                makeMove(selectedPiecePos.x, selectedPiecePos.y, boardPos.x, boardPos.y);
            }
        }
    }
}

void GameScreen::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    lastMoveFromRow = fromRow;
    lastMoveFromCol = fromCol;

    const Piece* targetPiece = chessBoard.getPieceAt(toRow, toCol);
    capturedPieceInfo.capturedType = PieceType::NONE;
    capturedPieceInfo.capturedColor = PieceColor::NONE;
    bool wasPromotion = false;

    bool isEnPassantCapture = false;
    int enPassantCapturedRow = -1;
    int enPassantCapturedCol = -1;

    bool isCastling = false;
    bool isKingsideCastling = false;
    int rookFromCol = -1;
    int rookToCol = -1;

    Piece* piece = chessBoard.getPieceAt(fromRow, fromCol);
    if (piece && piece->getType() == PieceType::KING && abs(fromCol - toCol) == 2) {
        isCastling = true;
        isKingsideCastling = (toCol > fromCol);

        if (isKingsideCastling) {
            rookFromCol = 7;
            rookToCol = 5;
        }
        else {
            rookFromCol = 0;
            rookToCol = 3;
        }
    }

    if (piece && piece->getType() == PieceType::PAWN) {
        bool isWhitePawn = piece->isWhite();

        if (isWhitePawn && fromRow == 3 && abs(fromCol - toCol) == 1 && toRow == 2 &&
            toCol == chessBoard.getEnPassantCol()) {
            isEnPassantCapture = true;
            enPassantCapturedRow = 3;
            enPassantCapturedCol = toCol;

            const Piece* capturedPawn = chessBoard.getPieceAt(enPassantCapturedRow, enPassantCapturedCol);
            if (capturedPawn) {
                capturedPieceInfo.capturedType = capturedPawn->getType();
                capturedPieceInfo.capturedColor = capturedPawn->getColor();
            }
        }
        else if (!isWhitePawn && fromRow == 4 && abs(fromCol - toCol) == 1 && toRow == 5 &&
            toCol == chessBoard.getEnPassantCol()) {
            isEnPassantCapture = true;
            enPassantCapturedRow = 4;
            enPassantCapturedCol = toCol;

            const Piece* capturedPawn = chessBoard.getPieceAt(enPassantCapturedRow, enPassantCapturedCol);
            if (capturedPawn) {
                capturedPieceInfo.capturedType = capturedPawn->getType();
                capturedPieceInfo.capturedColor = capturedPawn->getColor();
            }
        }
    }

    if (!isEnPassantCapture && targetPiece && !targetPiece->isEmpty()) {
        capturedPieceInfo.capturedType = targetPiece->getType();
        capturedPieceInfo.capturedColor = targetPiece->getColor();
    }

    bool success = chessBoard.makeMove(fromRow, fromCol, toRow, toCol);

    if (success) {
        std::string moveNotation;
        if (isCastling) {
            if (isKingsideCastling) {
                moveNotation = "O-O";
            }
            else {
                moveNotation = "O-O-O";
            }
        }
        else {
            moveNotation = generateMoveNotation(fromRow, fromCol, toRow, toCol);
        }

        currentPlayer = !currentPlayer;

        bool isCheck = chessBoard.isInCheck(currentPlayer);
        bool isCheckmate = chessBoard.isCheckmate(currentPlayer);

        currentPlayer = !currentPlayer;

        if (needsPromotion(toRow, toCol)) {
            promotionSquare.x = toRow;
            promotionSquare.y = toCol;

            wasPromotion = true;

            bool isWhitePiece = chessBoard.getPieceAt(toRow, toCol)->isWhite();
            promotionPopup.show(isWhitePiece);

            return;
        }
        else {
            isPieceSelected = false;
            boardView.clearHighlights();

            if (currentPlayer) {
                whiteTimer.stop();
                blackTimer.start();
            }
            else {
                blackTimer.stop();
                whiteTimer.start();
            }

            currentPlayer = !currentPlayer;
            ChessMove move(moveNotation, currentPlayer, isCheck, isCheckmate,
                capturedPieceInfo.capturedType, capturedPieceInfo.capturedColor, wasPromotion);

            move.setSourceCoords(fromRow, fromCol);
            move.setDestCoords(toRow, toCol);

            if (isEnPassantCapture) {
                move.setEnPassantCapture(true, enPassantCapturedRow, enPassantCapturedCol);
            }

            if (isCastling) {
                move.setCastling(isKingsideCastling, rookFromCol, rookToCol);
            }

            historyPanel.addMove(move);
            checkGameState();
        }
    }
}

bool GameScreen::needsPromotion(int row, int col) {
    const Piece* piece = chessBoard.getPieceAt(row, col);

    if (piece && piece->getType() == PieceType::PAWN) {
        if ((piece->isWhite() && row == 0) || (piece->isBlack() && row == 7)) {
            return true;
        }
    }

    return false;
}

std::string GameScreen::generateMoveNotation(int fromRow, int fromCol, int toRow, int toCol) {
    char files[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    char ranks[] = { '8', '7', '6', '5', '4', '3', '2', '1' };

    const Piece* piece = chessBoard.getPieceAt(toRow, toCol);

    std::string notation;

    if (piece) {
        switch (piece->getType()) {
        case PieceType::KING: notation += "K"; break;
        case PieceType::QUEEN: notation += "Q"; break;
        case PieceType::ROOK: notation += "R"; break;
        case PieceType::BISHOP: notation += "B"; break;
        case PieceType::KNIGHT: notation += "N"; break;
        default: break;
        }
    }

    notation += files[fromCol];
    notation += ranks[fromRow];

    const Piece* targetPiece = chessBoard.getPieceAt(toRow, toCol);
    if (targetPiece && !targetPiece->isEmpty()) {
        notation += "x";
    }
    else {
        notation += "-";
    }

    notation += files[toCol];
    notation += ranks[toRow];

    return notation;
}

std::string GameScreen::generatePromotionNotation(int fromRow, int fromCol, int toRow, int toCol, PieceType promotedTo) {
    char files[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    char ranks[] = { '8', '7', '6', '5', '4', '3', '2', '1' };

    std::string notation;

    notation += files[fromCol];

    const Piece* targetPiece = chessBoard.getPieceAt(toRow, toCol);
    if (targetPiece && !targetPiece->isEmpty()) {
        notation += "x";
    }

    notation += files[toCol];
    notation += ranks[toRow];

    notation += "=";

    switch (promotedTo) {
    case PieceType::QUEEN: notation += "Q"; break;
    case PieceType::ROOK: notation += "R"; break;
    case PieceType::BISHOP: notation += "B"; break;
    case PieceType::KNIGHT: notation += "N"; break;
    default: notation += "Q"; break;
    }

    return notation;
}


void GameScreen::checkGameState() {
    if (chessBoard.isCheckmate(currentPlayer)) {
        gameOver = true;
        whiteTimer.stop();
        blackTimer.stop();
        std::string message = currentPlayer ? "Checkmate! Black wins!" : "Checkmate! White wins!";
        sf::Color color = currentPlayer ? sf::Color::Black : sf::Color::White;
        showPopupWin(message, color);
    }
    else if (chessBoard.isStalemate(currentPlayer)) {
        gameOver = true;
        whiteTimer.stop();
        blackTimer.stop();
        std::string message = "Stalemate! Draw!";
        sf::Color color = sf::Color(150, 150, 150);
        showPopupWin(message, color);
    }
    else if (chessBoard.isInCheck(currentPlayer)) {
    }
}

void GameScreen::undoLastMove() {
    if (gameOver || historyPanel.getMoves().empty()) {
        return;
    }

    const ChessMove& lastMove = historyPanel.getLastMove();
    bool wasPromotion = lastMove.getWasPromotion();
    bool wasEnPassant = lastMove.getWasEnPassant();
    bool wasCastling = lastMove.getWasCastling();

    if (wasCastling) {
        int kingRow = lastMove.sourceRow;
        int kingFromCol = lastMove.sourceCol;
        int kingToCol = lastMove.destCol;

        int rookRow = kingRow;
        int rookFromCol = lastMove.getRookFromCol();
        int rookToCol = lastMove.getRookToCol();

        std::unique_ptr<Piece> king = chessBoard.removePieceAt(kingRow, kingToCol);
        std::unique_ptr<Piece> rook = chessBoard.removePieceAt(rookRow, rookToCol);

        if (king) king->setHasMoved(false);
        if (rook) rook->setHasMoved(false);

        chessBoard.setPieceAt(kingRow, kingFromCol, std::move(king));
        chessBoard.setPieceAt(rookRow, rookFromCol, std::move(rook));
    }
    else if (wasEnPassant) {

        int fromRow = lastMove.sourceRow;
        int fromCol = lastMove.sourceCol;
        int toRow = lastMove.destRow;
        int toCol = lastMove.destCol;

        int capturedRow = lastMove.enPassantCapturedRow;
        int capturedCol = lastMove.enPassantCapturedCol;

        std::unique_ptr<Piece> movingPawn = chessBoard.removePieceAt(toRow, toCol);

        chessBoard.setPieceAt(fromRow, fromCol, std::move(movingPawn));

        PieceColor capturedColor = currentPlayer ? PieceColor::WHITE : PieceColor::BLACK;
        std::unique_ptr<Piece> capturedPawn = std::make_unique<Pawn>(capturedColor);
        chessBoard.setPieceAt(capturedRow, capturedCol, std::move(capturedPawn));
    }
    else if (wasPromotion) {

        int fromRow = lastMove.sourceRow;
        int fromCol = lastMove.sourceCol;
        int toRow = lastMove.destRow;
        int toCol = lastMove.destCol;

        if (fromRow == -1 || toRow == -1) {
            std::string notation = lastMove.notation;

            size_t equalPos = notation.find('=');
            if (equalPos != std::string::npos && equalPos >= 2) {
                char destFile = notation[equalPos - 2];
                char destRank = notation[equalPos - 1];
                toCol = destFile - 'a';
                toRow = '8' - destRank;

                char sourceFile = notation[0];
                fromCol = sourceFile - 'a';

                if (toRow == 0) {
                    fromRow = 1;
                }
                else if (toRow == 7) {
                    fromRow = 6;
                }
            }
        }

        std::unique_ptr<Piece> promotedPiece = chessBoard.removePieceAt(toRow, toCol);

        std::unique_ptr<Piece> pawn = std::make_unique<Pawn>(currentPlayer ? PieceColor::BLACK : PieceColor::WHITE);
        chessBoard.setPieceAt(fromRow, fromCol, std::move(pawn));

        if (lastMove.getWasPieceCaptured()) {
            std::unique_ptr<Piece> capturedPiece = nullptr;

            switch (lastMove.getCapturedPieceType()) {
            case PieceType::PAWN:
                capturedPiece = std::make_unique<Pawn>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::ROOK:
                capturedPiece = std::make_unique<Rook>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::KNIGHT:
                capturedPiece = std::make_unique<Knight>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::BISHOP:
                capturedPiece = std::make_unique<Bishop>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::QUEEN:
                capturedPiece = std::make_unique<Queen>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::KING:
                capturedPiece = std::make_unique<King>(lastMove.getCapturedPieceColor());
                break;
            default:
                break;
            }

            if (capturedPiece) {
                chessBoard.setPieceAt(toRow, toCol, std::move(capturedPiece));
            }
        }
    }
    else {
        std::string notation = lastMove.notation;
        int startIndex = 0;
        if (notation[0] >= 'A' && notation[0] <= 'Z') {
            startIndex = 1;
        }

        char fromFile = notation[startIndex];
        char fromRank = notation[startIndex + 1];

        int toIndex = notation.find('-');
        if (toIndex == std::string::npos) {
            toIndex = notation.find('x');
        }

        if (toIndex == std::string::npos) {
            return;
        }

        toIndex += 1;
        char toFile = notation[toIndex];
        char toRank = notation[toIndex + 1];

        int fromCol = fromFile - 'a';
        int fromRow = '8' - fromRank;
        int toCol = toFile - 'a';
        int toRow = '8' - toRank;

        std::unique_ptr<Piece> movedPiece = chessBoard.removePieceAt(toRow, toCol);
        if (!movedPiece) {
            return;
        }

        chessBoard.setPieceAt(fromRow, fromCol, std::move(movedPiece));

        if (lastMove.getWasPieceCaptured()) {
            std::unique_ptr<Piece> capturedPiece = nullptr;

            switch (lastMove.getCapturedPieceType()) {
            case PieceType::PAWN:
                capturedPiece = std::make_unique<Pawn>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::ROOK:
                capturedPiece = std::make_unique<Rook>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::KNIGHT:
                capturedPiece = std::make_unique<Knight>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::BISHOP:
                capturedPiece = std::make_unique<Bishop>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::QUEEN:
                capturedPiece = std::make_unique<Queen>(lastMove.getCapturedPieceColor());
                break;
            case PieceType::KING:
                capturedPiece = std::make_unique<King>(lastMove.getCapturedPieceColor());
                break;
            default:
                break;
            }

            if (capturedPiece) {
                chessBoard.setPieceAt(toRow, toCol, std::move(capturedPiece));
            }
        }
    }

    historyPanel.removeLastMove();
    currentPlayer = !currentPlayer;

    if (currentPlayer) {
        blackTimer.stop();
        whiteTimer.start();
    }
    else {
        whiteTimer.stop();
        blackTimer.start();
    }

    isPieceSelected = false;
    boardView.clearHighlights();

}

void GameScreen::updateBackgroundSize() {
    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
}

void GameScreen::setPlayerTimes(int whiteTime, int blackTime) {
    whitePlayerTime = whiteTime;
    blackPlayerTime = blackTime;

    whiteTimer.reset(whiteTime);
    blackTimer.reset(blackTime);

    whiteTimer.stop();
    blackTimer.stop();

}

void GameScreen::showPopupWin(const std::string& message, sf::Color color) {
    showPopup = true;
    popupMessage = message;
    popupColor = color;

    popupText.setString(message);
    popupText.setFillColor(sf::Color::White);
    popupText.setCharacterSize(24);

    sf::Vector2u windowSize = window.getSize();
    float popupWidth = 400.0f;
    float popupHeight = 200.0f;

    popupBackground.setSize(sf::Vector2f(popupWidth, popupHeight));
    popupBackground.setPosition((windowSize.x - popupWidth) / 2, (windowSize.y - popupHeight) / 2);
    popupBackground.setFillColor(sf::Color(20, 30, 70, 230));
    popupBackground.setOutlineThickness(3);
    popupBackground.setOutlineColor(color);

    sf::FloatRect textBounds = popupText.getLocalBounds();
    popupText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    popupText.setPosition(
        windowSize.x / 2,
        (windowSize.y / 2) - 30
    );

    popupOkButton.setText("OK");

    float buttonX = (windowSize.x / 2) - 50;
    float buttonY = (windowSize.y / 2) + 30;
    popupOkButton.setPosition(buttonX, buttonY);

    sf::Color buttonColor(50, 80, 150);
    sf::Color hoverColor(100, 160, 255);
    popupOkButton.setColors(buttonColor, hoverColor);
}

void GameScreen::hidePopup() {
    showPopup = false;
}