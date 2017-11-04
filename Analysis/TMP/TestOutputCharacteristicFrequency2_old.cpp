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

int main()
{
  
  //int dimension,Particlenum;
  string dt,disperse,Pnum,dim;
  string wt,wt_li,wt_li2,wt_const_cut,rdtmp="EIGEnsAve_",rd,str,rd_iF;
  //stringstream ss;
  ifstream ifs,ifs_iF;
  ofstream ofs_li,ofs_li2,ofs;
  int N;

  binstat::InputStr(dt,disperse,Pnum,dim);
  //dimension=atoi(dim.c_str());
  //Particlenum=atoi(Pnum.c_str());
  rd=rdtmp+"BR0.05_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  rd_iF="InvariantFreq_mean_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
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
    
    const int Nd=15;
    const double gosa=0.25,expL_l=2-gosa,expL_h=2+gosa;
    double bb[Nd],omega_3p,omega_pp,omega_p,omega_l,dos_3p,dos_pp,dos_p,dos_l,omega_m,dos_m,ddos,ddos2,domega,domega2,eval,eval2,lomega_3p,lomega_pp,lomega_p,lomega_l,ldos_3p,ldos_pp,ldos_p,ldos_l,omega_ratio,cline,dphi,omega_iF;
    string line;
    int cnt=0,cnttmpL=0,cntfailL=0;
    vector<DOSset> vL,vL2,vC,vC2;
    
    while(getline(ifs,line)) {
      cout<<cnt<<"回目ループ"<<endl;
      stringstream ss(line);
      for(int i=0;i<Nd;i++) {
	ss>>bb[i];
	cout<<bb[i]<<' '; //stringstream test
      }
      cout<<endl;
      if(cnt==0) {//while初回のみ代入して終わり.
	omega_p=bb[0];
	dos_p=bb[10];
	lomega_p=log10(omega_p);
	ldos_p=log10(dos_p);
	dphi=bb[14];
      }
      else {
	if(cnt>=3) {
	  lomega_3p=lomega_pp;
	  ldos_3p=ldos_pp;
	}
	if(cnt>=2) {
	  lomega_pp=lomega_p;
	  ldos_pp=ldos_p;
	}
	lomega_p=lomega_l;
	ldos_p=ldos_l;
	
	omega_l=bb[0];
	dos_l=bb[10];
	lomega_l=log10(omega_l);
	ldos_l=log10(dos_l);
	
	domega=lomega_l-lomega_p;
	ddos=ldos_l-ldos_p;
	eval=ddos/domega;
	//ddos=dos_l-dos_p;

	//===========================
	//LINEAR part
	//===========================
	
	cout<<expL_l<<"<"<<eval<<"<"<<expL_h<<endl;
	if(eval>=expL_l && eval<=expL_h) {
	  cout<<"まる0"<<endl;
	  if(cntfailL==1) {
	    insertDOSData(vL,omega_p,dos_p,true);
	    insertDOSData(vL,omega_l,dos_l,true);
	    cnttmpL+=2;
	  }
	  else if(cntfailL==2) {
	    //insertDOSData(vL,omega_pp,dos_pp,false);
	    insertDOSData(vL,omega_p,dos_p,true);
	    insertDOSData(vL,omega_l,dos_l,true);
	    cnttmpL+=3;
	  }
	  else {
	    if(cnttmpL==0) {//2乗直線グループに入れる最初のおめが組についてはomega_pも
	      insertDOSData(vL,omega_p,dos_p,true);
	      cnttmpL+=1;
	    }
	    insertDOSData(vL,omega_l,dos_l,true);
	    cnttmpL+=1;
	  }
	  cntfailL=0;
	}//隣接点が2乗の傾きに分類.
	else {
	  if(cntfailL==0){
	    cntfailL+=1;
	  }
	  else if(cntfailL==1) {
	    domega=lomega_l-lomega_pp;
	    ddos=ldos_l-ldos_pp;
	    eval=ddos/domega;
	    if(eval>=expL_l && eval<=expL_h) {
	      cout<<"Lまる1"<<endl;
	      //insertDOSData(vL,omega_p,dos_p,false);
	      insertDOSData(vL,omega_l,dos_l,true);
	      cnttmpL+=2;
	      cntfailL=0;
	    }
	    else {
	      cntfailL+=1;
	    }
	  }
	  else if(cntfailL==2) {
	    domega=lomega_l-lomega_pp;
	    domega2=lomega_l-lomega_3p;
	    ddos=ldos_l-ldos_pp;
	    ddos2=ldos_l-ldos_3p;
	    eval=ddos/domega;
	    eval2=ddos2/domega2;
	    if((eval>=expL_l && eval<=expL_h) || (eval2>=expL_l && eval2<=expL_h)) {
	      cout<<"まる2"<<endl;
	      if((eval>=expL_l && eval<=expL_h) && (eval2>=expL_l && eval2<=expL_h)) {
		insertDOSData(vL,omega_pp,dos_pp,true);
		insertDOSData(vL,omega_p,dos_p,true);
		insertDOSData(vL,omega_l,dos_l,true);
	      }
	      else if((eval>=expL_l && eval<=expL_h) && !(eval2>=expL_l && eval2<=expL_h)) {
		insertDOSData(vL,omega_pp,dos_pp,true);
		//insertDOSData(vL,omega_p,dos_p,false);
		insertDOSData(vL,omega_l,dos_l,true);
	      }
	      else if(!(eval>=expL_l && eval<=expL_h) && (eval2>=expL_l && eval2<=expL_h)) {
		//insertDOSData(vL,omega_pp,dos_pp,false);
		//insertDOSData(vL,omega_p,dos_p,false);
		insertDOSData(vL,omega_l,dos_l,true);
	      }
	      else {
		cerr<<"条件分岐失敗.(count fail=2)"<<endl;
		exit(1);
	      }
	      cnttmpL+=3;
	      cntfailL=0;
	    }
	    else {//v初期化.
	      if(vL2.size()<vL.size()) {
	      vL2=vL;
	      }
	      vector<DOSset>().swap(vL);
	      cnttmpL=0;
	      cntfailL+=1;
	    }
	  }
	  else {
	    domega=lomega_l-lomega_pp;
	    domega2=lomega_l-lomega_3p;
	    ddos=ldos_l-ldos_pp;
	    ddos2=ldos_l-ldos_3p;
	    eval=ddos/domega;
	    eval2=ddos2/domega2;
	    if((eval>=expL_l && eval<=expL_h) || (eval2>=expL_l && eval2<=expL_h)) {
	      cout<<"まる3"<<endl;
	      if((eval>=expL_l && eval<=expL_h) && (eval2>=expL_l && eval2<=expL_h)) {
		insertDOSData(vL,omega_3p,dos_3p,true);
		insertDOSData(vL,omega_pp,dos_pp,true);
		//insertDOSData(vL,omega_p,dos_p,false);
		insertDOSData(vL,omega_l,dos_l,true);
	      }
	      else if((eval>=expL_l && eval<=expL_h) && !(eval2>=expL_l && eval2<=expL_h)) {
		//insertDOSData(vL,omega_3p,dos_3p,false);
		insertDOSData(vL,omega_pp,dos_pp,true);
		//insertDOSData(vL,omega_p,dos_p,false);
		insertDOSData(vL,omega_l,dos_l,true);
	      }
	      else if(!(eval>=expL_l && eval<=expL_h) && (eval2>=expL_l && eval2<=expL_h)) {
		insertDOSData(vL,omega_3p,dos_3p,true);
		//insertDOSData(vL,omega_pp,dos_pp,false);
		//insertDOSData(vL,omega_p,dos_p,false);
		insertDOSData(vL,omega_l,dos_l,true);
	      }
	      else {
		cerr<<"条件分岐失敗(countfail>=3)"<<endl;
		exit(1);
	      }
	      cnttmpL+=3;
	      cntfailL=0;
	    }
	    else {
	      cntfailL+=1;
	    }
	  }
	}//隣接点が2乗の傾きに分類できんかった場合.

	//modify...
	omega_3p=omega_pp;
	dos_3p=dos_pp;
	omega_pp=omega_p;
	dos_pp=dos_p;
	omega_p=omega_l;
	dos_p=dos_l;
      }//else loop (2回目以降)
      cnt+=1;
    }
    if(vL2.size()<vL.size()) {
      vL2=vL;
    }

    //-----
    if(vL2.size()<=0) {
      cerr<<"2乗フィットできませんでした."<<endl;
      exit(1);
    }
    else {
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

    omega_l=omega_m*sqrt(cline/dos_m);
    ofs<<dphi<<' '<<omega_l<<' '<<cline<<endl;   
    }

    
  }
}
