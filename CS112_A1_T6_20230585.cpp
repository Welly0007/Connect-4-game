// Program: Connect 4 Board Game


// Author:  Mohamed Walid 20230585


// Version: 2.0 Optimized


// Date:  Feb 22 2024


#include <iostream>
using namespace std;




// Golbal vars that are used frequently;
char board[6][7];       //  2d matrix of chars
bool playerX;           //  bool to control the turn
int gravity_ordr[7];    //  array to define the row in which the piece will be dropped, Gravity array

//  Functions

// To set every char in board to '_' and reset gravity ordr to the bottom of the board;
void reset_board(){
    // Initialize the board to empty '_' and reset gravity order to bottom
    for(int i=0;i<6;i++)
        for(int j=0;j<7;j++)
            board[i][j]='_';
    for(int i=0;i<7;i++)
        gravity_ordr[i]=5;
}

//Print the board with special form
void display_board(){
    // Display the board with row and column numbers
    for(int i=0;i<6;i++){
        cout<<i+1<<")  ";
        for(int j=0;j<7;j++){
            cout<<"|  "<<board[i][j]<<"  ";
        }
        cout<<"|";
        if(i<5){
            cout<<"\n    ___________________________________________\n";
        }else{
            cout<<"\n     -";
            for(int j=0;j<7;j++) {
                cout << "[" << j+1 << "]- ";
                if(j!=6)
                    cout<<"-";
            }
        }
    }
    cout<<"\n\n";
}

// handles the move of the player and returns it to be used in check_winner
int move_player(bool playerx){
    char chr;
    if(playerX) chr='X';
    else chr='O';
    if(playerx)
        cout<<"Player X ";
    else
        cout<<"Player O ";
    cout<<"Enter column number (1-7):";
    int mv_num;
    // Get player's move and validate
    while (true){
        cin>>mv_num;
        //handle invalid range
        if(mv_num>7 || mv_num<1){
            cout<<"please enter value from 1-7:";
            continue;
        }
        mv_num--;
        //handle occupied space
        if(board[gravity_ordr[mv_num]][mv_num]!='_'){
            cout<<"select empty space:";
        }
        else{
            board[gravity_ordr[mv_num]][mv_num]=chr;    // set space to player's char
            gravity_ordr[mv_num]--;                     // increasing gravity height
            return mv_num;                              // returning mv_num
        }
    }
}

// checks tie by looping over gravity array in every column
bool check_tie(){
    // If any column still has empty space, game is not tied
    for(int i=0;i<7;i++){
        if(gravity_ordr[i]!=-1) return false;
    }
    return true; // Game is tied
}

// Check if the current player has won
bool check_winner(int mv){
    char chr;
    if(playerX) chr='X';
    else chr='O';
    int curr_height = gravity_ordr[mv]+1, ctr=0;

    //  Check winner columns
    for(int i=0;i<7;i++){
        if(board[curr_height][i]==chr) ctr++;
        else
            ctr=0;
        if(ctr==4)
            return true; // Player wins
    }

    //  Check winner rows
    ctr=0;
    for (int i=5;i>=0;i--){
        if(board[i][mv]==chr) ctr++;
        else
            ctr=0;
        if(ctr==4)
            return true; // Player wins
    }

    //  Check Winner left-right diagonal
    ctr=0;
    int col =mv , row= 5 - curr_height;
    int start_row,start_col;
    if(col < row){
        start_row = 5 - (row-col);
        start_col = 0;
    }else if (col>row){
        start_row= 5;
        start_col= col-row;
    }else{
        start_row=5;
        start_col=0;
    }
    for (int i=0;i<6;i++){
        if(start_row-i>0 && start_col+i<7){
            if(board[start_row-i][start_col+i]==chr) ctr++;
            else
                ctr=0;
        }
        if(ctr==4)
            return true; // Player wins
    }

    //  Check Winner right-left diagonal
    ctr=0;
    row=curr_height;
    if(col-row==1){
        start_col=6;
        start_row=5;
    }else if(col==row){
        start_col=5;
        start_row=5;
    }else if(col<row){
        start_row=5;
        start_col=5-(row-col);
    }else if(col>row){
        if(col-row==2)
            start_row= 4;
        else
            start_row=3;
        start_col=6;
    }
    for (int i=0;i<6 && i <= start_row && i <= start_col;i++){
        if(start_row-i>0 && start_col+i<7){
            if(board[start_row-i][start_col-i]==chr) ctr++;
            else
                ctr=0;
        }
        if(ctr==4)
            return true; // Player wins
    }
    return false; // No winner yet
}

int main(){
    cout<<"             Welcome to Connect 4 Game";
    reset_board();      //initialize board
    playerX= true;
    bool end= false;    // to find if the game ends
    while(true) {
        cout << "\n\n";
        display_board();
        int mv = move_player(playerX);
        //  Tie check
        if (check_tie()) {
            cout<<"\n";
            display_board();
            cout << "\nTIE\n";
            end = true;
        }// Check Winner
        else if (check_winner(mv)) {
            display_board();
            if (playerX) cout << "\nPlayer X won!!!!\n";
            else cout << "\nPlayer O won!!!!\n";
            end = true;
        }
        //  Asks to play again
        if(end){
            cout << "\nDo you want to play again (Y/N):";
            string again;
            while (true) {
                cin >> again;
                if (again == "Y" || again == "y") {
                    reset_board();
                    end = false;
                    break;
                } else if (again == "N" || again == "n") {
                    cout << "See you Later !";
                    return 0;
                } else {
                    cout << "Enter a valid input (Y/N):";
                }
            }
        }else
            playerX = !playerX;     //switch turn
    }
}
