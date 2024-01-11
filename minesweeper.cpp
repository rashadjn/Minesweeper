#include <iostream>
#include "geesespotter_lib.h"

char * create_board(std::size_t x_dim, std::size_t y_dim){
    char* board = new char[x_dim * y_dim]{};

    for (std::size_t i{0}; i < x_dim * y_dim; ++i) {
        board[i] = 0;
    }
    return board;

}
void clean_board(char * board){
    delete[] board;
    board = nullptr;

}
// helper function to find index when given coordinates
int index(int x, int y, int x_dim){
    return (y * x_dim + x);
}

void print_board(char * board, std::size_t x_dim, std::size_t y_dim) {
    for (std::size_t  y = 0; y <  y_dim;  y++) {
        for(std::size_t x  = 0 ; x  <  x_dim;  x++) {
            char field  = board[index(x, y, x_dim)];
            // when field is marked
            if(field & marked_mask()){
                std::cout << "M";
            }
            // when field is hidden
            else if(field & hidden_mask()){
                    std::cout << "*";
            }
            // everything else
            else {
                std::cout << (field & value_mask());
            }
        }
        std::cout << std::endl;
    }

}

void hide_board(char * board, std::size_t x_dim, std::size_t y_dim) {
    for (std::size_t i = 0; i < x_dim * y_dim; i++){
        board[i] |= hidden_mask(); 
    }
}


int mark(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){
    char field = board[index(x_loc, y_loc, x_dim)];
    //if field is hidden
    if (field & hidden_mask()){
        board[index(x_loc, y_loc, x_dim)]^= marked_mask();
        return 0;
    }
    //if field is already revealed
    return 2;

}





void compute_neighbours(char * board, std::size_t x_dim, std::size_t y_dim){
    //iterate through every field in the board

    for (std::size_t i = 0; i < y_dim*x_dim; i++) {
        int count = 0;

        // coordinate system
        int x = i % x_dim;
        int y = i / x_dim;

    
        // if no goose, compute neighbors
        if (board[i] != 9) {

            // if we are in first column:
            if (x == 0) {
                // top left corner
                if (i == 0) {
                    if (board[i+1] == 9) {
                        count++;
                    }
                    if (board[i+x_dim] == 9) {
                        count++;
                    }
                    if (board[i+x_dim+1] == 9) {
                        count++;
                    }
                }
                 
                // every row except for last and first
                else if (y < y_dim-1) {
                    if (board[i-x_dim] == 9) {
                        count++;
                    }
                    if (board[i-x_dim+1] == 9) {
                        count++;
                    }
                    if (board[i+1] == 9) {
                        count++;
                    }
                    if (board[i+x_dim] == 9) {
                        count++;
                    }
                    if (board[i+x_dim+1] == 9) {
                        count++;
                    }
                }

                // bottom left corner
                else if (y == y_dim-1) {
                    if (board[i-x_dim] == 9) {
                        count++;
                    }
                    if (board[i-x_dim+1] == 9) {
                        count++;
                    }
                    if (board[i+1] == 9) {
                        count++;
                    }
                }
            }

            // far right column:
            else if (x == x_dim - 1) {

                // top right corner
                if (y == 0) {
                    if (board[i - 1] == 9) {
                        count++;
                    }
                    if (board[i + x_dim - 1] == 9) {
                        count++;
                    }
                    if (board[i + x_dim] == 9) {
                        count++;
                    }
                } 
                    
                // every row except for the last and first
                else if (y < y_dim - 1) {
                    if (board[i - x_dim] == 9) {
                        count++;
                    }
                    if (board[i - x_dim - 1] == 9) {
                        count++;
                    }
                    if (board[i - 1] == 9) {
                        count++;
                    }
                    if (board[i + x_dim - 1] == 9) {
                        
                        count++;
                    }
                    if (board[i + x_dim] == 9) {
                        count++;
                    }
                } 
                
                // bottom right corner
                else {
                    if (board[i - x_dim] == 9) {
                        count++;
                    }
                    if (board[i - x_dim - 1] == 9) {
                        count++;
                    }
                    if (board[i - 1] == 9) {
                        count++;
                    }
                    }
            } 

            // middle columns
            else {
                // top middle
                if (y == 0) { 
                    if (board[i - 1] == 9) {
                        count++;
                    }
                    if (board[i + 1] == 9) {
                        count++;
                    }
                    if (board[i + x_dim - 1] == 9) {
                        count++;
                    }
                    if (board[i + x_dim] == 9) {
                        count++;
                    }
                    if (board[i + x_dim + 1] == 9) {
                        count++;
                    }
                } 
                // middle rows
                else if (y < y_dim - 1) { 
                    if (board[i - x_dim - 1] == 9) {
                        count++;
                    }
                    if (board[i - x_dim] == 9) {
                        count++;
                    }
                    if (board[i - x_dim + 1] == 9) {
                        count++;
                    }
                    if (board[i - 1] == 9) {
                        count++;
                    }
                    if (board[i + 1] == 9){

                        count++;
                    }
                    if (board[i + x_dim - 1] == 9) {
                        count++;
                    }
                    if (board[i + x_dim] == 9) {
                        count++;
                    }
                    if (board[i + x_dim + 1] == 9) {
                        count++;
                    }

                } 
                    
                // bottom middle
                else { 
                    if (board[i - x_dim - 1] == 9) {
                        count++;
                    }
                    if (board[i - x_dim] == 9) {
                        count++;
                    }
                    if (board[i - x_dim + 1] == 9) {
                        count++;
                    }
                    if (board[i - 1] == 9) {
                        count++;
                    }
                    if (board[i + 1] == 9) {
                        count++;
                    }
                }
            }

            // count =  number of adjacent geese
            // set last 4 bits of board[i] to count
            board[i] = count;

        }
    }

}






