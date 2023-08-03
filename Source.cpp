//This App helps in memorizing german words' articles

#include<iostream>
#include<algorithm>
#include<memory>
#include<vector>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include<windows.h>
using namespace std;

class Cards
{
public:
    Cards() {};
    vector<string> derWords;
    vector<string> dasWords;
    vector<string> dieWords;
};

void init(Cards* cards) // reads the file and inputs words in their correct array
{
    fstream fin;
    fin.open("words.txt", ios::in);
    if (!fin)
    {
        cout << "file not found! \n";
       
    }
    else
    {
        while (fin)
        {
            string word;
            string gender;
            fin >> gender >> word;

            transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
            if (gender == "der")
            {
                cards->derWords.push_back(word);
            }
            else if (gender == "das")
            {
                cards->dasWords.push_back(word);
            }
            else if (gender == "die")
            {
                cards->dieWords.push_back(word);
            }
            else
            {
                continue;
            }

        }
    }



}

enum gender
{
    Der = 1,
    Das,
    Die
};

int pickRandom(bool der, bool das, bool die) //picks random words from the arrays (der/das/die) arrays
{
    int randGender;
    if (der && das && die)
    {
        srand(time(0));
        randGender = 1 + rand() % 3;
    }
    else if (der && das && !die)
    {
        srand(time(0));
        randGender = 1 + rand() % 2;
    }
    else if (der && !das && die)
    {
        srand(time(0));
        randGender = 1 + rand() % 2;
        randGender = (2 ? 3 : 1);
    }
    else if (!der && das && die)
    {
        srand(time(0));
        randGender = 1 + rand() % 2;
        randGender = (1 ? 2 : 3);
    }
    else if (der && !die && !das)
    {
        return Der;
    }
    else if (!der && die && !das)
    {
        return Die;
    }
    else if (!der && !die && das)
    {
        return Das;
    }

    return randGender;
}

void showRand() //this shows the user the word which he is required to write its article and corrects it.
{
    Cards cards;
    init(&cards);

    bool der = 1, das = 1, die = 1;



    while (!cards.derWords.empty() || !cards.dasWords.empty() || !cards.dieWords.empty()) // -------------------------------- modify the flow of der das die picking
    {
        int randGender = pickRandom(der, das, die);

        if (randGender == Der)
        {
            if (cards.derWords.empty())
            {
                der = 0;
                continue;
            }
            int randWord = rand() % cards.derWords.size();
            cout << "word: " << cards.derWords[randWord] << endl;

            vector<string>::iterator it = cards.derWords.begin();
            cards.derWords.erase(it + randWord);

            cout << "Enter your answer: ";
            string ans;
            cin >> ans;

            if (ans == "der")
            {
                cout << "correct!" << endl;
            }
            else
            {
                cout << "wrong! answer is: der" << endl;
            }

        }
        else if (randGender == Das)
        {
            if (cards.dasWords.empty())
            {
                das = 0;
                continue;
            }

            int randWord = rand() % cards.dasWords.size();
            cout << "word: " << cards.dasWords[randWord] << "\n";

            vector<string>::iterator it = cards.dasWords.begin();
            cards.dasWords.erase(it + randWord);

            cout << "Enter your answer: ";
            string ans;
            cin >> ans;
            if (ans == "das")
            {
                cout << "correct!" << endl;
            }
            else
            {
                cout << "wrong! answer is: das" << endl;
            }
        }
        else if (randGender == Die)
        {
            if (cards.dieWords.empty())
            {
                die = 0;
                continue;
            }

            int randWord = rand() % cards.dieWords.size();
            cout << "word: " << cards.dieWords[randWord] << "\n";

            vector<string>::iterator it = cards.dieWords.begin();
            cards.dieWords.erase(it + randWord);

            cout << "Enter your answer: ";
            string ans;
            cin >> ans;
            if (ans == "die")
            {
                cout << "correct!" << endl;
            }
            else
            {
                cout << "wrong! answer is: die" << endl;
            }
        }

        if (cards.dasWords.size() + cards.derWords.size() + cards.dieWords.size() == 0)
        {
            cout << "YOU FINISHED!\n";
            Sleep(1000);
            break;
        }
    }


}

int main()
{

    char ans;

    cout << "random word? <Y> <N>\n";
    cin >> ans;

    if (ans != 'Y' && ans != 'y')
    {
        cout << "are you sure? <Y> <N>";
        char confirm;
        cin >> confirm;
        if (confirm == 'Y' || confirm == 'y') return 0;
    }
    else
    {
        showRand();
    }

    return 0;
}
