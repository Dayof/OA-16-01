#include <inc_system.hpp>

int main( int argc, char *argv[] )
{
  if(argc==4)
  {
    vector<string> file_list_name(argv, argv + argc);
    if(!checkList(file_list_name)) cout << "Some file doesn't exist or can't be opened." << endl;
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
