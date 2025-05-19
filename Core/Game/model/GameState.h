#pragma once


class GameState {

  public:
    GameState() = delete;

  private:
    static const unsigned int castlingMask =      0b1111111111111111111111111110000;
    static const unsigned int EPSquareWhiteMask = 0b1111111111111000000000111111111;
    static const unsigned int EPSquareBlackMask = 0b1111000000000111111111111111111;
    static const unsigned int capturedPieceMask = 0b1111111111111111111111000001111;
    static const unsigned int promotionMoveMask = 0b0000111111111111111111111111111;


  public:
    static int getCastlingRights(unsigned int gameState);
    static int getEPSquareWhite(unsigned int gameState);
    static int getEPSquareBlack(unsigned int gameState);
    static int getCapturedPiece(unsigned int gameState);
    static int getPromotionMove(unsigned int gameState);

    static void setCastlingRights(int castleRights, unsigned int& gameState);
    static void setEPSquareWhite(int EPSquareWhite, unsigned int& gameState);
    static void setEPSquareBlack(int EPSquareBlack, unsigned int& gameState);
    static void setCapturedPiece(int capturedPiece, unsigned int& gameState);
    static void setPromotionMove(int promotionTo, unsigned int& gameState);    

};