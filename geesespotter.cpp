#include <iostream>
#include "geesespotter_lib.h"
#include "geesespotter.h"

char * createBoard(std::size_t xdim, std::size_t ydim) {
    int size = xdim*ydim;
    char * board = new char[size] {};
    
    for (int i=0; i<(xdim*ydim) ; i++) {
        board[i] = 0;
    }
    return board;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {
    for (int i=0; i<(xdim*ydim); i++) {
        if (board[i] == 9) {
            int xloc = i % xdim;
            int yloc = i / xdim;
            //up
            if(((yloc-1)>=0) && (board[(xdim*(yloc-1))+xloc]<9)) {
               board[(xdim*(yloc-1))+xloc] += 1;
            }
            //down
            if(((yloc+1)<=(ydim-1)) && (board[(xdim*(yloc+1))+xloc]<9)) {
                board[(xdim*(yloc+1))+xloc] += 1;
            }
            //left
            if(((xloc-1)>=0) && (board[(xdim*yloc)+xloc-1]<9)) {
                board[(xdim*yloc)+xloc-1] += 1;
            }
             //right
            if(((xloc+1)<=(xdim-1)) && (board[(xdim*yloc)+xloc+1]<9)) {
                board[(xdim*yloc)+xloc+1] += 1;
            }
            //up-left
            if((((yloc-1)>=0) && ((xloc-1)>=0)) && (board[(xdim*(yloc-1))+xloc-1]<9)) {
                board[(xdim*(yloc-1))+xloc-1] += 1;
            }
            //up-right
            if((((yloc-1)>=0) && ((xloc+1)<=(xdim-1))) && (board[(xdim*(yloc-1))+xloc+1]<9)) {
                board[(xdim*(yloc-1))+xloc+1] += 1;
            }
            //down-left
            if((((yloc+1)<=(ydim-1)) && ((xloc-1)>=0)) && (board[(xdim*(yloc+1))+xloc-1]<9)) {
                board[(xdim*(yloc+1))+xloc-1] += 1;
            }
            //down-right
            if((((yloc+1)<=(ydim-1)) && ((xloc+1)<=(xdim-1))) && (board[(xdim*(yloc+1))+xloc+1]<9)) {
                board[(xdim*(yloc+1))+xloc+1] += 1;
            }    
        }
    }        
}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim) {
    for (int i=0; i<(xdim*ydim); i++) {
        board[i] |= hiddenBit();
    }
}

void cleanBoard(char * board) {
    delete [] board;
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim) {
    int indxCounter{0};
    for (int i=0; i<ydim; i++) {
        for (int j=0; j<xdim; j++) {
            if(((hiddenBit() | markedBit()) & board[indxCounter]) == (hiddenBit() | markedBit())) {
                std::cout << 'M';
            } else if ((hiddenBit() & board[indxCounter]) == hiddenBit()) {
                std::cout << '*';
            } else {
                std::cout << char(board[indxCounter]+48);
            }
            indxCounter++;   
        }
        std::cout << std::endl;
    }
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std:: size_t xloc, std::size_t yloc) {
    if (((hiddenBit() | markedBit()) & board[(xdim*yloc)+xloc]) == (hiddenBit() | markedBit())) { // checking if marked at location
        return 1;
    } else if (((hiddenBit() | markedBit()) & board[(xdim*yloc)+xloc]) == board[(xdim*yloc)+xloc]) { //if not marked, check if revealed already.
        return 2;
    } else if ((board[(xdim*yloc)+xloc] ^ hiddenBit()) == 9) { // if its a goose, reveal goose (by removing hidden bit).
        board[(xdim*yloc)+xloc] ^= hiddenBit(); 
        return 9;
    } else {  //else if regular space, reveal it by removing hidden bit.
        board[(xdim*yloc)+xloc] ^= hiddenBit();  
        if (board[(xdim*yloc)+xloc] == 0) { //if location is showing 0, reveal neighbours.  --> problem
            //up
            if(((yloc-1)>=0) && (board[(xdim*(yloc-1))+xloc] < 9)) { 
                board[(xdim*(yloc-1))+xloc] ^= !(hiddenBit());
            }
            //down
            if(((yloc+1)<=(ydim-1)) && (board[(xdim*(yloc+1))+xloc] < 9)) { 
                board[(xdim*(yloc+1))+xloc] ^= !(hiddenBit());
            }
            //left
            if(((xloc-1)>=0) && (board[(xdim*yloc)+xloc-1] < 9)) { 
                board[(xdim*yloc)+xloc-1] ^= !(hiddenBit());
            }
            //right
            if(((xloc+1)<=(xdim-1)) && (board[(xdim*yloc)+xloc+1] < 9)) { 
                board[(xdim*yloc)+xloc+1] ^= !(hiddenBit());
            }
            //up-left
            if((((xloc-1)>=0) && ((yloc-1)>=0)) && (board[(xdim*(yloc-1))+xloc-1] < 9)) { 
                board[(xdim*(yloc-1))+xloc-1] ^= !(hiddenBit());
            }
            //up-right
            if((((xloc+1)<=(xdim-1)) && ((yloc-1)>=0)) && (board[(xdim*(yloc-1))+xloc+1] < 9)) { 
                board[(xdim*(yloc-1))+xloc+1] ^= !(hiddenBit());
            }
            //down-left
            if((((xloc-1)>=0) && ((yloc+1)<=(ydim-1))) && (board[(xdim*(yloc+1))+xloc-1] < 9)) { 
                board[(xdim*(yloc+1))+xloc-1] ^= !(hiddenBit());
            }
            //down-right
            if((((xloc+1)<=(xdim-1)) && ((yloc+1)<=(ydim-1))) && (board[(xdim*(yloc+1))+xloc+1] < 9)) { 
                board[(xdim*(yloc+1))+xloc+1] ^= !(hiddenBit());
            }   
        }
        return 0;
    }   
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std:: size_t xloc, std::size_t yloc) {
    if ((hiddenBit() & board[(xdim*(yloc))+xloc]) != hiddenBit()) {
        return 2;
    } else if (((hiddenBit() | markedBit()) & board[(xdim*(yloc))+xloc]) == (hiddenBit() | markedBit())) {
        board[(xdim*yloc)+xloc] ^= markedBit();
        return 0;
    } else {
        board[(xdim*yloc)+xloc] |= markedBit();
        return 0;
    }
}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim) {
    for (int i=0; i<(xdim*ydim); i++) {
        if ((((hiddenBit() & board[i]) == hiddenBit()) || ((markedBit() & board[i]) == markedBit())) && ((board[i] ^ hiddenBit()) != 9)) {
            return false;    //check if all hiddens (marked or not) have value 9. If not, return false. 
        } 
    }
    //at this point, if passed all circumstances above, should be at won state.*/
    return true;
}