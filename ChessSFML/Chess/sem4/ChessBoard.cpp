#include "ChessBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

ChessBoard::ChessBoard() : whiteKingMoved(false), blackKingMoved(false),
whiteRook1Moved(false), whiteRook2Moved(false),
blackRook1Moved(false), blackRook2Moved(false),
enPassantCol(-1), enPassantRow(-1) {
    resetBoard();
}


void ChessBoard::resetBoard() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col] = nullptr;
        }
    }

    board[0][0] = std::make_unique<Rook>(PieceColor::BLACK);
    board[0][1] = std::make_unique<Knight>(PieceColor::BLACK);
    board[0][2] = std::make_unique<Bishop>(PieceColor::BLACK);
    board[0][3] = std::make_unique<Queen>(PieceColor::BLACK);
    board[0][4] = std::make_unique<King>(PieceColor::BLACK);
    board[0][5] = std::make_unique<Bishop>(PieceColor::BLACK);
    board[0][6] = std::make_unique<Knight>(PieceColor::BLACK);
    board[0][7] = std::make_unique<Rook>(PieceColor::BLACK);

    for (int col = 0; col < 8; col++) {
        board[1][col] = std::make_unique<Pawn>(PieceColor::BLACK);
    }

    for (int col = 0; col < 8; col++) {
        board[6][col] = std::make_unique<Pawn>(PieceColor::WHITE);
    }

    board[7][0] = std::make_unique<Rook>(PieceColor::WHITE);
    board[7][1] = std::make_unique<Knight>(PieceColor::WHITE);
    board[7][2] = std::make_unique<Bishop>(PieceColor::WHITE);
    board[7][3] = std::make_unique<Queen>(PieceColor::WHITE);
    board[7][4] = std::make_unique<King>(PieceColor::WHITE);
    board[7][5] = std::make_unique<Bishop>(PieceColor::WHITE);
    board[7][6] = std::make_unique<Knight>(PieceColor::WHITE);
    board[7][7] = std::make_unique<Rook>(PieceColor::WHITE);

    whiteKingMoved = false;
    blackKingMoved = false;
    whiteRook1Moved = false;
    whiteRook2Moved = false;
    blackRook1Moved = false;
    blackRook2Moved = false;
    enPassantCol = -1;
    enPassantRow = -1;
}

const Piece* ChessBoard::getPieceAt(int row, int col) const {
    if (isValidPosition(row, col) && board[row][col]) {
        return board[row][col].get();
    }
    static EmptyPiece emptyPiece;
    return &emptyPiece;
}

Piece* ChessBoard::getPieceAt(int row, int col) {
    if (isValidPosition(row, col) && board[row][col]) {
        return board[row][col].get();
    }
    return nullptr;
}

void ChessBoard::setPieceAt(int row, int col, std::unique_ptr<Piece> piece) {
    if (isValidPosition(row, col)) {
        board[row][col] = std::move(piece);
    }
}

