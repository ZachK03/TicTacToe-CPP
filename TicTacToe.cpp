#include <iostream>
#include <vector>
#include <string>

void CreateHeaderText(std::string text);
void CreateDividerText(int dividerLength = 20);
void CreateErrorText(std::string text);
bool GetBoolUserInput(std::string text);

const std::vector<std::vector<int>> WinVectors {
    {0,1,2},
    {3,4,5},
    {6,7,8},
    {0,3,6},
    {1,4,7},
    {2,5,8},
    {0,4,8},
    {2,4,6}
};
void InitGame();
void DisplayGame(std::vector<int> gameData);
void DoPlayerMove(bool &isXMove, std::vector<int> &gameData);
bool CanMoveAtPosition(int moveIndex, std::vector<int> gameData);
void GetWinner(std::vector<int> gameData, bool &gameRunning);

int main() {
    CreateHeaderText("Welcome to Tic Tac Toe!");
    bool runGame = true;
    do {
        InitGame();
        if(GetBoolUserInput("Play again? Y/N\n")) {
            std::cout << "\n\n\n\n";
            CreateHeaderText("Starting game again...");
        } else {
            std::cout << "Quitting game...";
            runGame = false;
        }
    } while (runGame);
    return 0;
}

void InitGame() {
    bool gameRunning = true;
    std::vector<int> gameData {0,0,0,0,0,0,0,0,0};
    bool isXMove = true;
    do{
        DisplayGame(gameData);
        DoPlayerMove(isXMove,gameData);
        GetWinner(gameData, gameRunning);
    } while (gameRunning);
    return;
}

void DisplayGame(std::vector<int> gameData) {
    std::cout << "\n";
    CreateDividerText(11);
    std::cout << "\n";
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            std::cout << " ";
            switch (gameData[j + (i*3)]){
                case 0:
                    std::cout << (j+(i*3));
                    break;

                case 1:
                    std::cout << "X";
                    break;

                case 2:
                    std::cout << "O";
                    break;
                
                default:
                    break;
            }
            std::cout << " ";
            if(j != 2) {
                std::cout << "|";
            }
        }
        if(i != 2) {
            std::cout << "\n-----------\n";
        }
    }
    std::cout << "\n\n";
}

void DoPlayerMove(bool &isXMove, std::vector<int> &gameData) {
    int moveIndex = -1;
    do {
        if(isXMove) {
            std::cout << "X Player: ";
        } else {
            std::cout << "O Player: ";
        }
        std::cout << "Input the number where you'd like to move: ";
        std::cin >> moveIndex;
    } while (!(CanMoveAtPosition(moveIndex,gameData)));
    if(isXMove) {
        gameData[moveIndex] = 1;
        isXMove = false;
    } else {
        gameData[moveIndex] = 2;
        isXMove = true;
    }
}

bool CanMoveAtPosition(int moveIndex, std::vector<int> gameData) {
    if(moveIndex > 8 || moveIndex < 0) {
        std::cout << "Number isn't on the board!\n";
        return false;
    }
    if(gameData[moveIndex] == 0) {
        return true;
    }
    std::cout << "You can't move there!\n";
    return false;
}

void GetWinner(std::vector<int> gameData, bool &gameRunning) {
    int winner = 0;
    int firstPosition;
    bool isWin = false;
    bool isTie = true;
    for (int data : gameData) {
        if(data == 0) {
            isTie = false;
            break;
        }
    }
    if(isTie) {
        DisplayGame(gameData);
        std::cout << "Its a tie! No winner...\n";
        gameRunning = false;
        return;
    }
    for (std::vector<int> winVector : WinVectors) {
        if(isWin) {
            break;
        }
        firstPosition = gameData[winVector[0]];
        if(firstPosition == 0) {
            continue;
        }
        for(int i = 0; i < winVector.size(); i++) {
            if(gameData[winVector[i]] != firstPosition) {
                isWin = false;
                break;
            }
            if(gameData[winVector[i]] == firstPosition && i == 2) {
                isWin = true;
                winner = gameData[winVector[i]];
                break;
            }
        }
    }
    
    if(isWin) {
        DisplayGame(gameData);
        if(winner == 1) {
            std::cout << "X Player ";
        } else if (winner == 2) {
            std::cout << "O Player ";
        }
        std::cout << "wins the game!\n";
        gameRunning = false;
    }
}

void CreateHeaderText(std::string text) {
    for (int i = 0; i < text.size(); i++) {
        std::cout << "=";
    }
    std::cout << "\n" << text << "\n";
    for (int i = 0; i < text.size(); i++) {
        std::cout << "=";
    }
    std::cout << "\n";
}

void CreateDividerText(int dividerLength) {
    for (int i = 0; i < dividerLength; i++) {
        std::cout << "=";
    }
    std::cout << "\n";
}

void CreateErrorText(std::string text) {
    std::string errorText = "[ERROR] : ";
    errorText += text;
    CreateHeaderText(errorText);
}

bool GetBoolUserInput(std::string text) {
    char input;
    while (toupper(input) != 'Y' && toupper(input) != 'N') {
        std::cout << text;
        std::cin >> input;
    }
    if(toupper(input) == 'Y') {
        return true;
    } else {
        return false;
    }
}