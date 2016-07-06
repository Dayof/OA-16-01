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
