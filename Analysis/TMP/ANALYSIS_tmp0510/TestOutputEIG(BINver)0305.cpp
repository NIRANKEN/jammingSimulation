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
  
  //int dimension,Particlenum;
  double binrange=atof(argv[1]);//,EPS=numeric_limits<double>::epsilon();
  string dt,disperse,Pnum,dim;
  string wt,rdtmp="EIGEnsAve_",rd,str;
  //stringstream ss;
  ifstream ifs;
  ofstream ofs;
  int N;

  binstat::InputStr(dt,disperse,Pnum,dim);
  //dimension=atoi(dim.c_str());
  //Particlenum=atoi(Pnum.c_str());
  
  rd=rdtmp+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ifs.open(rd.data());
  wt=rdtmp+"BR"+argv[1]+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ofs.open(wt.data());
  N=atoi(Pnum.data());
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
      double sumc=0.0,minc,maxc,sgmc,cum=1.0/cumC,Range_e,Range_s,Range_m,Range_sinit,Range_sln10,Range_mln10; //Rangetmpはbinの始点,Rangeはbinの終点.
      //sumcはIPRのBIN内における総和,cumは1.0/データ数.
      int cnttmp,cnt=0,zeroeig=C-cumC;
      cumC=0;
      
      binstat::InputBINrange(binrange);//引数で入力したbin幅が妥当だったらスルー.
      binstat::initializeBINrange(Range_sinit,Range_s,Range_e,Range_m,Range_sln10,Range_mln10);
      binstat::updateBINrange(Range_s,Range_e,Range_m,Range_sln10,Range_mln10,binrange);
      while(getline(ifs,str)) {
	sscanf(str.data(),"%lf %lf %lf %lf",&a,&b,&c,&d);
	if(fabs(a)>EPS)
	  cumC++;
	else {
	  //ゼロ固有値process
	  if(cnt==0)
	    binstat::InitializeIPRparameter(c,sumc,minc,maxc,cnttmp,sgmc);
	  else
	    binstat::innerBINprocess(c,Range_s,Range_e,Range_m,sumc,minc,maxc,cnttmp,sgmc,C,ofs,cnt,cum,cumC,N);
	}
	
	if(cumC>=1) {
	  if(cumC==1) {
	    //Write eig by zeroeig methods.
	    binstat::ZeroEigenValprocess(Range_s,Range_e,Range_m,zeroeig,C,ofs,N);
	    cout<<zeroeig<<" "<<cnttmp<<endl;
	    while(b>=Range_e) {
	      binstat::updateBINrange(Range_s,Range_e,Range_m,Range_sln10,Range_mln10,binrange);
	    }
	    binstat::InitializeIPRparameter(c,sumc,minc,maxc,cnttmp,sgmc);
	  }
	  else {
	    //Write eig by nonzeroeig methods
	    if(b>=Range_sinit && !isnan(b)) {
	      //取り扱う固有振動数について処理
	      if(b>=Range_s && b<Range_e) {
		//bin内処理
		//IPRの和とbin内カウント更新.
		binstat::innerBINprocess(c,Range_s,Range_e,Range_m,sumc,minc,maxc,cnttmp,sgmc,C,ofs,cnt,cum,cumC,N);
	      }
	      else {
		//bin更新処理
		binstat::updateBINprocess(b,c,Range_s,Range_e,Range_m,Range_sln10,Range_mln10,sumc,minc,maxc,cnttmp,sgmc,C,binrange,ofs,cnt,cum,cumC,N);
	      }
	    }
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

  void ZeroEigenValprocess(double S,double E,double M,int zeroeig,double allC,ofstream &ofs,int N)
{
  double deltaomega_inv=1.0/(E-S),allC_inv=1.0/allC;
  ofs<<M<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<allC_inv*zeroeig*deltaomega_inv<<" "<<0<<" "<<zeroeig<<" "<<N<<endl;
  //0で埋めているところをどうするかは後で考える.
}
  
  //bin内処理メソッド.
  void innerBINprocess(double c,double S,double E,double M,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc,double allC,ofstream &ofs,int cnt,double cum,int cumcnt,int N) {
    binstat::ModifyIPRparameter(c,sumc,minc,maxc,tmpC,sgmc);
    if(cnt==allC-1) {
      double meanc=sumc/tmpC,meanc2=sgmc/tmpC;
      double deltaomega_inv=1.0/(E-S),allC_inv=1.0/allC;
      //FILE末端ならば書き込み sqrtに意味がない.
      ofs<<M<<" "<<meanc<<" "<<minc<<" "<<maxc<<" "<<sqrt((meanc2-meanc*meanc))<<" "<<tmpC*cum*deltaomega_inv<<" "<<allC_inv*tmpC*deltaomega_inv<<" "<<(cumcnt)*cum<<" "<<tmpC<<" "<<N<<endl;
      //bin代表点<<IPR平均値<<IPRmin値<<IPRmax値<<標準偏差<<ゼロ固有値なし分布<<ゼロ固有値あり分布<<ゼロ固有値なし累積分布<<binの中に入った固有振動数の数
    }
  }

  //bin更新処理メソッド.
  void updateBINprocess(double b,double c,double &S,double &E,double &M,double &Sln10,double &Mln10,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc,double allC,double range,ofstream &ofs,int cnt,double cum,int cumcnt,int N) {
    //cout<<"update"<<endl;
    double meanc=sumc/tmpC,meanc2=sgmc/tmpC;
    double deltaomega_inv=1.0/(E-S),allC_inv=1.0/allC;
    
    if(cnt<0) {
      cerr<<"your simulation must be periodic...\n(must detect zero frequency modes)"<<endl;
      exit(1);
    }
    else {
      //........BINrangeミスってなければ必ずこのループに入る.
      ofs<<M<<" "<<meanc<<" "<<minc<<" "<<maxc<<" "<<sqrt((meanc2-meanc*meanc))<<" "<<tmpC*cum*deltaomega_inv<<" "<<allC_inv*tmpC*deltaomega_inv<<" "<<(cumcnt)*cum<<" "<<tmpC<<" "<<N<<endl;
      while(b>=E) {
	//次に書き込みを行うBIN範囲を探索.
	//cout<<setprecision(10)<<b<<' '<<E<<endl;
	updateBINrange(S,E,M,Sln10,Mln10,range);
      }
      if(b<S||b>=E) {
	cerr<<"range-error!!"<<endl;
	cerr<<setprecision(15)<<"omega is "<<b<<", range is"<<S<<"<= xx <"<<E<<endl;
	exit(1);
      }
      binstat::InitializeIPRparameter(c,sumc,minc,maxc,tmpC,sgmc);
      //次の処理に対して,1個分のデータ入った状態で初期化.      
      if(cnt==allC-1) {
	//FILE末端ならば書き込み, 要変更.
	ofs<<M<<" "<<meanc<<" "<<minc<<" "<<maxc<<" "<<sqrt((meanc2-meanc*meanc))<<" "<<tmpC*cum*deltaomega_inv<<" "<<allC_inv*tmpC*deltaomega_inv<<" "<<(cumcnt)*cum<<" "<<tmpC<<" "<<N<<endl;
      }
      else if(cnt>=allC){
	//例外処理.
	cerr<<"your program is so poor!!!"<<endl;
	exit(1);
      }
    }
  }//update end

  void initializeBINrange(double &Sinit,double &S,double &E,double &M,double &Sln10,double &Mln10) {
    E=1.0e-8;//1.0e-6->1.0e-8
    Mln10=Sln10=-8;//-6->-8
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

  void InitializeIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc) {
    tmpC=1;
    minc=maxc=sumc=c;
    sgmc=c*c;
  }
  
  void ModifyIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc) {
    sumc+=c;
    tmpC+=1;
    if(minc>c)
      minc=c;
    if(maxc<c)
      maxc=c;
    sgmc+=c*c;
  }

  void writeEIGinfo_EOF();
  
}//namespace binstat end
