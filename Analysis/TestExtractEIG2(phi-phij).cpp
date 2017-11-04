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
#include "BIN.h"

using namespace std;

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

  int dimension,ParticleNum;
  double rangemin,rangemax,DPHI_m,rexp_max,rexp_min,binrange,EPS=numeric_limits<double>::epsilon(),meanDPHI=0.0;
  string dt,disperse,Pnum,dim,path;
  string wttmp,wt,wt2,wt3,wt4,wt5,rdtmp,rd;
  stringstream ss,ss2,ssdir;

  int Prt1,Prt2;
  double ratio,factMScaled=1;

  binstat::InputStr(dt,disperse,Pnum,dim);
  // cout<<"\nwhich directory you save data to? (path)";
  // cout<<"->";
  rdtmp=wttmp="EIG";
  cin>>path;
  dimension=atoi(dim.c_str());
  ParticleNum=atoi(Pnum.c_str());
  
  if(argc==3 || argc==6) {
      rexp_max=atof(argv[1]);
      binrange=atof(argv[2]);
      rdtmp="../"+rdtmp;
    if(argc<4) {
      cout<<"execute ExtractEIG-method with NORMAL MODE..."<<endl;
    }
    else {
      cout<<"execute ExtractEIG-method with MScaled MODE..."<<endl;
      Prt1=atoi(argv[3]);
      Prt2=atoi(argv[4]);
      ratio=atof(argv[5]);
      factMScaled=pow((Prt1+Prt2*pow(ratio,dimension))/(Prt1+Prt2),2.0/dimension);
      if((Prt1+Prt2)%2 ==1 ) {
	cerr<<"Pratio1:("<<Prt1<<") + Pratio2:("<<Prt2<<") must be even.";
	exit(1);
      }
    }
  }
  else {
    cerr<<"引数エラー\n第一引数:DPHIのBINmax(xxx)、pow(10,-xxx)"<<endl;
    cerr<<"第二引数:DPHIのBIN幅(yyy)、pow(10,-(xxx+yyy))"<<endl;
    exit(1);
  }
  
  rexp_min=rexp_max+binrange;
  rangemax=pow(10,-rexp_max);
  rangemin=pow(10,-rexp_min);

  DPHI_m=pow(10,-0.5*(rexp_max+rexp_min));

  ssdir<<"./"<<path<<"/";
  rd=rdtmp+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt=ssdir.str()+wttmp+"EnsAve_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt2=ssdir.str()+"tmpDPHI_"+wttmp+"EnsAve_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt3=ssdir.str()+"Unsorted_"+wttmp+"EnsAve_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt4=ssdir.str()+"DPHI_"+wttmp+"EnsAve_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt5=ssdir.str()+"StatInfo_"+wttmp+"EnsAve_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ofstream ofs(wt3.data()),ofs2(wt2.data());
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
    double eigTableVal[8]={0,0,0,0,0,0,0,0},minDPHI=1.0,maxDPHI=0.0,distancePHIm,distancePHIm_min,tmpDPHI,EigVal; //dummy variable
    int SampleCnt=0,N=dimension*ParticleNum,S,C=0,cntall=0,testcnt=0,countEigInfo=0;
    bool countedSample=false,sampledPHIdistance=false,validEigInfo=false;
    ifstream::pos_type ps_bin,ps_process,ps_tmp=ifs.tellg(),ps_tmptmp=ifs.tellg();
    while(getline(ifs,str)) {
      sscanf(str.data(),"%lf %lf %lf %lf %lf %lf %lf %lf",&eigTableVal[0],&eigTableVal[1],&eigTableVal[2],&eigTableVal[3],&eigTableVal[4],&eigTableVal[5],&eigTableVal[6],&eigTableVal[7]);
      
      if(cntall==0) {
	S=eigTableVal[0];
      }
      //対象部分のカウント
      if(eigTableVal[1]<rangemax && eigTableVal[1]>=rangemin && S==eigTableVal[0] && !countedSample) {
	distancePHIm=fabs(eigTableVal[1]-DPHI_m);
	if(C%N==0){
	  ps_tmptmp=ps_tmp;
	  countEigInfo=0;
	}
	if(eigTableVal[2]<EPS && fabs(eigTableVal[2])>EPS) {
	  // cout<<"invalid EIG is detected!"<<endl;
	}
	else {
	  countEigInfo++;
	}
	C++;
	
	if(C%N==0) {
	  if(countEigInfo==N) {
	    if(sampledPHIdistance==false) {
	      //一発目のサンプルならば即代入.
	      distancePHIm_min=distancePHIm;
	      ps_bin=ps_tmptmp;
	      sampledPHIdistance=true;
	    }
	    else {
	      //二発目以降であれば条件に見合った場合代入.
	      if(distancePHIm_min>distancePHIm) {
		distancePHIm_min=distancePHIm;
		ps_bin=ps_tmptmp;
	      }
	    }
	  }
	}
	if(minDPHI>distancePHIm) {
	  minDPHI=distancePHIm;
	}
	if(maxDPHI<distancePHIm) {
	  maxDPHI=distancePHIm;
	}
      }
      else { //PHIbinから外れた or サンプルナンバーが変わった.
	if(sampledPHIdistance) {
	  //Initialize
	  sampledPHIdistance=false;
	  if(S!=eigTableVal[0]) {
	    countedSample=false;
	  }
	  else {
	    countedSample=true;
	  }
	  C=0;
	  testcnt++;
	  // cout<<"sample number:"<<eigTableVal[0]<<", Sampled count:"<<testcnt<<endl;
	  //Back to the place to sample PHI
	  ps_process=ps_tmp;
	  ifs.seekg(ps_bin);
	  for(int i=0;i<N;i++) {
	    getline(ifs,str);
	    sscanf(str.data(),"%lf %lf %lf %lf %lf %lf %lf %lf",&eigTableVal[0],&eigTableVal[1],&eigTableVal[2],&eigTableVal[3],&eigTableVal[4],&eigTableVal[5],&eigTableVal[6],&eigTableVal[7]);
	    EigVal=factMScaled*fabs(eigTableVal[2]);
	    ofs<<setprecision(10)<<EigVal<<' '<<sqrt(EigVal)<<' '<<eigTableVal[4]<<' '<<eigTableVal[5]<<' '<<eigTableVal[6]<<' '<<eigTableVal[7]<<' '<<eigTableVal[1]<<' '<<DPHI_m<<endl;
	    if(i==0) {
	      tmpDPHI=eigTableVal[1];
	      meanDPHI+=log10(tmpDPHI); // log10 で(PHI-PHIJ)のbin平均
	      ofs2<<eigTableVal[0]<<' '<<tmpDPHI<<' '<<DPHI_m<<' '<<ParticleNum<<endl;
	      
	    }
	    else {
	      if(tmpDPHI!=eigTableVal[1]) {
		cerr<<"your program is poor (because your output is invalid)."<<endl;
		exit(1);
	      }
	    }
	  }// writing method
	  ifs.seekg(ps_process); //書き終えたら戻す.
	  SampleCnt++;
	}
	else {//bin内のサンプルを確保できずにサンプルナンバーが変わった場合.
	  if(S!=eigTableVal[0]) {
	    ifs.seekg(ps_tmp);//Sだけ更新したい.
	    countedSample=false;
	  }
	}
      }
      
      S=eigTableVal[0];
      //// cout<<"sample number: "<<S<<endl;
      cntall++;
      ps_tmp=ifs.tellg();
    }
    ofs.close();
    ofs2.close();
    ifs.close();
    /*
      ifs.clear();//clear fail and eof bits
      ifs.seekg(0,ios::beg);// back to the start
    */

    if(SampleCnt==0) {
      cerr<<"cannot execute sample average for this range...\n"<<endl;
      exit(1);
    }
    else {

      //EIG-Dataのソート
      // cout<<"ソートしています..."<<endl;
      ifs.open(wt3.data());
      ofs.open(wt.data());
      std::vector<ensave> input;
      string line;
      C=0;
      double normalize_f=1.0/SampleCnt;
      meanDPHI*=normalize_f;
      meanDPHI=pow(10,meanDPHI);
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
	ofs<<input[i].STR<<' '<<meanDPHI<<endl;
      }
      ofs.close();
      ifs.close();
      //----

      //DPHI-Dataのソート
      ofs2.open(wt4.data());
      ofs.open(wt5.data());
      ifs.open(wt2.data());
      input=vector<ensave>();
      line="";
      C=0;
      while(getline(ifs,line)) {
	sscanf(line.data(),"%lf %lf %lf %lf",&eigTableVal[0],&eigTableVal[1],&eigTableVal[2],&eigTableVal[3]);
	if(!line.empty()) {
	  ensave E={eigTableVal[1],line};
	  input.push_back(E);
	  C++;
	}
      }
      if(C!=SampleCnt) {
	cerr<<"DPHIで取得したサンプル数の不一致.ERROR!"<<endl;
	cerr<<"SampleCnt: "<<SampleCnt<<", readCnt: "<<C<<endl;
	exit(1);
      }
      ofs<<rangemin<<" "<<DPHI_m<<" "<<rangemax<<" "<<meanDPHI<<" "<<ParticleNum<<" "<<SampleCnt<<endl;
      ofs.close();
      sort(input.begin(),input.end(),Lesseig);
      for(int i=0;i<C;i++) {
	ofs2<<input[i].STR<<' '<<meanDPHI<<' '<<(i+1)*normalize_f<<endl;
      }
      //----
      
    }
  }
}
