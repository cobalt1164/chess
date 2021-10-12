#include "types.h"

// Conversion between the 64 bit board and the size 120 array board is done by
// indexing conversion arrays

int board120ToBoard64[BOARD_NUM];
int board64ToBoard120[64];

void initBoard120ToBoard64() {
   int i = 0;

   // Initialize each element with an impossible value as a fail-safe
   for (i = 0; i < BOARD_NUM; ++i) {
       board120ToBoard64[i] = 65;
   }

   for (i = 0; i < 64; ++i) {
       board64ToBoard120[i] = 120;
   }
}

void initialize() {

}
