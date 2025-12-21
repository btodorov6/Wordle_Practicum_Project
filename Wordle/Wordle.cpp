#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
const int wordLength = 5;
void printCharArr(char* arr)
{
    for (int i = 0;i < wordLength;i++)
    {
        cout << arr[i];
    }
    cout << endl;
}
bool isCharContainedInArr(char c,char* arr)
{
    for (int i = 0;i < wordLength;i++)
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
    cin.getline(userWord, wordLength+1);
    userWord[wordLength] = '\0';
}
bool areStringsEqual(char* userWord,char* targetWord,char* hints)
{
    bool isTrue = true;
    for (int i = 0;i < wordLength;i++)
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
    printCharArr(hints);
    return isTrue;
}
void printStartingScreen()
{
    cout << " __          ______  _____  _____  _      ______ " << endl
        << " \\ \\        / / __ \\|  __ \\|  __ \\| |    |  ____|" << endl
        << "  \\ \\  /\\  / / |  | | |__) | |  | | |    | |__   " << endl
        << "   \\ \\/  \\/ /| |  | |  _  /| |  | | |    |  __|  " << endl
        << "    \\  /\\  / | |__| | | \\ \\| |__| | |____| |____ " << endl
        << "     \\/  \\/   \\____/|_|  \\_\\_____/|______|______|" << endl << endl;
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
    word[wordLength] = '\0';
    wordFile.close();
}
int main()
{
    srand(time(0));
    printStartingScreen();
    char wordToGuess[wordLength + 1];
    bool isProgramFinished = false;
    int chooseStartingOperation = 0;
    do {
        cout << "Enter your input: ";
        cin >> chooseStartingOperation;
        cin.ignore();
    } while (startingInput(chooseStartingOperation, isProgramFinished));
    if (!isProgramFinished)
    {
        char userWord[wordLength + 1];
        char hints[wordLength + 1];
        chooseRandomWordFromFile(wordToGuess);
        for (int i = 0;i < 6;i++)
        {
            enterUserWord(userWord);
            if (areStringsEqual(userWord, wordToGuess,hints))
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