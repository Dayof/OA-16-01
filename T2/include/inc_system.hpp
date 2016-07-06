#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

#define TAMFIXO 24
// byte offset = RRN * TAMFIXO

using namespace std;

bool checkList(vector<string>);
void createFiles(vector<string>);
