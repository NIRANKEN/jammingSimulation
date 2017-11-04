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

            //0.Freq (bin_middle point)
	    //1.IPR (mean)
	    //2.IPR_min
	    //3.IPR_max
	    //4.IPR_variance -DY(log scale)
            //5.IPR_variance +DY(log scale)
	    //6.IPR_1st component (mean)
	    //7.IPR_2nd component (mean)
            //8.Ratio of small particles component for i-th eigenvector (mean)
	    //9.DOS (zero eig なし)
	    //10.DOS (zero eig あり)
            //11.cum DOS (zero eig なし)
            //12.binに入ったFreqの数
            //13.粒子数
            //14.DPHIの値(logscale bin middle point)
	    //15.None
            //16.None
            //17.None

int main()
{
  
  //int dimension,Particlenum;
  string dt,disperse,Pnum,dim;
  string wt,wt_li,wt_li2,wt_c,wt_c2,wt_const_cut,rdtmp="EIGEnsAve_",rd,str;
  //stringstream ss;
  ifstream ifs;
  ofstream ofs_li,ofs_li2,ofs_c,ofs_c2,ofs;
  int N;

  binstat::InputStr(dt,disperse,Pnum,dim);
  //dimension=atoi(dim.c_str());
  //Particlenum=atoi(Pnum.c_str());
  rd=rdtmp+"BR0.05_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ifs.open(rd.data());
  if(ifs.fail()) {
    cerr<<"catnot open your file: "<<rd<<endl;
    return 1;
  }
  else {
    wt_c="CONST_"+rd;
    wt_c2="tmpCONST_"+rd;
    ofs_c.open(wt_c.data());
    ofs_c2.open(wt_c2.data());
    wt_li="LINEAR_"+rd;
    wt_li2="tmpLINEAR_"+rd;
    ofs_li.open(wt_li.data());
    ofs_li2.open(wt_li2.data());
    wt="CharacteristicFrequency_"+rd;
    ofs.open(wt.data());
    
    N=atoi(Pnum.data());
    cout<<"\n\n2乗直線処理開始..."<<endl;
    
    const int Nd=15;
    const double gosa=0.25,expL_l=2-gosa,expL_h=2+gosa,expC_l=0.0-gosa,expC_h=0.0+gosa;
    double bb[Nd],omega_3p,omega_pp,omega_p,omega_l,dos_3p,dos_pp,dos_p,dos_l,omega_m,dos_m,ddos,ddos2,domega,domega2,eval,eval2,lomega_3p,lomega_pp,lomega_p,lomega_l,ldos_3p,ldos_pp,ldos_p,ldos_l,omega_ratio,cline,dphi;
    string line;
    int cnt=0,cnttmpL=0,cnttmpC=0,cntfailL=0,cntfailC=0;
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
	//CONST part
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
	    insertDOSData(vL,omega_pp,dos_pp,false);
	    insertDOSData(vL,omega_p,dos_p,false);
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
	      insertDOSData(vL,omega_p,dos_p,false);
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
	      insertDOSData(vL,omega_pp,dos_pp,false);
	      insertDOSData(vL,omega_p,dos_p,false);
	      insertDOSData(vL,omega_l,dos_l,true);
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
	      insertDOSData(vL,omega_3p,dos_3p,true);
	      insertDOSData(vL,omega_pp,dos_pp,false);
	      insertDOSData(vL,omega_p,dos_p,false);
	      insertDOSData(vL,omega_l,dos_l,true);
	      cnttmpL+=3;
	      cntfailL=0;
	    }
	    else {
	      cntfailL+=1;
	    }
	  }
	}//隣接点が2乗の傾きに分類できんかった場合.

	domega=lomega_l-lomega_p;
	ddos=ldos_l-ldos_p;
	eval=ddos/domega;
	//ddos=dos_l-dos_p;
	
	cout<<expC_l<<"<"<<eval<<"<"<<expC_h<<endl;

	//===========================
	//CONST part
	//===========================
	
	if(eval>=expC_l && eval<=expC_h) {
	  cout<<"まる0C"<<endl;
	  if(cntfailC==1) {
	    insertDOSData(vC,omega_p,dos_p,true);
	    insertDOSData(vC,omega_l,dos_l,true);
	    cnttmpC+=2;
	  }
	  else {
	    if(cnttmpC==0) {//2乗直線グループに入れる最初のおめが組についてはomega_pも
	      insertDOSData(vC,omega_p,dos_p,true);
	      cnttmpC+=1;
	    }
	    insertDOSData(vC,omega_l,dos_l,true);
	    cnttmpC+=1;
	  }
	  cntfailC=0;
	}//隣接点が2乗の傾きに分類.
	else {
	  if(cntfailC==1) {
	    domega=lomega_l-lomega_pp;
	    ddos=ldos_l-ldos_pp;
	    eval=ddos/domega;
	    if(eval>=expC_l && eval<=expC_h) {
	      cout<<"まる1C"<<endl;
	      insertDOSData(vC,omega_p,dos_p,false);
	      insertDOSData(vC,omega_l,dos_l,true);
	      cnttmpC+=2;
	      cntfailC=0;
	    }
	    else {
	      /*
	      if(cnttmpC>=6) {
		break;
	      }
	      */
	      if(vC2.size()<vC.size()) {
	      vC2=vC;
	      }
	      vector<DOSset>().swap(vC);
	      cnttmpC=0;
	      cntfailC+=1;
	    }
	  }
	  else {
	    domega=lomega_l-lomega_pp;
	    ddos=ldos_l-ldos_pp;
	    eval=ddos/domega;
	    if(eval>=expC_l && eval<=expC_h) {
	      cout<<"まる2"<<endl;
	      insertDOSData(vC,omega_pp,dos_pp,true);
	      insertDOSData(vC,omega_p,dos_p,false);
	      insertDOSData(vC,omega_l,dos_l,true);
	      cnttmpC+=3;
	      cntfailC=0;
	    }
	    else {
	      cntfailC+=1;
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
    if(vC2.size()<vC.size()) {
      vC2=vC;
    }
    //--------------
    
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
    if(vC2.size()<=0) {
      cerr<<"失敗！てへっ(はあと)"<<endl;
      exit(1);
    }
    else {
      cnt=0;
      const int NvC2=vC2.size(),NCm=vC2.size()/2;
      cline=vC2[NCm].dos;
      for(int i=0;i<NvC2;i++) {
	ofs_c2<<vC2[i].omega<<' '<<vC2[i].dos<<endl;
      }
      ofs_c2.close();
      
      for(int i=0;i<NvC2;i++) {
	//1:おめが, 2:線形フィットDOS, 3:真値(元でーた)DOS, 4:
	ofs_c<<vC2[i].omega<<' '<<cline<<' '<<vC2[i].dos<<endl;
      }
      cout<<"\nConst直線処理修了..."<<endl;
    }

    omega_l=omega_m*sqrt(cline/dos_m);
    ofs<<dphi<<' '<<omega_l<<' '<<cline<<endl;   


    
  }
}
