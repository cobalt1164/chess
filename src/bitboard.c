#include "types.h"
#include "stdio.h"

void printBitBoard(U64 board) {
    int file = FILE_A;
    int rank = RANK_1;
    int square = A1;
    U64 shift = 1ULL;

    printf("\n");
    for (int file = FILE_A; file <= 8; ++file) {
        for (int rank = RANK_1; rank <= 8; ++rank) {
            square = fileRankTo64(file, rank);
            
            if ((shift << square) & board)
                printf("X");
            else
                printf("-");
        } 
        printf("\n");
    }
}    
            
