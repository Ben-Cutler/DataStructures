/***********************
Name : Benjamin B Cutler
BCutlerP7.cpp
Purpose: To evaluate an infix expression, convert it to postfix and finally evaluate it to 3 decimal places. Uses a linked list implementation
Inputs: From the user, gets an expression, such as 4+5*8/3^2=.
Outputs: The computer would display the solution to, in this case: 4+5*8/3^2=. This case would be equal to 8.444;
***************************/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
const int DECIMALPTS =3; // Number of Decimal Points to display


struct userNode{
    /***********************
    Struct to hold either a number XOR an operator that the user entered.
    ************************/
        float number; // Holds a number the user inputted.
        char Operator; // Holds an operator. If there is a number put in the number field, this will be '0', and that lets the program distinguish which field to look at.
        userNode *next; // Pointer to the next node
};

class numOpStack {
    userNode* head; // Head pointer.
    public:
    numOpStack(); // Default Constructor
    bool isEmpty(); // Returns true if the stack is empty. Returns false otherwise
    void push(char op); // Puts a char/operator on the stack.
    void push(float num); // Puts a number on the stack
    char top(string); // displays the char field of the top of the stack. text needed to disambiguate
    float top(void); // displays the float field of the top of the stack.
    void pop(); // Removes top of the stack.

};
/************************
|  Function Prototypes  |
*************************/
numOpStack getPostFix(); // Gets infix from the user, returns postfix as a stack
numOpStack reverseStack(numOpStack); // Reverses an inputted stack
float postFixToFloat(numOpStack); // Takes in a stack corresponding to an infix value, returns the solved float value
char charSwap (char inChar ); // Swaps - to + and / to *
bool precidence(char leftChar,char rightChar); // Determines precidence of operators (^,*/,+-)
void printvalue(float val); // Prints the inputted value to DECIMALPTS precision

/************************
|    numOpStack Methods   |
*************************/
numOpStack :: numOpStack(){ // Default Constructor
    head = NULL; // Sets head to NULL
};
bool numOpStack :: isEmpty(){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    None
    Post- conditions:
    Returns 'True' if the stack is empty;
    Returns 'False' if the stack is full;

    Purpose :
    To determine if a stack is empty or not;
    $*$*$*$*$*$*$*$*$*$*$*/
    return (head==NULL);
}

void numOpStack :: push(char op){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    A char 'op', which is an operator '^','*','/','+','-'
    Post- conditions:
    Puts the operator in the char field of the stack, adjusts the head pointer.
    Purpose :
    To add an operator to the stack
    $*$*$*$*$*$*$*$*$*$*$*/
    userNode *newNode = new userNode; // Make a new node to be pushed onto the stack
    newNode->Operator = op; // Set the operator to be the user's operator
    newNode->next = head; // links this newNode to the previous node
    head = newNode; // Makes this newNode the head
}
void numOpStack :: push(float num){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    A float, num, which is from the user's input.
    Post- conditions:
    Puts the number in the num field, and sets the operator field to be 0.
    Purpose :
    To add a number to the stack.
    $*$*$*$*$*$*$*$*$*$*$*/
    userNode *newNode = new userNode; // Make a new node to be pushed onto the stack
    newNode->Operator = 0; // We need to set the operator to 0. Since it's 0 we can distinguish the float node from the operator node because this node will have a 0 operator field.
    newNode->number = num; // Sets the number to be num
    newNode->next = head; // Links this to the previous node
    head = newNode; // Makes this newNode the head.
}

float numOpStack :: top(void){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    Nothing
    Post- conditions:
    Returns the number field of the top of the stack
    Purpose :
    To display the number field of the top of the stack
    $*$*$*$*$*$*$*$*$*$*$*/

    if ( this ->isEmpty() ){
        cout << "Empty Stack! Returning '0' " << endl; // Returns message if I try to view the top of an empty stack
        return 0;
    }
    return (head ->number); // Otherwise, it returns whatever data is there.
}

