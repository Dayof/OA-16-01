/* Trabalho de OA 2016/01
Desenvolvedoras:
1. Dayanne Fernandes da Cunha - 13/0107191
2.
*/

#include <my_drive.h>

int main( int argc, char *argv[] )
{

    //test with ./my_drive < db.txt
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

    insertBlock(var);

    //showMenu();  
        
    //fatlist *ft = initFatList();
    //initFatSec();

    return 0;
}

// void insertFatList()
// {
//     fatlist_s fl = {file, sector}
//     fatfiles.push_back(fatlist_s());
// }

// void insertFatSec()
// {
//     fatsec.push_back(NULL);
//     fatsec[0] = NULL;
// }

// receive index of the cylinder that will be create
void initCylinder(int index_cy)
{
    cylinder.push_back(track_array());
    for(int i=0; i<CYLINDER_SIZE; ++i)
    {
        cylinder[index_cy].track.push_back(cluster_array());
        for(int j=0; j<TRACK_SIZE; ++j)
        { 
            cylinder[index_cy].track[i].cluster.push_back(sector_array());  
            for(int n=0; n<CLUSTER_SIZE; ++n)
            { 
                cylinder[index_cy].track[i].cluster[j].sector.push_back(block());
            }
        }
    }

    
}

vector<string> stringSector(const string& bytes)
{
    vector<string> sectors;
    string aux_s(bytes);
    int ind_string = 0;
    cout << "valor inicial da string: " << aux_s.size() << endl;

    while(aux_s.size()>512){
        sectors.push_back(aux_s.substr(0,512));
        
        ind_string+=512;
        aux_s = bytes.substr(ind_string);
    }
    sectors.push_back(aux_s);

    for(int i=0;i<sectors.size();++i){
        cout << "bytes string inserida: " << sectors[i].size() << endl;
        cout << "string " << i << ": " << sectors[i] << endl;
    }
        

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

    for(int k=0; k<CYLINDERS && it_size<sec_size; ++k)
    {
            //init cylinder
            initCylinder(k);

        for(int j=0; j<TRACK_SIZE; ++j)
        {    
            for(int i=0; i<CYLINDER_SIZE; ++i)
            {
                for(int n=0; n<CLUSTER_SIZE && it_size<sec_size; ++n, ++it_size)
                {
                    // sectors available
                    if(cylinder[k].track[i].cluster[j].sector[n].bytes_s == "")
                    {    
                        cout << it_size << endl;
                        cylinder[k].track[i].cluster[j].sector[n].bytes_s = sectors[it_size];
                        cout << "setor: " << n << " cluster: " << j << " trilha: " << i << " cilindro: " << k << endl;
                        cout << "string inserida nos setores: " << cylinder[k].track[i].cluster[j].sector[n].bytes_s << endl;
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
    string buffer;
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
    string text, file, fileout;

    // TODO : verificar se ele digitar com .txt na string
    cout << "Informe o nome do arquivo: \n(Até 100 caracteres)" << endl;
    getline(cin, file);
    fileout=file + ".txt";

    cout << "ESCREVA ABAIXO\nQUANDO TERMINAR DE DIGITAR PRESSIONE A TECLA ENTER PARA GRAVAR NO ARQUIVO" << endl;
    cout << endl;

    getline(cin, text);

    insertBlock(text);


    // TODO : confirmar o texto digitado, caso contrario possibilitar digitar novamente
    cout << endl;
    cout << endl;
    cout << "TEXTO DIGITADO" << endl;
    cout << endl;

    cout << text << endl;

    cout << "Pressione enter para continuar..." << endl;
    cin.get();

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