bool ChessBoard::isValidPosition(int row, int col) const {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

bool ChessBoard::isPieceOfCurrentPlayer(int row, int col, bool isWhiteTurn) const {
    const Piece* piece = getPieceAt(row, col);
    return piece && !piece->isEmpty() && ((isWhiteTurn && piece->isWhite()) || (!isWhiteTurn && piece->isBlack()));
}

std::vector<sf::Vector2i> ChessBoard::getPossibleMoves(int row, int col) const {
    const Piece* piece = getPieceAt(row, col);
    if (piece && !piece->isEmpty()) {
        return piece->getPossibleMoves(row, col, *this);
    }
    return {};
}

bool ChessBoard::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (!isValidPosition(fromRow, fromCol) || !isValidPosition(toRow, toCol)) {
        return false;
    }

    Piece* piece = getPieceAt(fromRow, fromCol);
    if (!piece || piece->isEmpty()) {
        return false;
    }

    bool isWhiteTurn = piece->isWhite();

    auto possibleMoves = getPossibleMoves(fromRow, fromCol);
    bool moveFound = false;
    for (const auto& move : possibleMoves) {
        if (move.x == toRow && move.y == toCol) {
            moveFound = true;
            break;
        }
    }

    if (!moveFound) {
        return false;
    }

    bool isCastling = false;
    if (piece->getType() == PieceType::KING && abs(fromCol - toCol) == 2) {
        isCastling = true;

        if (isKingInCheck(isWhiteTurn ? PieceColor::WHITE : PieceColor::BLACK)) {
            return false;
        }

        bool isKingsideCastling = (toCol > fromCol);
        int middleCol = isKingsideCastling ? 5 : 3;

        if (wouldMoveExposeKing(fromRow, fromCol, fromRow, middleCol, isWhiteTurn)) {
            return false;
        }

        if (wouldMoveExposeKing(fromRow, fromCol, toRow, toCol, isWhiteTurn)) {
            return false;
        }

        int rookFromCol = isKingsideCastling ? 7 : 0;
        int rookToCol = isKingsideCastling ? 5 : 3;

        auto rook = std::move(board[fromRow][rookFromCol]);
        board[fromRow][rookFromCol] = nullptr;
        board[fromRow][rookToCol] = std::move(rook);

        if (board[fromRow][rookToCol]) {
            board[fromRow][rookToCol]->setHasMoved(true);
        }
    }
    else if (wouldMoveExposeKing(fromRow, fromCol, toRow, toCol, isWhiteTurn)) {
        return false;
    }

    bool isEnPassantCapture = false;
    if (piece->getType() == PieceType::PAWN &&
        toCol == enPassantCol &&
        ((isWhiteTurn && fromRow == 3 && toRow == 2) ||
            (!isWhiteTurn && fromRow == 4 && toRow == 5))) {

        int capturedRow = isWhiteTurn ? 3 : 4;
        board[capturedRow][enPassantCol] = nullptr;
        isEnPassantCapture = true;
    }

    auto movingPiece = std::move(board[fromRow][fromCol]);
    board[fromRow][fromCol] = nullptr;
    board[toRow][toCol] = std::move(movingPiece);

    if (board[toRow][toCol]) {
        board[toRow][toCol]->setHasMoved(true);
    }

    if (board[toRow][toCol] && board[toRow][toCol]->getType() == PieceType::KING) {
        if (board[toRow][toCol]->isWhite()) {
            whiteKingMoved = true;
        }
        else {
            blackKingMoved = true;
        }
    }
    else if (board[toRow][toCol] && board[toRow][toCol]->getType() == PieceType::ROOK) {
        if (board[toRow][toCol]->isWhite()) {
            if (fromCol == 0) whiteRook1Moved = true;
            if (fromCol == 7) whiteRook2Moved = true;
        }
        else {
            if (fromCol == 0) blackRook1Moved = true;
            if (fromCol == 7) blackRook2Moved = true;
        }
    }

    if (board[toRow][toCol] && board[toRow][toCol]->getType() == PieceType::PAWN && abs(fromRow - toRow) == 2) {
        enPassantCol = toCol;
        enPassantRow = (fromRow + toRow) / 2;
    }
    else {
        enPassantCol = -1;
        enPassantRow = -1;
    }

    return true;
}

void ChessBoard::promotePawn(int row, int col, PieceType newType) {
    if (!isValidPosition(row, col)) {
        return;
    }

    Piece* piece = getPieceAt(row, col);
    if (!piece || piece->getType() != PieceType::PAWN) {
        return;
    }

    PieceColor color = piece->getColor();
    std::unique_ptr<Piece> newPiece;

    switch (newType) {
    case PieceType::QUEEN:
        newPiece = std::make_unique<Queen>(color);
        break;
    case PieceType::ROOK:
        newPiece = std::make_unique<Rook>(color);
        break;
    case PieceType::BISHOP:
        newPiece = std::make_unique<Bishop>(color);
        break;
    case PieceType::KNIGHT:
        newPiece = std::make_unique<Knight>(color);
        break;
    default:
        newPiece = std::make_unique<Queen>(color);
        break;
    }

    setPieceAt(row, col, std::move(newPiece));
}

