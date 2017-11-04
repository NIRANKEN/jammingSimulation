#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


inline void ssClear(stringstream &ss) {
  ss.str("");
  ss.clear(stringstream::goodbit);
  return;
}

int main()
{
  ifstream ifs("testdata.txt");
  const int valnum=9;
  int N,val[valnum];
  string line;
  stringstream ss;
  
  cout<<"何行読み込みますか?"<<endl;
  cin>>N;
  cout<<endl;
  cout<<"ifstreamのポインタ位置: "<<ifs.tellg()<<endl;
  for(int i=0;i<N;i++) {
    getline(ifs,line);
    
    int lN=line.size(),asciiline[lN];
    for(int j=0;j<lN;j++) {
      asciiline[j]=line.at(j);
      cout<<asciiline[j]<<' ';
    }
    cout<<endl;
    
    cout<<"ifstreamのポインタ位置: "<<ifs.tellg()<<endl;
    ssClear(ss);
    ss<<line;
    for(int j=0;j<valnum;j++) {
      ss>>val[j];
      cout<<val[j]<<' ';
    }
    cout<<endl;

  }
    

}

