/* Trabalho de OA 2016/01
Desenvolvedoras:
1. Dayanne Fernandes da Cunha - 13/0107191
2. Rafaella dos Reis Santos - 14/0159932
*/

#include <my_drive.h>

class Coordinate
{
public:
    int cylinder, track, cluster;
    void empty();
    Coordinate(int cylinder, int track, int cluster);
};

void Coordinate::empty()
{
    this->cylinder = 0;
    this->track = 0;
    this->cluster = 0;
}

Coordinate::Coordinate(int cylinder, int track, int cluster)
{
    this->cylinder = cylinder;
    this->cluster = cluster;
    this->track = track;
}

int main( int argc, char *argv[] )
{
    //init fat list
    initFatSec();

    //init cylinder
    initCylinder();
    
    showMenu();

    //test with ./my_drive < db.txt
    // vector <string> v;
    // ostringstream oss;
    // string var;

    // copy(istream_iterator<string>(cin),
    //     istream_iterator<string>(),
    //     back_inserter(v));

    // if (!v.empty())
    // {
    //     copy(v.begin(), v.end()-1,
    //         ostream_iterator<string>(oss, " "));

    //     oss << v.back();
    // }
    // var = oss.str();
    
    // for(int i=0; i<151;++i) insertBlock("text.txt", var);

    return 0;
}

void initFatSec()
{
    fatent_s fs = {0, 0, -1};
    for(int i=0; i< 3000;++i) fatsec.push_back(fs);
}


void insertFatList(const string& file, unsigned int sector,  unsigned long bytes)
{
    fatlist_s fl = {file, sector, bytes};
    fatfiles.push_back(fl);
}

void insertFatSec(vector<int> sectors_it)
{
    for(int i=0;i<sectors_it.size();++i)
    {
        fatsec[sectors_it[i]].used=1;
        if(i==sectors_it.size()-1)
        {
            fatsec[sectors_it[i]].eof=1;
            fatsec[sectors_it[i]].next=-1;
        }
        else fatsec[sectors_it[i]].next=sectors_it[i+1];
    }
}

// receive index of the cylinder that will be create
void initCylinder()
{
    for(int k=0; k<CYLINDERS; ++k)
    {
        cylinder.push_back(track_array());
        for(int i=0; i<TRACK_PER_CYLINDER; ++i)
        {
            cylinder[k].track.push_back(cluster_array());
            for(int j=0; j<CLUSTER_PER_TRACK; ++j)
            {
                cylinder[k].track[i].cluster.push_back(sector_array());
                for(int n=0; n<SECTOR_PER_CLUSTER; ++n)
                {
                    cylinder[k].track[i].cluster[j].sector.push_back(block());
                }
            }
        }
    }
}

vector<string> stringSector(const string& bytes)
{
    vector<string> sectors;
    string aux_s(bytes);
    int ind_string = 0;

    stringstream ss;
    ss << aux_s.size();
    sectors.push_back(ss.str());

    while(aux_s.size()>512){
        sectors.push_back(aux_s.substr(0,512));

        ind_string+=512;
        aux_s = bytes.substr(ind_string);
    }
    sectors.push_back(aux_s);

    return sectors;
}

Coordinate* searchCluster()
{
    for(int i=0; i<TRACK_PER_CYLINDER; ++i)
    {
        for(int k=0; k<CYLINDERS; ++k)
        {
            for(int j=0; j<CLUSTER_PER_TRACK; ++j)
            {
                if(clusterAvailable(k,i,j))
                    return new Coordinate(k,i,j);
            }
        }
    }

    return NULL; // HD is full
}

bool clusterAvailable(int cylinder, int track, int cluster)
{
    int sector=(300*cylinder)+(60*track)+(4*cluster), result = false;
    if(fatsec[sector].used==0) result = true;

    return result;
}

//Alocando no setor
void insertBlock(const string& filename, const string& bytes)
{
    vector<string> sectors;
    vector<int> vectors_it;
    int sec_size, it_size=1, iter_sector=-1, next_sector=0;
    unsigned long total_size;
    clock_t t;
    Coordinate* empty_cluster;

    sectors = stringSector(bytes);
    stringstream(sectors[0]) >> total_size;
    sec_size = sectors.size();

    t=clock();

    empty_cluster = searchCluster();

    if(!empty_cluster)
    {
        cout << "Hard Drive is full. Please free some space before writing again.";
        return;
    }

    for(int k=empty_cluster->cylinder; k<CYLINDERS && it_size<sec_size; ++k)
    {
        for(int j=empty_cluster->cluster; j<CLUSTER_PER_TRACK && it_size<sec_size; ++j)
        {
            for(int i=empty_cluster->track; i<TRACK_PER_CYLINDER && it_size<sec_size; ++i)
            {
                empty_cluster->empty();
                //if cluster is not available
                if(!clusterAvailable(k,i,j)) continue;

                for(int n=0; n<SECTOR_PER_CLUSTER && it_size<sec_size; ++n, ++it_size)
                {
                    // Parallel write on cylinder
                    iter_sector=n+(300*k)+(60*i)+(4*j);
                    vectors_it.push_back(iter_sector);

                    //cout << it_size << endl;
                    cylinder[k].track[i].cluster[j].sector[n].bytes_s = sectors[it_size];

                    //cout << "setor: " << n << " cluster: " << j << " trilha: " << i << " cilindro: " << k << endl;

                }
            }
        }
    }

    insertFatSec(vectors_it);

    insertFatList(filename, vectors_it[0], total_size);

    t = clock()-t;

    showTime(t);
}

