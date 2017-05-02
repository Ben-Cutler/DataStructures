/*$*$*$*$*$*$*$*$*$*$*$
Benjamin B Cutler

Program : bcutlerP4.cpp

Purpose : To get a sudoku board from the user, then display it, and check it for errors

Input : A text file, which is used in the method ‘ fillboard’. This text file has 81 numbers in it.

Output : A nice board, a message saying which columns are wrong, and another message saying wether the board is right or not.
$*$*$*$*$*$*$*$*$*$*$*$*/

#include <iostream>
#include<fstream>
const int rowSize = 9; // Size of each row / Column.
const int numBoxes=3; // Number of Boxes we print. Should always be three, but it might be change worthy?
using namespace std;
class sudoku{
    /*
    Sudoku Class holds a 9x9 board, and three methods:
    One method (Fill Board) fills the board from a text file that the user enters
    One method (Display Board) displays the board
    One Method (testboard) that tests whether or not the board is correct or not
    */
    int board[rowSize][rowSize]; // start with a 9x9 board, which is empty of relevant data
    void printANumFreeRow(); // This method is used when we want to print the header of the board
    void printANumRow(int); // This method is used when we want to print a row of sudoku numbers. The integer inputted is what row we print
    bool testARowOrCol(int rowToUse, string rowOrCol); // Tests both rows and columns to see if there are any redundant values in either. The algorithm is similar, so they are the same method
    bool testAllSquares (); // Tests for repeated values in the 3x3 'boxes'

public:
    void fillboard(); // Gathers data from a textfile which the user enters
    void displayboard(); // Prints a handsome board
    void testboard(); // Tests the board for errors
};

void sudoku::fillboard (){

    /*$*$*$*$*$*$*$*$*$*$*$*$*$
    Inputs : Prompts user for the name of a .txt file, the user input is a cstring which is less than 20 chars. If the cstring is the name of a file with 81 numbers in it, then it generates a sudoku board. This will keep asking the user for a file
    Outputs : Returns no values, but changes the value of the board to an array corresponding to the text file that the user entered.
    Purpose : Fills the sudoku board with the numbers the user's text file has. If the user enters an incorrect text file, then it will keep asking
    *$*$*$*$*$*$*$*$*$*$*$*$*$*$*/
    const int ASCIItoInt = 48;
    const int sizeoftextfilename = 20; // The size of the text file's name
    ifstream inFP; // File pointer for the text file the user enters
    char textfilename[sizeoftextfilename]; // A cstring which the user enters
    cout << "This project is totally complete" << endl;
    cout << "What is the name of the text file you want to open?" << endl;
    cout << "(For example : p4input.txt)" << endl;
    cin >> textfilename; // Here's where the user enters their filename
    inFP.open(textfilename ); // sets the file pointer to the text document

    while (!inFP){// Makes sure that there is an address associated with the pointer
        cout << "No file with that name detected. Did you mean: " << textfilename << ".txt ? " << endl;
        cin >> textfilename;
        inFP.open(textfilename ); // sets the file pointer to the text document
    }

    char sudokunumber; // We have to get the number for the sudoku board one at a time, so the easiest way is using a char and turning it into an int. If we used int sudokunumber then it would grab all 9 ints from the row
    for(int i=0 ; i<rowSize;i++){
        for(int j = 0 ; j<rowSize ; j++){
            inFP >> (sudokunumber); // We get a number from the file

            board[i][j] = int(sudokunumber) - ASCIItoInt; // we turn the char into an int, BUT we remove 48 because the ASCII value of 0 is 48, the ASCII value of 1 is 49... etc. We put this int into the array.
        }
    }
    inFP.close(); // Finally we close the file.
}

void sudoku::displayboard(){
 /*
Inputs : The user enters no data, and this changes no data
Outputs : This script prints rows which have numbers, or are dividers of 3x3 boxes
Purpose : To display the data in an aesthetically pleasing manner
 */
     for (int i=0; i<rowSize/numBoxes; i++){
        printANumFreeRow();  // This displays the nice bar on the top of the sudoku board

        for(int j = 0; j<rowSize/numBoxes;j++){
            printANumRow(rowSize/numBoxes*i +j); // This displays the rows which have numbers in them.
            }
        }
    printANumFreeRow(); // We have a bar on the bottom of the board, so we print a final one.
}

void sudoku::printANumFreeRow() {
    /*
    Input <none>
    Output : A bar of text
    Purpose :This just prints a short row which is a delimiter between 3x3 grids.
    */

    cout << "+-------+-------+-------+" << endl;

}

void sudoku::printANumRow(int num){
    /*
    Inputs : Takes in no data, but references the board
    Outputs : Displays a row which has numbers in it.
    Purpose : To display rows which have numbers in them
    */
    for (int i = 0; i<rowSize ; i++){
       if (!( i%numBoxes )){
             cout << "| "; // There should be a bar before the 0th value, the 3rd value, the 6th integer
       }
        cout << board[num][i] << ' '; // prints the board and a space char
    }
    cout << '|' << endl; // There needs to be a bar at the very end of the row
}



