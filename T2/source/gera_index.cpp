#include <inc_system.hpp>


class PrimaryIndex
{
public:
  PrimaryIndex(string f){filename = f;};
  void createPI(vector<string>, int);
  // void insert(string);
  // void remove(string);
  // void search(string);
  // void print();
private:
  string filename;
};

class InvertIndex
{
public:
  InvertIndex(string f){filename = f;};
  void createII(vector<string>, int);
  // void insert(string);
  // void remove(string);
  // void search(string);
  // void print();
private:
  string filename;
};

int main( int argc, char *argv[] )
{
  if(argc==4)
  {
    vector<string> file_list_name(argv, argv + argc);
    if(!checkList(file_list_name)) cout << "Some file doesn't exist or can't be opened." << endl;
    else createFiles(file_list_name);
  }
  else{
    cout << "Wrong parameter." << endl;
  }
  return 0;
}

bool checkList(vector<string> files)
{
  ifstream myfile;
  bool result = true;

  for(int i=1;i<3;++i)
  {
    myfile.open (files[i]);
    if (!myfile.is_open()) result = false;
    else myfile.close();
  }

  return result;
}

void createFiles(vector<string> files)
{
  PrimaryIndex PI1("index_lista1.txt"), PI2("index_lista2.txt"), PI3("index_lista3.txt");
  PI1.createPI(files, 1);
  //TODO delimit pipe |
  //PI2.createPI(files, 2);
  //PI3.createPI(files, 3);

  // InvertIndex II1("sec_lista1.txt"), II2("sec_lista2.txt"), II3("sec_lista3.txt");
  // II1.createII();
  // II2.createII();
  // II3.createII();
}

void PrimaryIndex::createPI(vector<string> files, int indexFile)
{
  ofstream index;
  ifstream benchmark;
  string id;
  int i=0;

  index.open(this->filename);
  benchmark.open(files[indexFile]);

  if(index.is_open() && benchmark.is_open())
    while(benchmark >> id)
    {
      index << id << " " << i << endl;
      benchmark.ignore(256, '\n');
      ++i;
    }

  index.close();
  benchmark.close();
}

void InvertIndex::createII(vector<string> files, int indexFile)
{
  ofstream file;
  file.open(this->filename, ios::in);
  file.close();
}
