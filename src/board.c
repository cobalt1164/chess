#include "stdio.h" 
#include "types.h"
#include "assert.h"

void updatePieceLists(BOARD_STRUCT *board) {
    int piece, index, color;

    for (index = 0; index < BOARD_NUM; ++index) {
        piece = board->pieces[index];
        color = pieceColor[piece];

        if (piece != EMPTY) {
            if (majorPiece[piece] == TRUE) board->majorPieces[color]++;
            if (minorPiece[piece] == TRUE) board->minorPieces[color]++;
            if (bigPiece[piece] == TRUE) board->bigPieces[color]++;
        }
    }

    board->material[color] += pieceValue[piece];

    board->pieceList[piece][board->numPieces[piece]] = index;
    board->numPieces[piece]++;

    if (piece == WHITE_KING) board->kingSquares[WHITE] = index;
    if (piece == BLACK_KING) board->kingSquares[BLACK] = index;

}

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

int parseFen(char *fen, BOARD_STRUCT *board) {
    assert(fen != NULL);
    assert(board != NULL);

    int rank = RANK_8;
    int file = FILE_A;
    int piece = 0;
    int count = 0;
    int i = 0;
    int square64 = 0;
    int square120 = 0;

    resetBoard(board);
    
    while ((rank >= RANK_1) && *fen) {
        count = 1;
        switch (*fen) {
            case 'p': piece=BLACK_PAWN; break;
            case 'r': piece=BLACK_ROOK; break;
            case 'n': piece=BLACK_KNIGHT; break;
            case 'b': piece=BLACK_BISHOP; break;
            case 'k': piece=BLACK_KING; break;
            case 'q': piece=BLACK_QUEEN; break;
            case 'P': piece=WHITE_PAWN; break;
            case 'R': piece=WHITE_ROOK; break;
            case 'N': piece=WHITE_KNIGHT; break;
            case 'B': piece=WHITE_BISHOP; break;
            case 'K': piece=WHITE_KING; break;
            case 'Q': piece=WHITE_QUEEN; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                      piece = EMPTY;
                      count = *fen - '0';
                      break;

            case '/': case ' ':
                      rank--;
                      file = FILE_A;
                      fen++;
                      continue;

            default:
                      printf("Error in FEN parse\n");
                      return -1;
        }

        for (i = 0; i < count; ++i) {
            if (piece != EMPTY) {
                board->pieces[fileRankTo120(file, rank)] = piece;
            }
            file++;
        }
        fen++;
    }

    assert(*fen == 'w' || *fen == 'b');

    board->side = (*fen == 'w') ? WHITE : BLACK;
    fen += 2;

    for (i = 0; i < 4; ++i) {
        if (*fen == ' ') {
            break;
        }

        switch (*fen) {
            case 'K': board->castlePerms |= WHITE_KING_CASTLING; break;
            case 'Q': board->castlePerms |= WHITE_QUEEN_CASTLING; break;
            case 'k': board->castlePerms |= BLACK_KING_CASTLING; break;
            case 'q': board->castlePerms |= BLACK_QUEEN_CASTLING; break;
            default:
                      break;
        }
        fen++;
    }

    fen++;

    assert(board->castlePerms >= 0 && board->castlePerms <= 15);
    
    if (*fen != '-') {
        // Simple way to convert file/rank string to int
        file = fen[0] - 'a';
        rank = fen[1] - '1';
        assert(file >= FILE_A && file <= FILE_H);
        assert(rank >= RANK_1 && rank <= RANK_8);

        board->enPassant = fileRankTo120(file, rank);
    }

    board->positionKey = genPositionKey(board);
    updatePieceLists(board);

    return 0;
}

void printBoard(const BOARD_STRUCT *pos) {
    int square, file, rank, pieceOnSquare;
    printf("Board:\n");

    for (rank = RANK_8; rank >= RANK_1; --rank) {
        printf("%d  ", rank + 1);
        
        for (file = FILE_A; file <= FILE_H; ++file) {
            square = fileRankTo120(file, rank);
            pieceOnSquare = pos->pieces[square];
            printf("%3c", pieceChars[pieceOnSquare]);
        }
        printf("\n");
    }
    printf("\n   ");
    
    for (file = FILE_A; file <= FILE_H; ++file) {
        printf("%3c", 'a' + file);
    }
    printf("\n");
    printf("side:%c\n", sideChars[pos->side]);
    printf("enPassant:%d\n", pos->enPassant);
    printf("castling:%c%c%c%c\n", 
            pos->castlePerms & WHITE_KING_CASTLING ? 'K' : '-',
            pos->castlePerms & WHITE_QUEEN_CASTLING ? 'Q' : '-',
            pos->castlePerms & BLACK_KING_CASTLING ? 'k' : '-',
            pos->castlePerms & BLACK_QUEEN_CASTLING ? 'q' : '-'
          );
    printf("positionKey:%llX\n",pos->positionKey);
}
