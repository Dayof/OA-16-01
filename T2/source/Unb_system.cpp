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

  int searchStudentInPkIndex1(string);
  int searchStudentInPkIndex2(string);
  int searchStudentInPkIndex3(string);

  void deleteStudentPkIndex(int, int);
  bool completeDelStudent();
  bool delInFile(string, string, vector<pair<string, int> >);

  bool gradStudentDisc(int, int, string);
  bool gradNewStudentDisc(int, int, string);

  void loadPkIndex(string, int);
  void attPkIndex();
private:
  vector<pair<string,int> > indexList, indexList2, indexList3;
  vector<pair<string,int> > indexListPRR, indexListPRR2, indexListPRR3;
  int del_reg, del_reg2, del_reg3;
};

int main( int argc, char *argv[] )
{
  cout << "Executando gerador de índices..." << endl;
  system("./gera_index lista1.txt lista2.txt lista3.txt");
  cout << "Índices atualizados!" << endl;
  pressEnter();
  showMenu();
}

void showMenu()
{
    string buffer;
    int op;
    StudentManagement students;

    students.loadPkIndex("index_lista1.txt", 1);
    students.loadPkIndex("index_lista2.txt", 2);
    students.loadPkIndex("index_lista3.txt", 3);

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

void StudentManagement::loadPkIndex(string filename, int index)
{
  ifstream pkIndex;
  int prr, nrr;
  string id;

  pkIndex.open(filename);

  if(pkIndex.is_open())
  {
    pkIndex >> nrr;
    pkIndex.ignore(256, '\n');
    if(index==1) this->del_reg=nrr;
    if(index==2) this->del_reg2=nrr;
    else this->del_reg3=nrr;

    while(pkIndex >> id >> prr >> nrr)
    {
      pkIndex.ignore(256, '\n');
      pair<string,int> n(id,nrr);
      if(index==1) this->indexList.push_back(n);
      else if(index==2) this->indexList2.push_back(n);
      else this->indexList3.push_back(n);

      pair<string,int> p(id,prr);
      if(index==1) this->indexListPRR.push_back(p);
      else if(index==2) this->indexListPRR2.push_back(p);
      else this->indexListPRR3.push_back(p);
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
  bool incorrect = false;
  int pos_student1, pos_student2, pos_student3;

  clearScreen();

  do {
    cout << "Escreva o ID do aluno a ser jubilado:" << endl;
    cout << "ID (ID000, de 000 a 999)\n";
    cin >> id;
    if(id.size()!=5)
    {
      incorrect=true;
      cout << "Dado incorreto, tente inserir novamente." << endl;
      pressEnter();
    }
    else
    {
      pos_student1=this->searchStudentInPkIndex1(id);
      pos_student2=this->searchStudentInPkIndex2(id);
      pos_student3=this->searchStudentInPkIndex3(id);
      if(pos_student1>=0 || pos_student2>=0 || pos_student3>=0) incorrect=false;
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
    if(pos_student1>=0) this->deleteStudentPkIndex(pos_student1, 1);
    if(pos_student2>=0) this->deleteStudentPkIndex(pos_student2, 2);
    if(pos_student3>=0) this->deleteStudentPkIndex(pos_student3, 3);
    cout << "Aluno deletado com sucesso." << endl;
    pressEnter();
  }
  showMenu();
}

void StudentManagement::deleteStudentPkIndex(int pos_student, int index)
{
  if(index==1)
  {
    this->indexList[pos_student].second=-1;
    ++this->del_reg;
  }
  else if(index==2)
  {
    this->indexList2[pos_student].second=-1;
    ++this->del_reg2;
  }
  else
  {
    this->indexList3[pos_student].second=-1;
    ++this->del_reg3;
  }

  if(this->del_reg<5 && this->del_reg2<5 && this->del_reg3<5) this->attPkIndex();
  else
  {
    if(this->completeDelStudent())
      cout << "Estudantes deletados dos benchmarks com sucesso!" << endl;
    cout << "Executando gerador de índices..." << endl;
    system("./gera_index lista1.txt lista2.txt lista3.txt");
    cout << "Índices atualizados!" << endl;
  }
}

int StudentManagement::searchStudentInPkIndex1(string id)
{
  vector<pair<string,int> >::iterator it;
  for(it=this->indexList.begin(); it!=this->indexList.end();++it)
    if((*it).first==id) break;

  if(it==this->indexList.end()) return -10000;
  else return (distance(this->indexList.begin(), it));
}

int StudentManagement::searchStudentInPkIndex2(string id)
{
  vector<pair<string,int> >::iterator it;
  for(it=this->indexList2.begin(); it!=this->indexList2.end();++it)
    if((*it).first==id) break;

  if(it==this->indexList2.end()) return -10000;
  else return (distance(this->indexList2.begin(), it));
}

int StudentManagement::searchStudentInPkIndex3(string id)
{
  vector<pair<string,int> >::iterator it;
  for(it=this->indexList3.begin(); it!=this->indexList3.end();++it)
    if((*it).first==id) break;

  if(it==this->indexList3.end()) return -10000;
  else return (distance(this->indexList3.begin(), it));
}


bool StudentManagement::completeDelStudent()
{
  vector<pair<string, int> > del_stu1, del_stu2, del_stu3;

  for(int j=0; j<this->indexList.size(); ++j)
  {
    if(this->indexList[j].second==-1)
    {
      pair<string, int> p(this->indexListPRR[j].first,
                          this->indexListPRR[j].second);
      del_stu1.push_back(p);
    }
  }

  for(int j=0; j<this->indexList2.size(); ++j)
  {
    if(this->indexList2[j].second==-1)
    {
      pair<string, int> p(this->indexListPRR2[j].first,
                          this->indexListPRR2[j].second);
      del_stu2.push_back(p);
    }
  }

  for(int j=0; j<this->indexList3.size(); ++j)
  {
    if(this->indexList3[j].second==-1)
    {
      pair<string, int> p(this->indexListPRR3[j].first,
                          this->indexListPRR3[j].second);
      del_stu3.push_back(p);
    }
  }

  if(this->delInFile("lista1.txt", "out1.txt", del_stu1) &&
    this->delInFile("lista2.txt", "out2.txt", del_stu2) &&
    this->delInFile("lista3.txt", "out3.txt", del_stu3)) return true;
  else return false;
}

bool StudentManagement::delInFile(string filename, string filename2,
                                vector<pair<string, int> > students_to_be_del)
{
  ofstream index_out_file(filename2);
  ifstream indexFile(filename);
  vector<string> lines;
  string line;

  if(indexFile.is_open())
  {
    for(int i=0; i<students_to_be_del.size(); ++i)
    {
      indexFile.seekg(students_to_be_del[i].second);
      getline(indexFile, line);
      lines.push_back(line);
    }

    indexFile.seekg(0, ios::beg);
    while(getline(indexFile, line))
      if(find(lines.begin(),lines.end(),line)==lines.end())
        index_out_file << line << endl;
  }
  else return false;

  indexFile.close();
  index_out_file.close();

  remove(filename.c_str());
  rename(filename2.c_str(), filename.c_str());

  return true;
}

void StudentManagement::attPkIndex()
{
  ofstream pkIndex, pkIndex2, pkIndex3;

  pkIndex.open("index_lista1.txt");
  pkIndex2.open("index_lista2.txt");
  pkIndex3.open("index_lista3.txt");

  if(pkIndex.is_open())
  {
    pkIndex << this->del_reg << endl;

    for(int j=0; j<this->indexList.size(); ++j)
      pkIndex << indexList[j].first << " " << indexListPRR[j].second
      << " " << indexList[j].second << endl;
  }
  if(pkIndex2.is_open())
  {
    pkIndex2 << this->del_reg2 << endl;

    for(int j=0; j<this->indexList2.size(); ++j)
      pkIndex2 << indexList2[j].first << " " << indexListPRR2[j].second
      << " " << indexList2[j].second << endl;
  }

  if(pkIndex3.is_open())
  {
    pkIndex3 << this->del_reg3 << endl;

    for(int j=0; j<this->indexList3.size(); ++j)
      pkIndex3 << indexList3[j].first << " " << indexListPRR3[j].second
      << " " << indexList3[j].second << endl;
  }

  pkIndex.close();
  pkIndex2.close();
  pkIndex3.close();
}

void StudentManagement::gradingStudent()
{
  string id, grad, msgerror;
  bool incorrect = false;
  int pos_student1, pos_student2=-1000,
      pos_student3=-1000, disc, gradi1, gradi2;

  clearScreen();

  do {
    cout << "Escreva o ID do aluno para dar nota:" << endl;
    cout << "ID (ID000, de 000 a 999)\n";
    cin >> id;

    if(id.size()!=5){ incorrect=true; msgerror="ID";}
    else
    {
      pos_student1=this->searchStudentInPkIndex1(id);
      if(pos_student1>=0) incorrect=false;
      else
      {
        cout << "Estudante não existe! Tente inserir outro nome." << endl;
        pressEnter();
        incorrect=true;
        continue;
      }
    }
    cout << "Escreva o número da disciplina (1,2):" << endl;
    cin >> disc;

    if(disc!=1 && disc!=2){ incorrect=true; msgerror="disciplina";}

    cout << "Escreva a nota (0,0 de 0 a 9 e 10):" << endl;
    cin >> grad;
    gradi1 = grad[0] - '0';
    if(grad.size()==3)
    {
      gradi2 = grad[2] - '0';
      if(gradi2<0 || gradi2>10) incorrect=true; msgerror="nota";
    }
    if(gradi1<0 || gradi1>10 || grad.size()>3 ||
      grad.size()==1){ incorrect=true; msgerror="nota";}

    if(incorrect)
    {
      cout << "Erro nos dados inseridos de " << msgerror << "." << endl;
      cout << "Tente inserir novamente." << endl;
      pressEnter();
    }
  } while(incorrect);

  if(disc==1) pos_student2=this->searchStudentInPkIndex2(id);
  else pos_student3=this->searchStudentInPkIndex3(id);

  if(pos_student2>=0)
  {
    pos_student2=this->indexListPRR2[pos_student2].second;
    if(this->gradStudentDisc(pos_student2, 1, grad))
      cout << "Nota gravada com sucesso." << endl;
  }
  else if(this->gradNewStudentDisc(pos_student1, 1, grad)) cout << "Nota gravada com sucesso." << endl;
  else if(pos_student3>=0)
  {
    pos_student3=this->indexListPRR3[pos_student3].second;
    if(this->gradStudentDisc(pos_student3, 2, grad))
      cout << "Nota gravada com sucesso." << endl;
  }
  else{ this->gradNewStudentDisc(pos_student1, 2, grad); cout << "Nota gravada com sucesso." << endl;}

  cout << "Executando gerador de índices..." << endl;
  system("./gera_index lista1.txt lista2.txt lista3.txt");
  cout << "Índices atualizados!" << endl;
  getchar();
  pressEnter();

  showMenu();
}

bool StudentManagement::gradNewStudentDisc(int pos_student, int index, string grad)
{
  ofstream indexFile;
  ifstream indexStuFile("lista1.txt");
  string info, id, mat, name;

  if(index==1) indexFile.open("lista2.txt", ios::app);
  else indexFile.open("lista3.txt", ios::app);

  pos_student=this->indexListPRR[pos_student].second;

  if(indexFile.is_open() && indexStuFile.is_open())
  {
    indexStuFile.seekg(pos_student);
    indexStuFile >> id >> mat >> name;
    info=id+"|"+mat+"|"+name+"|"+grad;

    indexFile << info << endl;
  }
  else return false;

  indexFile.close();
  indexStuFile.close();

  return true;
}

//TODO check duplicate grades from one student
bool StudentManagement::gradStudentDisc(int pos_student, int index,
                                        string grad)
{
  ofstream outIndexFile("out.txt");
  ifstream indexFile;
  vector<string> lines;
  string line, id, mat, name, info, filename;
  size_t s;

  if(index==1) filename = "lista2.txt";
  else filename = "lista3.txt";

  indexFile.open(filename);

  if(indexFile.is_open())
  {
    indexFile.seekg(pos_student);

    getline(indexFile,id,'|');
    getline(indexFile,mat,'|');
    getline(indexFile,name,'|');
    info=id+"|"+mat+"|"+name+"|"+grad;

    indexFile.seekg(0, ios::beg);
    s=indexFile.tellg();
    if(s==pos_student){ outIndexFile << info << endl; getline(indexFile,line);}
    while(getline(indexFile, line))
    {
      if(s==pos_student) outIndexFile << info << endl;
      else outIndexFile << line << endl;
      s=indexFile.tellg();
    }
  }
  else return false;

  indexFile.close();
  outIndexFile.close();

  remove(filename.c_str());
  rename("out.txt", filename.c_str());

  return true;
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
