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

int main(int argc, char** argv)
{
  if(argc!=2) {
    cerr<<"生DOS=> \"0\", 平滑化DOS=> \"1\"を引数に入力して下さい."<<endl;
    exit(1);
  }
  string rdtmp;
  switch(atoi(argv[1])) {
  case 0: rdtmp="EIGEnsAve_"; break;
  case 1: rdtmp="SM_EIGEnsAve_"; break;
  default: cerr<<"ERROR!!"<<endl; exit(1); break;
  }
  //int dimension,Particlenum;
  string dt,disperse,Pnum,dim;
  string wt,wt_li,wt_li2,wt_c,wt_c2,wt_const_cut,rd,str;
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
    // cout<<"\n\n2乗直線処理開始..."<<endl;
    
    const int Nd=15,n=5;
    const double gosa=0.25,expL_l=2-gosa,expL_h=2+gosa,expC_l=0.0-gosa,expC_h=0.0+gosa;
    double data[Nd],omega_m,dos_m,omega_ratio,cline,dphi;
    double omega[n],dos[n],Domega[n-2],Ddos[n-2],Eval[n-2],lomega[n],ldos[n];
    string line;
    int cnt=0,cnttmpL=0,cnttmpC=0,cntfailL=0,cntfailC=0;
    vector<DOSset> vL,vL2,vC,vC2;
    
    while(getline(ifs,line)) {
      // cout<<cnt<<"回目ループ"<<endl;
      stringstream ss(line);
      for(int i=0;i<Nd;i++) {
	ss>>data[i];
	// cout<<data[i]<<' '; //stringstream test
      }
      // cout<<endl;
      if(cnt==0) {//while初回のみ代入して終わり.
	omega[1]=data[0];
	dos[1]=data[10];
	lomega[1]=log10(omega[1]);
	ldos[1]=log10(dos[1]);
	
	dphi=data[14];
      }
      else {
	for(int i=n-1;i>=1;i--) {
	  if(i>=2) {
	  if(cnt>=i) {
	    lomega[i]=lomega[i-1];
	    ldos[i]=ldos[i-1];
	  }
	  }
	  else {
	    lomega[i]=lomega[i-1];
	    ldos[i]=ldos[i-1];    
	  }
	}
	omega[0]=data[0];
	dos[0]=data[10];
	lomega[0]=log10(omega[0]);
	ldos[0]=log10(dos[0]);
	Domega[0]=lomega[0]-lomega[1];
	Ddos[0]=ldos[0]-ldos[1];
	Eval[0]=Ddos[0]/Domega[0];
	//ddos=dos_l-dos_p;

	//===========================
	//LINEAR part
	//===========================
	
	// cout<<expL_l<<"<"<<Eval[0]<<"<"<<expL_h<<endl;
	if(Eval[0]>=expL_l && Eval[0]<=expL_h) {
	  // cout<<"まる0"<<endl;

	  if(cntfailL>=1 && cntfailL<=n-2) {
	    for(int i=1;i>=0;i--)
	      insertDOSData(vL,omega[i],dos[i],true);
	    cnttmpL+=(cntfailL+1);
	  }
	  else {
	    if(cnttmpL==0) {//2乗直線グループに入れる最初のおめが組についてはomega_pも
	      insertDOSData(vL,omega[1],dos[1],true);
	      cnttmpL+=1;
	    }
	    insertDOSData(vL,omega[0],dos[0],true);
	    cnttmpL+=1;
	  }
	  cntfailL=0;
	}//隣接点が2乗の傾きに分類.
	else {//**//**//
	  if(cntfailL==0){
	    cntfailL+=1;
	  }
	  else if(cntfailL==1) {
	    Domega[0]=lomega[0]-lomega[2];
	    Ddos[0]=ldos[0]-ldos[2];
	    Eval[0]=Ddos[0]/Domega[0];

	    if(Eval[0]>=expL_l && Eval[0]<=expL_h) {
	      // cout<<"Lまる1"<<endl;
	      //insertDOSData(vL,omega_p,dos_p,false);
	      insertDOSData(vL,omega[0],dos[0],true);
	      cnttmpL+=2;
	      cntfailL=0;
	    }
	    else {
	      cntfailL+=1;
	    }
	  }
	  else if(cntfailL==2) {
	    bool bb[2];
	    for(int i=0;i<2;i++) {
	      Domega[i]=lomega[0]-lomega[i+2];
	      Ddos[i]=ldos[0]-ldos[i+2];
	      Eval[i]=Ddos[i]/Domega[i];
	      bb[i]=(Eval[i]>=expL_l && Eval[i]<=expL_h);
	    }

	    if(bb[0] || bb[1]) {
	      // cout<<"まる2"<<endl;
	      if(bb[0] && bb[1]) {
		for(int i=3;i>=0;i--) {
		  if(i!=1)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else if(bb[0] && !bb[1]) {
		for(int i=2;i>=0;i--) {
		  if(i!=1)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else if(!bb[0] && bb[1]) {
		for(int i=1;i>=0;i--) {
		  if(i!=1)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else {
		cerr<<"条件分岐失敗.(count fail=2)"<<endl;
		exit(1);
	      }
	      cnttmpL+=3;
	      cntfailL=0;
	    }
	    else {
	      cntfailL+=1;
	    }
	  }
	  else if(cntfailL==3) {
	    
	    bool bb[3];
	    for(int i=0;i<3;i++) {
	      Domega[i]=lomega[0]-lomega[i+2];
	      Ddos[i]=ldos[0]-ldos[i+2];
	      Eval[i]=Ddos[i]/Domega[i];
	      bb[i]=(Eval[i]>=expL_l && Eval[i]<=expL_h);
	    }

	    if(bb[0] || bb[1] || bb[2]) {
	      if(bb[0] && bb[1] && bb[2]) {
		for(int i=4;i>=0;i--) {
		  if(i!=1)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else if(bb[0] && bb[1] && !bb[2]) {
		for(int i=3;i>=0;i--) {
		  if(i!=1)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else if(bb[0] && !bb[1] && bb[2]) {
		for(int i=4;i>=0;i--) {
		  if(i!=1 && i!=3)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else if(!bb[0] && bb[1] && bb[2]) {
		for(int i=4;i>=0;i--) {
		  if(i!=1 && i!=2)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else if(bb[0] && !bb[1] && !bb[2]) {
		for(int i=2;i>=0;i--) {
		  if(i!=1)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else if(!bb[0] && bb[1] && !bb[2]) {
		for(int i=3;i>=0;i--) {
		  if(i!=1 && i!=2)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else if(!bb[0] && !bb[1] && bb[2]) {
		for(int i=4;i>=0;i--) {
		  if(i!=1 && i!=2 && i!=3)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
	      }
	      else {
		cerr<<"条件分岐失敗.(count fail=3)"<<endl;
		exit(1);
	      }
	      cnttmpL+=4;
	      cntfailL=0;
	    }
	    else {
	      //v初期化.
	      if(vL2.size()<=vL.size()) {
		vL2=vL;
	      }
	      vector<DOSset>().swap(vL);
	      cnttmpL=0;
	      cntfailL+=1;
	    }
	  }
	  else {
	    bool bb[3];
	    for(int i=0;i<3;i++) {
	      Domega[i]=lomega[0]-lomega[i+2];
	      Ddos[i]=ldos[0]-ldos[i+2];
	      Eval[i]=Ddos[i]/Domega[i];
	      bb[i]=(Eval[i]>=expL_l && Eval[i]<=expL_h);
	    }
	    
	    if(bb[0] || bb[1] || bb[2]) {
	      if(bb[0] && bb[1] && bb[2]) {
		for(int i=4;i>=0;i--) {
		  if(i!=1)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
		cnttmpL+=4;
	      }
	      else if(bb[0] && bb[1] && !bb[2]) {
		for(int i=3;i>=0;i--) {
		  if(i!=1)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
		cnttmpL+=3;
	      }
	      else if(bb[0] && !bb[1] && bb[2]) {
		for(int i=4;i<=0;i--) {
		  if(i!=1 && i!=3)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
		cnttmpL+=4;
	      }
	      else if(!bb[0] && bb[1] && bb[2]) {
		for(int i=4;i>=0;i--) {
		  if(i!=1 && i!=2)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
		cnttmpL+=4;
	      }
	      else if(bb[0] && !bb[1] && !bb[2]) {
		for(int i=2;i>=0;i--) {
		  if(i!=1)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
		cnttmpL+=2;
	      }
	      else if(!bb[0] && bb[1] && !bb[2]) {
		for(int i=3;i>=0;i--) {
		  if(i!=1 && i!=2)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
		cnttmpL+=3;
	      }
	      else if(!bb[0] && !bb[1] && bb[2]) {
		for(int i=4;i>=0;i--) {
		  if(i!=1 && i!=2 && i!=3)
		    insertDOSData(vL,omega[i],dos[i],true);
		}
		cnttmpL+=4;
	      }
	      else {
	      cerr<<"条件分岐失敗.(count fail=3)"<<endl;
	      exit(1);
	      }
	      cntfailL=0;
	    }
	    else {
	      cntfailL+=1;
	    }
	  }
	}//隣接点が2乗の傾きに分類できんかった場合 - end.

	//===========================
	//CONST part
	//===========================
	
	Domega[0]=lomega[0]-lomega[1];
	Ddos[0]=ldos[0]-ldos[1];
	Eval[0]=Ddos[0]/Domega[0];
	//ddos=dos_l-dos_p;
	// cout<<expC_l<<"<"<<Eval[0]<<"<"<<expC_h<<endl;
	
	if(Eval[0]>=expC_l && Eval[0]<=expC_h) {
	  // cout<<"まる0C"<<endl;
	  if(cntfailC==1) {
	    for(int i=1;i>=0;i--)
	      insertDOSData(vC,omega[i],dos[i],true);
	    cnttmpC+=2;
	  }
	  else {
	    if(cnttmpC==0) {//2乗直線グループに入れる最初のおめが組についてはomega_pも
	      insertDOSData(vC,omega[1],dos[1],true);
	      cnttmpC+=1;
	    }
	    insertDOSData(vC,omega[0],dos[0],true);
	    cnttmpC+=1;
	  }
	  cntfailC=0;
	}//隣接点が2乗の傾きに分類.
	else {
	  if(cntfailC==1) {
	    Domega[0]=lomega[0]-lomega[2];
	    Ddos[0]=ldos[0]-ldos[2];
	    Eval[0]=Ddos[0]/Domega[0];
	    if(Eval[0]>=expC_l && Eval[0]<=expC_h) {
	      // cout<<"まる1C"<<endl;
	      for(int i=1;i>=0;i--)
		insertDOSData(vC,omega[i],dos[i],true);
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
	    Domega[0]=lomega[0]-lomega[2];
	    Ddos[0]=ldos[0]-ldos[2];
	    Eval[0]=Ddos[0]/Domega[0];

	    if(Eval[0]>=expC_l && Eval[0]<=expC_h) {
	      // cout<<"まる2"<<endl;
	      for(int i=2;i>=0;i--)
		insertDOSData(vC,omega[i],dos[i],true);
	      cnttmpC+=3;
	      cntfailC=0;
	    }
	    else {
	      cntfailC+=1;
	    }
	  }
	}//隣接点が2乗の傾きに分類できんかった場合.

	//const end//

	//modify...
	for(int i=n-1;i>=1;i--) {
	      omega[i]=omega[i-1];
	      dos[i]=dos[i-1];
	}
	
      }//else loop (2回目以降)
      cnt+=1;
    }
    if(vL2.size()<=vL.size()) {
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

    omega[0]=omega_m*sqrt(cline/dos_m);
    ofs<<dphi<<' '<<omega[0]<<' '<<cline<<endl;   


    
  }
}