bool is_game_won(char * board, std::size_t x_dim, std::size_t y_dim){
    for (int i{0}; i < (x_dim*y_dim); i++) {
        if ((board[i] & value_mask()) != 9) {
            if ((board[i] & hidden_mask())) {
                return false;
            }
        }
    }

    return true;   

}





int reveal(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){
    

//if field is marked 
char field = board[index(x_loc, y_loc, x_dim)];
    if((field & marked_mask()) == marked_mask()){
        return 1;
    }
//if field is already revealed
    if((field & hidden_mask()) !=hidden_mask())   {
         return 2;      
            }
//if there is goose in field
    if((field & value_mask()) == 9){
    board[index(x_loc, y_loc, x_dim)]^= hidden_mask();

    return 9;
    }
// reveal field if it is not marked, revealed, or a goose
    board[index(x_loc, y_loc, x_dim)]^= hidden_mask();


//function for when fields are equal to 0
if ((field & value_mask()) == 0) {

// coordinate system
int x = x_loc;
int y = y_loc; 


// top left corner 
if ( x==0 && y==0) {
    if (board[index(x+1, y, x_dim)] & hidden_mask()){
        board[index(x+1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y+1, x_dim)] & hidden_mask()){
        board[index(x, y+1, x_dim)] ^= hidden_mask();
        }
    if (board[index(x+1, y+1, x_dim)] & hidden_mask()){
        board[index(x+1, y+1, x_dim)] ^= hidden_mask();
     }
 }
// top right corner 
else if ( x==x_dim-1 && y==0) {
    if (board[index(x-1, y, x_dim)] & hidden_mask()){
        board[index(x-1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y+1, x_dim)] & hidden_mask()){
        board[index(x, y+1, x_dim)] ^= hidden_mask();
    }
    if (board[index(x-1, y+1, x_dim)] & hidden_mask()){
        board[index(x-1, y+1, x_dim)] ^= hidden_mask();
    }
}

 

// bottom left corner 
else if ( x==0 && y==y_dim-1) {
    if (board[index(x+1, y, x_dim)] & hidden_mask()){
        board[index(x+1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y-1, x_dim)] & hidden_mask()){
         board[index(x, y-1, x_dim)] ^= hidden_mask();
    }
    if (board[index(x+1, y-1, x_dim)] & hidden_mask()){
        board[index(x+1, y-1, x_dim)] ^= hidden_mask();
    }

}

// bottom right corner 
else if ( x==x_dim-1 && y==y_dim-1) {
    if (board[index(x-1, y, x_dim)] & hidden_mask()){
        board[index(x-1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y-1, x_dim)] & hidden_mask()){
    board[index(x, y-1, x_dim)] ^= hidden_mask();
    }
    if (board[index(x-1, y-1, x_dim)] & hidden_mask()){
    board[index(x-1, y-1, x_dim)] ^= hidden_mask();
    }

}

//top edge
else if (y==0){
    if (board[index(x-1, y, x_dim)] & hidden_mask()){
        board[index(x-1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x+1, y, x_dim)] & hidden_mask()){
        board[index(x+1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y+1, x_dim)] & hidden_mask()){
        board[index(x, y+1, x_dim)] ^= hidden_mask();
    }
    if (board[index(x-1, y+1, x_dim)] & hidden_mask()){
        board[index(x-1, y+1, x_dim)] ^= hidden_mask();  
    }
    if (board[index(x+1, y+1, x_dim)] & hidden_mask()){
        board[index(x+1, y+1, x_dim)] ^= hidden_mask();  
    } 


}

//bottom edge
else if (y==y_dim-1){
    if (board[index(x-1, y, x_dim)] & hidden_mask()){
        board[index(x-1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x+1, y, x_dim)] & hidden_mask()){
        board[index(x+1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y-1, x_dim)] & hidden_mask()){
        board[index(x, y-1, x_dim)] ^= hidden_mask();  
    } 
    if (board[index(x-1, y-1, x_dim)] & hidden_mask()){
        board[index(x-1, y-1, x_dim)] ^= hidden_mask();   
    }
    if (board[index(x+1, y-1, x_dim)] & hidden_mask()){
        board[index(x+1, y-1, x_dim)] ^= hidden_mask();   
    }


}

//left edge
else if (x==0){
    if (board[index(x+1, y, x_dim)] & hidden_mask()){
        board[index(x+1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y+1, x_dim)] & hidden_mask()){
        board[index(x, y+1, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y-1, x_dim)] & hidden_mask()){
    board[index(x, y-1, x_dim)] ^= hidden_mask();   
    }
    if (board[index(x+1, y-1, x_dim)] & hidden_mask()){
        board[index(x+1, y-1, x_dim)] ^= hidden_mask();   
    }
    if (board[index(x+1, y+1, x_dim)] & hidden_mask()){
        board[index(x+1, y+1, x_dim)] ^= hidden_mask();   
    }

}

//right edge
else if (x==x_dim-1){
    if (board[index(x-1, y, x_dim)] & hidden_mask()){
        board[index(x-1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y+1, x_dim)] & hidden_mask()){
        board[index(x, y+1, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y-1, x_dim)] & hidden_mask()){
        board[index(x, y-1, x_dim)] ^= hidden_mask();   
    }
    if (board[index(x-1, y-1, x_dim)] & hidden_mask()){
        board[index(x-1, y-1, x_dim)] ^= hidden_mask();   
    }
    if (board[index(x-1, y+1, x_dim)] & hidden_mask()){
        board[index(x-1, y+1, x_dim)] ^= hidden_mask();   
    }
 }


//middle fields
else {
    if (board[index(x-1, y, x_dim)] & hidden_mask()){
    board[index(x-1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x+1, y, x_dim)] & hidden_mask()){
        board[index(x+1, y, x_dim)] ^= hidden_mask();
    }
    if (board[index(x, y+1, x_dim)] & hidden_mask()){
        board[index(x, y+1, x_dim)] ^= hidden_mask();   
    }
    if (board[index(x, y-1, x_dim)] & hidden_mask()){
        board[index(x, y-1, x_dim)] ^= hidden_mask();   
    }
    if (board[index(x+1, y+1, x_dim)] & hidden_mask()){
        board[index(x+1, y+1, x_dim)] ^= hidden_mask();
    }
    if (board[index(x-1, y+1, x_dim)] & hidden_mask()){
        board[index(x-1, y+1, x_dim)] ^= hidden_mask();
    }
    if (board[index(x+1, y-1, x_dim)] & hidden_mask()){
        board[index(x+1, y-1, x_dim)] ^= hidden_mask();
    }
    if (board[index(x-1, y-1, x_dim)] & hidden_mask()){
        board[index(x-1, y-1, x_dim)] ^= hidden_mask();
    }

    }


return 0;

}
return 0;

}
