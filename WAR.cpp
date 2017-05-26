/****
Benjamin Cutler
bcutlerp8.cpp

Purpose : To Play a full game of 'WAR' with custom player names.

Inputs : Prompts the user for two player names, and asks them if they want to play 'fastmode' If they don't play 'fastmode' then they have to press enter every hand.

Outputs : Displays a table every hand with:
What hand number they are on
Player names
What cards they are playing
If it's war, then that there are secret cards on the table.

And finally who won at the very end.

**/




/*
 * deckOfCards.cpp
 *
 *  Class that sets up a deck of cards for project P8
 *
 *  This class and the struct below SHOULD NOT BE MODIFIED.
 *  (You can put output statements in for debugging, but comment them
 *  out before turning in the project.)
 *
 *  Replace these comments with your own.
 */

#include<iostream>
#include<cstdlib>
#include<assert.h>
#include<ctime>
#include<queue>
#include<iomanip>
#include<sstream>
using namespace std;

struct card {
   int value;	// point value of card (2-14; Ace is high)
   string suit;	// Hearts, Diamonds, Clubs, Spades
   string face;	// Jack, Queen, King, or Ace (or none)
   bool dealt;	// if this card has been dealt
};

class deckOfCards {
   card deck [52];   	// note: no constant here because things are hardcoded for a standard 52 card deck
   int numberDealt; 	// number of cards dealt so far

public:
   deckOfCards ();
   card dealCard ();
};

deckOfCards :: deckOfCards () {
/*
 *  Constructor.
 *  Set up a standard set of 52 cards.
 */
   int i;

   numberDealt = 0;

   for (i = 0; i < 52; i++) {
      deck[i].dealt = false;
      if (i < 13) {
         deck[i].value = i+2;
         deck[i].suit = "Hearts";
      } else if (i < 26) {
         deck[i].value = i-11;
         deck[i].suit = "Diamonds";
      } else if (i < 39) {
         deck[i].value = i-24;
         deck[i].suit = "Clubs";
      } else {
         deck[i].value = i-37;
         deck[i].suit = "Spades";
      }

      if (deck[i].value == 11)
         deck[i].face = "Jack";
      else if (deck[i].value == 12)
         deck[i].face = "Queen";
      else if (deck[i].value == 13)
         deck[i].face = "King";
      else if (deck[i].value == 14)
         deck[i].face = "Ace";
      else
         deck[i].face = "";
   }
}

card deckOfCards :: dealCard () {
/*
 * Deal one card from deck.
 * Precondition: Deck has been created
 * Postcondition: Returns a random card from the deck
 */

   int index;

   assert (numberDealt < 52);
   srand(time(NULL));
   index = rand () % 52;	// random number in range 0-51
   while (deck[index].dealt) {
      index = rand () % 52;
   }
   deck[index].dealt = true;
   numberDealt++;
   return deck[index];
}



class playGame{
     string player1; // Name of player 1
     string player2;
     queue<card> player1Deck; // Player 1's Deck
     queue<card> player2Deck;
     int hand; // Number of games played (includes current game)
     int spacing; // For output purposes.
     bool winner; // False if no one has won.
     bool fastMode; // If it's false, you have to hit enter every round.
     bool playOneRound(char); // Plays one round of war
     void printCharNTimes(char, int); // Prints a char n times
     string playerText(card); // Generates output text from a card

public:
    playGame(); // constructor
    void play(); // Plays the game

 };

playGame :: playGame(){
     /*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*
     Display gaudy text and get player names
     *$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*/
     cout << " **       **                  **" << endl;
     cout << "/**      /**                 /**" << endl;
     cout << "/**   *  /**  ******   ******/**" << endl;
     cout << "/**  *** /** //////** //**//*/**" << endl;
     cout << "/** **/**/**  *******  /** / /**" << endl;
     cout << "/**** //**** **////**  /**   // " << endl;
     cout << "/**/   ///**//********/***    **" << endl;
     cout << "//       //  //////// ///    // " << endl; // Take from ::  http://patorjk.com/software/taag/#p=display&h=2&f=3-D&t=War!
     cout << "Please Enter the name of player 1 : " << endl;
     cin >> player1;
     cout << "Please Enter the name of player 2 : " << endl;
     cin >> player2;
     /*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*
     Next we make each player's deck
     $*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*$*/
     winner = false; // There is not a winner yet
     int decksize = 26; // 52/2
     spacing = 30; // For Alignment
     deckOfCards game; // Make a deck of cards that are going to get played
     for (int i=0 ; i<decksize ; ++i){ // Deal cards to each player
         player1Deck.push(game.dealCard());
         player2Deck.push(game.dealCard());
     }
     cout << "Would you like to play Fast mode? (No hitting <enter> required!) (Y/N)" << endl;
     char fastModeText; // Fast mode bypasses all the hitting enter which can sometimes show down games
     cin >> fastModeText;
     if (fastModeText == 'Y' || fastModeText == 'y'){ // Fast mode - Doesn't require hitting enter every hand
        fastMode = true;
     }else{
         fastMode = false;
     }

     hand = 0; // number of hands played so far
 }

