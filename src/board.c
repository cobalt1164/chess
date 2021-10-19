#include "stdio.h"
#include "types.h"

void resetBoard(BOARD_STRUCT *board) {
    int i = 0;

    for (i = 0; i < BOARD_NUM; ++i) {
        board->pieces[i] = SQ_NONE;
    }
    
    for (i = 0; i < 64; ++i) {
        board->pieces[board64To120[i]] = EMPTY;
    }

    for (i = 0; i < 3; ++i) {
        board->bigPieces[i] = 0;
        board->majorPieces[i] = 0;
        board->minorPieces[i] = 0;
        board->pawns[i] = 0ULL;
    }

    for (i = 0; i < 13; ++i) {
        board->numPieces[i] = 0;
    }

    board->kingSquares[WHITE] = board->kingSquares[BLACK] = SQ_NONE;

    board->side = BOTH;
    board->enPassant = SQ_NONE;
    board->fiftyMoveRule = 0;

    board->ply = 0;
    board->plyHistory = 0;
    
    board->castlePerms = 0;
    board->positionKey = 0ULL;


}
