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
int main(int argc, char **argv)
{

  if(argc!=3) {
    cerr<<"引数エラー\n第一引数:DPHIのBINmax(xxx)、pow(10,-xxx)"<<endl;
    cerr<<"第二引数:DPHIのBIN幅(yyy)、pow(10,-xxx+yyy)"<<endl;
  }
  
  
    
  
  int dimension,Particlenum;
  double rangemin,rangemax,DPHI_m,rexp_max,rexp_min,binrange;//,EPS=numeric_limits<double>::epsilon();
  string dt,disperse,Pnum,dim;
  string wt,wt2,wt3,rdtmp="EIG",rd;
  stringstream ss,ss2,ssdir;

  rexp_max=atof(argv[1]);
  binrange=atof(argv[2]);
  rexp_min=rexp_max+binrange;
  
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

  rangemax=pow(10,-rexp_max);
  rangemin=pow(10,-rexp_min);

  DPHI_m=pow(10,-0.5*(rexp_max+rexp_min));

  ssdir<<"./"<<rexp_min<<"_"<<rexp_max<<"/";
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
    double eigTableVal[8]={0,0,0,0,0,0,0,0},div,ddiv,minDPHI,maxDPHI; //dummy variable
    int cntflg=0,N=dimension*Particlenum,NN,sampleN=0,S,cum,C=0;
    bool countedSample=false;
    ifstream::pos_type ps;
    while(getline(ifs,str)) {
      sscanf(str.data(),"%lf %lf %lf %lf %lf %lf %lf %lf",&eigTableVal[0],&eigTableVal[1],&eigTableVal[2],&eigTableVal[3],&eigTableVal[4],&eigTableVal[5],&eigTableVal[6],&eigTableVal[7]);

      //サンプルナンバー(S)が変わったらフラグ初期化.
      if(cntflg==N && eigTableVal[0]!=S) {
	sampleN++;
	cntflg=0;
      }
	
      //対象部分のカウント
      if(eigTableVal[1]<rangemax && eigTableVal[1]>=rangemin && cntflg<N) {
	S=eigTableVal[0];
	cntflg++;
	if(C==0) {
	  minDPHI=maxDPHI=eigTableVal[1];
	}
	else {
	  if(minDPHI>eigTableVal[1])
	    minDPHI=eigTableVal[1];
	  if(maxDPHI<eigTableVal[1])
	    maxDPHI=eigTableVal[1];
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
    ofs2<<"(PHI-PHIJ)min = "<<minDPHI<<"(PHI-PHIJ)max = "<<maxDPHI<<endl;
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
	sscanf(str.data(),"%lf %lf %lf %lf %lf %lf %lf %lf",&eigTableVal[0],&eigTableVal[1],&eigTableVal[2],&eigTableVal[3],&eigTableVal[4],&eigTableVal[5],&eigTableVal[6],&eigTableVal[7]);
	
	//サンプルナンバー(S)が変わったらフラグ初期化.
	if(cntflg==N && eigTableVal[0]!=S) {
	  cntflg=0;
	}
	//対象部分のカウント
	if(eigTableVal[1]<rangemax && eigTableVal[1]>=rangemin && cntflg<N) {
	  //if(c>EPS)
	  eigTableVal[2]=fabs(eigTableVal[2]);
	  ofs<<eigTableVal[2]<<' '<<sqrt(eigTableVal[2])<<' '<<eigTableVal[4]<<' '<<eigTableVal[5]<<' '<<eigTableVal[6]<<' '<<eigTableVal[7]<<' '<<eigTableVal[1]<<' '<<DPHI_m<<endl;

	    //0.samplenum
	    //1.DPHI
	    //2.EVal
	    //3.Freq
	    //4.IPR
	    //5.IPR_1st(small)
	    //6.IPR_2nd(large)
	    //7.the number of the participating particles (1st component)

	    //    |
	    //    |
	    //    v
	    
  	    //0.EVal
	    //1.Freq
	    //2.IPR
	    //3.IPR_1st(small)
	    //4.IPR_2nd(large)
	    //5.the number of the participating particles (1st component)
	    //6.DPHI
	    //7.DPHI (center point (logscale))
	  
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
      C=0;
      while(getline(ifs,line)) {
	sscanf(line.data(),"%lf %lf %lf %lf %lf %lf %lf %lf",&eigTableVal[0],&eigTableVal[1],&eigTableVal[2],&eigTableVal[3],&eigTableVal[4],&eigTableVal[5],&eigTableVal[6],&eigTableVal[7]);
	if(!line.empty()) {
	  ensave E={eigTableVal[1],line};
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
