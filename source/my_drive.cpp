/* Trabalho de OA 2016/01
Desenvolvedoras:
1. Dayanne Fernandes da Cunha - 13/0107191
2.
*/

#include <my_drive.h>

int main()
{
    string var;

    cin >> var;

    block *b = createBlock(var);
    sector_array *sa = createSector(b);
    cluster_array *ca = createCluster(sa);
    track_array *ta = createTrack(ca);
    createCylinder(ta);

    cout << "block: " << b->bytes_s << endl;
    cout << "block from sector: " << sa->sector[0].bytes_s << endl;
    cout << "block from sector from cluster: " << ca->cluster[0].sector[0].bytes_s << endl;
    cout << "block from sector from cluster from track: " << ta->track[0].cluster[0].sector[0].bytes_s << endl;
    cout << "block from sector from cluster from track from cylinder: " << cylinder->track[0].cluster[0].sector[0].bytes_s << endl;
    getchar();

    //showMenu();

    return 0;
}

// Alocando no setor
block *createBlock(const string& bytes)
{
    block *b = new block;
    b->bytes_s = bytes;
    return b;
}

// Construtor de setor
sector_array *createSector(block *b)
{
    sector_array *sa = new sector_array;
    sa->sector[0] = *b;
    return sa;
}

// Construtor de cluster
cluster_array *createCluster(sector_array *sa)
{
    cluster_array *ca = new cluster_array;
    ca->cluster[0] = *sa;
    return ca;
}

// Construtor da trilha
track_array *createTrack(cluster_array *ca)
{
    track_array *ta = new track_array;
    ta->track[0] = *ca;
    return ta;
}

// Construtor do cilindro
void *createCylinder(track_array *ta)
{
    cylinder = new track_array;
    *cylinder= *ta;
}

// return the index of the cluster empty locate at track_array struct
// int checkClusterEmpty(sector_array *sa)
// {
//     int index;



//     return 
// }

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

