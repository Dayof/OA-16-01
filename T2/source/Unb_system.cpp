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
  string generateLastId(fstream &);
private:
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
      id = this->generateLastId(index);
      index << id << " " << infoStudent[0] << " ";
            this->registerNameFile(index, infoStudent[1]);
      index << " " << infoStudent[2] << "    " << infoStudent[3]
            << "         " << infoStudent[4] << endl;
      system("./gera_index lista1.txt lista2.txt lista3.txt");
    }

    index.close();
  }
  else showMenu();
}

string StudentManagement::generateLastId(fstream &index)
{
  string id, ad1= "0", ad2= "00";
  int aux;

  index.seekg(-56, ios::end);
  index >> id;

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
