/* Trabalho de OA 2016/01
Desenvolvedoras:
1. Dayanne Fernandes da Cunha - 13/0107191
2.
*/

#include <my_drive.h>

int main()
{
    unsigned char *var;
    memcpy(var, "hm", 3);

    block *b = createBlock(var);
    cluster_array *ca = createCluster(b);
    sector_array *sa = createTrack(ca);
    track_array *ta = createCylinder(sa);

    printf("block: %s\n",b->bytes_s);
    getchar();

    printf("block from cluster: %s\n",ca->sector[0].bytes_s);
    getchar();

    printf("block from cluster from track: %s\n",sa->cluster[0].sector[0].bytes_s);
    getchar();

    printf("block from cluster from track from cylinder: %s\n",ta->track[0].cluster[0].sector[0].bytes_s);
    getchar();

    showMenu();

    return 0;
}

// Construtor de setores
block *createBlock(unsigned char *bytes)
{
    block *b = (block*)malloc(sizeof(unsigned char));
    
    memcpy(b->bytes_s, bytes, sizeof(&bytes));
    printf("%s\n", b->bytes_s);
    getchar();

    return b;
}

// Construtor de cluster
cluster_array *createCluster(block *b)
{
    cluster_array *ca = (cluster_array*)malloc(sizeof(b));
    
    ca->sector[0] = *b;

    return ca;
}

// Construtor de trilha
sector_array *createTrack(cluster_array *ca)
{
    sector_array *sa = (sector_array*)malloc(sizeof(ca));
    
    sa->cluster[0] = *ca;

    return sa;
}

// Construtor de cilindro
track_array *createCylinder(sector_array *sa)
{
    track_array *ta = (track_array*)malloc(sizeof(sa));
    
    ta->track[0] = *sa;

    return ta;
}

// Funcao que mostra o menu inicial
void showMenu()
{
    int op;

    clearScreen();
    printf("1 - Escrever Arquivo\n2 - Ler Arquivo\n3 - Apagar Arquivo\n4 - Mostrar Tabela FAT\n5 - Sair\n");
    scanf("%d", &op);

    switch(op)
    {
        case 1:
            writeFile();
            break;
        case 2:
            readFile();
            break;
        case 3:
            delFile();
            break;
        case 4:
            showFAT();
            break;
        case 5:
            printf("Saindo..\n");
            break;
        default:
            printf("Opção inválida, digite novamente\n");
            sleep(1);
            showMenu();
    }

}

void clearScreen()
{
    system(CLEAR);
}

void writeFile()
{
    size_t num_bytes;
    char file[100], fileout[104], text[1024];

    // TODO : verificar se ele digitar com .txt na string
    printf("Informe o nome do arquivo:\n(Até 100 caracteres)\n");
    scanf("%101s", file);
    getchar();

    strcat(fileout, file);
    strcat(fileout, ".txt");

    printf("ESCREVA ABAIXO\nQUANDO TERMINAR DE DIGITAR PRESSIONE A TECLA ENTER PARA GRAVAR NO ARQUIVO\n\n");
    scanf("%1024[^\n]", text);

    // TODO : confirmar o texto digitado, caso contrario possibilitar digitar novamente
    printf("\n\nTEXTO DIGITADO\n\n");
    printf("%s\n", text);
    sleep(1);

    // block b = {"hm"};
    //printf("%s\n", b.bytes_s);

    showMenu();

}

void readFile()
{
    char file[100], fileout[104], text_out[1024];

    printf("Informe o nome do arquivo:\n");
    scanf("%101s", file);
    getchar();
    
    strcat(fileout, file);
    strcat(fileout, ".txt");


    showMenu();

}

void delFile()
{

}

void showFAT()
{

}

