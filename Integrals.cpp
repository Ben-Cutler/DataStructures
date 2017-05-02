/****
Benjamin Cutler
bcutlerp3.cpp

Purpose : To compute the integral of one of two functions within a margin of error 'epsilon'

Inputs : Inputs an integer which will integrate one of two functions or exit from the program,
a float named 'epsilon' which is the precision we integrate to,
and a float named 'rightx' which is to what value of x we integrate to.

Outputs : A table which tells the user:
which function number is being integrated,
the rightmost x they entered
What Epsilon they entered,
Then the number of rectangles used compute the integral
as well as the left and right sum displayed to four decimal places.

**/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
const int MAXINTERVALS = 5000;

void integrate(int num, float eps , float rightx); // This function calls the numerical integrator, and displays the data
float integratenumerically(int num, int intervals , float rightx ,string); // This carries out the left and rightpoint integration
float f1(float); // Output = (input^2) +3
float f2(float); // Output = 2*sqrt(input)

int main(){

    int fctnum; // This integer (1,2,or 3) will be used to get function 1, function 2, or exit.
    float epsilon; // How close the left integral and right integral should be
    float rightx; // Upper bound of the integral

    do{ // This Do-While loop is because the program should compute integrals until the user sets 'fctnum = 3'


        cout << "Please enter a integer corresponding to a function to integrate" << endl;
        cout << "Function '1' is y = x^2 +3 " << endl << "Function '2' is y = 2 sqrt(x) " << endl;
        cout << "Press 3 to exit the program" << endl << endl << endl;
        cin >> fctnum;

        while (!(fctnum == 1 || fctnum == 2 || fctnum == 3)){  //  If the user tries to make 'fctnum' 4 or something, this will trap that bad input.
                cout << "Please enter a valid input!" << endl;
                cin >> fctnum;
        }

        if (fctnum !=3){ // If the user doesn't enter 3, then we prompt them for an epsilon and a rightmost x which we can use as parameters for the integral.
            cout << "Please enter a value for epsilon!" << endl;
            cin >> epsilon ;
            cout << "Enter a value for the rightmost spot" << endl;
            cin >> rightx ;
            integrate (fctnum,epsilon,rightx); // This passes all the data which the user entered to a function that will solve the given problem

        }

    }while (fctnum !=3); // end of do-while loop. We break from the loop if the user enters 3

    cout << "Bye!" << endl; // Shows the program ended
    return 0;
}

void integrate (int fctnum , float epsilon , float rightx){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    fctnum   : An int which is choses the function to integrate. Pass by val
    epsilon  : A float which is how close the left sum has to be to the right sum. Pass by Val
    rightx   : A float which is the upper bound of the integral. Pass by Val

    Post- conditions:
    Returns nothing.

    Purpose : Use Upper/Lower sum to integrate a function within a margin of error, epsilon. Then it displays the data.
    $*$*$*$*$*$*$*$*$*$*$*/

    int intervals ; // Number of steps the for loop takes or how many 'rectangles' are being used
    float leftsum; // Computed value of the left sum taken at the interval
    float rightsum; // Computed value of right sum taken at interval.
    intervals = 0; // Number of squares. Increases first, then is used to compute the integral


    do{
            intervals++; // ups the interval by 1
            leftsum = integratenumerically(fctnum,intervals,rightx , "Left"); // Computes Left sum
            rightsum = integratenumerically(fctnum,intervals,rightx, "Right"); // Computer Right sum

    }while ( (abs (rightsum-leftsum) >= abs(epsilon)) && (intervals < MAXINTERVALS) ); // Forces a break from while loop if the left sum and right sum are within epsilon of each other,or the number of intervals if >=5,000
    // The Abs is there in case the user enters a negative x value

    if (intervals == MAXINTERVALS){ // If there are too many intervals we display a special message
            cout << "Woah dude! Too many sub intervals! Use a larger epsilon" << endl;
    } // If there are not 5,000 intervals we display the user's input, and the values of each sum, and how many rectangles were used to compute that sum.

        cout << "Function Chosen: " << setw(4) << fctnum << endl;
        cout << "Rightmost x :" << setw(8) << rightx << endl;
        cout << "Epsilon: " << setw(12) << epsilon << endl;
        cout << endl;
        cout << fixed << showpoint; // Used to round correctly
        cout << "Number of Intervals:" << setw(9) << intervals << endl;
        cout << "Upper (Right) Sum:" << setw(11) << setprecision(4) << rightsum << endl;
        cout << "Left (Lower) Sum: " << setw(11) << setprecision(4) << leftsum << endl;

    return ; // Void type.
}
float integratenumerically(int num, int intervals , float rightx,string text){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    num       : An Int which has the same purpose as 'fctnum' to make sure the correct function is integrated. Pass by val
    intervals : How many times the for loop should go around or how many rectanges we are using in our Riemann sum. Pass by val
    rightx    : A float which is our integral upper bound. Pass by val
    text      : A string that is "Left" or "Right" Used to determine if we are doing a left integral or a right integral. Pass by val

    Post-Condition
    sum       : A float which is the numerical integral value. The final value of the Riemann Sum.

    Purpose:
    To integrate the function named by 'num' with 'intervals' steps up to 'rightx' with a scheme that is a 'text' sum.

    $*$*$*$*$*$*$*$*$*$*$*/

    float sum; // The total computed Riemann Sum
    float dx; // The width of each rectangle. In a proper integral this goes to 0
    float x; // Where we are in x space.
    x=0; // We start at 0
    sum = 0;
    dx = (rightx ) /intervals; // dx * intervals = rightx,
    int i;
    // We do the integration this way so that we don't have to write a three more functions that are very similar.

      // Left endpoint. Start with the rectangle on the left, Right starts with the rectangle of the right.
    for (i=0;i<intervals;i++){
        if (text == "Right"){
            x = x+dx;}
        if ( num == 1){
            sum = sum + dx * f1(x);} // Rectangle area = width * height
        else if (num == 2){
            sum = sum + dx * f2(x);}
        if (text == "Left"){
            x = x+dx;}
        }

    return sum; // Returns the Riemann sum.
}
float f1(float x){ // Function 1 is output = input^2 +3
    /*$*$*$*$*$*
    Pre-Condition :
    'x' : a float, where we are in x space. Pass by Value

    Post-Condition:
    'y' : a float which is x^2 +3

    Purpose:
    We need to know the function to integrate it

    $*$*$*$*$*$*/
    float y;
    y = pow(x,2) +3;
    return y;
}

float f2(float x){
    /*$*$*$*$*$*
    Pre-Condition :
    'x' : a float, where we are in x space. Pass by Value

    Post-Condition:
    'y' : a float which is 2*sqrt(x)

    Purpose:
    We need to know the function to integrate it

    $*$*$*$*$*$*/
    float y;
    y = 2 * sqrt(x);
    return y;
}

