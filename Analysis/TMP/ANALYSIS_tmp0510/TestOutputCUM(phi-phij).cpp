#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include "nr.h"
#include "BIN.h"

using namespace std;


//sampleのデータを集めるだけ。
int main(int argc, char* argv[])
{
  if(argc!=2)
    {
      cout<<"引数が"<<argc<<"個宣言されています.\n";
      cout<<"-----\n引数1...bin幅(log10)\n----------\nになります.(default: 0.05)\n";
      exit(1);
    }
  int rangenum=0,dimension,Particlenum;
  double rangemin,rangemax,binrange=atof(argv[1]);;
  string dt,disperse,Pnum,dim;
  string wt,wt2,rdtmp="EIG",rd;
  stringstream ss,ss2;
  
  cout<<"本プログラムは,"<<endl;
  cout<<"(2)EigCum0xxxx_\"phi\".txt"<<endl;
  cout<<"の統計平均をテキストにまとめるプログラムです.\n"<<endl;

  cout<<"which \"date\" do you execute the FIRE program??"<<endl;
  cout<<"\"date\" (e.g. 0208)-> ";
  cin>>dt;
  cout<<"monodisperse? or bidisperse? (MONO or BI)"<<endl;
  cout<<"->";
  cin>>disperse;
  cout<<"\nHow many particles?? (e.g. 128)"<<endl;
  cout<<"->";
  cin>>Pnum;
  cout<<"\nwhich dimension?? (2D or 3D)";
  cout<<"->";
  cin>>dim;
  rd=rdtmp+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt=rdtmp+"SamplePHI-PHIJ_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt2=rdtmp+"CumdistOfPHI-PHIJ_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  
  dimension=atoi(dim.c_str());
  Particlenum=atoi(Pnum.c_str());

  binstat::InputBINrange(binrange);
  
  ofstream ofs(wt.data());
  cout<<"\n\nsammpling programを開始します..."<<endl;
  //テーブル作成部分
    
  ifstream ifs;
  ifs.open(rd.data());
  string str;
    
  //ファイル開けなかったら次のサンプルへ.
  if(ifs.fail()) {
    cerr<<"catnot open your file..."<<endl;
    return 1;
  }
  else {
    double a=0,b=0,c=0,d=0,e=0,f=0,div,ddiv,bmin,bmax,btmp; //dummy variable
    string str_a="";
    int cntflg=0,N=dimension*Particlenum,NN,sampleN=0,S,cum,C=0;


    while(getline(ifs,str)) {
	sscanf(str.data(),"%lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f);
	if(C==0) {
	  btmp=b;
	  sampleN++;
	}
	else {
	  if(btmp!=b) {
	    btmp=b;
	    ofs<<b<<endl;
	    sampleN++;
	  }
	}
	C++;
      }
    ofs.close();
    ifs.close();
      if(sampleN==0) {
      cerr<<"cannot execute sample average for this range...\n"<<endl;
      exit(1);
    }
      else {
	ifs.open(wt.data());
	ofs.open(wt2.data());
	std::vector<double> x(std::istream_iterator<double>(ifs), {});
	std::sort(x.begin(),x.end());
	div=1.0/sampleN;
	C=1;
	for(const auto& elem: x) {
	  ofs<<elem<<" "<<C*div<<endl;
	  C++;
	    }
      }
  }
}


namespace binstat {
  //テキストR&W用パラメータ代入メソッド.
  void InputStr(string &a,string &b, string &c, string &d) {
    cout<<"本プログラムは,"<<endl;
    cout<<"(2)EigCum0xxxx_\"phi\".txt"<<endl;
    cout<<"の統計平均をテキストにまとめるプログラムです.\n"<<endl;
    cout<<"which \"date\" do you execute the FIRE program??"<<endl;
    cout<<"\"date\" (e.g. 0208)-> ";
    cin>>a;
    cout<<"monodisperse? or bidisperse? (MONO or BI)"<<endl;
    cout<<"->";
    cin>>b;
    cout<<"\nHow many particles?? (e.g. 128)"<<endl;
    cout<<"->";
    cin>>c;
    cout<<"\nwhich dimension?? (2D or 3D)";
    cout<<"->";
    cin>>d;
    return;
  }

  //BINrange設定用メソッド.
  void InputBINrange(double &br) {
    int cnt=0;
    while(br<=0.1 || br>=1.0) {
      cout<<"bin幅(log10)が不適切なので再度取ります.入力してください.(MAX:1.0, MIN:0.1)"<<endl;
      cout<<"-> ";
      cin>>br;
      cnt+=1;
      if(cnt>20) {
	cerr<<"Invalid binrange for your statistics"<<endl;
	exit(1);
      }
    }    
    return;
  }
  
//bin内処理メソッド.
  void innerBINprocess(double M,double sumc,double minc,double maxc,int tmpC,double allC,ofstream &ofs,int cnt,double cum) {
    //cout<<"inner"<<endl;
    double divc=1.0/tmpC;
    if(cnt==allC-1) {
      //FILE末端ならば書き込み
      ofs<<M<<" "<<sqrt(M)<<" "<<divc*sumc<<" "<<minc<<" "<<maxc<<" "<<cum*tmpC<<" "<<cum*(cnt+1)<<endl;
    }
  }

  //bin更新処理メソッド.
  void updateBINprocess(double b,double c,double &S,double &E,double &M,double &Sln10,double &Mln10,double sumc,double minc,double maxc,int tmpC,double allC,double range,ofstream &ofs,int cnt,double cum) {
    cout<<"update"<<endl;
    double divc=1.0/tmpC;
    if(cnt==0) {
      cerr<<"your simulation must be periodic...\n(must detect zero frequency modes)"<<endl;
      exit(1);
    }
    else {
      //........BINrangeミスってなければ必ずこのループに入る.
      ofs<<M<<" "<<sqrt(M)<<" "<<divc*sumc<<" "<<minc<<" "<<maxc<<" "<<cum*tmpC<<" "<<cum*(cnt+1)<<endl;
      while(b>=E) {
	//次に書き込みを行うBIN範囲を探索.
	updateBINrange(S,E,M,Sln10,Mln10,range);
      }
      if(cnt==allC-1) {
	//FILE末端ならば書き込み
	ofs<<M<<" "<<sqrt(M)<<" "<<divc*sumc<<" "<<minc<<" "<<maxc<<" "<<cum*tmpC<<" "<<cum*(cnt+1)<<endl;
      }
      else if(cnt>=allC){
	//例外処理.
	cerr<<"your program is so poor!!!"<<endl;
	exit(1);
      }
    }
  }//update end

  void initializeBINrange(double &Sinit,double &S,double &E,double &M,double &Sln10,double &Mln10) {
    E=1.0e-6;
    Mln10=Sln10=-6;
    Sinit=S=M=E;
    return;
  }

  void updateBINrange(double &S,double &E,double &M,double &Sln10,double &Mln10,double range) {
    //cout<<S<<" "<<M<<" "<<E<<endl;
    S=E;
    Sln10+=range;
    E=pow(10,Sln10);
    Mln10=Sln10+0.5*range;
    M=pow(10,Mln10);
    return;
  }
  
}//namespace binstat end
