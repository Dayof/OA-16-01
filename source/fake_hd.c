/* Trabalho de OA 2016/01
Desenvolvedoras:
1. Dayanne Fernandes da Cunha - 13/0107191
2.
*/

#include <stdio.h>

// Estrutura de bloco
typedef struct block 
{
    // Tamanho de cada setor
    unsigned char bytes_s[512];
} block;

// Estrutura de setor
typedef struct sector_array 
{
    // Setores por trilha
    block sector[60];
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
    unsigned int used;
    unsigned int eof;
    unsigned int next;
} fatent;

// ASSINATURAS DAS FUNCOES
void showMenu();

int main()
{
    showMenu();

    return 0;
}

// Funcao que mostra o menu inicial
void showMenu()
{
    printf("1 - Escrever Arquivo\n2 - Ler Arquivo\n3 - Apagar Arquivo\n4 - Mostrar Tabela FAT\n5 - Sair\n");
}