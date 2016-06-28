#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <ctime>

using namespace std;

// Estrutura de bloco 
struct block 
{
    // Tamanho de cada setor
    // Limite de 512 bytes
    string bytes_s;
};

// Estrutura de cluster
struct sector_array 
{
    // Setores por cluster
    vector<block> sector;
};

// Estrutura de setor
struct cluster_array
{
    // Cluster por trilha
    vector<sector_array> cluster;
};

// Estrutura de trilha
struct track_array 
{
    // trilhas por cilindro
    vector<cluster_array> track;
};

// Ponteiro para o cilindro
vector<track_array> cylinder;

// Tabela FAT
struct fatlist_s
{
    // Lista com os nomes dos arquivos
    // Limite 100 caracteres
    string file_name;
    // Primeiro setor onde o arquivo esta armazenado no HD
    unsigned int first_sector;
    unsigned long total_bytes;
};

// Lista dos nomes dos arquivos inseridos
vector<fatlist_s> fatfiles;

// Entrada na tabela FAT
struct fatent_s
{
    // Indica se o setor esta livre ou sendo utilizado
    unsigned int used;
    // Informa se e o ultimo setor do arquivo
    unsigned int eof;
    // Informa proximo setor do arquivo
    unsigned int next;
};

// Limite de 300 setores por cilindro
// 900 setores no total (3 cilindros)
vector<fatent_s> fatsec;

#ifdef __linux__
    #define CLEAR "clear"
#elif _WIN64
    #define CLEAR "cls"
#elif __APPLE__
    #define CLEAR "clear"
#endif

#define SECTOR_PER_CLUSTER 4
#define CLUSTER_PER_TRACK 15 
#define TRACK_PER_CYLINDER 5 
#define CYLINDERS 10

double CLOCKS_PER_MILI = CLOCKS_PER_SEC / 1000.0;

// ASSINATURAS DAS FUNCOES
void showMenu();
void clearScreen();

void initFatSec();
void insertFatList(const string&, unsigned int);
void insertFatSec(vector<int>);
void initCylinder();
void insertBlock(const string&, const string&);

void writeFile();
void readFile();
void delFile();
void showFAT();

int fileInFAT(string);
bool delFileInFAT(int, string);
string showFile(int);
void writeFileHD(string);
void showTime(clock_t);
bool clusterAvailable(int, int, int);



