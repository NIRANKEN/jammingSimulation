#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <limits>
#include <cmath>

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
  
  int dimension,Particlenum;
  double binrange=0.05;//,EPS=numeric_limits<double>::epsilon();
  string dt,disperse,Pnum,dim;
  string wt,rdtmp="EIGEnsAve_",rd,str;
  stringstream ss;
  ifstream ifs;
  ofstream ofs;

  binstat::InputStr(dt,disperse,Pnum,dim);
  dimension=atoi(dim.c_str());
  Particlenum=atoi(Pnum.c_str());
  
  rd=rdtmp+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ifs.open(rd.data());
  wt=rdtmp+"BR"+argv[1]+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ofs.open(wt.data());
  
  cout<<"\n\nBINでの統計処理を開始します..."<<endl;

  if(ifs.fail()) {
    cerr<<"catnot open your file..."<<endl;
    return 1;
  }
  else {
    int C=0,cumC=0;
    double a=0.0,b=0.0,c=0.0,d=0.0,EPS=numeric_limits<double>::epsilon();
      while(getline(ifs,str)) {
	sscanf(str.data(),"%lf %lf %lf %lf",&a,&b,&c,&d);
	if(fabs(a)>EPS)
	  cumC++;
	C++;
      }
      ifs.clear();//clear fail and eof bits
      ifs.seekg(0,ios::beg);// back to the start
      str="";
      /*
      const int C=cnt;
      Vec_DP phi(C),eng(C),vviter(C);
      DP PHIJ=0.0;
      */
      a=b=c=d=0.0;
      double sumc=0.0,minc,maxc,cum=1.0/cumC,Range_e,Range_s,Range_m,Range_sinit,Range_sln10,Range_mln10; //Rangetmpはbinの始点,Rangeはbinの終点.
      //sumcはIPRのBIN内における総和,cumは1.0/データ数.
      int cnttmp,cnt=0;
      cumC=0;
      
      binrange=atof(argv[1]);
      binstat::InputBINrange(binrange);//引数で入力したbin幅が妥当だったらスルー.
      binstat::initializeBINrange(Range_sinit,Range_s,Range_e,Range_m,Range_sln10,Range_mln10);
      binstat::updateBINrange(Range_s,Range_e,Range_m,Range_sln10,Range_mln10,binrange);
      while(getline(ifs,str)) {
	sscanf(str.data(),"%lf %lf %lf %lf",&a,&b,&c,&d);
	if(fabs(a)>EPS)
	  cumC++;
	if(cumC==1) {
	  binstat::InitializeIPRparameter(c,sumc,minc,maxc,cnttmp);
	}
	//Range_sinitよりも小さい固有値はスルーする.
	if(b>=Range_sinit && !isnan(b)) {
	  //bin内処理
	  if(b>=Range_s && b<Range_e) {
	    //IPRの和とbin内カウント更新.
	    binstat::ModifyIPRparameter(c,sumc,minc,maxc,cnttmp);

	    binstat::innerBINprocess(c,Range_m,sumc,minc,maxc,cnttmp,C,ofs,cnt,cum,cumC);
	  }
	  //bin更新処理
	  else {
	    binstat::updateBINprocess(b,c,Range_s,Range_e,Range_m,Range_sln10,Range_mln10,sumc,minc,maxc,cnttmp,C,binrange,ofs,cnt,cum,cumC);
	  }
	}
	cnt++;//全体カウント
      }//while end
      ofs.close();
  }//else(FILE open) end
  ifs.close();
}//end


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
    while(br<0.0001 || br>0.1) {
      cout<<"bin幅(log10)が不適切なので再度取ります.入力してください.(MAX:0.1, MIN:0.0001)"<<endl;
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
  void innerBINprocess(double c,double M,double &sumc,double &minc,double &maxc,int &tmpC,double allC,ofstream &ofs,int cnt,double cum,int cumcnt) {
    //cout<<"inner"<<endl;
    if(cnt==allC-1) {
      //FILE末端ならば書き込み sqrtに意味がない.
      ofs<<M<<" "<<sqrt(M)<<" "<<sumc/tmpC<<" "<<minc<<" "<<maxc<<" "<<tmpC*cum<<" "<<(cumcnt)*cum<<" "<<tmpC<<endl;
    }
  }

  //bin更新処理メソッド.
  void updateBINprocess(double b,double c,double &S,double &E,double &M,double &Sln10,double &Mln10,double &sumc,double &minc,double &maxc,int &tmpC,double allC,double range,ofstream &ofs,int cnt,double cum,int cumcnt) {
    cout<<"update"<<endl;
    if(cnt<0) {
      cerr<<"your simulation must be periodic...\n(must detect zero frequency modes)"<<endl;
      exit(1);
    }
    else {
      //........BINrangeミスってなければ必ずこのループに入る.
      ofs<<M<<" "<<sqrt(M)<<" "<<sumc/tmpC<<" "<<minc<<" "<<maxc<<" "<<tmpC*cum<<" "<<(cumcnt)*cum<<" "<<tmpC<<endl;
      while(b>=E) {
	//次に書き込みを行うBIN範囲を探索.
	cout<<setprecision(10)<<b<<' '<<E<<endl;
	updateBINrange(S,E,M,Sln10,Mln10,range);
      }
      if(b<S||b>=E) {
	cerr<<"range-error!!"<<endl;
	cerr<<setprecision(15)<<"omega is "<<b<<", range is"<<S<<"<= xx <"<<E<<endl;
	exit(1);
      }
      binstat::InitializeIPRparameter(c,sumc,minc,maxc,tmpC);
      //次の処理に対して,1個分のデータ入った状態で初期化.      
      if(cnt==allC-1) {
	//FILE末端ならば書き込み, 要変更.
	ofs<<M<<" "<<sqrt(M)<<" "<<sumc/tmpC<<" "<<minc<<" "<<maxc<<" "<<tmpC*cum<<" "<<(cumcnt)*cum<<" "<<tmpC<<endl;
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

  void InitializeIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC) {
    tmpC=1;
    minc=maxc=sumc=c;
  }
  
  void ModifyIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC) {
    sumc+=c;
    tmpC+=1;
    if(minc>c)
      minc=c;
    if(maxc<c)
      maxc=c;
  }
  
}//namespace binstat end
