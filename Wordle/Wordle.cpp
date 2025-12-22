#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
const int WORD_LENGTH = 5;
const char* GREEN = "\033[42m";
const char* YELLOW = "\033[43m";
const char* RED = "\033[41m";
const char* RESET = "\033[0m";
const char* RED_LETTERS = "\033[91m";
const char* BOLD = "\033[1m";
const char* BlINKING_BLACK = "\033[5;40m";
const char* BlINKING_RED_LETTERS = "\033[5;31m";
const char* GREEN_LETTERS = "\033[92m";
const char* BLUE_LETTERS = "\033[94m";
const char* UNDERLINE = "\033[4m";
const char* ERASE_LINE = "\033[1A\033[2K";
const char* CLEAR_SCREEN = "\033[2J\033[H";

void invalidInput()
{
    cout << RED_LETTERS << "Input is invalid. Choose a number between 1 and 3 from the options above." << RESET << endl;
}
void exitFunc()
{
    cout << BlINKING_RED_LETTERS << "Exiting Program..." << RESET << endl;
}
int getLengthOfString(char* arr)
{
    int counter = 0;
    while (arr[counter] != '\0')
    {
        counter++;
    }
    return counter;
}
bool areStringsSame(char* str1, char* str2)
{
    int len1 = getLengthOfString(str1);
    int len2 = getLengthOfString(str2);

    if (len1 != len2) return false;

    for (int i = 0; i < len1; i++)
    {
        if (str1[i] != str2[i]) return false;
    }
    return true;
}
void adminCommands(int& adminInput)
{
    switch (adminInput)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        exitFunc();
        break;
    default:
        invalidInput();
        break;
    }
}
bool doesStringHaveCapitalLetter(char* str)
{
    int length = getLengthOfString(str);
    for (int i = 0; i < length; i++)
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
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        cout << arr[i];
    }
    cout << endl;
}
bool isCharContainedInArr(char c, char* arr)
{
    for (int i = 0; i < WORD_LENGTH; i++)
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
    cout << GREEN_LETTERS << "You guessed the word" << RESET;
}
void printLoseText(char* correctWord)
{
    cout <<RED_LETTERS<< "You ran out of attempts. The word was - ";
    printCharArr(correctWord);
    cout << RESET;
}
void enterUserWord(char* userWord)
{
    bool isWordValid = false;
    while (!isWordValid)
    {
        cin.getline(userWord, 32);
        if (getLengthOfString(userWord) != 5)
        {
            cout << ERASE_LINE;
            cout << RED_LETTERS << "Word must be exactly 5 letters!" << RESET << endl;
        }
        else
        {
            isWordValid = true;
            for (int i = 0; i < WORD_LENGTH; i++)
            {
                userWord[i] = makeCharCapital(userWord[i]);
            }
            userWord[WORD_LENGTH] = '\0';
        }
    }
}
bool areStringsEqual(char* userWord, char* targetWord, char* hints, int i)
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
    cout << ERASE_LINE;
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
    if (isTrue == false && i < 7)
        cout << endl << BOLD << UNDERLINE << "ROUND" << RESET << BOLD << ' ' << i << RESET << endl;
    else
        cout << endl;
    return isTrue;
}
void printASCIIart()
{
    cout << BlINKING_BLACK
        << " __          ______  _____  _____  _      ______ " << endl
        << " \\ \\        / / __ \\|  __ \\|  __ \\| |    |  ____|" << endl
        << "  \\ \\  /\\  / / |  | | |__) | |  | | |    | |__   " << endl
        << "   \\ \\/  \\/ /| |  | |  _  /| |  | | |    |  __|  " << endl
        << "    \\  /\\  / | |__| | | \\ \\| |__| | |____| |____ " << endl
        << "     \\/  \\/   \\____/|_|  \\_\\_____/|______|______|" << RESET << endl << endl;
}
void printStartingScreen()
{
    printASCIIart();
    cout <<GREEN_LETTERS<< "1.Login as an existing user." << endl<< "2.Register a new user."<<RESET<<endl<< BlINKING_RED_LETTERS<< "3.Exit Program"<<RESET << endl;
}
void exitFunc(bool& finishProgram)
{
    finishProgram = true;
    cout << BlINKING_RED_LETTERS << "Exiting Program..." << RESET << endl;
}

