#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

#define TAMFIXO 24
// byte offset = RRN * TAMFIXO

using namespace std;

bool checkList(vector<string>);
void createFiles(vector<string>);

void showMenu();
void clearScreen();
void pressEnter();

#ifdef __linux__
    #define CLEAR "clear"
#elif _WIN64
    #define CLEAR "cls"
#elif __APPLE__
    #define CLEAR "clear"
#endif
