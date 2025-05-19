#pragma once


class GameState {

  public:
    GameState() = delete;

  private:
    static const int castlingMask =      0b1111111111111111111111111110000;
    static const int EPSquareWhiteMask = 0b1111111111111000000000111111111;
    static const int EPSquareBlackMask = 0b1111000000000111111111111111111;
    static const int capturedPieceMask = 0b1111111111111111111111000001111;
    static const int promotionMoveMask = 0b0000111111111111111111111111111;


  public:
    static int getCastlingRights(int gameState);
    static int getEPSquareWhite(int gameState);
    static int getEPSquareBlack(int gameState);
    static int getCapturedPiece(int gameState);
    static int getSideToMove(int gameState);
    static int getPromotionMove(int gameState);

    static void setCastlingRights(int castleRights, int& gameState);
    static void setEPSquareWhite(int EPSquareWhite, int& gameState);
    static void setEPSquareBlack(int EPSquareBlack, int& gameState);
    static void setCapturedPiece(int capturedPiece, int& gameState);
    static void setPromotionMove(int promotionTo, int& gameState);    

};