void showTime(clock_t t)
{
    cout << "elapsed seconds: " << t / CLOCKS_PER_MILI << endl;
    cin.get();
}

// Funcao que mostra o menu inicial
void showMenu()
{
    string buffer;
    int op;

    clearScreen();
    cout << "1 - Escrever Arquivo\n2 - Ler Arquivo\n3 - Apagar Arquivo\n4 - Mostrar Tabela FAT\n5 - Sair" << endl;
    cin >> op;

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
            cin.get();
            cout << "Opção inválida, digite novamente" << endl;
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
    string text, file, fileout;

    while(true)
    {
        // TODO : verificar se ele digitar com .txt na string
        cout << "Informe o nome do arquivo:" << endl;
        cin.get();
        getline(cin, file);
        fileout=file + ".txt";

        if(fileInFAT(fileout)!=-1)
        {
            cout << "Arquivo já existe no HD. "<< endl;
            cout << "Pressione enter para continuar..." << endl;
            cin.get();
        } 
        else break;   
    }

    cout << "ESCREVA ABAIXO\nQUANDO TERMINAR DE DIGITAR PRESSIONE A TECLA ENTER PARA GRAVAR NO ARQUIVO\n" << endl;

    getline(cin, text);

    insertBlock(fileout, text);

    // TODO : confirmar o texto digitado, caso contrario possibilitar digitar novamente
    cout << "\n\nTEXTO DIGITADO\n" << endl;

    cout << text << endl;

    cout << "Pressione enter para continuar..." << endl;
    cin.get();

    showMenu();

}

void readFile()
{
    string file, fileout, str_file;
    int f_sector;
    clock_t t;

    // TODO : verificar se ele digitar com .txt na string
    cout << "Informe o nome do arquivo:" << endl;
    cin.get();
    getline(cin, file);
    fileout=file + ".txt";
    f_sector = fileInFAT(fileout);

    if(f_sector!=-1)
    {
        t=clock();
        str_file = showFile(f_sector);
        t=clock()-t;
        showTime(t);

        cout << str_file << endl;
        writeFileHD(showFile(f_sector));
    }
    else cout << "Arquivo não existente." << endl;

    cout << "Pressione enter para continuar..." << endl;
    cin.get();

    showMenu();

}

void writeFileHD(string text)
{
    ofstream file;
    file.open("SAIDA.txt");
    file << text;
    file.close();
}

string showFile(int first_sector)
{
    string all_file="";
    int sector, cluster, track, cylind;

    sector=first_sector;

    while(fatsec[sector].eof!=1)
    {
        sector=sector%300;
        cluster=sector/4;
        track=cluster/15;
        cylind=track/5;
        all_file=all_file+cylinder[cylind].track[track].cluster[cluster].sector[sector%4].bytes_s;

        sector = fatsec[sector].next;
    }

    sector=sector%300;
    cluster=sector/4;
    track=cluster/15;
    cylind=track/5;
    all_file=all_file+cylinder[cylind].track[track].cluster[cluster].sector[sector%4].bytes_s;

    return all_file;
}

int fileInFAT(string filename)
{
    int result = -1;

    for(int i=0; i<fatfiles.size();++i)
    {
        if(fatfiles[i].file_name == filename)
        {
            result = fatfiles[i].first_sector;
            break;
        }
    }

    return result;
}

bool delFileInFAT(int f_sector, string filename)
{
    bool result = false;
    int j, aux_j;

    j = f_sector;

    try
    {
        while(fatsec[j].eof!=1)
        {
            fatsec[j].used=0;
            fatsec[j].eof=0;
            aux_j = fatsec[j].next;
            fatsec[j].next=-1;
            j = aux_j;
        }

        fatsec[j].used=0;
        fatsec[j].eof=0;
        aux_j = fatsec[j].next;
        fatsec[j].next=-1;
        j = aux_j;

        for(int i=0; i<fatfiles.size();++i)
        {
            if(fatfiles[i].file_name == filename)
            {
                fatfiles.erase(fatfiles.begin()+i);
                result = true;
                break;
            }
        }
    }
    catch (exception& e)
    {
        cerr << "Exception catched : " << e.what() << endl;
        result = false;
    }

    return result;
}

void delFile()
{
    string file, fileout;
    int f_sector;
    clock_t t;

    // TODO : verificar se ele digitar com .txt na string
    cout << "Informe o nome do arquivo:" << endl;
    cin.get();
    getline(cin, file);
    fileout=file + ".txt";
    f_sector = fileInFAT(fileout);

    if(f_sector!=-1)
    {
        if(delFileInFAT(f_sector,fileout)) cout << "Arquivo deletado com sucesso!" << endl;
        else cout << "Ocorreu algum erro na deleção." << endl;
    }
    else cout << "Arquivo não existente." << endl;

    cout << "Pressione enter para continuar..." << endl;
    cin.get();

    showMenu();
}

void showFAT()
{
    int j=0;

    cout << "NOME      TAMANHO EM DISCO        LOCALIZAÇÃO" << endl;

    for(int i=0; i < fatfiles.size(); ++i)
    {
        cout << fatfiles[i].file_name << "      " << fatfiles[i].total_bytes << " Bytes                 ";
        j = fatfiles[i].first_sector;

        while(fatsec[j].eof!=1)
        {
            cout << j << " ";
            j = fatsec[j].next;
        }

        cout << j << " ";
        cout << endl;
    }

    cin.get();
    cout << "\nPressione enter para continuar..." << endl;
    cin.get();
    
    showMenu();
}