bool ChessBoard::isKingInCheck(PieceColor kingColor) const {
    int kingRow = -1, kingCol = -1;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Piece* piece = getPieceAt(row, col);
            if (piece && piece->getType() == PieceType::KING && piece->getColor() == kingColor) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    if (kingRow == -1) {
        return false;
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Piece* piece = getPieceAt(row, col);
            if (piece && !piece->isEmpty() && piece->getColor() != kingColor) {
                auto moves = piece->getPossibleMoves(row, col, *this);
                for (const auto& move : moves) {
                    if (move.x == kingRow && move.y == kingCol) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


bool ChessBoard::wouldMoveExposeKing(int fromRow, int fromCol, int toRow, int toCol, bool isWhiteTurn) const {
    ChessBoard tempBoard;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            tempBoard.board[r][c] = nullptr;
        }
    }

    const Piece* movingPiece = getPieceAt(fromRow, fromCol);
    bool isPawnMove = movingPiece && movingPiece->getType() == PieceType::PAWN;
    bool isEnPassantCapture = isPawnMove &&
        toCol == enPassantCol &&
        ((isWhiteTurn && fromRow == 3 && toRow == 2) ||
            (!isWhiteTurn && fromRow == 4 && toRow == 5));

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (r == fromRow && c == fromCol) {
                continue;
            }

            if (isEnPassantCapture &&
                ((isWhiteTurn && r == 3 && c == enPassantCol) ||
                    (!isWhiteTurn && r == 4 && c == enPassantCol))) {
                continue;
            }

            const Piece* piece = getPieceAt(r, c);
            if (piece && !piece->isEmpty()) {
                PieceColor color = piece->getColor();
                std::unique_ptr<Piece> newPiece;

                switch (piece->getType()) {
                case PieceType::PAWN:   newPiece = std::make_unique<Pawn>(color); break;
                case PieceType::ROOK:   newPiece = std::make_unique<Rook>(color); break;
                case PieceType::KNIGHT: newPiece = std::make_unique<Knight>(color); break;
                case PieceType::BISHOP: newPiece = std::make_unique<Bishop>(color); break;
                case PieceType::QUEEN:  newPiece = std::make_unique<Queen>(color); break;
                case PieceType::KING:   newPiece = std::make_unique<King>(color); break;
                default: continue;
                }

                newPiece->setHasMoved(piece->getHasMoved());
                tempBoard.board[r][c] = std::move(newPiece);
            }
        }
    }

    if (movingPiece && !movingPiece->isEmpty()) {
        PieceColor color = movingPiece->getColor();
        std::unique_ptr<Piece> newPiece;

        switch (movingPiece->getType()) {
        case PieceType::PAWN:   newPiece = std::make_unique<Pawn>(color); break;
        case PieceType::ROOK:   newPiece = std::make_unique<Rook>(color); break;
        case PieceType::KNIGHT: newPiece = std::make_unique<Knight>(color); break;
        case PieceType::BISHOP: newPiece = std::make_unique<Bishop>(color); break;
        case PieceType::QUEEN:  newPiece = std::make_unique<Queen>(color); break;
        case PieceType::KING:   newPiece = std::make_unique<King>(color); break;
        default: break;
        }

        if (newPiece) {
            newPiece->setHasMoved(true);
            tempBoard.board[toRow][toCol] = std::move(newPiece);
        }
    }

    tempBoard.enPassantCol = this->enPassantCol;
    tempBoard.enPassantRow = this->enPassantRow;

    PieceColor kingColor = isWhiteTurn ? PieceColor::WHITE : PieceColor::BLACK;
    bool result = tempBoard.isKingInCheck(kingColor);
    return result;
}

