/***********************
Name : Benjamin B Cutler
bCutlerp6.cpp
Purpose: To make a dictionary / Linked List that displays useful data.
Inputs: A filename and corresponding text file of which contains words that get added to the dictionary, and for a high count and a low count: To displays words with occurrence between those two numbers. This text file must end with the string "DONE"
Outputs: Shows small tables which displays how often certain words appear.

***************************/


#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
const char UPPERCASE = 32;
const char FIRSTLETTER = 'A';
const char LASTLETTER = 'z';
const int LINEWIDTH = 25;

struct laBlenkWord {
	// Holds the name of a word, how many occurances there are of it, and a pointer to the next word in alphabetical order
	string name; // The word that is added to the dictionary
	int count; // The number of times that word appears
	laBlenkWord*next; // Pointer to next node in the LL
};

class  laBlenk{
	laBlenkWord *head; // Head pointer, part of class so that all members can access it
	void addToLinkedList(string inword); // Private method to add a member to the LL
	void RecHelper(laBlenkWord*); // Private member of class that helps the recursion go on
	void RecHelper2(laBlenkWord*);
	void printequals(int n);
public:
	 laBlenk(); // Constructor
	 bool readText(string filename); // Method that reads the text from a file, and generates links from each word
	 void displayStats(); // Displays which members appear more than once, and which members appear once both in alphabetical order
	 void displayStats(char R); // Displays which members appear more than once in reverse alphabetical order
	 void displayStats(int low, int high); // Displays values bounded between low and high (inclusively) in numerical order

};

laBlenk :: laBlenk(){
	head = NULL; // The only thing we need to do in the constructor is to make the head point to NULL
}
bool laBlenk :: readText(string filename){
/****************************
	Pre Condition - A String that is associated with a filename
	Post Condition - Returns true if the filename is associated with a valid text file, returns false if it is not associated with a valid text file
	Purpose : To look through the text file associated with 'filename' and make a linked list from each unique word in the file name

*****************************/
	ifstream inFP; // Make an ifstreamso that we can open a file that the user provides
	inFP.open(filename.c_str() ); // Open the file
	string word; // Each word in the file will be stored in this variable
	char wordend; // In addition, the last letter of the word is stored. This is to remove punctiation
	while (inFP){
		inFP >> word; // get a word from the infp
		if (word == "DONE"){
            inFP.close(); // if it's done we close the program and return true, to tell the user that a valid file was entered
			return true;
		}
		wordend = word[word.length() -1]; // Assign wordend to the second do last character in the string array ; the last char is a null char
		while ( ( (wordend < FIRSTLETTER) || (wordend > LASTLETTER) ) ) { // If the end of the word is a period, or a comma or something this will catch that punctuation. This is done with a while loop to protect from '...' or other punctiation like that
			word.erase(word.length() -1); // If there is punctuation, just erase it.
			wordend = word[word.length() -1]; // Then we update the word end
		}
		if (word[0] >= FIRSTLETTER && word[0] <= LASTLETTER - UPPERCASE){ // Next we check if the first letter is capitalized
			word[0] = word[0] + UPPERCASE; // If it is, we make it lower case
		}
		addToLinkedList(word); // Finally we add the word to the list
	}
    inFP.close(); // If we don't see a "DONE" at the end of the text file, then eventually inFP will be null, so we close it
	return false; // and if there is no "DONE" (or no file pointer) then we return false
}

