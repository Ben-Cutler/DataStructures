#include<iostream>


using namespace std;
struct word {
    char letter;
    int passedBy;
    word *next[26];
    word();
};
word :: word(){
    for (int i=0 ; i<26 ; i++){
        next[i] = nullptr;
    }
    letter = '?';
    passedBy = 0;
};
class trie{
    word *head[26];
    public:
    trie();
    void add_word(string);
    int count_words(string);
};
trie :: trie(){

    for (int i=0 ; i<26 ; i++){
        (head)[i] = nullptr;
    }
}
void trie :: add_word(string str){
    word *cur = *head;
    int id = ( str[0] - 'a');
    if ( ! ( head[id])){
        head[id] = new word;
    }
    cur = head[id];

    for (int i=0 ; str[i] ; i++){

        (cur)->letter = str[i]; // You could check it, but checking it is probably as fast as resetting it
        ((cur)->passedBy) +=1;
        //cout <<"Passed By this " <<  ((cur)->passedBy) << endl;

        if (str[i+1]){
            id = ( str[i+1] - 'a');
            if ( !((cur)->next[id]) ){ // If the next node there isn't built - build one
                (cur)->next[id] = new word;

            }
            cur = (cur)->next[ id]; // Update cur
        }
    }
}

int trie:: count_words(string str){
    word *cur = *head;
    int id = ( str[0] - 'a');
    if (! head[id]){
            return 0;
    }
    cur = head[id];

    for (int i=0 ; str[i] ; i++){

            //cout <<"Passed By this " <<  ((cur)->passedBy) << endl;

        if (str[i+1]){
            id = ( str[i+1] - 'a');
            if (! ((cur)->next[ id]) ){
                return 0;
            }
            cur = (cur)->next[ id]; // Update cur
        }
    }
    return ((cur)->passedBy);

}


int main(){

    int n;
    cin >> n;
    trie myTrie;
    for(int a0 = 0; a0 < n; a0++){
        string op;
        string contact;
        cin >> op >> contact;
        if (op == "add"){
            myTrie.add_word(contact);
        }else{
            cout << myTrie.count_words(contact) << endl;
        }
    }

    /*
    int numTimes;
    trie myTrie;
    string Werd;
    cin >> numTimes;
    for (int i=0 ; i<numTimes ; i++){
        cin >> Werd;
        //cout << Werd << endl;
        myTrie.add_word(Werd);
        cout << "Done!!" << endl;
    }

    cin >> Werd;
    cout << myTrie.count_words(Werd);
    */




    return 0;
}
