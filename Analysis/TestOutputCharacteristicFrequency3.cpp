#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <limits>
#include <cmath>
#include <vector>
#include "BIN.h"
#include "l_approx.h"

using namespace std;

int main(int argc,char** argv)
{
  if(argc!=2) {
    cerr<<"生DOS=> \"0\", 平滑化DOS=> \"1\"を引数に入力して下さい."<<endl;
    exit(1);
  }
  string rdtmp,rd_iFtmp;
  switch(atoi(argv[1])) {
  case 0: rdtmp="EIGEnsAve_"; rd_iFtmp="InvariantFreq_mean_"; break;
  case 1: rdtmp="SM_EIGEnsAve_"; rd_iFtmp="SM_InvariantFreq_mean_"; break;
  default: cerr<<"ERROR!!"<<endl; exit(1); break;
  }
  
  //int dimension,Particlenum;
  string dt,disperse,Pnum,dim;
  string wt,wt_li,wt_li2,wt_const_cut,rd,str,rd_iF;
  //stringstream ss;
  ifstream ifs,ifs_iF;
  ofstream ofs_li,ofs_li2,ofs;
  int N;

  binstat::InputStr(dt,disperse,Pnum,dim);
  //dimension=atoi(dim.c_str());
  //Particlenum=atoi(Pnum.c_str());
  rd=rdtmp+"BR0.05_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  rd_iF=rd_iFtmp+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ifs.open(rd.data());
  if(ifs.fail()) {
    cerr<<"catnot open your file: "<<rd<<endl;
    return 1;
  }
  else {
    wt_li="LINEAR2_"+rd;
    wt_li2="tmpLINEAR2_"+rd;
    ofs_li.open(wt_li.data());
    ofs_li2.open(wt_li2.data());
    wt="CharacteristicFrequency2_"+rd;
    ofs.open(wt.data());
    
    N=atoi(Pnum.data());
    cout<<"\n\n2乗直線処理開始..."<<endl;
    
    const int Nd=15,n=4;
    const double gosa=0.25,expL_l=2-gosa,expL_h=2+gosa;
    double data[Nd],omega_m,dos_m,omega_ratio,cline,dphi,omega_iF;
    double omega[n],dos[n],lomega[n],ldos[n],Domega[n-1],Ddos[n-1],Eval[n-1];
    bool bb[n-1],fitted,inserted;	 
    string line;
    int cnt=0,cnttmpL=0,cntfailL=0,longestRange,dist;
    vector<DOSset> vL,vL2,vC,vC2,vline2;
    DOSfitter dfitter;

    vector<DOSfitter> l2set;
    
    while(getline(ifs,line)) {
      // cout<<cnt<<"回目ループ"<<endl;
      stringstream ss(line);
      for(int i=0;i<Nd;i++) {
	ss>>data[i];
	// cout<<data[i]<<' '; //stringstream test
      }
      // cout<<endl;
      if(cnt==0) {//while初回のみ代入して終わり.
	omega[0]=data[0];
	dos[0]=data[10];
	lomega[0]=log10(omega[1]);
	ldos[0]=log10(dos[1]);
	
	dphi=data[14];
      }
      else {
	for(int i=n-1;i>=0;i--) {
	  if(i==0) {
	    omega[0]=data[0];
	    dos[0]=data[10];
	    lomega[0]=log10(omega[0]);
	    ldos[0]=log10(dos[0]);
	  }
	  else {
	  omega[i]=omega[i-1];
	  dos[i]=dos[i-1];
	  lomega[i]=lomega[i-1];
	  ldos[i]=ldos[i-1];
	  }
	}

	for(int i=0;i<n-1;i++) {
	  if(i<cnt) {
	    Domega[i]=lomega[0]-lomega[i+1];
	    Ddos[i]=ldos[0]-ldos[i+1];
	    Eval[i]=Ddos[i]/Domega[i];
	    bb[i]=(Eval[i]>=expL_l && Eval[i]<=expL_h);
	  }
	  else {
	    bb[i]=false;
	  }
	}
	
	fitted=inserted=false;
	for(int i=0;i<n-1;i++) {
	  if(bb[i] && !fitted) {
	    dist=i+1;
	    if(l2set.size()==0) {
	      vector<DOSset> v;
	      insertDOSData(v,omega[dist],dos[dist],true);//要素追加
	      insertDOSData(v,omega[0],dos[0],true);
	      insertLineData(l2set,v,0,dist);//直線追加
	    }
	    else {
	      for(unsigned int j=0;j<l2set.size();j++) {
		if(l2set[j].enableAddomega==dist) {
		  if(dist==1 || !l2set[j].addedDiscontinuousPlot) {
		    modifyDOSfitter(l2set,j,omega[0],dos[0],true,dist);
		    inserted=true;
		  }
		}
	      }
	      if(!inserted) {
		  vector<DOSset> v;
		  insertDOSData(v,omega[dist],dos[dist],true);//要素追加
		  insertDOSData(v,omega[0],dos[0],true);
		  insertLineData(l2set,v,0,dist);//直線追加
	      }
	    }
	    //fitted=true;    
	  }
	  // cout<<"aaa"<<endl;
	}
	for(unsigned int j=0;j<l2set.size();j++) {
	    l2set[j].enableAddomega+=1;
	    // cout<<"bbb"<<endl;
	}
      }//else loop (2回目以降)
      // cout<<cnt<<"回目のループ演算を終えました."<<endl;
      cnt+=1;
    }
    
    if(vL2.size()<=vL.size()) {
      vL2=vL;
    }

    //-----
    if(l2set.size()<=0) {
      cerr<<"ひとつも直線2乗フィットすることができませんでした."<<endl;
      exit(1);
    }
    else {

      dfitter=l2set[0];
      longestRange=l2set[0].rangeLength;
      for(unsigned int j=1;j<l2set.size();j++) {
	if(dfitter.Dset.size()<3 && l2set[j].Dset.size() >=3) {//3点以上フィット成功しているところを重点的に.
	  dfitter=l2set[j];
	}
	if(l2set[j].rangeLength >= dfitter.rangeLength) {//広い領域でフィッティングできているところを重点的に.
	  dfitter=l2set[j];
	}
      }

      vL2=dfitter.Dset;//とりまつなぎ。
      const int NvL2=vL2.size(),NLm=vL2.size()/2;
      omega_m=vL2[NLm].omega;
      dos_m=vL2[NLm].dos;
      for(int i=0;i<NvL2;i++) {
	ofs_li2<<vL2[i].omega<<' '<<vL2[i].dos<<endl;
      }
      for(int i=0;i<NvL2;i++) {
	//1:おめが, 2:線形フィットDOS, 3:真値(元でーた)DOS, 4:
	if(i!=NLm) {
	  omega_ratio=pow(vL2[i].omega/omega_m,2);
	  ofs_li<<vL2[i].omega<<' '<<dos_m*omega_ratio<<' '<<vL2[i].dos<<endl;
	}
	else {
	  ofs_li<<omega_m<<' '<<dos_m<<' '<<dos_m<<endl;
	}
      }
      cout<<"\n2乗直線処理修了..."<<endl;
    }

    
    ifs_iF.open(rd_iF.data());
    if(ifs_iF.fail()) {
      cerr<<"readERROR: "<<rd_iF<<endl;
      exit(1);
    }
    else {
      getline(ifs_iF,line);
      stringstream ss_iF(line);
      ss_iF>>omega_iF>>cline;

      omega[0]=omega_m*sqrt(cline/dos_m);
      ofs<<dphi<<' '<<omega[0]<<' '<<cline<<' '<<N<<endl;   
    }

    
  }
}
