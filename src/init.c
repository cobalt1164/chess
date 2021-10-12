#include "types.h"
#include "stdio.h"

// Conversion between the 64 bit board and the size 120 array board is done by
// indexing conversion arrays

int board120ToBoard64[BOARD_NUM];
int board64ToBoard120[64];

void initBoardConversion() {
    int i = 0;
    int square64 = 0;
    int square = A1;
    int file = FILE_A;
    int rank = RANK_1;

    // Initialize each element with an impossible value as a fail-safe
    for (i = 0; i < BOARD_NUM; ++i) {
        board120ToBoard64[i] = 65;
    }

    for (i = 0; i < 64; ++i) {
        board64ToBoard120[i] = 120;
    }

    for (rank = RANK_1; rank <= RANK_8; ++rank) {  
        for (file = FILE_A; file <= FILE_H; ++file) {
            square = FILE_RANK_TO_120SQUARE(file, rank);
            board120ToBoard64[square] = square64;
            board64ToBoard120[square64] = square;
            square64++;
        }
    }
}

void initAll() {
    initBoardConversion();
}
