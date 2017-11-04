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
  string wt,wt_li,wt_li2,wt_const,wt_const_cut,rdtmp="EIGEnsAve_",rd,str;
  //stringstream ss;
  ifstream ifs;
  ofstream ofs_c,ofs_li,ofs_li2,ofs_const_cut,ofs;
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
    wt_li="LINEAR_"+rd;
    wt_li2="tmpLINEAR_"+rd;
    ofs_li.open(wt_li.data());
    ofs_li2.open(wt_li2.data());
    N=atoi(Pnum.data());
    cout<<"\n\n2乗直線処理開始..."<<endl;
    
    const int Nd=12;
    const double gosa=0.25,exp_l=2-gosa,exp_h=2+gosa;
    double bb[Nd],omega_3p,omega_pp,omega_p,omega_l,dos_3p,dos_pp,dos_p,dos_l,omega_m,dos_m,ddos,ddos2,domega,domega2,eval,eval2,lomega_3p,lomega_pp,lomega_p,lomega_l,ldos_3p,ldos_pp,ldos_p,ldos_l,omega_ratio;
    string line;
    int cnt=0,cnttmp=0,cntfail=0;
    vector<DOSset> v,v2;
    
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
	dos_p=bb[8];
	lomega_p=log10(omega_p);
	ldos_p=log10(dos_p);
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
	dos_l=bb[8];
	lomega_l=log10(omega_l);
	ldos_l=log10(dos_l);
	
	domega=lomega_l-lomega_p;
	ddos=ldos_l-ldos_p;
	eval=ddos/domega;
	//ddos=dos_l-dos_p;
	cout<<exp_l<<"<"<<eval<<"<"<<exp_h<<endl;
	if(eval>=exp_l && eval<=exp_h) {
	  cout<<"まる0"<<endl;
	  if(cntfail==1) {
	    insertDOSData(v,omega_p,dos_p);
	    insertDOSData(v,omega_l,dos_l);
	    cnttmp+=2;
	  }
	  else if(cntfail==2) {
	    insertDOSData(v,omega_pp,dos_pp);
	    insertDOSData(v,omega_p,dos_p);
	    insertDOSData(v,omega_l,dos_l);
	    cnttmp+=3;
	  }
	  else {
	    if(cnttmp==0) {//2乗直線グループに入れる最初のおめが組についてはomega_pも
	      insertDOSData(v,omega_p,dos_p);
	      cnttmp+=1;
	    }
	    insertDOSData(v,omega_l,dos_l);
	    cnttmp+=1;
	  }
	  cntfail=0;
	}//隣接点が2乗の傾きに分類.
	else {
	  if(cntfail==0){
	    cntfail+=1;
	  }
	  else if(cntfail==1) {
	    domega=lomega_l-lomega_pp;
	    ddos=ldos_l-ldos_pp;
	    eval=ddos/domega;
	    if(eval>=exp_l && eval<=exp_h) {
	      cout<<"まる1"<<endl;
	      insertDOSData(v,omega_p,dos_p);
	      insertDOSData(v,omega_l,dos_l);
	      cnttmp+=2;
	      cntfail=0;
	    }
	    else {
	      cntfail+=1;
	    }
	  }
	  else if(cntfail==2) {
	    domega=lomega_l-lomega_pp;
	    domega2=lomega_l-lomega_3p;
	    ddos=ldos_l-ldos_pp;
	    ddos2=ldos_l-ldos_3p;
	    eval=ddos/domega;
	    eval2=ddos2/domega2;
	    if((eval>=exp_l && eval<=exp_h) || (eval2>=exp_l && eval2<=exp_h)) {
	      cout<<"まる2"<<endl;
	      insertDOSData(v,omega_pp,dos_pp);
	      insertDOSData(v,omega_p,dos_p);
	      insertDOSData(v,omega_l,dos_l);
	      cnttmp+=3;
	      cntfail=0;
	    }
	    else {//v初期化.
	      if(v2.size()<v.size()) {
	      v2=v;
	      }
	      vector<DOSset>().swap(v);
	      cnttmp=0;
	      cntfail+=1;
	    }
	  }
	  else {
	    domega=lomega_l-lomega_pp;
	    domega2=lomega_l-lomega_3p;
	    ddos=ldos_l-ldos_pp;
	    ddos2=ldos_l-ldos_3p;
	    eval=ddos/domega;
	    eval2=ddos2/domega2;
	    if((eval>=exp_l && eval<=exp_h) || (eval2>=exp_l && eval2<=exp_h)) {
	      cout<<"まる3"<<endl;
	      insertDOSData(v,omega_3p,dos_3p);
	      insertDOSData(v,omega_pp,dos_pp);
	      insertDOSData(v,omega_p,dos_p);
	      insertDOSData(v,omega_l,dos_l);
	      cnttmp+=3;
	      cntfail=0;
	    }
	    else {
	      cntfail+=1;
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
    if(v2.size()<v.size()) {
      v2=v;
    }

    if(v2.size()<=0) {
      cerr<<"2乗フィットできませんでした."<<endl;
      exit(1);
    }
    else {
      const int Nv2=v2.size(),Nm=v2.size()/2;
      omega_m=v2[Nm].omega;
      dos_m=v2[Nm].dos;
      for(int i=0;i<Nv2;i++) {
	ofs_li2<<v2[i].omega<<' '<<v2[i].dos<<endl;
      }
      for(int i=0;i<Nv2;i++) {
	//1:おめが, 2:線形フィットDOS, 3:真値(元でーた)DOS, 4:
	if(i!=Nm) {
	  omega_ratio=pow(v2[i].omega/omega_m,2);
	  ofs_li<<v2[i].omega<<' '<<dos_m*omega_ratio<<' '<<v2[i].dos<<endl;
	}
	else {
	  ofs_li<<omega_m<<' '<<dos_m<<' '<<dos_m<<endl;
	}
      }
      cout<<"\n2乗直線処理修了..."<<endl;
    }
  }
}