bool ChessBoard::isCheckmate(bool isWhiteTurn) const {
    PieceColor kingColor = isWhiteTurn ? PieceColor::WHITE : PieceColor::BLACK;

    if (!isKingInCheck(kingColor)) {
        return false;
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Piece* piece = getPieceAt(row, col);
            if (piece && !piece->isEmpty() && piece->getColor() == kingColor) {
                auto moves = getPossibleMoves(row, col);

                for (const auto& move : moves) {
                    if (!wouldMoveExposeKing(row, col, move.x, move.y, isWhiteTurn)) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool ChessBoard::isStalemate(bool isWhiteTurn) const {
    PieceColor kingColor = isWhiteTurn ? PieceColor::WHITE : PieceColor::BLACK;

    if (isKingInCheck(kingColor)) {
        return false;
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Piece* piece = getPieceAt(row, col);
            if (piece && !piece->isEmpty() && piece->getColor() == kingColor) {
                auto moves = getPossibleMoves(row, col);

                for (const auto& move : moves) {
                    if (!wouldMoveExposeKing(row, col, move.x, move.y, isWhiteTurn)) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool ChessBoard::isInCheck(bool isWhitePlayer) const {
    sf::Vector2i kingPos(-1, -1);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Piece* piece = getPieceAt(row, col);
            if (piece && piece->getType() == PieceType::KING &&
                ((isWhitePlayer && piece->isWhite()) || (!isWhitePlayer && piece->isBlack()))) {
                kingPos = sf::Vector2i(row, col);
                break;
            }
        }
        if (kingPos.x != -1) break;
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Piece* piece = getPieceAt(row, col);
            if (piece && !piece->isEmpty() &&
                ((isWhitePlayer && piece->isBlack()) || (!isWhitePlayer && piece->isWhite()))) {

                auto moves = getPossibleMoves(row, col);

                for (const auto& move : moves) {
                    if (move.x == kingPos.x && move.y == kingPos.y) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

std::unique_ptr<Piece> ChessBoard::removePieceAt(int row, int col) {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        return nullptr;
    }

    std::unique_ptr<Piece> removedPiece = std::move(board[row][col]);

    board[row][col] = nullptr;

    return removedPiece;
}

bool ChessBoard::canCastleKingside(bool isWhite) const {
    int row = isWhite ? 7 : 0;

    if (isWhite && (whiteKingMoved || whiteRook2Moved)) return false;
    if (!isWhite && (blackKingMoved || blackRook2Moved)) return false;

    if (!isPathClear(row, 4, row, 7)) return false;

    PieceColor kingColor = isWhite ? PieceColor::WHITE : PieceColor::BLACK;
    if (isKingInCheck(kingColor)) return false;

    if (isPathUnderAttack(row, 4, 6, kingColor)) return false;

    return true;
}

bool ChessBoard::canCastleQueenside(bool isWhite) const {
    int row = isWhite ? 7 : 0;

    if (isWhite && (whiteKingMoved || whiteRook1Moved)) return false;
    if (!isWhite && (blackKingMoved || blackRook1Moved)) return false;

    if (!isPathClear(row, 0, row, 4)) return false;

    PieceColor kingColor = isWhite ? PieceColor::WHITE : PieceColor::BLACK;
    if (isKingInCheck(kingColor)) return false;

    if (isPathUnderAttack(row, 2, 4, kingColor)) return false;

    return true;
}

bool ChessBoard::isPathClear(int startRow, int startCol, int endRow, int endCol) const {
    if (startRow != endRow) {
        int colDir = 0;
        int rowDir = (endRow > startRow) ? 1 : -1;

        for (int r = startRow + rowDir; r != endRow; r += rowDir) {
            if (!getPieceAt(r, startCol)->isEmpty()) {
                return false;
            }
        }
    }
    else {
        int colDir = (endCol > startCol) ? 1 : -1;

        for (int c = startCol + colDir; c != endCol; c += colDir) {
            if (!getPieceAt(startRow, c)->isEmpty()) {
                return false;
            }
        }
    }

    return true;
}

bool ChessBoard::isPathUnderAttack(int row, int startCol, int endCol, PieceColor kingColor) const {
    PieceColor opponentColor = (kingColor == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;

    for (int col = startCol; col <= endCol; col++) {
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                const Piece* piece = getPieceAt(r, c);
                if (piece && !piece->isEmpty() && piece->getColor() == opponentColor) {
                    auto moves = piece->getPossibleMoves(r, c, *this);

                    for (const auto& move : moves) {
                        if (move.x == row && move.y == col) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}