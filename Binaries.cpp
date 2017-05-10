/*$*$*$*$*$*$*$*$*$*$*$
Benjamin B Cutler
Program : bcutlerP5.cpp : Method Definitions.     bcutlerMain.cpp  : My main function   bcutlerP5.h : Header w/ declarations and prototypes.

Purpose : To make computers work with binary numbers (Imagine that!) Includes a binary class which has overloaded '+', '=', '>>','<<','+=', and '++' . Works with NEGATIVE numbers too!

Input : Doesn't input anything directly, but the user can get a binary working via the 'cin' operator to add a binary number or the overloaded '=' operator to get a base10 number in.

Output : Can return input via the 'cout' command to return the base2 value of the binary, or you can user the method toDecimal() which will return the base10 number.
$*$*$*$*$*$*$*$*$*$*$*$*/

#include <iostream>
#include <cmath>

using namespace std;
const int MAXCHARSIZE = 20; // Maximum number of binary characters that we can put in a base 2 number
const int ASCII2INT = 48; // Convenient number to have.
class binary {
    int *base2; // pointer to the base2 integer Array
    int base10;// the base10 integer
    int* base10toBase2(int base10); // A Method that Turns a base10 value into a base2 array.
    bool negsign; // Helps the program determine if a negative sign should be displayed.
public:
    binary(); // Constructor
    binary operator=(int base10num ); // Overloaded operator to allow setting 'binary = base10val)
    int toDecimal(); // Returns the base10 value.
    friend ostream& operator << ( ostream&, binary&); // Makes binaries work with cout
    friend istream& operator >> ( istream&, binary& ); // Makes binaries work with cin
    binary operator+(int base10num); // Easiest case of addition : (binary + base10num)
    friend binary operator+(int base10num, binary operand) ; // Other case (base10num + binary)
    binary operator+(binary operand); // Final case: binary + binary
    binary& operator+=(binary operand); // binarynum += binarynum
    binary& operator+=(int base10num); // Binarynum += base10num
    binary& operator++(); // pre increment operator ex: binary c ; ++c;
    binary operator++(int); // Post Increment Operator; int is an unused parameter,ex : binary c; c++;
};

binary :: binary( ){ // Constructor
    base10 = 0; // Set base10 to be 0 as well.
    base2  = new int[MAXCHARSIZE];  // Set the base2 pointer to a new RAM allocation
    base2 = base10toBase2(base10);
}

/*
Operators
*/