void laBlenk :: addToLinkedList(string inWord){
/**********************************
	Pre Condition : A string 'inWord'
	Post condition : Returns nothing
	Purpose : To put that string into the linked list at the correct spot

***********************************/
	laBlenkWord *prev; // Pointer to the previous link
	laBlenkWord *newitem; // Pointer to the new node
	laBlenkWord *cur; // Pointer to the current node
	bool found; // Test if we have found  the right spot for the linked list

	newitem = new laBlenkWord; // We make a new node to add to the linked list
	newitem-> name = inWord; // We set its name to be the word passed to the method
	newitem ->count = 1; // We set count to be 1, since it's the only occurance of that word so far
	cur = head; // We set the current pointer to the head
	prev = NULL; // We are at the head, so there is no previous one to the head
	found = false; // We have for yet found a spot yet

	while (cur && !found){ // We iterate through the Linked List to find where to put it in alphabetical order
		if ( (newitem->name) <= (cur -> name) ){ // Comparisons work on strings!!
			found = true; // Once we find a place we stop looking
			if ( (inWord) == (cur ->name)){ // If there is a duplicate name we don't add it
				(cur->count) = (cur->count) +1 ; // Instead we just increase count by 1
				delete newitem; // delete the link
				return; // and end the method
			}

		}else {
			prev = cur; // If we have not hit a spot, then we move our pointer one spot
			cur = cur ->next; //
		}
	}
	//cout << "ONTO IF STATEMENT" << endl;
	if (prev){
		newitem->next = cur; // Common case where we are inserting into a spot in the LL that isn't the head
		prev -> next = newitem;
	} else{
		newitem -> next = head; // Case where we are adding to the first part of a linked list
		head = newitem;
	}

}
void laBlenk :: displayStats(){
/***************************************
	Pre Condition: none
	Post Condition :none
	Purpose: Makes a table to show the user which words in the Linked List occur more than once, and which occur once.

****************************************/
	laBlenkWord *cur; // Since we are looking through the list we only need the cur pointer
	cout << "Words in Alphabetical Order" << endl;
	cout << "Word" << setw(LINEWIDTH -4 ) << "Count" << endl;
	printequals(LINEWIDTH); // prints equal signs
	cur = head; // Set the cur pointer to point at the head of the list
	while(cur){
		if ((cur ->count) >1){ // If there are more than one of a word, then we display it
			cout << cur->name << setw(LINEWIDTH - (cur->name).length()) << cur ->count << endl;
		}
			cur = cur->next; // This sets us to the next link in the list

	}
	cur = head; // We reset cur here since we will be going around again
	cout << "Words with count = 1" << endl;
	printequals(LINEWIDTH); // print more equals signs
	while(cur){
		if ((cur ->count) == 1){ // This time we loop through and if there is only one entry then we display it
			cout << cur->name << ' ';
		}
			cur = cur->next; // This sends us to the next link in the LL
	}
	cout << endl;
	return;
}
void laBlenk :: displayStats(char R){
/***********************************
	Pre Condition : A character 'R' If there's any other char inputted it does nothing
	Post condition : displays a table and some text
	Purpose to display words with occurance >1 in reverse alphabetical order
************************************/
    if (R != 'R'){ // catch a char other than an R being entered
        cout << "ERROR: Reverse word printing requires an 'R' to be entered" << endl;
        return;
    }
	cout << "Words in Reverse Alphabetical Order" << endl;
	cout << "Word" << setw(LINEWIDTH - 4) << "Count" << endl;
	printequals(LINEWIDTH);
	RecHelper(head); // Passes the pointer to a function that prints the values recursively
	printequals(LINEWIDTH); // prints equal signs
	cout << "Words with count = 1" << endl;
	RecHelper2(head);
	cout << endl;
	return ;


}
void laBlenk :: RecHelper(laBlenkWord *ptr){
/******************************
	Pre condition  : a pointer to a 'leBlenkWord'
	Post condition : Displays the table itself (Displaystats just helps display stuff)
	Purpose : To display words in reverse alphabetical order by calling itself then displaying the word
*******************************/
	if (ptr){
		RecHelper(ptr ->next); // Calls itself to print the next value in the array if the pointer is not at the very end
		if ((ptr -> count) >1){ // Here we print ones that appear more than once
			cout << ptr->name << setw(LINEWIDTH - (ptr->name).length()) << ptr ->count << endl;
			//
		}
	}
}
void laBlenk :: RecHelper2(laBlenkWord *ptr){
    if (ptr){
        RecHelper2(ptr ->next);
        if ((ptr->count) ==1){
            cout << ptr->name << ' ';
        }
    }
}
void laBlenk :: displayStats(int low, int high){
/********************************
 Pre Condition : An integer 'low' that is the lower bound for frequencies to print and another integer 'high' that is the upper bound for frequencies to display
 Post Condition : A Table which shows in frequency order the
 Purpose : To display a table which shows the ranking of each word in frequency order bounded between 'high' and 'low' inclusively
*********************************/
	laBlenkWord *cur; // Pointer to current link
	cout << "Words in frequency order" << endl;
	cout << "Word" << setw(LINEWIDTH - 4) << "Count" << endl;
	printequals(LINEWIDTH);
	for(int i=high; i>=low;i--){ // This time we are looping through the counts.
		cur = head; // At the beginning of the for loop we reset cur
        while(cur){
            if ((cur ->count) == i){ // and we only print the counts that appear
                cout << cur->name << setw(LINEWIDTH - (cur->name).length()) << cur ->count << endl;
            }
                cur = cur->next; //
            }
    }
    cout << endl;
}
void laBlenk :: printequals(int n){
/*****************************
Pre condition : An int 'n' which is the number of equals signs we have to print out
Post condition : Returns nothing, but prints n equals signs and an endl;
Purpose : To print n equals signs.
******************************/
	for(int i=0 ; i<n ; i++){
		cout << '='; // Prints n equals signs
	}
	cout << endl; // and an endl
}

int main () {
    laBlenk myList; // Make a list
    string fileName; // Declare a name for a file
    int low, high; // Lower and upper bound
    cout << "Enter file name: ";
    cin >> fileName; // Get the file name from the user
    if (myList.readText (fileName)) { // If the file is valid, then this program continues
        myList.displayStats(); // Displays the stats of words that have >1 occurances and 1 occurance
        cout << "Enter low count: ";
        cin >> low; // Get a lower bound
        cout << "Enter high count: ";
        cin >> high; // Get a high bound
        myList.displayStats(low, high); // Display numbers that have occuraces between low and high
        myList.displayStats( 'R'); // Then display in reverse alphabetical order the numbers that have >1 occurance
    } else // If something is wrong with the file, then we display an error message.
        cout << "Error - problem reading file." << endl;
return 0;
}