char numOpStack :: top(string text){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    A string, which should be "char" to distinguish this function from the float one.
    Post- conditions:
    Returns the char / operator field of the top of the stack
    Purpose :
    To display the operator field of the top of the stack
    $*$*$*$*$*$*$*$*$*$*$*/
    if ( this ->isEmpty() ){
        cout << "Empty Stack! Returning '0' " << endl; // If the stack is empty, it just returns a 0 and some text.
        return 0;
    }
    if (text == "char"){
        return (head ->Operator); // If the method is called with the right text, it returns the operator field of the stack
    } else{
        cout << "Char top method must be called with the text 'char' " << endl; // If the method is called with some other text, it throws a message
        return 0;
    }
}
void numOpStack :: pop(){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    None
    Post- conditions:
    Deletes top of stack
    Purpose :
    Deletes the top of the stack so the stack can be traversed.
    $*$*$*$*$*$*$*$*$*$*$*/
    userNode *temp; // Make a temporary pointer to a node so that we can logically and physically delete the data
    if (head != NULL){ // Makes sure we aren't popping an empty stack
        temp = head;
        head = head->next; // Logically delete the node
        delete temp; // physically delete the node
        return;
    }else{
        cout << "Cannot Pop empty stack!" << endl; // If the stack is empty, it shows a message
        return;
    }
}
/************************
|       Functions       |
*************************/
char charSwap (char inChar ){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    Inchar -> A character that is an operator.
    Post-conditions:
    If the operator is a '*' it becomes a '/'. If it's a '-' then the char becomes a '+'
    Purpose :
    To save lines of code by reducing the number of operators to compare in the precedence function from 5 to 3. Saves possibly a headache as well
    $*$*$*$*$*$*$*$*$*$*$*/
    if (inChar == '/'){
        inChar = '*';
    }else if (inChar == '-'){
        inChar = '+';
    }
    return inChar;
}
bool precidence(char leftChar,char rightChar){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    leftChar ->  An operator stored as a char +;-  *;/  ^ .
    rightChar -> An operator stored as a char +;-  *;/  ^ .
    Post- conditions:
    Returns true if the precedence of the operator on the left is greater or equal to the one of the right, returns false otherwise.

    Purpose :
    To compare the precedence of two operators : ^ > * == / > + == - .
    $*$*$*$*$*$*$*$*$*$*$*/
    /*******
    Since the precedence of '* == /' and '+ == -' are the same, it's not valuable to differentiate between them for this problem
    Therefore if the left operator is a  '/' or a '-' then we can make it a * or a + for convenience
    ********/
    leftChar  = charSwap(leftChar);
    rightChar = charSwap(rightChar);
    /*
    Next we solve for the easiest case : both operators are the same precedence.
    */
    if (leftChar == rightChar){
        return true;
    } else if (leftChar == '^'){ // The ^ has highest precedence, so if the left operator is a ^ then it has to be true.
        return true;
    } else if (leftChar == '*' && rightChar == '+'){ // If the * (or /) is on the left, and a + (or -) is on the right then the left char has precedence
        return true;
    }
    return false; // By switching chars, this cuts down on cases. Every other case is operator where the right is larger.

}
numOpStack  getPostFix(){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    Prompts user for the infix expression (5+7=) interpreting all numbers as floats
    Post- conditions:
    returns the postfix (57+) in the form of a stack.
    Purpose :
    To get infix from the user and turn it into a postfix expression that is easy to solve
    $*$*$*$*$*$*$*$*$*$*$*/
    numOpStack outputStack; // Make a stack that will get returned.
    numOpStack operatorStack; // Make a temporary stack that will become filled with operators
    char userOperator; // Operator the user enters
    float userFloat; // Float the user enters
    do{
        cin >> (userFloat); // inputs the user's float
        cin.get(userOperator); // inputs the user's operator

        outputStack.push(userFloat); // Push the operand to the stack that gets returned
        if (userOperator != '='){ // If the operator the user enters is '=', we are done
            if (!operatorStack.isEmpty() ){
                if ( precidence(operatorStack.top("char"), userOperator)  ){ // If there is an operator in the operator stack, then we compare its precedence with the incoming operator
                    outputStack.push(operatorStack.top("char")); // if the top of the operator stack has equal or greater precedence, we push the top of the operator stack to the output stack
                    operatorStack.pop(); // We then remove that from the operator stack
                    operatorStack.push(userOperator); // and put the new operator on that operator stack
                }else{
                    operatorStack.push(userOperator); // If the new operator has lower precedence, we put it on the operator stack
                }
            }else{
                operatorStack.push(userOperator); // if the operator stack is empty, we can't compare it with anything so we push the new operator onto the operator stack.
            }
        }
    }while (userOperator != '='); // When we see an equals sign, we know we are done.

    while (! operatorStack.isEmpty()){ // Finally, we push the rest of the operators on the operator stack onto the output stack.
        outputStack.push(operatorStack.top("char"));
        operatorStack.pop();
    }
    outputStack = reverseStack(outputStack); // This stack is backwards though! We need to reverse it.
    return outputStack; // We return the correctly ordered stack of postfix.
}
float postFixToFloat(numOpStack inStack){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    A stack - inStack which is in postfix ordering
    Post- conditions:
    Returns a float which is the evaluated postfix expression
    Purpose :
    To convert postfix stacks to floating pt numbers
    $*$*$*$*$*$*$*$*$*$*$*/
    float num; // last number on the top of the stack
    char op; // last operator on the top of the stack
    float operand1; // left operator
    float operand2; // right operator. We need to distinguish left and right operand since ^,*,/,+,- don't all have an associative law
    numOpStack tempStack; // Temporary stack used to hold floats
     while (! inStack.isEmpty() ){
        num = inStack.top(); // We get the num from the top of the stack
        op  = inStack.top("char"); // we get the operator (which could be a 0 instead of an operator) from the top of the stack

        if (op == 0){ // If the operator is 0, then there is a number in the node.
                tempStack.push(num); // We push that to the temp stack
        }else{
            operand2 = tempStack.top(); // Once we hit an operator, we pop the top two floats from the stack.
            tempStack.pop();
            operand1 = tempStack.top();
            tempStack.pop();

            switch (op){ // We then evaluate the expression ' operand1 op operand2 '
                case '^' : tempStack.push( pow(operand1,operand2)); break;
                case '*' : tempStack.push( operand1 * operand2); break;
                case '/' : tempStack.push( operand1/operand2); break;
                case '+' : tempStack.push( operand1 + operand2); break;
                case '-' : tempStack.push( operand1 - operand2); break;
                default : cout << "Error evaluating operation" << endl;
            }
        }

        inStack.pop(); // pops to the next iteration of the stack
     }
    return tempStack.top(); // once the postfix stack is empty, the temporary stack will contain only the solution
}
numOpStack reverseStack(numOpStack inStack){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    A stack - inStack, which is in backwards post fix notation
    Post- conditions:
    Returns a stack that is inStack that is in proper post fix (not reversed) notation
    Purpose :
    To make a backwards post fix stack -- double backwards -- or in the correct ordering.
    $*$*$*$*$*$*$*$*$*$*$*/
    numOpStack tempStack; // Make a temporary stack
    while (!inStack.isEmpty()){
            if (inStack.top("char") == 0){ // If the stack has a 0 in the operator field, it has a number in it
                tempStack.push(inStack.top());
            }else{
                tempStack.push(inStack.top("char")); // If it has a non-zero operator, then it has an operator in its data field.
            }
            inStack.pop(); // Once it pushes a number or operator, we go to the next node in the stack
    }
    return tempStack; // We return the reversed stack
}
void printvalue(float val){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    A float, val
    Post- conditions:
    Returns nothing, but prints the val up to DECIMALPTS places
    Purpose :
    To print the value of 'val' to 3 decimal places
    $*$*$*$*$*$*$*$*$*$*$*/
    cout << fixed <<showpoint;
    cout  << setprecision(DECIMALPTS)<<val;
    return;
}


int main(){
    /*$*$*$*$*$*$*$*$*$*$*
    Pre-Conditions:
    Asks user for an infix expression
    Post- conditions:
    Displays the numeric solution of the infix expression to 3 decimal places
    Purpose :
    To print the value of the infix expression to 3 decimal places
    $*$*$*$*$*$*$*$*$*$*$*/
    numOpStack myStack; // Make a stack
    myStack = getPostFix(); // Prompt user for infix. returns post fix notation of the user's infix
    printvalue( postFixToFloat(myStack)); // turns post fix into a val with 'postFixToFloat'. Prints it to 3 decimal places wit 'printvalue'
return 0;
}