void sudoku:: testboard(){
    /*
    Inputs : references 'board'
    Outputs : Tells the user if their board is correct of not
    Purpose : To tell the user if their board is correct or not
    */
    bool failed; // Ultimately we are interested in whether the board "Passes" or "Fails" the tests.
    failed = 0; // We presume it passes though!

        for (int i=0;i<rowSize;i++){
                failed += testARowOrCol(i,"Row");
                failed += testARowOrCol(i,"Column"); // We test each row and each column individually and if one fails, we set the failed bool equal to 1
        }
        failed += testAllSquares(); // finally we test all of the squares to see if one of them fails.

        if ( failed) { // If it failed, then we print this sad message
                cout <<endl << "This sudoku board is not correct" << endl;
        } else {
            cout << endl << endl; // If we didn't fail, then we print a nice message
            printANumFreeRow();
            cout << "|   This is correct!    |"<< endl;
            printANumFreeRow();
        }


}
bool  sudoku::testARowOrCol(int rowOrColNum,string rowOrCol){
    /*
    Inputs : An Int 'rowOrColNum' which will be [0,8]. It will be either a row or a column, which is number 'rowORColNum'. The string 'rowORCol' tells is of the number corresponds to a row or a col
    Outputs: Returns a bool, 'failed' . If it returns 0 then it didn't find a duplicate value in the row or column If it returns 1 it also displays the repeated value, and column/row
    Purpose: To test a row or column for duplicate values.
    */

    bool failed ; // We are only interested if there is a duplicate value, not how many
    failed = 0; // But we still presume there are no duplicates.
        for (int i=0; i<rowSize && failed ==0 ;i++){ // We go through each row with two for loops
                for (int j=i+1 ;j<rowSize && failed ==0 ;j++){ // We start j with i+1 so that we don't double count ; if a !=b, then b!=a, and we shouldn't bother checking.

                    if (rowOrCol == "Row"){ // We test rows and cols similar enough such that they can be in the same method
                        if (( board[rowOrColNum][i]) == (board[rowOrColNum][j])  ) { // If two values are the same we have a duplicate value, then it fails
                            failed = 1;
                            cout << "Repeated Value of " << board[rowOrColNum][j] << " in " << rowOrCol << ' ' << (rowOrColNum +1) << endl; // We then say the duplicated value, and the value of the duplicated value
                        } // end of same value if statement
                    }else if (rowOrCol == "Column") { // We do the same thing for a column, except the ordering is opposite of what we loop through.
                        if ( board[i][rowOrColNum] == board[j][rowOrColNum]  ) {
                            failed = 1;
                            cout << "Repeated Value of " << board[j][rowOrColNum] << " in " << rowOrCol  << ' ' << (rowOrColNum +1 )<< endl;
                        } // end of sameness if statement
                } // end of if-else for Row/Column

            } // end of j loop
        } // end of i loop
        return failed;
} // End of Method

bool sudoku::testAllSquares(){
    /*
    Inputs: None
    Outputs: a bool: 'atLeastOneFail'. If at least one square fails then we return a 0.
    Purpose: To determine if there is a duplicate value in all the squares.
    */
    int squareWeAreOn; // Counts 1 - <rowSize>. If square n fails, then it will be displayed to the user.
    int squareToRow[rowSize]; // In order to simplify the problem, we turn the box into a 1x9 array, and check if the array is valid.
    int arrayCounter; // Another counting variable.
    bool failed; // checks if the specific 3x3 box failed
    bool atLeastOneFail; // Checks if there is at least one fail in one 3x3 box.
    squareWeAreOn = 0; // We will increase this at the start, so we start on 0
    for (int i = 0 ; i<rowSize; i+= numBoxes){ // We start at the top left corner of each box
            for (int j = 0 ; j<rowSize ; j +=numBoxes){
                    squareWeAreOn++; // and increase the number of the square we are on
                    arrayCounter = 0;
                        for (int k = 0; k<numBoxes ; k++){
                            for (int l=0 ; l<numBoxes;l++){
                                    squareToRow [arrayCounter] = board[l+ j][k+i]; // We then go through the box, and populate the array with values that were in the box
                                    arrayCounter++;
                            } // end l loop
                    }//end k loop
                    failed = 0; // We reset failed for every box. The failed variable stops the looping when a box fails, but we want to test every box.
                    for (int m = 0;m<rowSize && failed == 0;m++){
                            for (int n=m+1 ;n<rowSize && failed ==0 ;n++){ // We set n = m+1 so we don't double count
                                    if ( squareToRow[m] == squareToRow[n]  ){ // We check for a duplicate value
                                        failed = 1; // and if we find a duplicate value, we have a box failed
                                        atLeastOneFail = 1; // And at least one failed in the boxes
                                        cout << "Repeated value of " << squareToRow[m] << " in Box " << squareWeAreOn<< endl; // And we tell the user.
                                    }
                            }
                    }
            } // end of 'j' for loop
    } // end 'i' for loop
    return atLeastOneFail;
} // end method

int main(){
    sudoku sudokuBoard; // Make an instance of the sudoku board
    sudokuBoard.fillboard(); // Fill it with values
    sudokuBoard.displayboard(); // Display the board
    sudokuBoard.testboard(); // Tell the user if the board is any good
    return 0;

}