void registerFunc()
{
    fstream usersFile("users.txt", ios::in | ios::out | ios::app);
    bool isUsernameValid = false;
    bool isPasswordValid = false;
    char username[17];
    char password[17];
    char userFileInfo[32];
    cout << BOLD << ".REGISTERING NEW USER." << RESET << endl;
    cout << RED_LETTERS << "Username must be between 3 - 16 characters long!" << endl;
    cout << "Password must be more than 8 characters and include a capital letter!" << RESET << endl;
    while (!isUsernameValid)
    {
        cout << "Enter username: ";
        cin.getline(username, 17);
        if (getLengthOfString(username) < 3) {
            cout << RED_LETTERS << "Username too short" << RESET << endl;
            continue;
        }
        bool exists = false;
        usersFile.clear();
        usersFile.seekg(0, ios::beg);
        while (usersFile >> userFileInfo)
        {
            char extractedName[17];
            int i = 0;
            while (userFileInfo[i] != '-') {
                extractedName[i] = userFileInfo[i];
                i++;
            }
            extractedName[i] = '\0';

            if (areStringsSame(username, extractedName)) {
                exists = true;
                break;
            }
        }
        if (exists) {
            cout << RED_LETTERS << "Username already taken! Try another." << RESET << endl;
        }
        else {
            isUsernameValid = true;
        }
    }
    while (!isPasswordValid)
    {
        cout << "Enter password: ";
        cin.getline(password, 17);
        if (getLengthOfString(password) >= 8 && doesStringHaveCapitalLetter(password)) {
            isPasswordValid = true;
        }
        else {
            cout << RED_LETTERS << "Invalid Password" << RESET << endl;
        }
    }
    usersFile.clear();
    usersFile << username << "-" << password << endl;
    cout << GREEN_LETTERS << "You registered successfully." << RESET << endl;
    usersFile.close();
}

void loginFunc(bool& isAdmin)
{
    ifstream usersFile("users.txt");
    bool isUsernameFound = false, isPasswordCorrect = false;
    char username[17];
    char password[17];
    char existingUserInformation[32];
    char existingUsername[17];
    char existingPassword[17];
    cout << BOLD << ".LOGGING IN EXISTING USER." << RESET << endl;
    while (!isUsernameFound)
    {
        cout << "Enter username: ";
        cin.getline(username, 17);
        while (usersFile >> existingUserInformation)
        {
            int i = 0;
            while (existingUserInformation[i] != '-') {
                existingUsername[i] = existingUserInformation[i];
                i++;
            }
            existingUsername[i] = '\0';

            int k = 0;
            i++;
            while (existingUserInformation[i] != '\0') {
                existingPassword[k] = existingUserInformation[i];
                i++;
                k++;
            }
            existingPassword[k] = '\0';
            if (areStringsSame(username, existingUsername))
            {
                isUsernameFound = true;
                break;
            }
        }
        if (!isUsernameFound)
        {
            cout << RED_LETTERS << "No such user exists. Try again." << RESET << endl;
            usersFile.clear();
            usersFile.seekg(0, ios::beg);
        }
    }
    while (!isPasswordCorrect)
    {
        cout << "Enter Password: ";
        cin.getline(password, 17);
        if (areStringsSame(existingPassword, password))
        {
            isPasswordCorrect = true;
        }
        else
        {
            cout<< RED_LETTERS << "Incorrect password. Try again" << RESET << endl;
        }
    }
    cout << CLEAR_SCREEN;
    printASCIIart();
    cout << "Succesfully logged in as "<<BLUE_LETTERS;
    if (areStringsSame(username, (char*)"administrator"))
    {
        cout << "admin";
        isAdmin = true;
    }
    else
        cout << username;
    cout << RESET << endl;
    usersFile.close();
}

bool startingInput(const int n, bool& finishProgram, bool& isAdmin)
{
    switch (n)
    {
    case 1:
        loginFunc(isAdmin);
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
    int num = (rand() % wordCount) + 1;
    for (int i = 0; i < num; i++)
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
    bool isProgramFinished = false, isAdmin = false;
    int chooseStartingOperation = 0;

    do {
        cout << "Enter your input: ";
        cin >> chooseStartingOperation;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (startingInput(chooseStartingOperation, isProgramFinished, isAdmin));

    if (!isProgramFinished && !isAdmin)
    {
        cout << BOLD << "GUESS THE WORD" << endl << UNDERLINE << "ROUND" << RESET << BOLD << " 1" << RESET << endl;
        char userWord[32];
        char hints[WORD_LENGTH + 1];
        chooseRandomWordFromFile(wordToGuess);
        for (int i = 0; i < 6; i++)
        {
            enterUserWord(userWord);
            if (areStringsEqual(userWord, wordToGuess, hints, i + 2))
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

    if (isAdmin)
    {
        int adminInput = 0;
        cout <<BLUE_LETTERS<< "1.Add new words" << endl << "2.Look at the leaderboard"<<RESET << endl<<BlINKING_RED_LETTERS << "3.Exit program" <<RESET<< endl;
        while (adminInput != 3)
        {
            cout << "Enter your input: ";
            cin >> adminInput;
            cin.clear();
            cin.ignore(1000, '\n');
            adminCommands(adminInput);
        }
    }
}