/* = */
binary binary :: operator = (int base10num  ){ //
    /*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
    Inputs : Left Side : A Binary Type    Right Side : An int named 'base10num'
    Outputs : Returns an pointer to itself
    Purpose : Lets the user set a binary type into a base10 value into their binary object and access its base2 / base10 components.
    *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
    if (base10num <0 ){ // We need to get a value for negsign, so that it isn't random RAM which isn't good for testing..
            negsign = true;  // If the number of the right hand of the equals sign is negative, then of course there's a negative sign.
    }else{
        negsign = false; // Otherwise, there isn't
    }
    base2 = base10toBase2(base10num); // We make a base2 from the user's base10
    this->base10 = base10num; // and set the base10 part of the binary to be the user's number.
    return *this; // Return the object, 'this'
}
/* + */
binary binary :: operator + (int base10num){
    /*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*
    Inputs: Left Side : A Binary type 'this'    Right Side : An int 'base10num'
    Outputs: Returns a new binary number, which has the binary and base10 .
    Purpose: This operator adds ' Binary + base10number ' and returns a binary type :
    binary Num1 = binary Num2 + 7 would be valid input for this specific operator
    *+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/
    binary outBinary; // We make a new binary that will get returned
    outBinary.base10 = base10 + base10num; // Its base10 value is just the base10 value of the binary on the left, and the base10 int on the right
    outBinary.base2  = base10toBase2( outBinary.base10 ); // We use that base10 val to compute the base2 value
    if (outBinary.base10 <0) { // Finally we give this base10 a sign
        outBinary.negsign = true;
    } else{
        outBinary.negsign = false;
    }
    return outBinary; // Now we can overload other '+' operators using this operator as a reference.
}

binary operator + (int base10num, binary operand){ //
    /*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*
    Inputs: Left Side : A base10 Number, 'base10num'     Right Side : A Binary Type, 'operand'
    Outputs: Returns a new binary number, which has the binary incremented by base10num units.
    Purpose: This operator adds 'Binary + base10number ' and returns a binary type :
    *+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/
    binary outBinary; // Make a new binary
    outBinary = (operand + base10num); // Set it to be the same as if you added them the other way.
    return outBinary ;
}

binary binary :: operator + (binary operand){ //
    /*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*
    Inputs: Left Side : A Binary Type, 'this'     Right Side : A Binary Type 'operand'
    Outputs: Returns a new binary object which is the sum of 'this'  and the operand
    Purpose: This overloaded operator adds two binary types
    +*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/
    binary outBinary; // Make a new Binary
    outBinary = (base10 + operand.base10); // Set it equal to the sum of the base10 of the left and right binaries. using the overloaded '='
    return outBinary ; // Returns that binary.
}
/* += */

binary& binary :: operator+=(binary operand){
    /*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*
    Inputs: Left Side : A Binary Type, 'this'     Right Side : A Binary Type 'operand'
    Outputs: Returns a pointer to the class object
    Purpose: Adds a value 'operand' to the Left hand binary type.
    +=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*/
    *this +=operand.base10;
    return *this; // We are changing the object on the right, so we need to return a pointer.
}

binary& binary :: operator+=(int base10num){
    /*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*
    Inputs: Left Side : A Binary Type, 'this'     Right Side : An int 'base10num'
    Outputs: Returns a pointer to the class object
    Purpose: Adds a value 'base10num' to the Left hand binary type.
    +=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*+=*/
    base10 +=base10num; // scales base10 by a factor of base10num
    base2 = this->base10toBase2(base10); // Updates the base2
    return *this; // Returns the itself.
}

/* ++ */
binary& binary :: operator++(){
    /*++*++*++*++*++*++*++*++*++*++*
    Inputs: LHS : A Binary Type  RHS : Nothing
    Outputs: Returns a pointer to itself
    Purpose: Adds one to itself,  ++Binary
    ++*++*++*++*++*++*++*++*++*++*++*/
    *this +=1; // Increments this by 1;
    return *this; // Returns itself.
}

binary binary :: operator++(int ){
    /*++*++*++*++*++*++*++*++*++*++*
    Inputs: Needs a Dummy Variable: an int 'dummy' to be inputted, but I don't know why, the compiler asked for it.
    Outputs: Returns a copy of itself
    Purpose: Post Increment operator, Binary++; Adds one to itself, but returns itself without the added 1
    ++*++*++*++*++*++*++*++*++*++*++*/
    binary outBinary; // Make a new binary that gets returned
    outBinary = *this; // Set it equal to the binary on the right
    ++ *this; // Increment this binary normally
    return outBinary; // But we want to return a binary of this unchanged
}



/* >> || << */
ostream& operator << ( ostream& co , binary& operand){
    /*<<*<<*<<*<<*<<*<<*<<*<<*<<*<<*
    Inputs: An ostream 'cout' (co) which is used to display text and a binary 'operand'
    Outputs: Displays the base 2 (Binary) value of the binary object. Returns the cout operator
    Purpose: This operator displays the elements in the list which are  not the trailing zeros. Unless we are James Bond, we don't care about the zeros before integers.
    <<*<<*<<*<<*<<*<<*<<*<<*<<*<<*/
    bool trailingzeros = true; // We don't want to print the zeroes before the 1, so we don't.
    if (operand.base10 < 0 || operand.negsign){
            co << '-'; // If it's negative, we print the negative sign. as well.
    }
    for (int i=0; i<MAXCHARSIZE ; i++){ // We then print each element of the base2 array, one by one
            if ( (*(operand.base2 +i)) ){ // Unless it's a zero, in which we don't print it unless we hit a 1 first.
                    trailingzeros = false; // Once we hit a 1 we can start printing stuff
            }
            if (!trailingzeros){ // Once we are beyond the initial zeros we don't print, we can start printing numbers.
                    co << *(operand.base2 +i);
                }
    }
    if (trailingzeros){ // In the case when it's all zero, we just print a 0.
            cout << 0;
    }
    return co; // We return a cout statement so that we can cout end lines, and more text if we like. (cout << binary << cout "Hi" ...)
}

istream& operator >> (  istream& ci , binary& operand){
    /*>>*>>*>>*>>*>>*>>*>>*>>*>>*
    Inputs: An istream 'ci' which is the cin operator. A Binary (Bass by Ref) operand, which is having its base2 value entered
    Outputs: Returns the 'cin' operator
    Purpose: This operator allows 'cin' to input the base 2 value.
    >>*>>*>>*>>*>>*>>*>>*>>*>>*/
    char userchar; // User's input char
    int *temparray = new int[MAXCHARSIZE]; // We fill up a temporary array with the user's chars. This will need to be translated, so it has to be temporary. It needs to be translated so that it's consistently ordered.
    int charsInBinary = 0; // We also need to know how many chars to translate .
    bool newLineEntered = false; // Once the user enters a newline or space or tab,
    operand.negsign = false;
    for(int i=0 ; (i<MAXCHARSIZE && !newLineEntered );i++){ // We stop the for loop if the user enters a tab/space/enter or if enough chars are entered.
            ci.get(userchar); // Gets the char from the display
            if (userchar == '\n' || userchar == ' '  || userchar == '\t'){ // If the user enters a space, a tab or hits enter, the program will stop looking for input.
                    newLineEntered = true ;
            }
            else if (userchar == '-'){ // Also checks for a '-' sign.
                    operand.negsign = true;
                    --i; // We aren't putting the - sign in the array, so we don't want to  increment the array if the user enters it.
            }
            else{
                    *(temparray+i) = (userchar) - (ASCII2INT); // If it's not a space or tab or enter or dash then it will be stored in the array. Does not check for bad input.
                    charsInBinary++; // Also increases the counter for chars in binary.
            }
    }
    for(int i=0 ; (i<charsInBinary );i++){
             *(operand.base2 +i + (MAXCHARSIZE - charsInBinary)) = *(temparray+ i); // We  then translate each char to the right, so that our base2 array is in the form '000000001' rather than '100000000'
    }
    delete temparray; // Finally, we return the ram to the OS
    operand.toDecimal(); // and make sure the base2 and base10 are in sync
    return ci; // then return a cin, so that we can chain cin statements.
}
/*
Methods
*/

int* binary::base10toBase2(int base10){
    /*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*
    Inputs: An integer, 'base10'  which is a base10 number. Since the max size is 20, then it can't be much over 1 million.
    Outputs: An integer array, where each value in the array is a 1 or a 0; corresponding to the base 2 value of 'base10'
    Purpose: This function turns a base10 int into an array of 1s and 0s corresponding to the value of base10 in binary.
    $*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*/
    int *binaryarray = new int[MAXCHARSIZE]; // Allocate new RAM for the base2 array
    if (base10<0){ // Determine if we need a negative sign or not
            negsign = true;
            base10 = abs(base10); // If there is a negative sign, we don't want it when we make our array.
    }else{
        negsign = false;
    }

    for(int i=0 ; i<MAXCHARSIZE ; i++){ // We need to convert base 10 to base 2. The algorithm is pretty straightforward.
        *(binaryarray +( MAXCHARSIZE-1) -i) = base10 % 2; // The -1 is for the Null at the end!! /*We start from the leftmost edge of the array and go inwards */
        base10 = base10/2;
    }
    if(negsign){ // If there is a negative sign, we now return it to the base10 value, which is negative.
        base10 = base10*-1;
    }

    delete base2; // We delete the old base 2 to save memory

    return binaryarray; // and return it to point at this new value
}
int binary :: toDecimal(){
    /*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*
    Inputs: None
    Outputs: Returns the base10 value
    Purpose: This method turns a base2 int array of 1s and 0s corresponding to its value of base 10 .
    $*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*/
    base10 = 0; // First we reset base10 to be 0
    for(int i=0;i<MAXCHARSIZE ; i++){
        base10 += *( base2 + i ) * pow(2,MAXCHARSIZE -i -1 ); // converting from base2 to base 10 just involves doing 2^n and multiplying it be the binary at that location
    }
    if (negsign){
            base10 = base10*-1; // and if the negative sign is there, then we multiply the base10 val by -1.
    }
    return base10; // Return the base10 value so that we can cout the binary value.
}
/*
Main!
*/

int main(){
    binary one,two,three;

    int inum;
    cout << "Type in Two Binary Numbers to Add " << endl;
    cin >> one ;
    cin >> two ;
    one = one + two;
    cout << "Sum is: " << one << endl;
    inum = 18;
    three = inum;
    three = 4 + three;
    cout << "Binary is: " << three << endl;
    cout <<"Its Decimal Value is: " << three.toDecimal() << endl;


    return 0;
}
