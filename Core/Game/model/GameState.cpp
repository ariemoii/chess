#include "GameState.h"
#include <iostream>

//first 1-4 bits are castling rights
//with bits 1-2 being for  white king and queen, and 3-4 black king and
//queenside, respectively.
int GameState::getCastlingRights(int gameState) {
  return gameState & 0b1111;
}

//bits 5-9 are the piece that is captured
int GameState::getCapturedPiece(int gameState) {
  return (gameState >> 4) & 0b11111;
}

//bits 10-18 are the square white can en passant to
int GameState::getEPSquareWhite(int gameState) {
  return (gameState >> 9) & 0b111111111;
}
//bits 19-27 are the square black can en passant to
int GameState::getEPSquareBlack(int gameState) {
  return (gameState >> 18) & 0b111111111;
}

//bits 28-31 show promotion
int GameState::getPromotionMove(int gameState) {
  
  return (gameState >> 27) & 0b1111;
}

void GameState::setCastlingRights(int castlingRights, int& gameState) {
  gameState &= castlingMask;
  gameState |= castlingRights;
}

void GameState::setCapturedPiece(int capturedPiece, int& gameState) {
  capturedPiece <<= 4;
  gameState &= capturedPieceMask;
  gameState |= capturedPiece;
}

void GameState::setEPSquareWhite(int EPSquareWhite, int& gameState) {
  EPSquareWhite <<= 9;
  gameState &= EPSquareWhiteMask;
  gameState |= EPSquareWhite;
}

void GameState::setEPSquareBlack(int EPSquareBlack, int& gameState) {
  EPSquareBlack <<= 18;
  gameState &= EPSquareBlackMask;
  gameState |= EPSquareBlack;
}

void GameState::setPromotionMove(int promotionTo, int& gameState) {
  promotionTo <<= 27;
  gameState &= promotionMoveMask;
  gameState |= promotionTo;
}