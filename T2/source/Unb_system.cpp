#include <inc_system.hpp>

class StudentManagement
{
public:
  StudentManagement(){};
  void insertNewStudent();
  void deleteStudent(); //jubilar
  void gradingStudent();
  void report();
  void search();

  bool askInfoStudent(vector<string> &);
  void registerNameFile(fstream &, string);
  string generateLastId();
  int searchStudentInPkIndex(string);
  void deleteStudentPkIndex(int);

  void loadPkIndex();
  void attPkIndex();
private:
  vector<pair<string,int> > indexList;
  int del_reg;
};

int main( int argc, char *argv[] )
{
    showMenu();
}

void showMenu()
{
    string buffer;
    int op;
    StudentManagement students;

    students.loadPkIndex();

    clearScreen();
    cout << "Sistema de Notas UnB v0.1 beta" << endl;
    cout << "1. Inserir novo aluno na UnB\n"
            "2. Jubilar um aluno da UnB\n"
            "3. Dar nota ao aluno numa disciplina\n"
            "4. Relatório\n"
            "5. Buscar\n"
            "6. Sair" << endl;
    cin >> op;

    switch(op)
    {
        case 1:
            students.insertNewStudent();
            break;
        case 2:
            students.deleteStudent();
            break;
        case 3:
            students.gradingStudent();
            break;
        case 4:
            students.report();
            break;
        case 5:
            students.search();
            break;
        case 6:
            cout << "Saindo..\n" << endl;
            break;
        default:
            cin.get();
            cout << "Opção inválida, digite novamente" << endl;
            pressEnter();
            showMenu();
    }

}

void StudentManagement::loadPkIndex()
{
  ifstream pkIndex;
  string id;
  int nrr;

  pkIndex.open("index_lista1.txt");

  if(pkIndex.is_open())
  {
    pkIndex >> nrr;
    pkIndex.ignore(256, '\n');
    this->del_reg=nrr;

    while(pkIndex >> id >> nrr)
    {
      pkIndex.ignore(256, '\n');
      pair<string,int> p(id,nrr);
      this->indexList.push_back(p);
    }
  }

  pkIndex.close();
}

void StudentManagement::insertNewStudent()
{
  fstream index;
  vector<string> infoStudent;
  string id;

  if(this->askInfoStudent(infoStudent))
  {
    index.open("lista1.txt", ios::in | ios::app);
    if(index.is_open())
    {
      id = this->generateLastId();
      index << id << " " << infoStudent[0] << " ";
            this->registerNameFile(index, infoStudent[1]);
      index << " " << infoStudent[2] << "    " << infoStudent[3]
            << "         " << infoStudent[4] << endl;
      cout << "Executando gerador de índices..." << endl;
      system("./gera_index lista1.txt lista2.txt lista3.txt");
      cout << "Índices atualizados!" << endl;
    }

    index.close();
  }
  else showMenu();
}

string StudentManagement::generateLastId()
{
  string id, ad1= "0", ad2= "00";
  int aux;

  id=this->indexList.back().first;

  id.erase(0,2);
  aux = stoi(id);
  ++aux;

  if(to_string(aux).size()==2) id="ID" + ad1 + to_string(aux);
  else if(to_string(aux).size()==1) id="ID" + ad2 + to_string(aux);
  else id="ID" + to_string(aux);

  return id;
}

void StudentManagement::registerNameFile(fstream &index, string name)
{
  int s_name = name.size();
  if(s_name<23)
  {
    index << name;
    for(int i=0; i<(23-s_name); ++i) index << " ";
  }
}

bool StudentManagement::askInfoStudent(vector<string> &infoStudent)
{
  string mat, nome, op, curso, turma, ans;
  bool incorrect;

  clearScreen();
  do {
    cout << "Escreva as seguintes informações do estudante:" << endl;
    cout << "Matrícula (000000, de 0 a 999999)\n";
    cin >> mat;
    cout << "Nome (Até 23 caracteres)\n";
    cin >> nome;
    cout << "Operação (00, de 0 a 99)\n";
    cin >> op;
    cout << "Curso (A, de A-Z)\n";
    cin >> curso;
    cout << "Turma (AA, de A-Z)\n";
    cin >> turma;
    if( mat.size()!=6 || nome.size()>23 ||
        op.size()!=2 || curso.size()!=1 || turma.size()!=2)
    {
      incorrect=true;
      cout << "Algum dado está incorreto, tente inserir novamente." << endl;
      pressEnter();
    }
    else incorrect=false;
  } while(incorrect);

  cout << "Deseja confirmar os dados acima? (y/n)" << endl;
  cin >> ans;

  if(ans=="y")
  {
    infoStudent.push_back(mat);
    infoStudent.push_back(nome);
    infoStudent.push_back(op);
    infoStudent.push_back(curso);
    infoStudent.push_back(turma);

    return true;
  }
  else return false;
}

void StudentManagement::deleteStudent()
{
  string id, ans;
  bool incorrect;
  int pos_student;

  clearScreen();
  do {
    cout << "Escreva o ID do aluno a ser jubilado:" << endl;
    cout << "ID (ID000, de 000 a 999)\n";
    cin >> id;
    if( id.size()!=5)
    {
      incorrect=true;
      cout << "Dado incorreto, tente inserir novamente." << endl;
      pressEnter();
    }
    else
    {
      pos_student=this->searchStudentInPkIndex(id);
      if(pos_student>=0) incorrect=false;
      else
      {
        cout << "Estudante não existe! Tente inserir outro nome." << endl;
        pressEnter();
        incorrect=true;
      }
    }
  } while(incorrect);

  cout << "Deseja jubilar o aluno de ID " << id << " ? (y/n)" << endl;
  cin >> ans;

  if(ans=="y")
  {
    this->deleteStudentPkIndex(pos_student);
    cout << "Aluno deletado com sucesso." << endl;
    pressEnter();
  }
  showMenu();
}

void StudentManagement::deleteStudentPkIndex(int pos_student)
{
  this->indexList[pos_student].second=-1;
  ++this->del_reg;
  this->attPkIndex();
}

void StudentManagement::attPkIndex()
{
  ofstream pkIndex;

  pkIndex.open("index_lista1.txt");

  if(pkIndex.is_open())
  {
    pkIndex << this->del_reg << endl;

    for(int j=0; j<this->indexList.size(); ++j)
      pkIndex << indexList[j].first << " " << indexList[j].second << endl;
  }

  pkIndex.close();
}

int StudentManagement::searchStudentInPkIndex(string id)
{
  vector<pair<string,int> >::iterator it;
  for(it=this->indexList.begin(); it!=this->indexList.end();++it)
    if((*it).first==id) break;

  if(it==this->indexList.end()) return -10000;
  else return (distance(this->indexList.begin(), it));
}

void StudentManagement::gradingStudent()
{

}

void StudentManagement::report()
{

}

void StudentManagement::search()
{

}

void clearScreen()
{
    system(CLEAR);
}

void pressEnter()
{
    cout << "Pressione enter para continuar..." << endl;
    getchar();
}
