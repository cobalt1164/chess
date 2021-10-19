#include "types.h"
#include "assert.h"

// A position hashkey is created from randomized U64 numbers in pieceKeys,
// sideKey, and castleKeys

U64 genPositionKey(const BOARD_STRUCT *position) {
    int square = 0;
    int piece = EMPTY;
    U64 finalKey = 0;

    for (square = 0; square < BOARD_NUM; ++square) {
        piece = position->pieces[square];
        if (piece != SQ_NONE && piece != EMPTY) {
            assert(piece >= WHITE_PAWN && piece <= BLACK_KING);
            finalKey ^= pieceKeys[piece][square];
        }
    }

    if (position->side == WHITE) {
        finalKey ^= sideKey;
    }

    // position->enPassant will be SQ_NONE by default

    if (position->enPassant != SQ_NONE) {
        assert(position->enPassant >= 0 && position->enPassant < BOARD_NUM);
        
        // The EMPTY dimension of pieceKeys is reserved for enPassant squares.
        // This functions as an array for en passant keys without creating a
        // new array specifically for it.
        finalKey ^= pieceKeys[EMPTY][position->enPassant];
    }

    assert(position->castlePerms >= 0 && position->castlePerms <=15);

    finalKey ^= castleKeys[position->castlePerms];

    return finalKey;
}
