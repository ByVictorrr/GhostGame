#include <iostream>
#include <fstream>
#include <unistd.h> //for delay
#define Max 1000
#define Alphabet 26
using namespace std;

struct Node{
    //holds number of last index of address to store each  [a|b|c|Element|d|e|f|g]
    Node *child[Alphabet];
    bool Prefix_end;
    //for start of work
    //when great new node
    Node(){
    for (int x=0 ; x<Alphabet; x++) {
        //every node being made is childs are intilaized
        child[x] = NULL;
    }
    }
};
//for people that play game
struct Person{
    //each person has name
    string Name;
    //each person has points
    int points;
    //initalizing each person
    Person(){
        Name = "None";
        points =100;
    }
};

class GhostClassGame{
private:

    //root of tree which contains first character root[0] = A, root[1] = B ..
    Node *root, *exampleRoot;
    //used
    string words;
    //count the turn
    int count;
    //string for input character
    string wordFromPick;
    //for inputing works from txt
    ifstream readwordss;
    //for example play
    string WordCPU[Max];
    string wordExample;
    int numberOfGames;
    int numOfPlayers;
    Person Names[4];
public:
    ~GhostClassGame(){
        delete root;
    }

    GhostClassGame()
    {
        //counting the number each node
        count = 0;
        //initialize root as new node when default constructor
        root = new Node();
        //root end prefix word = false
        root->Prefix_end = false;
        //reintializing

        exampleRoot = root;

        wordFromPick= "";
        numOfPlayers = numberOfGames=0;

}
    //score card if want to see results
    void ScoreCard(int numOfPlayers)
    {
        //showing score card
        cout << "SCORECARD: \n";
        //name followed by points
        cout << "Name      ||     Points\n\n";
        //loops through x to get to numb of players
        for (int x= 0; x<numOfPlayers; x++) {
            //print out name depending on index and loop points
            cout << Names[x].Name <<  "   "  << Names[x].points << endl;
        }
        Play();
    }


    void insertWordList( string words, ifstream& readWords)
    {
        //open the wordlist
        readWords.open("wordlist.txt");
        int inserted =0;

        while (readWords >> words) {

            //if words more than 5 than add in
            if (words.length() > 4) {
                inserted = inserted+1;
                //insert every word that fits condition
                Insert(words, root);}
        }
        readWords.close();

        }
        //close file






    //insert new value in tree
    void Insert(string word, Node *current)
    {

       // current->PrefixCount++;
        //parsing throught the word length
        for (int i=0; i<word.length(); i++) {
            //to get the index of each address of node
            int letter = (int)word[i] - (int)'a';

            //case 1: if root is emptty base case
            if(current->child[letter] == NULL){
                //if null then make new child

                current->child[letter] = new Node();
                //cout << "new node with letter " << word[i] << "\n";

                //set that child to current and transverse
                current = current->child[letter];

            }
            else{
                //if not child isnt root then work way down
                current = current->child[letter];
            }
        }
        //end of a word
        current->Prefix_end = true;

    }


    //search a string
    bool searchWord(string word, Node *current)
    {
        //get root and make as current


        //for loop to search not depending on index with respect to word length
        for(int i = 0; i<word.length(); i++)
        {
            //when searching for a word by character index and thats empty
            if (current->child[(int)word[i] -(int)'a']==NULL){
                //return false
                return false;
            }
            else{
                //if current child isnt null get the address of child
                current = current->child[((int)word[i]-(int)('a'))];
            }
        }
        //return the current word deprending on the prefix being true
        return current->Prefix_end;

    }


    bool checkLeadingToWord(string wordInput, Node *root)
    {
        Node *temp = root;
        //loop through each word
        for(int i = 0; i<wordInput.length(); i++){
           //if character of word isnt in the root
            if(temp->child[(int)wordInput[i] -(int)'a'] != NULL){
                //set root to its child of string
                temp = temp->child[(int)wordInput[i] -(int)'a'];
            }
            else{
                //eventually set NULL to temp if character not
                temp= NULL;
            }
        }
        //to tell the word isnt in the trie
        if (temp == NULL ) {
            //print out not leading to word
            cout << "Not leading to a word!\n";
            return false;
        }
        return true;
    }



