/* Trabalho 2 de OA 2016/01
Desenvolvedora:
1. Dayanne Fernandes da Cunha - 13/0107191
*/

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

  void printReport(vector<vector<vector<string> > >);

  bool searchStudentInSkIndex(string, vector<string>&);

  void printGradSearch(vector<string>);

  void loadPkIndex(string, int);
  void loadSkIndex(string, int);
  void attPkIndex();
private:
  vector<pair<string,int> > indexList, indexList2, indexList3;
  vector<pair<string, vector<string> > > indexSkList, indexSkList2, indexSkList3;
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

    for(int i=1; i<=3; ++i)
    {
      students.loadPkIndex("index_lista"+to_string(i)+".txt", i);
      students.loadSkIndex("sec_lista"+to_string(i)+".txt", i);
    }

    clearScreen();
    cout << "Sistema de Notas UnB v0.1 beta" << endl;
    cout << "1. Inserir nova(o) aluna(o) na UnB\n"
            "2. Jubilar um aluna(o) da UnB\n"
            "3. Dar nota ao aluna(o) numa disciplina\n"
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

void StudentManagement::loadSkIndex(string filename, int index)
{
  ifstream skIndex;
  string name, nrr, line, word_aux;
  vector<string> nrrList;
  vector<string> words;

  skIndex.open(filename);

  if(skIndex.is_open())
  {
    while(!skIndex.eof())
    {
      nrrList.clear();
      words.clear();

      getline(skIndex, line);
      for(int i=0; i<line.size();++i)
      {
        if(line[i]==' ')
        {
          words.push_back(word_aux);
          word_aux.clear();
        }
        else word_aux+=line[i];
      }

      if(words[1][1]!='D')
      {
        name=words[0] + ' ' + words[1];
        for(int j=2; j<words.size(); ++j) nrrList.push_back(words[j]);
      }
      else
      {
        name=words[0];
        for(int j=1; j<words.size(); ++j) nrrList.push_back(words[j]);
      }

      pair<string, vector<string> > p(name,nrrList);
      if(index==1) this->indexSkList.push_back(p);
      else if(index==2) this->indexSkList2.push_back(p);
      else this->indexSkList3.push_back(p);
    }
  }

  skIndex.close();
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
    cout << "Escreva as seguintes informações da(o) estudante:" << endl;
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
    cout << "Escreva o ID da(o) aluna(o) a ser jubilada(o):" << endl;
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

  cout << "Deseja jubilar o aluna(o) de ID " << id << " ? (y/n)" << endl;
  cin >> ans;

  if(ans=="y")
  {
    if(pos_student1>=0) this->deleteStudentPkIndex(pos_student1, 1);
    if(pos_student2>=0) this->deleteStudentPkIndex(pos_student2, 2);
    if(pos_student3>=0) this->deleteStudentPkIndex(pos_student3, 3);
    cout << "Aluna(o) deletada(o) com sucesso." << endl;
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
      cout << "Estudantes deletada(o)s dos benchmarks com sucesso!" << endl;
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

bool StudentManagement::searchStudentInSkIndex(string name,
  vector<string>& nrrList)
{
  vector<pair<string, vector<string> > >::iterator it;
  for(it=this->indexSkList.begin(); it!=this->indexSkList.end();++it)
    if((*it).first==name) break;

  if(it==this->indexSkList.end()) return false;
  else
  {
    nrrList=(*it).second;
    return true;
  }
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
    cout << "Escreva o ID da(o) aluna(o) para dar nota:" << endl;
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

  if(disc==1)
  {
    pos_student2=this->searchStudentInPkIndex2(id);
    if(pos_student2>=0)
    {
      pos_student2=this->indexListPRR2[pos_student2].second;
      if(this->gradStudentDisc(pos_student2, 1, grad))
        cout << "Nota gravada com sucesso." << endl;
    }
    else
    {
      this->gradNewStudentDisc(pos_student1, 1, grad);
      cout << "Nota gravada com sucesso." << endl;
    }
  }
  else
  {
    pos_student3=this->searchStudentInPkIndex3(id);
    if(pos_student3>=0)
    {
      pos_student3=this->indexListPRR3[pos_student3].second;
      if(this->gradStudentDisc(pos_student3, 2, grad))
        cout << "Nota gravada com sucesso." << endl;
    }
    else
    {
      this->gradNewStudentDisc(pos_student1, 2, grad);
      cout << "Nota gravada com sucesso." << endl;
    }
  }

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

// If a student id is missing of a list file then
// the second vector will have less element
// TODO students that exist in list2 or list3 but not in list1
// TODO students with duplicate grad in list2 or list3
// infogeral[infostu[infolist1, infolist2, infolist3]]
void StudentManagement::report()
{
  string id1, id2, id3, mat, nome, op, curso, turma, grad1, grad2;
  vector<string> infoList1, infoList2, infoList3;
  vector<vector<vector<string> > > infoGeral;
  ifstream indexInfoGrad1File("lista2.txt");
  ifstream indexInfoGrad2File("lista3.txt");
  ifstream indexInfoFile("lista1.txt");
  vector<vector<string> > infoStu;
  bool found1=false, found2=false;


  if(indexInfoFile.is_open() && indexInfoGrad1File.is_open() &&
    indexInfoGrad2File.is_open())
  {
    for(int i=0; i<this->indexListPRR.size();++i)
    {
      infoList1.clear();
      infoList2.clear();
      infoList3.clear();
      infoStu.clear();

      indexInfoFile.seekg(this->indexListPRR[i].second);

      indexInfoFile >> id1 >> mat >> nome >> op;

      // if op is a continue of the name
      if(op[0]>='A')
      {
        nome+= ' ' + op;
        indexInfoFile >> op >> curso >> turma;
      }
      else indexInfoFile >> curso >> turma;

      infoList1.push_back(id1);
      infoList1.push_back(mat);
      infoList1.push_back(nome);
      infoList1.push_back(op);
      infoList1.push_back(curso);
      infoList1.push_back(turma);

      infoStu.push_back(infoList1);

      auto compId = [id1](const pair<string, int>& element){
        return element.first == id1; };

      auto result = find_if(this->indexListPRR2.begin(),
        this->indexListPRR2.end(), compId);

      // id found in list1 exist in list2
      if(result!=this->indexListPRR2.end())
      {
        indexInfoGrad1File.seekg((*result).second);

        getline(indexInfoGrad1File,id2,'|');
        getline(indexInfoGrad1File,mat,'|');
        getline(indexInfoGrad1File,nome,'|');
        getline(indexInfoGrad1File,grad1,'\n');

        infoList2.push_back(id2);
        infoList2.push_back(mat);
        infoList2.push_back(nome);
        infoList2.push_back(grad1);

        infoStu.push_back(infoList2);
      }
      else
      {
        infoList2.push_back(id1);
        infoList2.push_back(mat);
        infoList2.push_back(nome);
        infoList2.push_back("SR");

        infoStu.push_back(infoList2);
      }

      auto result2 = find_if(this->indexListPRR3.begin(),
        this->indexListPRR3.end(), compId);

      // id found in list1 exist in list3
      if(result2!=this->indexListPRR3.end())
      {
        indexInfoGrad2File.seekg((*result2).second);

        getline(indexInfoGrad2File,id3,'|');
        getline(indexInfoGrad2File,mat,'|');
        getline(indexInfoGrad2File,nome,'|');
        getline(indexInfoGrad2File,grad2,'\n');

        infoList3.push_back(id3);
        infoList3.push_back(mat);
        infoList3.push_back(nome);
        infoList3.push_back(grad2);

        infoStu.push_back(infoList3);
      }
      else
      {
        infoList3.push_back(id1);
        infoList3.push_back(mat);
        infoList3.push_back(nome);
        infoList3.push_back("SR");

        infoStu.push_back(infoList3);
      }

      infoGeral.push_back(infoStu);
    }
  }

  indexInfoFile.close();
  indexInfoGrad1File.close();
  indexInfoGrad2File.close();

  this->printReport(infoGeral);
}

// 1 vector. list of all students
// 2 vector. list of the 3 infos from a student
// 3 vector. list of attributes from a list info of a student
void StudentManagement::printReport(vector<vector<vector<string> > > info)
{
  for(int i=0; i<info.size();++i)
  {
    cout << "<" << info[i][0][1] << " " << info[i][0][2] << " "
    << info[i][0][3] << " " << info[i][0][4] << " " << info[i][0][5]
    << ">" << endl;
    cout << "Computação Quântica Avançada III:" << " " << info[i][1][3] << endl;
    cout << "Modelagem Aeroespacial Alienígena II:" << " " << info[i][2][3] << endl;
    pressEnter();
  }
}

void StudentManagement::search()
{
  string nome, msgerror;
  bool incorrect=false;
  vector<string> nrrList;

  clearScreen();

  do {
    cout << "Escreva o nome da(o) aluna(o) (até 23 caracteres):" << endl;
    cin >> nome;

    if(nome.size()>23){ incorrect=true; msgerror="nome";}
    else
    {
      if(this->searchStudentInSkIndex(nome, nrrList))
        this->printGradSearch(nrrList);
      else
      {
        cout << "Estudante não existe! Tente inserir outro nome." << endl;
        pressEnter();
        incorrect=true;
      }
    }
  } while(incorrect);
}

void StudentManagement::printGradSearch(vector<string> nrrList)
{
  vector<vector<vector<string> > > infoGeral;
  vector<vector<string> > infoStu;
  vector<string> infoList2, infoList3;
  string id, id2, id3, mat, nome, op, curso, turma, grad1, grad2;
  ifstream indexInfoGrad1File("lista2.txt");
  ifstream indexInfoGrad2File("lista3.txt");
  vector<pair<string,int> >::iterator it;
  vector<int> infoList;

  if(indexInfoGrad1File.is_open() && indexInfoGrad2File.is_open())
  {

    for(int m=0; m<nrrList.size(); ++m)
    {
      infoList.clear();
      infoList2.clear();
      infoList3.clear();
      infoStu.clear();

      id = nrrList[m];

      for(it=this->indexListPRR2.begin(); it!=this->indexListPRR2.end();++it)
        if((*it).first==id) infoList.push_back((*it).second);

      // name found in list1 exist in list2
      if(!infoList.empty())
      {
        for(int t=0; t<infoList.size(); ++t)
        {
          indexInfoGrad1File.seekg(infoList[t]);

          getline(indexInfoGrad1File,id2,'|');
          getline(indexInfoGrad1File,mat,'|');
          getline(indexInfoGrad1File,nome,'|');
          getline(indexInfoGrad1File,grad1,'\n');

          infoList2.push_back(id2);
          infoList2.push_back(mat);
          infoList2.push_back(nome);
          infoList2.push_back(grad1);

          getchar();

          infoStu.push_back(infoList2);
        }
      }
      else
      {
        infoList2.push_back(id);
        infoList2.push_back(mat);
        infoList2.push_back(nome);
        infoList2.push_back("SR");

        infoStu.push_back(infoList2);
      }

      infoList.clear();

      for(it=this->indexListPRR3.begin(); it!=this->indexListPRR3.end();++it)
        if((*it).first==id) infoList.push_back((*it).second);

      // id found in list1 exist in list3
      if(!infoList.empty())
      {
        for(int t=0; t<infoList.size(); ++t)
        {
          indexInfoGrad2File.seekg(infoList[t]);

          getline(indexInfoGrad2File,id3,'|');
          getline(indexInfoGrad2File,mat,'|');
          getline(indexInfoGrad2File,nome,'|');
          getline(indexInfoGrad2File,grad2,'\n');

          infoList3.push_back(id3);
          infoList3.push_back(mat);
          infoList3.push_back(nome);
          infoList3.push_back(grad2);

          infoStu.push_back(infoList3);
        }
      }
      else
      {
        infoList3.push_back(id);
        infoList3.push_back(mat);
        infoList3.push_back(nome);
        infoList3.push_back("SR");

        infoStu.push_back(infoList3);
      }

      infoGeral.push_back(infoStu);
    }
  }

  indexInfoGrad1File.close();
  indexInfoGrad2File.close();

  for(int i=0; i<infoGeral.size();++i)
  {
    cout << "Id: " << nrrList[i] << endl;
    cout << "Computação Quântica Avançada III:" << " "
    << infoGeral[i][0][3] << endl;
    cout << "Modelagem Aeroespacial Alienígena II:" << " "
    << infoGeral[i][1][3] << endl;
    pressEnter();
  }
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
