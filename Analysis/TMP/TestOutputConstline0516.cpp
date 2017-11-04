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
  string wt,wt_c,wt_c2,rdtmp="EIGEnsAve_",rd,str;
  //stringstream ss;
  ifstream ifs;
  ofstream ofs_c,ofs_c2,ofs;
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
    N=atoi(Pnum.data());
    cout<<"\n\n直線処理開始..."<<endl;
    
    const int Nd=12;
    const double gosa=0.1,exp_l=0,exp_h=0+gosa;
    double bb[Nd],omega_pp,omega_p,omega_l,dos_pp,dos_p,dos_l,ddos,domega,eval,lomega_pp,lomega_p,lomega_l,ldos_pp,ldos_p,ldos_l,omega_ratio;
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
	  if(cntfail==1) {
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
	      if(cnttmp>=6) {
		break;
	      }
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
	    ddos=ldos_l-ldos_pp;
	    eval=ddos/domega;
	    if(eval>=exp_l && eval<=exp_h) {
	      cout<<"まる2"<<endl;
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
      cerr<<"失敗！てへっ(はあと)"<<endl;
      exit(1);
    }
    else {
      cnt=0;
      const int Nv2=v2.size(),Nm=v2.size()/2;
      double dos_m=v2[Nm].dos;
      for(int i=0;i<Nv2;i++) {
	ofs_c2<<v2[i].omega<<' '<<v2[i].dos<<endl;
      }
      ofs_c2.close();
      
      for(int i=0;i<Nv2;i++) {
	//1:おめが, 2:線形フィットDOS, 3:真値(元でーた)DOS, 4:
	ofs_c<<v2[i].omega<<' '<<dos_m<<' '<<v2[i].dos<<endl;
      }
      cout<<"\nConst直線処理修了..."<<endl;
    }
  }
}
