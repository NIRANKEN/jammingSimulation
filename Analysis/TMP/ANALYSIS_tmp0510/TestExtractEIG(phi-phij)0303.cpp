#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "nr.h"

using namespace std;


struct ensave {
  double eig;
  string STR;
};
bool Lesseig(const ensave &rE, const ensave &lE) {
  return rE.eig < lE.eig;
}

//sampleのデータを集めるだけ。
int main()
{
  int rangenum=0,dimension,Particlenum;
  double rangemin,rangemax;//,EPS=numeric_limits<double>::epsilon();
  string dt,disperse,Pnum,dim;
  string wt,wt2,wt3,rdtmp="EIG",rd;
  stringstream ss,ss2,ssdir;
  
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
  
  dimension=atoi(dim.c_str());
  Particlenum=atoi(Pnum.c_str());

  while(rangenum<1 || rangenum>8) {
    cout<<"どこのレンジのPHI-PHIJにします?(1~6で選んでね.)"<<endl;
    cout<<"(1)... [1.0e-2, 1.0e-1)\n";
    cout<<"(2)... [1.0e-3, 1.0e-2)\n";
    cout<<"(3)... [1.0e-4, 1.0e-3)\n";
    cout<<"(4)... [1.0e-5, 1.0e-4)\n";
    cout<<"(5)... [1.0e-6, 1.0e-5)\n";
    cout<<"(6)... [1.0e-7, 1.0e-6)\n";
    
    cout<<"(7)... [5.0e-2, 1.0e-1)\n";
    cout<<"(8)... [1.0e-2, 5.0e-2)\n";
    cout<<"(9)... None\n"<<endl;
    cout<<"-> ";
    cin>>rangenum;
  }

  if(rangenum>=1 && rangenum<=6) {
    rangemin=0.1;//初期値.最小1回,最大6回は反復するはず.
    for(int i=0;i<rangenum;i++) {
      rangemax=rangemin;
      rangemin*=0.1;
    }
    cout<<"(*u*)"<<rangemin<<" "<<rangemax<<endl;
  }
  else if(rangenum==7){
    rangemax=0.1;
    rangemin=0.05;
  }
  else if(rangenum==8){
    rangemax=0.05;
    rangemin=0.01;
  }
  else {
  }
  

  ssdir<<"./"<<rangenum<<"/";
  rd=rdtmp+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt=ssdir.str()+rdtmp+"EnsAve_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt3=ssdir.str()+"Unsorted_"+rdtmp+"EnsAve_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  
  ofstream ofs(wt3.data()),ofs2;
  cout<<"\n\nsammpling programを開始します..."<<endl;
  //テーブル作成部分
  ifstream ifs;
  ifs.open(rd.data());
  string str;
    
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
    double a=0,b=0,c=0,d=0,e=0,f=0,div,ddiv,bmin,bmax; //dummy variable
    string str_a="";
    int cntflg=0,N=dimension*Particlenum,NN,sampleN=0,S,cum,C=0;
      
    while(getline(ifs,str)) {
      sscanf(str.data(),"%lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f);

      //サンプルナンバー(S)が変わったらフラグ初期化.
      if(cntflg==N && a!=S) {
	sampleN++;
	cntflg=0;
      }
	
      //対象部分のカウント
      if(b<rangemax && b>=rangemin && cntflg<N) {
	S=a;
	cntflg++;
	if(C==0) {
	  bmin=bmax=b;
	}
	else {
	  if(bmin>b)
	    bmin=b;
	  if(bmax<b)
	    bmax=b;
	}
	C++;
      }
    }
    //テキスト末尾での書き込み.
    if(cntflg==N) {
      sampleN++;
    }
    wt2=ssdir.str()+"Hey_"+rdtmp+"EnsAve_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
    ofs2.open(wt2.data());
    ofs2<<"(PHI-PHIJ)min = "<<bmin<<"(PHI-PHIJ)max = "<<bmax<<endl;
    ofs2<<"サンプル数: "<<sampleN<<endl;
    ofs2.close();
    
    ifs.clear();//clear fail and eof bits
    ifs.seekg(0,ios::beg);// back to the start

    if(sampleN==0) {
      cerr<<"cannot execute sample average for this range...\n"<<endl;
      exit(1);
    }
    else {
      NN=N*sampleN;//こいつら何者??????????????????????????????????????
      div=1.0/sampleN;
      ddiv=1.0/NN;
      C=cum=0;
      cout<<sampleN<<"個のサンプルから採取しています...";
      while(getline(ifs,str)) {
	sscanf(str.data(),"%lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f);
	
	//サンプルナンバー(S)が変わったらフラグ初期化.
	if(cntflg==N && a!=S) {
	  cntflg=0;
	}
	//対象部分のカウント
	if(b<rangemax && b>=rangemin && cntflg<N) {
	  //if(c>EPS)
	  c=fabs(c);
	  ofs<<c<<' '<<sqrt(c)<<' '<<e<<' '<<b<<endl;
	  cntflg++;
	  cum++;
	}
	C++;
      }
      ofs.close();
    }

    ifs.close();
    if(sampleN==0) {
      cerr<<"cannot execute sample average for this range...\n"<<endl;
      exit(1);
    }
    else {
      //wt2="Sorted_"+wt;
      cout<<"ソートしています..."<<endl;
      ifs.open(wt3.data());
      ofs.open(wt.data());
      std::vector<ensave> input;
      string line;
      a=b=c=d=0.0;
      C=0;
      while(getline(ifs,line)) {
	sscanf(line.data(),"%lf %lf %lf %lf",&a,&b,&c,&d);
	if(!line.empty()) {
	  ensave E={b,line};
	  input.push_back(E);
	  C++;
	}
      }
      std::sort(input.begin(),input.end(),Lesseig);
      for(int i=0;i<C;i++) {
	ofs<<input[i].STR<<endl;
      }
      ofs.close();
      ifs.close();
    }
  }
}