bool playGame :: playOneRound(char rec = ' '){
    /********************************
    Pre-cond  :  A char, which if it's r means this function is being called recursively
    Post-cond :  Plays one round, returns false if someone won. returns true otherwise.

    Purpose   :  To play a single round of war, and determine if someone has won the game. It also mutes some text if this function is being called recursively via a war game
    ************************************/

    if (player1Deck.empty()){  // If player 1's deck is empty - player 2 wins
        cout <<endl<<endl<< player2 << " Wins!! " << endl;
        winner = true;
        return false;
    }else if(player2Deck.empty() ){ // If player 2's deck is empty - player 1 wins
        winner = true;
        cout <<endl<<endl<< "Player " << player1 << " Wins!! " << endl;
        return false;
    } // This method ignores the possibility that both players can simultaneously lose - that has a probability of about 1 in 10^14 though, which is safe to ignore.
    card player1Card = player1Deck.front(); // Deals a card to player 1
    card player2Card = player2Deck.front();
    string p1text = playerText(player1Card); // Generates text to display for player 1's card
    string p2text = playerText(player2Card);
    player1Deck.pop();
    player2Deck.pop(); // removes the card that was dealt from the top of the deck.
    if (!fastMode && rec != 'r'){ // If we are doing a war within a war, then we aren't going to ask the user to hit return
        cout <<endl << endl << "Press enter " << endl;
        char temp;
        cin.get( temp);
    }
    /**
    Text to Display
    **/
    if (rec != 'r'){ // if we aren't in a war, then we display the hand and player name
        ++hand; // Increment hands
        cout << "Hand  :  " << hand << endl;
        cout << player1 << setw(spacing - player1.size()) << player2 << endl; // Displays player names
        printCharNTimes('-',(spacing +7)); cout << endl; // Prints bars
    }
    cout << p1text << setw(spacing - p1text.size() + p2text.size() - player2.size()) << p2text << endl;
    /**
    Whomever wins gets both the cards - but if you pass the cards in the same order for each player, then the decks reach an equilibrium and the game goes on for tens of thousands of rounds.
    This is why player1 gets cards in different order than player 2
    **/

    if (player1Card.value > player2Card.value){ // player 1 wins
        player1Deck.push(player2Card);
        player1Deck.push(player1Card);
        cout << player1 << " Wins this hand" << endl;
        return true;
    }else if(player1Card.value < player2Card.value){ // player 2 wins
        player2Deck.push(player1Card);
        player2Deck.push(player2Card);
        cout << setw(spacing) << player2 << " Wins this hand" << endl;
        return false;
    }else{ // Case of war : Give each player a secret card, and play a game to determine the winner
        printCharNTimes('-', spacing/2 +1); cout << " WAR "; printCharNTimes('-',spacing/2 +1); cout << endl;  // Displays WAR text centered
        card player1SecretCard = player1Deck.front();
        card player2SecretCard = player2Deck.front();
        cout << "Secret Card" << setw(spacing - player2.size()) << "Secret Card" << endl;
        player1Deck.pop();
        player2Deck.pop();
        if ( this ->playOneRound('r')) { // Player 1 wins. We call the recursive function with a 'r' to suppress some output text.
            player1Deck.push(player2Card);
            player1Deck.push(player1Card);
            player1Deck.push(player2SecretCard);
            player1Deck.push(player1SecretCard);
        }else{ // player 2 wins
            player2Deck.push(player2Card);
            player2Deck.push(player1Card);
            player2Deck.push(player1SecretCard);
            player2Deck.push(player2SecretCard);
        }
    }
}
string playGame :: playerText(card playerCard){
    /**
    Pre-Cond  : A card
    Post Cond : Text which says "(face || value) of ( suit) "

    Purpose : To generate text which will be displayed under the name of each player
    **/
    string ptext; // text that gets returned

    if (playerCard.value > 10){ // If the card's value is greater than 10, then we are just concatenating strings
        ptext = (playerCard.face + " of " + playerCard.suit);
    }else{ // Otherwise, we have to make an ostringstream which can handle ints better.
        ostringstream temp; // A thing that is easier to concatenate integers to strings easily
        temp << playerCard.value;
        ptext = temp.str() + " of " + playerCard.suit;
    }
    return ptext;
}
void playGame :: printCharNTimes(char ch, int n){
    /***********************************************
    Pre cond  : A char ch, and an int 'n'.
    Post cond : Prints 'ch' 'n' times

    Purpose   : To print ch 'n' times
    *********************************************/

    for (int i=0; i<(n);++i){
        cout << ch;
    }
}
void playGame :: play(){
    /**********************************
    Precond   : A game that has not yet been played (If it has been played nothing will happen)
    Post Cond : returns nothing, but changes the game to be one that is finished.

    Purpose   : plays games until there is a winner
    *************************************/
    while(!winner){this -> playOneRound();}
}

int main () {
   playGame game;
   game.play();
   return 0;
}
