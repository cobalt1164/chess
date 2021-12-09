#include "types.h"
#include "stdio.h"

// Matt Taylor's Folding Trick

const int lsb_64_table[64] = {
	63, 30,  3, 32, 59, 14, 11, 33,
	60, 24, 50,  9, 55, 19, 21, 34,
	61, 29,  2, 53, 51, 23, 41, 18,
	56, 28,  1, 43, 46, 27,  0, 35,
	62, 31, 58,  4,  5, 49, 54,  6,
	15, 52, 12, 40,  7, 42, 45, 16,
	25, 57, 48, 13, 10, 39,  8, 44,
	20, 47, 38, 22, 17, 37, 36, 26
};

int popBit(U64 *bb) {
	U64 b = *bb ^ (*bb - 1);
	unsigned int folded = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
	*bb &= (*bb - 1);
    return lsb_64_table[folded * 0x78291ACF >> 26];
}

int countBits(U64 bb) {
    int i;
    for (i = 0; bb; ++i, bb &= (bb - 1));
    return i;
}


void printBitBoard(U64 board) {
    int file = FILE_A;
    int rank = RANK_1;
    int square = A1;
    U64 shift = 1ULL;

    printf("\n");
    for (int rank = RANK_8; rank >= RANK_1; --rank) {
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
            
