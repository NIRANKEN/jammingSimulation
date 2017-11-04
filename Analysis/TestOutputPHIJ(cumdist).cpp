#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <limits>
#include "nr.h"
#include <vector>
#include <algorithm>

using namespace std;


//sampleのデータを集めるだけ。
int main()
{
  int dimension,Particlenum;
  string dt,disperse,Pnum,dim;
  string wt,rdtmp="PHIJ",rd,wt2;
  
  stringstream ss,ss2;
  
  cout<<"本プログラムは,"<<endl;
  cout<<"(1)PHIJ0xxxx_\"phi\".txt"<<endl;
  cout<<"の統計平均をテキストにまとめるプログラムです.\n"<<endl;

  // cout<<"which \"date\" do you execute the FIRE program??"<<endl;
  // cout<<"\"date\" (e.g. 0208)-> ";
  cin>>dt;
  // cout<<"monodisperse? or bidisperse? (MONO or BI)"<<endl;
  // cout<<"->";
  cin>>disperse;
  // cout<<"\nHow many particles?? (e.g. 128)"<<endl;
  // cout<<"->";
  cin>>Pnum;
  // cout<<"\nwhich dimension?? (2D or 3D)";
  // cout<<"->";
  cin>>dim;
  rd=rdtmp+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt=rdtmp+"PHIJ_CumDist_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt2=rdtmp+"PHIJ_StatInfo"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  dimension=atoi(dim.c_str());
  Particlenum=atoi(Pnum.c_str());
  
  ofstream ofs(wt.data()),ofs2(wt2.data());
  // cout<<"\n\nsammpling programを開始します..."<<endl;
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
    /*
      int cnt=0;
      while(getline(ifs,str))
      cnt+=1;
      ifs.clear();//clear fail and eof bits
      ifs.seekg(0,ios::beg);// back to the start

      const int C=cnt;
      Vec_DP phi(C),eng(C),vviter(C);
      DP PHIJ=0.0;
    */
    double a=0,b=0,div,EPS=numeric_limits<double>::epsilon(),PHI_mean=0.0,PHI_var=0.0,PHI_sd,PHI_se; //dummy variable
    string str_a="";
    int cum,C=0;
    vector<double> vec;    
      
    while(getline(ifs,str)) {
      sscanf(str.data(),"%lf %lf",&a,&b); //a = sample num, b = PHIJ
      if(b>EPS && b<1) {
	vec.push_back(b);
	C++;
	PHI_mean+=b;
	PHI_var+=b*b;
      }
    }
    sort(vec.begin(),vec.end());

    ifs.clear();//clear fail and eof bits
    ifs.seekg(0,ios::beg);// back to the start

    //サンプルの統計情報(粒子数,平均,分散,標準偏差,標準誤差)
    div=1.0/C;
    cum=0;
    C=0;
    PHI_mean*=div;
    PHI_var*=div;
    PHI_var-=PHI_mean*PHI_mean;
    PHI_sd=sqrt(PHI_var);
    PHI_se=sqrt(PHI_var*div);
    ofs2<<Particlenum<<" "<<PHI_mean<<" "<<PHI_var<<" "<<PHI_sd<<" "<<PHI_se<<endl;
    
    while(getline(ifs,str)) {
      sscanf(str.data(),"%lf %lf",&a,&b);
      if(b>EPS && b<1) {//valid PHI range
	C++;
	//累積分布用の書き込み.
	ofs<<vec[C-1]<<' '<<C*div<<endl;
      }
    }
    ofs.close();
  }
  ifs.close();
}