    //the score of the game
    int score(int players)
    {
        //whatever player based on counter
        if (Names[players].points > 0) {
        Names[players].points =  Names[players].points - 5;

        }
        else{
            cout << "YOU have lost" << Names[players].Name << " Your Score is: " << Names[players].points << "\n";
            exit(EXIT_FAILURE);
        }

        return Names[players].points;
    }

    //menu for our game
    void Play(){
        //making phony variable
        ifstream fin;
        //word we run though for instrustions
        string words;


        //choice for each option
        int choice = ChoiceMenu();

        //loop through
        do {
            //if s
            switch (choice) {
                case 1:
                    game(numOfPlayers,wordFromPick,Names);
                    //smart game
                    break;
                case 2:
                    instruction(words, fin);
                    //Instructions
                    break;
                    //example of game;
                case 3:
                    //Example
                    ExamplePlay(count);
                    break;
                case 4:
                    ScoreCard(numOfPlayers);
                default:
                    //exit
                    cout << "Thank You trying out 'Victors Ghost Game'\n";
                    exit(EXIT_FAILURE);

                    break;
            }
        }while (choice !=6);
        cout << " Exit\n";
    }
    //if game is at first game
    int NumberOfPlayers(int &numOfPlayers, int &points)
    {
        //set points to 100
        points=100;
        //if and only if its the first game
        if (numberOfGames==1) {
            cout << "How many Players(2-4):";
            //number of players
            cin >> numOfPlayers;
            //then loop through and intilaize

            //inserting words in the trie
            insertWordList(words, readwordss);
            //since we only need to insert words once we do only if num of games =1

            for (int x=0; x<numOfPlayers; x++){
                cout << "Player " << x+1 << " Name: " <<endl;
                //getting name of player
                cin >> Names[x].Name;
                //points of that player = 100
                Names[x].points= points;

                cout << endl;
        }
        }
        //this returns how many players are plaing
        return numOfPlayers;
    }




    void game(int &numOfPlayers, string &CharBeingAdded, Person *Names)
    {
        //first game keep track of
        numberOfGames++;

       //number of players are repsented by function
        numOfPlayers = NumberOfPlayers(numOfPlayers,Names[numOfPlayers].points);

        int playersturn =0;
        //game is true
        bool CurentGame = true;
        //reseting input
        char input = ' ';


        while (CurentGame) {

            //if players turn reaches number of player
            if (playersturn == numOfPlayers) {
                playersturn = 0;
            }

            //showing the score dependent on player
            cout << " SCORE: " << Names[playersturn].points << endl;
            //there name depending on the players turn
            cout << "Player " << playersturn+1 << " " << Names[playersturn].Name << "\n";

            cout << "\nYour Word: " << CharBeingAdded <<"\n";

            cout << "\nEnter in a Character(a-z): ";

            while(!(cin >> input)) {
                //cin.clear();
                cout << "Invalid value, try again.";

                //minus from players 5 points
               Names[playersturn].points = score(playersturn);
                cout << "Minus -5 point!!\n";
                cout << "Score: " << Names[playersturn].points << " \n";

                cout << "Minus 5 points! " << Names[playersturn].points;
            }
            //add char to other typed in char
            CharBeingAdded = returnWord(input);


            //if found word with a character of more 5 characters you lost
            if(searchWord(CharBeingAdded,root)==true)
            {
                //player that lost
                cout << "YOU HAVE LOST: ";
                //player # lost
                cout << "Player " << playersturn+1  << " " << Names[playersturn].Name <<  endl;

                //minus from players 5 points
                Names[playersturn].points = score(playersturn);

                cout << "Minus -5 point!!\n";

                cout << "Score: " << Names[playersturn].points << " \n";

                //string you spelled
                cout << "\nYou Have spelled: " << CharBeingAdded << "! \n";
                //reseting th game by false
                CurentGame = false;
                wordFromPick = "";
                cout << "\n\n";
                Play();
            }
            //check if leader to word if not run through scope
            if (checkLeadingToWord(CharBeingAdded, root) == false) {

                CurentGame = false;

                //minus from players 5 points
                      Names[playersturn].points = score(playersturn);
                //minus 5 for going out of the trie tree
                cout << "Minus -5 point!!\n";

                cout << "Score: " << Names[playersturn].points << " \n";

                cout << CharBeingAdded  << " does not spell anything"<< "! \n";
                cout << Names[playersturn].Name << ", You loose this round\n";

                   wordFromPick = "";
                cout << "\n\n";

                Play();

            }
            if (Names[playersturn].points == 0 ) {
                cout << "SCORE: "<< score(playersturn) << " \n";
                cout << Names[playersturn].Name << " You Lost" << endl;
            }

            playersturn++;
            count++;

        }

    }


