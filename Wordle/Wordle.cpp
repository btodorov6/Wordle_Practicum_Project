#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
const int WORD_LENGTH = 5;
const char* GREEN = "\033[42m";
const char* YELLOW = "\033[43m";
const char* RED = "\033[41m";
const char* RESET = "\033[0m";
const char* RED_LETTERS = "\033[91m";
const char* BOLD = "\033[1m";
const char* BlINKING_BLACK = "\033[5;40m";
const char* GREEN_LETTERS = "\033[92m";
const char* UNDERLINE = "\033[4m";
int getLengthOfString(char* arr)
{
    int counter = 0;
    while (arr[counter] != '\0')
    {
        counter++;
    }
    return counter;
}
bool doesStringHaveCapitalLetter(char* str)
{
    int length = getLengthOfString(str);
    for (int i = 0;i < length;i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            return true;
        }
    }
    return false;
}
char makeCharCapital(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 'A';
    }
    return c;
}
void printCharArr(char* arr)
{
    for (int i = 0;i < WORD_LENGTH;i++)
    {
        cout << arr[i];
    }
    cout << endl;
}
bool isCharContainedInArr(char c,char* arr)
{
    for (int i = 0;i < WORD_LENGTH;i++)
    {
        if (arr[i] == c)
        {
            return true;
        }
    }
    return false;
}
void printWinText()
{
    cout << "You guessed the word";
}
void printLoseText(char* correctWord)
{
    cout << "You ran out of attempts. The word was - ";
    printCharArr(correctWord);
}
void enterUserWord(char* userWord)
{
    cin.getline(userWord, WORD_LENGTH + 1);
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        userWord[i] = makeCharCapital(userWord[i]);
    }
    userWord[WORD_LENGTH] = '\0';
}
bool areStringsEqual(char* userWord, char* targetWord, char* hints,int i)
{
    bool isTrue = true;
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        if (userWord[i] != targetWord[i])
        {
            if (isCharContainedInArr(userWord[i], targetWord))
            {
                hints[i] = 'y';
            }
            else
            {
                hints[i] = 'r';
            }
            isTrue = false;
        }
        else
        {
            hints[i] = 'g';
        }
    }

    for (int i = 0; i < WORD_LENGTH; i++)
    {
        if (hints[i] == 'g')
        {
            cout << GREEN << userWord[i] << RESET;
        }
        else if (hints[i] == 'y')
        {
            cout << YELLOW << userWord[i] << RESET;
        }
        else
        {
            cout << RED << userWord[i] << RESET;
        }
    }
    if (isTrue == false)
        cout << endl << BOLD << UNDERLINE << "ROUND" << RESET << BOLD << ' ' << i << RESET << endl;
    else
        cout << endl;
    return isTrue;
}
void printStartingScreen()
{
    cout<< BlINKING_BLACK
        << " __          ______  _____  _____  _      ______ " << endl
        << " \\ \\        / / __ \\|  __ \\|  __ \\| |    |  ____|" << endl
        << "  \\ \\  /\\  / / |  | | |__) | |  | | |    | |__   " << endl
        << "   \\ \\/  \\/ /| |  | |  _  /| |  | | |    |  __|  " << endl
        << "    \\  /\\  / | |__| | | \\ \\| |__| | |____| |____ " << endl
        << "     \\/  \\/   \\____/|_|  \\_\\_____/|______|______|" << RESET << endl << endl;
    cout << "1.Login as an existing user." << endl;
    cout << "2.Register a new user." << endl;
    cout << "3.Exit Program" << endl;
}
void invalidInput()
{
    cout << "Input is invalid. Choose a number between 1 and 3."<<endl;
}
void exitFunc(bool& finishProgram)
{
    finishProgram = true;
    cout << "Exiting Program..."<<endl;
}
void registerFunc()
{
    ofstream usersFile("users.txt",ios::app );
    bool isUsernameValid = false;
    bool isPasswordValid = false;
    char username[17];
    char password[17];
    cout <<BOLD<< ".REGISTERING NEW USER." <<RESET<< endl;
    cout << RED_LETTERS<< "Username must be between 3 - 16 characters long!"<<endl;
    cout << "Password must be more than 8 characters and include a capital letter!" <<RESET<< endl;
    while (!isUsernameValid)
    {
        cout << "Enter username: ";
        cin.getline(username, 17);

        if (getLengthOfString(username) >= 3) {
            isUsernameValid = true;
        }
        else
        {
            cout << RED_LETTERS << "Username too short" << RESET << endl;
        }
    }
    while (!isPasswordValid)
    {
        cout << "Enter password: ";
        cin.getline(password, 17);
        if (getLengthOfString(password) >= 8 && doesStringHaveCapitalLetter(password)) {
            isPasswordValid = true;
        }
        else
        {
            cout << RED_LETTERS << "Invalid Password" << RESET << endl;
        }
    }
    usersFile << username << "-" << password << endl;
    cout << GREEN_LETTERS << "You registered succesfully." << RESET << endl;
    usersFile.close();
}
void loginFunc()
{

}
bool startingInput(const int n, bool& finishProgram)
{
    switch (n)
    {
    case 1:
        loginFunc();
        return false;
    case 2:
        registerFunc();
        return false;
    case 3:
        exitFunc(finishProgram);
        return false;
    default:
        invalidInput();
        return true;
    }
}
void chooseRandomWordFromFile(char* word)
{
    ifstream wordFile("words.txt");
    int wordCount = 5;
    int num = (rand() % wordCount)+1;
    for (int i = 0;i < num;i++)
    {
        wordFile >> word;
    }
    word[WORD_LENGTH] = '\0';
    wordFile.close();
}
int main()
{
    srand((unsigned int)time(0));
    printStartingScreen();
    char wordToGuess[WORD_LENGTH + 1];
    bool isProgramFinished = false;
    int chooseStartingOperation = 0;
    do {
        cout << "Enter your input: ";
        cin >> chooseStartingOperation;
        cin.ignore();
    } while (startingInput(chooseStartingOperation, isProgramFinished));
    if (!isProgramFinished)
    {
        cout << BOLD << "GUESS THE WORD" << endl << UNDERLINE << "ROUND" << RESET << BOLD << " 1" << RESET << endl;
        char userWord[WORD_LENGTH + 1];
        char hints[WORD_LENGTH + 1];
        chooseRandomWordFromFile(wordToGuess);
        for (int i = 0;i < 6;i++)
        {
            enterUserWord(userWord);
            if (areStringsEqual(userWord, wordToGuess,hints,i+2))
            {
                printWinText();
                break;
            }
            else if (i == 5)
            {
                printLoseText(wordToGuess);
                break;
            }
        }
    }
}