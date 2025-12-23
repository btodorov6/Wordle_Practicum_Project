#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

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
const char* DARK_RED_LETTERS= "\033[31m";
const char* DARK_GREEN_LETTERS = "\033[32m";
const char* BOLD = "\033[1m";
const char* BlINKING_BLACK = "\033[5;40m";
const char* BlINKING_RED_LETTERS = "\033[5;31m";
const char* GREEN_LETTERS = "\033[92m";
const char* BLUE_LETTERS = "\033[94m";
const char* UNDERLINE = "\033[4m";
const char* ERASE_LINE = "\033[1A\033[2K";
const char* CLEAR_SCREEN = "\033[2J\033[H";
const char* BLINKING_GOLD = "\033[5;38;5;220m";
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
int powerOfTen(int power)
{
    int num = 1;
    while (power > 0)
    {
        num *= 10;
        power--;
    }
    return num;
}
int convertCharArrToInteger(char* arr)
{
    int value = 0, i=0;
    int length = getLengthOfString(arr);
    while (arr[i] != '\0')
    {
        value += (arr[i] - 48) * powerOfTen(length-1);
        length--;
        i++;
    }
    return value;
}
void updateLeaderboards(char* username, bool hasWon)
{
    fstream leaderboardFile("leaderboard.txt");
    ofstream tempFile("temp.txt");
    bool isOperationCompleted = false;
    if (!leaderboardFile)
    {
        tempFile << username << "-1/" << (hasWon ? 1 : 0) << endl;
        tempFile.close();
        (void)rename("temp.txt", "leaderboard.txt");
        return;
    }
    char wholeLine[32];
    char existingUser[17];
    bool isUserFound = false;
    while (leaderboardFile >> wholeLine)
    {
        int i = 0;
        while (wholeLine[i] != '-')
        {
            existingUser[i] = wholeLine[i];
            i++;
        }
        existingUser[i] = '\0';
        if (areStringsSame(existingUser, username))
        {
            isUserFound = true;
            i++;
            char gamesPlayedStr[5];
            int j = 0;
            while (wholeLine[i] != '/')
            {
                gamesPlayedStr[j] = wholeLine[i];
                ++j;++i;
            }
            gamesPlayedStr[j] = '\0';
            int gamesPlayed = convertCharArrToInteger(gamesPlayedStr);
            gamesPlayed++;
            char winsString[5];
            i++;
            j = 0;
            while (wholeLine[i] != '\0')
            {
                winsString[j] = wholeLine[i];
                ++j;
                ++i;
            }
            winsString[j] = '\0';
            int winsTotal = convertCharArrToInteger(winsString);
            if (hasWon)
                winsTotal++;
            tempFile << username << "-" << gamesPlayed << "/" << winsTotal << endl;
            break;
        }
        else
        {
            tempFile << wholeLine << endl;
        }
    }
    leaderboardFile.clear();
    if (!isUserFound)
    {
        tempFile << username << "-1/" << (hasWon ? 1 : 0) << endl;
    }
    leaderboardFile.close();
    tempFile.close();
    remove("leaderboard.txt");
    (void)rename("temp.txt", "leaderboard.txt");
}
char makeCharCapital(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 'A';
    }
    return c;
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
void addWords(char* wordsAdded)
{
    fstream wordsFile("words.txt", ios::in | ios::out | ios::app);
    char existingWord[6], wordToAdd[32];
    bool isWordValid = false;
    while (!isWordValid)
    {
        cout << "Enter word to add: " << endl;
        enterUserWord(wordToAdd);
        bool exists = false;
        wordsFile.clear();
        wordsFile.seekg(0, ios::beg);
        while (wordsFile >> existingWord)
        {
            if (areStringsSame(existingWord, wordToAdd))
            {
                exists = true;
                break;
            }
        }
        if (exists)
        {
            cout << ERASE_LINE << ERASE_LINE;
            cout << RED_LETTERS << "Such a word already exists" << RESET << endl;
        }
        else
        {
            wordsFile.clear();
            wordsFile.seekp(0, ios::end);
            wordsFile << endl;
            wordsFile << wordToAdd;
            isWordValid = true;
            cout << BLUE_LETTERS << wordToAdd << RESET << GREEN_LETTERS << " successfully added to the list." << RESET << endl;
        }
    }
    int i = 0,j=0;
    while (wordsAdded[i] != '\0')
    {
        ++i;
    }
    while (wordToAdd[j] != '\0')
    {
        wordsAdded[i] = wordToAdd[j];
        ++i;
        ++j;
    }
    wordsAdded[i] = ' ';
    wordsAdded[i + 1] = '\0';
    wordsFile.close();
}
void removeWords(char* wordsRemoved)
{
    ifstream wordsFile("words.txt");
    ofstream tempFile("temp.txt");
    char existingWord[6], wordToRemove[32];
    bool isWordValid = false;
    while (!isWordValid)
    {
        cout << "Enter word to remove: " << endl;
        enterUserWord(wordToRemove);

        bool exists = false;
        wordsFile.clear();
        wordsFile.seekg(0, ios::beg);
        while (wordsFile >> existingWord)
        {
            if (areStringsSame(existingWord, wordToRemove))
            {
                exists = true;
                break;
            }
        }
        if (exists)
        {
            wordsFile.clear();
            wordsFile.seekg(0, ios::beg);
            bool firstWord = true;
            while (wordsFile >> existingWord)
            {
                if (!areStringsSame(existingWord, wordToRemove))
                {
                    if (!firstWord)
                    {
                        tempFile << endl;
                    }
                    tempFile << existingWord;
                    firstWord = false;
                }
            }
            wordsFile.close();
            tempFile.close();
            remove("words.txt");
            (void)rename("temp.txt", "words.txt");

            cout << BLUE_LETTERS << wordToRemove << RESET << GREEN_LETTERS << " successfully removed." << RESET << endl;
            int i = 0, j = 0;
            while (wordsRemoved[i] != '\0')
            {
                ++i;
            }
            while (wordToRemove[j] != '\0')
            {
                wordsRemoved[i] = wordToRemove[j];
                ++i;
                ++j;
            }
            wordsRemoved[i] = ' ';
            wordsRemoved[i + 1] = '\0';

            isWordValid = true;
        }
        else
        {
            cout << ERASE_LINE << ERASE_LINE;
            cout << RED_LETTERS << "No such word exists in the list" << RESET << endl;
        }
    }
}
void modifyWords(char* wordsAdded,char* wordsRemoved)
{
    bool isInputValid = false;
    int modifyInput;
    cout << BOLD << "1.Add words" << endl << "2.Remove words" << endl<<"Enter your input: ";
    cin >> modifyInput;
    cin.clear();
    cin.ignore(1000, '\n');
    while (!isInputValid)
    {
        if (modifyInput == 1)
        {
            addWords(wordsAdded);
            isInputValid = true;
        }
        else if (modifyInput == 2)
        {
            removeWords(wordsRemoved);
            isInputValid = true;
        }
        else
        {
            cout << "Input is invalid choose option 1 or 2" << endl;
        }
    }
}
void invalidInput()
{
    cout << RED_LETTERS << "Input is invalid. Choose a number between 1 and 3 from the options above." << RESET << endl;
}
void exitFunc()
{
    cout << BlINKING_RED_LETTERS << "Exiting Program..." << RESET << endl;
}
void adminCommands(int& adminInput,char* wordsAdded,char* wordsRemoved)
{
    switch (adminInput)
    {
    case 1:
        modifyWords(wordsAdded,wordsRemoved);
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
void printCharArr(char* arr)
{
    int i = 0;
    while (arr[i] != '\0')
    {
        cout << arr[i];
        ++i;
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
    cout << BLINKING_GOLD
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
    cout <<DARK_GREEN_LETTERS<< "1.Login as an existing user." << endl<< "2.Register a new user."<<RESET<<endl<< DARK_RED_LETTERS<< "3.Exit Program"<<RESET << endl;
}
void printAdminCommands(char* wordsAdded,char* wordsRemoved)
{
    cout << CLEAR_SCREEN;
    printASCIIart();
    cout << "Successfully logged in as " << BLUE_LETTERS<<"admin"<<RESET<<endl;
    cout << BLUE_LETTERS << "1.Modify word list" << endl << "2.Look at the leaderboard" << RESET << endl << DARK_RED_LETTERS << "3.Exit program" << RESET << endl;
    if (wordsAdded[0] != '\0')
    {
        cout << "Words added: "<<GREEN_LETTERS;
        printCharArr(wordsAdded);
        cout << RESET;
    }
    if (wordsRemoved[0] != '\0')
    {
        cout << "Words removed: " << RED_LETTERS;
        printCharArr(wordsRemoved);
        cout << RESET;
    }
}
void exitFunc(bool& finishProgram)
{
    finishProgram = true;
    cout << BlINKING_RED_LETTERS << "Exiting Program..." << RESET << endl;
}
void registerFunc(char* username)
{
    fstream usersFile("users.txt", ios::in | ios::out | ios::app);
    bool isUsernameValid = false;
    bool isPasswordValid = false;
    char password[17];
    char userFileInfo[34];
    cout << BOLD << ".REGISTERING NEW USER." << RESET << endl;
    cout << RED_LETTERS << "Username must be between 3 - 16 letters!" << endl;
    cout << "Password must be between 8 - 16 letters and include a capital letter!" << RESET << endl;
    while (!isUsernameValid)
    {
        cout << "Enter username: ";
        if (!cin.getline(username, 17))
        {
            cout << RED_LETTERS << "Username too long!"<<RESET<<endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (getLengthOfString(username) < 3) {
            cout << RED_LETTERS << "Username too short!" << RESET << endl;
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
        isPasswordValid = true;
        cout << "Enter password: ";
        if (!cin.getline(password, 17))
        {
            cout << RED_LETTERS << "Password too long! ";
            cin.clear();
            cin.ignore(1000, '\n');
            isPasswordValid = false;
        }
        else if (getLengthOfString(password) < 8)
        {
            cout << RED_LETTERS << "Password too short! ";
            isPasswordValid = false;
        }
        if (!doesStringHaveCapitalLetter(password))
        {
            cout << RED_LETTERS << "Password must have capital letters!";
            isPasswordValid = false;
        }
        if (!isPasswordValid)
        {
            cout << RESET << endl;
        }
    }
    usersFile.clear();
    usersFile << username << "-" << password << endl;
    cout << CLEAR_SCREEN;
    printASCIIart();
    cout << GREEN_LETTERS << "You registered successfully as " << RESET << BLUE_LETTERS << username << RESET << endl;
    usersFile.close();
}
void loginFunc(bool& isAdmin, char* username)
{
    ifstream usersFile("users.txt");
    bool isUsernameFound = false, isPasswordCorrect = false;
    char password[17];
    char existingUserInformation[34];
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
    if (areStringsSame(username,(char*)"administrator"))
    {
        isAdmin = true;
    }
    cout << "Succesfully logged in as "<<BLUE_LETTERS<<username<<RESET<<endl;
    usersFile.close();
}
bool startingInput(const int n, bool& finishProgram, bool& isAdmin, char* username)
{
    switch (n)
    {
    case 1:
        loginFunc(isAdmin,username);
        return false;
    case 2:
        registerFunc(username);
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
    int wordCount = 0;
    char tempWord[6] = "";
    while (wordFile >> tempWord)
    {
        wordCount++;
    }
    wordFile.clear();
    wordFile.seekg(0, ios::beg);
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
    char username[17];
    do {
        cout << "Enter your input: ";
        cin >> chooseStartingOperation;
        cin.clear();
        cin.ignore(1000, '\n');
    } while (startingInput(chooseStartingOperation, isProgramFinished, isAdmin, username));

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
                updateLeaderboards(username, true);
                printWinText();
                break;
            }
            else if (i == 5)
            {
                updateLeaderboards(username, false);
                printLoseText(wordToGuess);
                break;
            }
        }
    }

    if (isAdmin)
    {
        char wordsAdded[500]="", wordsRemoved[500]="";
        int adminInput = 0;
        while (adminInput != 3)
        {
            printAdminCommands(wordsAdded,wordsRemoved);
            cout << "Enter your input: ";
            cin >> adminInput;
            cin.clear();
            cin.ignore(1000, '\n');
            adminCommands(adminInput,wordsAdded,wordsRemoved);
        }
    }
}