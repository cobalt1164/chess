#include "types.h"
#include "stdio.h"

// Conversion between the 64 bit board and the size 120 array board is done by
// indexing conversion arrays

int board120To64[BOARD_NUM];
int board64To120[64];

// Set/clear masks for the 64 bit boards

U64 SetMask[64];
U64 ClearMask[64];

void initBoardConversion() {
    int i = 0;
    int square64 = 0;
    int square = A1;
    int file = FILE_A;
    int rank = RANK_1;

    // Initialize each element with an impossible value as a fail-safe
    for (i = 0; i < BOARD_NUM; ++i) {
        board120To64[i] = 65;
    }

    for (i = 0; i < 64; ++i) {
        board64To120[i] = 120;
    }

    for (rank = RANK_1; rank <= RANK_8; ++rank) {  
        for (file = FILE_A; file <= FILE_H; ++file) {
            square = fileRankTo120(file, rank);
            board120To64[square] = square64;
            board64To120[square64] = square;
            square64++;
        }
    }
}

void initBitMasks() {
    int i = 0;
    for (i = 0; i < 64; ++i) {
        SetMask[i] = 0ULL;
        SetMask[i] |= 1ULL << i;
        ClearMask[i] = ~SetMask[i];
    }
}

void initAll() {
    initBoardConversion();
    initBitMasks();
}
