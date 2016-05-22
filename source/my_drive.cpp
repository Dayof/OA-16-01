/* Trabalho de OA 2016/01
Desenvolvedoras:
1. Dayanne Fernandes da Cunha - 13/0107191
2.
*/

#include <my_drive.h>

int main()
{
    string var;

    getline(cin, var);
    //fatlist *ft = initFatList();
    //initFatSec();
    insertBlock(var, 0);

    //showMenu();

    return 0;
}

// fatlist initFatList()
// {
//     fatlist *ft = new fatlist;
//     ft = NULL;
//     return ft;
// }

// void initFatSec()
// {
//     fatsec.push_back(NULL);
//     fatsec[0] = NULL;
// }

void initCylinder(block b)
{
    cylinder.push_back(track_array());
    cylinder[0].track.push_back(cluster_array());
    cylinder[0].track[0].cluster.push_back(sector_array());
    cylinder[0].track[0].cluster[0].sector.push_back(b);

    cout << cylinder[0].track[0].cluster[0].sector[0].bytes_s << endl;
}

//Alocando no setor
void insertBlock(const string& bytes, int sector)
{
    vector<string> sectors;
    string s, aux_s;
    int l, s_limit;
    while(bytes.size()>512){
        l=0;
        for(int k=0;k<4;++k){
            aux_s = bytes.substr(l, bytes.size());
            cout << aux_s << endl;
            s_limit = aux_s.size()%512;
            if(aux_s.size()<512){
                s = s.substr(l-1, l+s_limit-1);
                cout << "string cut: " << s << endl;
            }
            else{
                s = aux_s;
            }
            sectors[k] = s;
        }
        l+=512;
    }

    block b = {bytes};
    if(!cylinder.empty()) 
        for(int i=0; i<CYLINDER_SIZE; ++i)
            for(int j=0; j<TRACK_SIZE; ++j){
                if(cylinder[0].track[i].cluster[j].sector.size()<=CLUSTER_SIZE) 
                {    
                    for(int n=sectors.size(); n<4; ++n)
                    {
                        block b = {sectors[n]};
                        cout << b.bytes_s << endl;
                        cylinder[0].track[i].cluster[j].sector.push_back(b);
                    }
                }
            }
    else
    {
        initCylinder(b);
    } 
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

