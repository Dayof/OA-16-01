/* Trabalho de OA 2016/01
Desenvolvedoras:
1. Dayanne Fernandes da Cunha - 13/0107191
2.
*/

#include <my_drive.h>

int main( int argc, char *argv[] )
{

    vector <string> v;
    ostringstream oss;
    string var;

    copy(istream_iterator<string>(cin),
        istream_iterator<string>(),
        back_inserter(v));

    if (!v.empty())
    {
        std::copy(v.begin(), v.end()-1,
            ostream_iterator<string>(oss, " "));

        oss << v.back();
    }
    var = oss.str();
        
    //fatlist *ft = initFatList();
    //initFatSec();
    insertBlock(var);

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

// receive index of the cylinder that will be create
void initCylinder(block b, int index_cy)
{
    cylinder.push_back(track_array());
    cylinder[index_cy].track.push_back(cluster_array());
    cylinder[index_cy].track[0].cluster.push_back(sector_array());
    cylinder[index_cy].track[0].cluster[0].sector.push_back(b);

    cout << "string inserida ao iniciar cilindro: " << cylinder[index_cy].track[0].cluster[0].sector[0].bytes_s << endl;
}

vector<string> stringSector(const string& bytes)
{
    vector<string> sectors;
    string aux_s(bytes);
    int ind_string = 0;
    cout << "valor inicial da string: " << aux_s.size() << endl;

    while(aux_s.size()>512){
        sectors.push_back(aux_s.substr(0,ind_string+512));
        ind_string+=512;
        aux_s = bytes.substr(ind_string);
    }
    sectors.push_back(aux_s);

    for(int i=0;i<sectors.size();++i)
        cout << "string " << i << ": " << sectors[i] << endl;

    return sectors;
}

//Alocando no setor
void insertBlock(const string& bytes)
{
    vector<string> sectors;
    int sec_size, it_size=0;

    sectors = stringSector(bytes);
    sec_size = sectors.size();

    cout << "tamanho do vetor das strings: " << sec_size << endl;

    for(int i=0; i<CYLINDER_SIZE; ++i)
    {
        for(int k=0; k<CYLINDERS && it_size<sec_size; ++k)
        {
            //init cylinder
            block b = {sectors[it_size]};
            it_size++;
            initCylinder(b, k);

            for(int j=0; j<TRACK_SIZE; ++j)
            {   
                if(cylinder[k].track[i].cluster[j].sector.size()<=CLUSTER_SIZE)
                {    
                    // sectors available 
                    for(int n=sectors.size(); n<CLUSTER_SIZE && it_size<sec_size; ++n, ++it_size)
                    {
                        cout << it_size << endl;
                        block b = {sectors[it_size]};
                        cylinder[k].track[i].cluster[j].sector.push_back(b);
                        cout << "string inserida nos setores: " << cylinder[k].track[i].cluster[j].sector[it_size].bytes_s << endl;
                    }
                }
            }
        }
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

