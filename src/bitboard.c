#include "types.h"
#include "stdio.h"

void printBitBoard(U64 board) {
    int file = FILE_A;
    int rank = RANK_1;
    int square = A1;
    U64 shift = 1ULL;

    printf("\n");
    for (int rank = RANK_1; rank <= RANK_8; ++rank) {
        for (int file = FILE_A; file <= FILE_H; ++file) {
            square = fileRankTo64(file, rank);
            
            if ((shift << square) & board)
                printf("X");
            else
                printf("-");
        } 
        printf("\n");
    }
}    
            
