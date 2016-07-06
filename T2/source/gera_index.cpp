#include <inc_system.hpp>

class PrimaryIndex
{
public:
  PrimaryIndex(string f){filename = f;};
  void createPI(vector<string>, int);
  void insertOrdered(vector<pair<string,int> > &, pair<string,int>);
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
  void insertOrdered(vector<pair<string, vector<int> > > &, int, string);
  void insertOrderedInvertList(vector<int> &, int);
  void printVectorSec(ofstream &, vector<int>);
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
  PI2.createPI(files, 2);
  PI3.createPI(files, 3);

  InvertIndex II1("sec_lista1.txt"), II2("sec_lista2.txt"), II3("sec_lista3.txt");
  II1.createII(files, 1);
  //II2.createII(files, 2);
  //II3.createII(files, 3);
}

void PrimaryIndex::createPI(vector<string> files, int indexFile)
{
  ofstream index;
  ifstream benchmark;
  string id;
  vector<pair<string,int> > indexList;
  int i=0;

  index.open(this->filename);
  benchmark.open(files[indexFile]);

  if(index.is_open() && benchmark.is_open())
  {
    if(indexFile==1)
      // static file
      while(benchmark >> id)
      {
        benchmark.ignore(256, '\n');
        pair<string,int> p(id,i);
        this->insertOrdered(indexList, p);
        ++i;
      }
    else
      // dynamic file
      while(getline(benchmark,id,'|'))
      {
        benchmark.ignore(256, '\n');
        pair<string,int> p(id,i);
        this->insertOrdered(indexList, p);
        ++i;
      }
  }

  // number of deleted registers of the data file
  index << 0 << endl;

  for(int j=0; j<indexList.size(); ++j)
    index << indexList[j].first << " " << indexList[j].second << endl;

  index.close();
  benchmark.close();
}

void PrimaryIndex::insertOrdered(vector<pair<string,int> > &indexList, pair<string,int> id)
{
  vector<pair<string,int> >::iterator it = indexList.end()-1;
  pair<string,int> aux;

  if(indexList.empty()) indexList.push_back(id);
  else if((*it).first>id.first)
  {
    while((*it).first>id.first) --it;
    aux=*it;
    indexList.insert(it+1,id);
  }
  else indexList.push_back(id);
}

void InvertIndex::createII(vector<string> files, int indexFile)
{
  ofstream index;
  ifstream benchmark;
  string id, number, name;
  vector<pair<string, vector<int> > > pkList;
  vector<string> nameList;
  int i=0;

  index.open(this->filename);
  benchmark.open(files[indexFile]);

  if(index.is_open() && benchmark.is_open())
  {
    if(indexFile==1)
      // static file
      while(benchmark >> id >> number >> name)
      {
        benchmark.ignore(256, '\n');
        // cout << name << endl;
        // getchar();
        this->insertOrdered(pkList, i, name);
        ++i;
      }
    // else
    //   // dynamic file
    //   while(getline(benchmark,id,'|'))
    //   {
    //     benchmark.ignore(256, '\n');
    //     pair<string,int> p(id,i);
    //     this->insertOrdered(indexList, p);
    //     ++i;
    //   }
  }

  for(int j=0; j<pkList.size(); ++j)
  {
    index << pkList[j].first << " ";
    this->printVectorSec(index, pkList[j].second);
    index << endl;
  }

  index.close();
  benchmark.close();
}

void InvertIndex::printVectorSec(ofstream &index, vector<int> pkList)
{
  for(int i=0; i<pkList.size(); ++i) index << pkList[i] << " ";
}

void InvertIndex::insertOrdered(vector<pair<string, vector<int> > > &pkList, int rrn, string name)
{
  vector<pair<string, vector<int> > >::iterator it = pkList.begin();
  pair<string, vector<int> > aux;
  vector<int> nameList;

  if(pkList.empty())
  {
    nameList.push_back(rrn);
    aux=make_pair(name, nameList);
    pkList.push_back(aux);
  }
  else
  {
    while(it!=pkList.end())
    {
      if((*it).first!=name) it++;
      else break;
    }
    if(it!=pkList.end())
    {
      nameList = (*it).second;
      this->insertOrderedInvertList(nameList, rrn);
      (*it).second = nameList;
    }
    else
    {
      nameList.push_back(rrn);
      aux=make_pair(name, nameList);
      pkList.push_back(aux);
    }
  }

  // cout << pkList.back().first << endl;
  // this->printVectorSec(pkList.back().second);
  // cout << endl;
  // getchar();
}

void InvertIndex::insertOrderedInvertList(vector<int> &nameList, int rrn)
{
  vector<int>::iterator it = nameList.end()-1;
  int aux;

  if(*it>rrn)
  {
    while(*it>rrn) --it;
    aux=*it;
    nameList.insert(it+1,rrn);
  }
  else nameList.push_back(rrn);
}
