#pragma once
#include "model/Piece.h"
#include "model/Board.h"
#include <array>
#include <vector>
#include <map>

struct dictKey {
  int startSquare;
  U64 blockerBitboard;
};

class MoveData {

  public:
    enum Direction { N=16, E=1, S=-16, W=-1, NE=17, SE=-15, SW=-17, NW=15 };

    static constexpr int ATTACK_KING = 1 << (Piece::KING | Piece::NONE);
    static constexpr int ATTACK_QUEEN = 1 << (Piece::QUEEN | Piece::NONE);
    static constexpr int ATTACK_ROOK = 1 << (Piece::ROOK | Piece::NONE);
    static constexpr int ATTACK_BISHOP = 1 << (Piece::BISHOP | Piece::NONE);
    static constexpr int ATTACK_KNIGHT = 1 << (Piece::KNIGHT | Piece::NONE);
    static constexpr int ATTACK_WHITE_PAWN = 1 << (Piece::PAWN | Piece::WHITE);
    static constexpr int ATTACK_BLACK_PAWN = 1 << (Piece::PAWN | Piece::BLACK);

    //used to convert from piece to attack piece
    static constexpr int pieceToAttackPiece[32] {
      0, 0, 0, 0, 0, 0, 0, 0,
      0, ATTACK_WHITE_PAWN, ATTACK_KNIGHT, ATTACK_KING, ATTACK_QUEEN, ATTACK_ROOK, ATTACK_BISHOP, 0, 
      0, ATTACK_BLACK_PAWN, ATTACK_KNIGHT, ATTACK_KING, ATTACK_QUEEN, ATTACK_ROOK, ATTACK_BISHOP, 0,
      0, 0, 0, 0, 0, 0, 0, 0
    };

    MoveData();

    //used for debugging
    void printAttackArray();

    bool canAttack(int piece, int fromSquare, int toSquare, Board* board);
    static std::string intToSquare(int square);
    static int squareToInt(std::string square);

    //normally using a vector is relatively slow and we avoid it, but this is 
    //precomputed, so it is fine
    std::vector<U64> preComputeBlockerBitboards(U64 movementMask);
    void printBitboard(U64 bitboard);
    U64 createRookLegalMoveBitboard(int square, U64 blockerMask);

  public:

    //store the direction squares a piece can move to


    std::array<int, 64> bishopDirections;
    std::array<int, 64> rookDirections;
    std::array<int, 64> queenDirections;
    std::array<int, 64> kingDirections;
    std::array<int, 64> knightDirections;
    std::array<int, 64> blackPawnDirections;
    std::array<int, 64> whitePawnDirections;

    std::array<int, 265> directionVector;

    //store for every square a bitboard of where a piece on that square can move to
    std::array<U64, 64> bishopMoves{};
    std::array<U64, 64> rookMoves{};
    std::array<U64, 64> queenMoves{};
    std::array<U64, 64> kingMoves{};
    std::array<U64, 64> knightMoves{};

    std::map<dictKey, U64> rookLookupTable;


  private:
    //attack array from 
    //https://web.archive.org/web/20071027053053/http://www.brucemo.com/compchess/programming/0x88.htm,
    std::array<int, 265> attackArray{};

    //stored N, E, S, W
    std::array<std::array<int, 4>, 64> squaresTillEdge;

  private:
    void preComputeMoveData();
    void preComputeAttackArray();
    void preComputeAttackSlidingPiece(std::array<int, 64> slidingPieceArray, int type);
    void preComputeDirectionArray();
    void preComputeSquaresTillEdge();
    void preComputeMoveBitboards();
    void fillRookLookupTable();
    
    
};