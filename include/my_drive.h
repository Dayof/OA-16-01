#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Estrutura de bloco 
typedef struct block 
{
    // Tamanho de cada setor
    unsigned char bytes_s[512];
} block;

// Estrutura de cluster
typedef struct cluster_array 
{
    // Setores por cluster
    block sector[4];
} cluster_array;

// Estrutura de setor
typedef struct sector_array 
{
    // Cluster por trilha
    cluster_array cluster[15];
} sector_array;

// Estrutura de trilha
typedef struct track_array 
{
    // trilhas por cilindro
    sector_array track[5];
} track_array;

// Ponteiro para o cilindro
track_array *cylinder;

// Tabela FAT
typedef struct fatlist_s
{
    // Lista com os nomes dos arquivos
    char file_name[100];
    // Primeiro setor onde o arquivo esta armazenado no HD
    unsigned int first_sector;
} fatlist;

// Entrada na tabela FAT
typedef struct fatent_s
{
    // Indica se o setor esta livre ou sendo utilizado
    unsigned int used;
    // Informa se e o ultimo setor do arquivo
    unsigned int eof;
    // Informa proximo setor do arquivo
    unsigned int next;
} fatent;

#ifdef __linux__
    #define CLEAR "clear"
#elif _WIN64
    #define CLEAR "cls"
#elif __APPLE__
    #define CLEAR "clear"
#endif

// ASSINATURAS DAS FUNCOES
void showMenu();
void clearScreen();

block *createBlock(unsigned char*);
cluster_array *createCluster(block*);
sector_array *createTrack(cluster_array*);
track_array *createCylinder(sector_array*);

void writeFile();
void readFile();
void delFile();
void showFAT();