    //for the menu option
    int ChoiceMenu()
    {
        int choice = 0;

        cout << "\nMain Menu\n";
        cout << "1. start Game\n";
        cout << "2. Instructions\n";
        cout << "3. Example\n";
        cout << "4. Score Cards\n";
        cout << "5. Exit\n";
        cin >> choice;

        return choice;
    }


    string returnWord(char input)
    {
        //if count is =0 just return first
        if (count == 0) {
            wordFromPick =input;
            return wordFromPick;
        }
        else{
            //else return the input + string
            wordFromPick = wordFromPick+input;
            return wordFromPick;
        }
    }

    //instrustions of game
    void instruction(string words, ifstream& fin)
    {
        //instructoins
        fin.open("instructions.txt");

        cout << "instructions:\n" << endl;
        //while its open
        while (!fin.eof()) {
            //print out each words
            cout << words << " ";
            //read from the file
            fin>> words;

        }
        cout << "\n\n";

        fin.close();
        //go back to the menu
        Play();
    }

   //getting random string by returning random index
    string getRandomString()
    {
        //giving the wordCPU to the array of words
        insertExampleWords(WordCPU, readwordss,exampleRoot);
        //randomly accessing a index
        return WordCPU[arc4random() % 100];
    }

    //parse through every word
    char parseWord(char*par, int count, string random){
        // loop through the string
        for (int x=0; x<random.length(); x++){
            //get char depending on the count
            par[x] = random[x];
        }
        return par[count];
    }


    //for inserting txt file for examples
    void insertExampleWords( string words[], ifstream& readWords, Node *root)
    {
        //open the wordlist
        readWords.open("Test.txt");

        for (int x=0; x<Max; x++) {
            //read from file words
                readWords >> words[x];
            //insert these into the trie
            Insert(words[x], exampleRoot);
        }
        readWords.close();

    }
    //close file



    void ExamplePlay(int &count)
    {
        cout << "\nEXAMPLE:\n";

        bool CurentGame = true;

        count = 0;

        char input[Max];

        for (int x=0; x<Max; x++) {
            input[x] =' ';
        }
        //CPU names
        string CPU1 = "CPU 1";
        //Cpu names
         string CPU2 = "CPU 2";
        //read from file
        ifstream readswords;
        //get random index in found words
         int randomIndex = arc4random()% Max;
        //getting random rstring for radonom string
        WordCPU[randomIndex] = getRandomString();
        //from the input string
        string CharBeingAdded;

        //insertExampleWords(WordCPU, readswords, root);

        wordFromPick = "";


        while (CurentGame) {
            //the count determines the cpu
            if(count % 2 == 0)
            {
                cout << "\n " << CPU1 << ": ";
            }
            else{
               cout << "\n " << CPU2 << ": ";
            }
            //allows delay
            usleep(900000);

            //parse through random word
               input[count] = parseWord(input, count, WordCPU[randomIndex]);

            //add each character by input add to string
            CharBeingAdded = returnWord(input[count]);

            cout << "\nWord: " << CharBeingAdded <<"\n";

            //if the word that is being entered by CPU is found
            if(searchWord(CharBeingAdded,exampleRoot)==true)
                {
                if (count % 2 ==0) {
                    cout << CPU1 << " You have lost!!!";
                }
                else{
                    cout << CPU2 << " You have lost!!";
                }
                //game not longer true
                CurentGame = false;
                //spelling
                    wordFromPick = "";
                cout << "You Have spelled: " << CharBeingAdded << " \n";

                    Play();

            }
        //for turn
            count++;
        }
    }


};



int main()
{
    GhostClassGame G1;

    G1.Play();


    return 0;
}

