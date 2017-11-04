#ifndef _JTMESSAGE_H_
#define _JTMESSAGE_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include "nr.h"

using namespace std;

namespace JT
{
  //----------------------//
  //----Message output----//
  //--(in jtmessage.cpp)--//
  //----------------------//
  inline bool errArguments(int c);
  inline bool errArguments_re(int c);
  inline bool errPN(int PN);
  inline bool errDim(int D);
  inline void startingMessage(int s,int e,double phis,double phio,double Dphi);
  inline bool errPratio(int Prt, int PN);
  inline void ssInput(stringstream &ss,int a);
  inline void ssInput(stringstream &ss,DP a);
  inline void loopErrWrite(stringstream &ss,int snum,int iter,DP PHI,DP pot,DP ftol,int VViter,DP noise_strength);
  inline void jacobiErrWrite(stringstream &ss,ofstream &errFIRE,int snum,int iter,DP PHI,DP pot,DP ftol,int VViter);
  inline void simErrWrite(stringstream &ss,ofstream &ofs,Vec_I_DP &z, int dim,int PN,DP PHI,DP rt,int Prt1,int Prt2,int snum,int iter,DP pot,int VViter,bool eig,bool ipr,bool jacobi);
  inline void setOFSsingle(ofstream &ofs,string date,int samplenum, DP PHI);
  inline void setOFSsingle_re(ofstream &ofs,string date,int samplenum, DP PHI);
  inline void setOFScoddist(ofstream &ofs,string date,int samplenum, DP PHI);
  inline void setOFSsimerr(ofstream &ofs,string date,int samplenum, DP PHI, int iter);
  inline void setOFSeigmethod(int seednum,double PHI,string &str);
  inline void setOFSmode(int seednum,double PHI,int modenum,string &str);
  namespace dim2 {
    inline void simErrWrite(stringstream &ss,ofstream &ofs,Vec_I_DP &z,DP Lx,DP Ly,int dim,int PN,DP R,DP phi,DP rt,int Prt1,int Prt2,int snum,int iter,DP pot,int VViter,bool eig,bool ipr,bool jacobi); 
  }
  namespace dim3 {
    inline void simErrWrite(stringstream &ss,ofstream &ofs,Vec_I_DP &z,DP Lx,DP Ly,DP Lz,int dim,int PN,DP R,DP phi,DP rt,int Prt1,int Prt2,int snum,int iter,DP pot,int VViter,bool eig,bool ipr,bool jacobi); 
  }
}

namespace JT
{
  
  inline bool errArguments(int c) {
    if(c!=11) {
      //argv[0]を含むため,計9個の宣言.
      cerr<<"引数が"<<c<<"個宣言されています."<<endl;
      cerr<<"-----\n引数1...seed値の始まり"<<endl;
      cerr<<"引数2...seed値の終わり"<<endl;
      cerr<<"引数3...スタートのPHI値"<<endl;
      cerr<<"引数4...PHIの目的地\n!!ただし引数4=0.0ならばquenching dynamicsをする."<<endl;
      cerr<<"引数5...PHIの刻み幅(プラスで徐々にPHIを増やす、マイナスで徐々にPHIを減らす)"<<endl;
      cerr<<"引数6...粒子数"<<endl;
      cerr<<"引数7...空間次元"<<endl;
      cerr<<"引数8...粒子のサイズ比1:x"<<endl;
      cerr<<"引数9...1成分目の粒子の混合比I (I:II)"<<endl;
      cerr<<"引数10...2成分目の粒子の混合比II (I:II)"<<endl;
      cerr<<"----------\nになります.\n"<<endl;
      return true;
    }
    return false;
  }
  inline bool errArguments_re(int c) {
    if(c!=6) {
      //argv[0]を含むため,計9個の宣言.
      cerr<<"引数が"<<c<<"個宣言されています."<<endl;
      cerr<<"-----\n引数1...seed値の始まり"<<endl;
      cerr<<"引数2...seed値の終わり"<<endl;
      cerr<<"引数3...スタートのPHI値"<<endl;
      cerr<<"引数4...PHIの目的地\n!!ただし引数4=0.0ならばquenching dynamicsをする."<<endl;
      cerr<<"引数5...PHIの刻み幅(プラスで徐々にPHIを増やす、マイナスで徐々にPHIを減らす)"<<endl;
      cerr<<"----------\nになります.\n"<<endl;
      return true;
    }
    return false;
  }
  inline bool errPN(int PN) {
    if(static_cast<int>(0.5*PN)-(0.5*PN)!=0) {
      cerr<<"particle number must be even.\n"<<endl;
      return true;
    }
    return false;
  }
  inline bool errDim(int D) {
    if(D!=2 && D!=3) {
      cerr<<"you simulation must be done for only 2D or 3D.\n"<<endl;
      return true;
    }
    return false;
  }
  inline void startingMessage(int s,int e,double phis,double phio,double Dphi) {
    cout<<'\n'<<s<<"~"<<e<<"までのseed値で反復試行します."<<endl;
    cout<<"スタートのPHIは"<<phis<<"でスタートします."<<endl;
    cout<<"...... あなたの目的のPHIは"<<phio<<"とします."<<endl;
    cout<<"PHIの刻み幅は"<<Dphi<<"とします."<<endl;
    cout<<"Velret(FIREver.)のシミュレーションを開始します.\n\n"<<endl;
  }
  inline bool errPratio(int Prt, int PN) {
    if(PN%(Prt+1) !=0.0) {
      cerr<<"your particle ratio is disable for this program...\n\n"<<endl;
      return true;
    }
    return false;
  }
  inline bool errPratio(int Prt1,int Prt2,int PN) {
    if(PN%(Prt1+Prt2) !=0.0) {
      cerr<<"your particle ratio is disable for this program...\n\n"<<endl;
      return true;
    }
    return false;
  }
  inline void ssInput(stringstream &ss,int a) {
    ss.str("");//個々のconfigurationの様子を記録
    ss.clear(stringstream::goodbit);
    ss<<a;
  }
  inline void ssInput(stringstream &ss,DP a) {
    ss.str("");//個々のconfigurationの様子を記録
    ss.clear(stringstream::goodbit);
    ss<<setprecision(10)<<a;
  }
  inline void loopErrWrite(stringstream &ss,int snum,int iter,DP PHI,DP pot,DP ftol,int VViter,DP noise_strength) {
    ss.str("");
    ss.clear(stringstream::goodbit);
    ss<<"Err_R"<<snum<<"_itertimes"<<iter<<"_PHI"<<PHI<<".txt";
    ofstream errFIRE(ss.str().data());
    errFIRE<<setprecision(10)<<snum<<' '<<PHI<<' '<<pot<<' '<<ftol<<' '<<VViter<<' '<<noise_strength<<endl;
    errFIRE.close();
  }
  inline void jacobiErrWrite(stringstream &ss,ofstream &errFIRE,int snum,int iter,DP PHI,DP pot,DP ftol,int VViter) {
    ss.str("");
    ss.clear(stringstream::goodbit);
    ss<<"JacobiErr_R"<<snum<<"_PHI"<<PHI<<".txt";
    errFIRE.open(ss.str().data(),ios::app);
    errFIRE<<setprecision(10)<<snum<<' '<<PHI<<' '<<iter<<' '<<pot<<' '<<ftol<<' '<<VViter<<endl;
    errFIRE.close();
  }

  inline void simErrWrite(stringstream &ss,ofstream &ofs,Vec_I_DP &z, int dim,int PN,DP PHI,DP rt,int Prt1,int Prt2,int snum,int iter,DP pot,int VViter,bool eig,bool ipr,bool jacobi) {
    ss.str("");
    ss.clear(stringstream::goodbit);
    ss<<"SimErr_R"<<snum<<"_PHI"<<PHI<<".txt";
    ofs.open(ss.str().data(),ios::app);
    ofs<<setprecision(10)<<snum<<' '<<PHI<<' '<<iter<<' '<<pot<<' '<<VViter<<' '<<eig<<' '<<ipr<<' '<<jacobi<<endl;
    ofs.close();
    string w_zahyo="Zahyo_"+ss.str();
    ofstream ofs2(w_zahyo.data());
    ofs2<<setprecision(10)<<dim<<' '<<PN<<' '<<PHI<<' '<<rt<<' '<<Prt1<<' '<<Prt2<<endl;
    for(int i=0;i<PN;i++) {
      for(int j=0;j<dim-1;j++)
	ofs2<<setprecision(16)<<z[dim*i+j]<<' ';
      ofs2<<setprecision(16)<<z[dim*(i+1)-1]<<endl;
    }

  }
  inline void dim2::simErrWrite(stringstream &ss,ofstream &ofs,Vec_I_DP &z,DP Lx,DP Ly,int dim,int PN,DP R,DP phi,DP rt,int Prt1,int Prt2,int snum,int iter,DP pot,int VViter,bool eig,bool ipr,bool jacobi) {
    ss.str("");
    ss.clear(stringstream::goodbit);
    ss<<"SimErr_R"<<snum<<"_PHI"<<phi<<".txt";
    ofs.open(ss.str().data(),ios::app);
    ofs<<setprecision(10)<<snum<<' '<<phi<<' '<<iter<<' '<<pot<<' '<<VViter<<' '<<eig<<' '<<ipr<<' '<<jacobi<<endl;
    ofs.close();
    string w_zahyo="Zahyo_"+ss.str();
    ofstream ofs2(w_zahyo.data());
    ofs2<<setprecision(16)<<dim<<' '<<PN<<' '<<R<<' '<<phi<<' '<<rt<<' '<<Prt1<<' '<<Prt2<<' '<<Lx<<' '<<Ly<<endl;
    for(int i=0;i<PN;i++) {
      for(int j=0;j<dim-1;j++)
	ofs2<<setprecision(16)<<z[dim*i+j]<<' ';
      ofs2<<setprecision(16)<<z[dim*(i+1)-1]<<endl;
    }

  }
  inline void dim3::simErrWrite(stringstream &ss,ofstream &ofs,Vec_I_DP &z,DP Lx,DP Ly,DP Lz,int dim,int PN,DP R,DP phi,DP rt,int Prt1,int Prt2,int snum,int iter,DP pot,int VViter,bool eig,bool ipr,bool jacobi) {
    ss.str("");
    ss.clear(stringstream::goodbit);
    ss<<"SimErr_R"<<snum<<"_PHI"<<phi<<".txt";
    ofs.open(ss.str().data(),ios::app);
    ofs<<setprecision(10)<<snum<<' '<<phi<<' '<<iter<<' '<<pot<<' '<<VViter<<' '<<eig<<' '<<ipr<<' '<<jacobi<<endl;
    ofs.close();
    string w_zahyo="Zahyo_"+ss.str();
    ofstream ofs2(w_zahyo.data());
    ofs2<<setprecision(16)<<dim<<' '<<PN<<' '<<R<<' '<<phi<<' '<<rt<<' '<<Prt1<<' '<<Prt2<<' '<<Lx<<' '<<Ly<<' '<<Lz<<endl;
    for(int i=0;i<PN;i++) {
      for(int j=0;j<dim-1;j++)
	ofs2<<setprecision(16)<<z[dim*i+j]<<' ';
      ofs2<<setprecision(16)<<z[dim*(i+1)-1]<<endl;
    }
  }

  inline void setOFSsingle(ofstream &ofs,string date,int samplenum, DP PHI) {
    stringstream ss;
    ss<<"BIPhiEngVV"<<date<<"_RAND"<<samplenum<<'_'<<PHI<<".txt";
    ofs.open(ss.str().data());
  }
  inline void setOFSsingle_re(ofstream &ofs,string date,int samplenum, DP PHI) {
    stringstream ss;
    ss<<"BIPhiEngVV"<<date<<"_RAND"<<samplenum<<'_'<<PHI<<".txt";
    ofs.open(ss.str().data(),ios::app);
  }
  inline void setOFScoddist(ofstream &ofs,string date,int samplenum, DP PHI) {
    stringstream ss;
    ss<<"VV"<<date<<"_CODDIST"<<samplenum<<'_'<<PHI<<".txt";
    ofs.open(ss.str().data());
  }
inline void setOFSeigmethod(int seednum,double PHI,string &str)
  {
    stringstream ss,ss2;
    JT::ssInput(ss,seednum);
    JT::ssInput(ss2,PHI);
    if(seednum<10)
      str ="EigCum0000"+ss.str()+'_'+ss2.str()+".txt";
    else if(seednum>=10 && seednum<100)
      str ="EigCum000"+ss.str()+'_'+ss2.str()+".txt";
    else if(seednum>=100 && seednum<1000)
      str ="EigCum00"+ss.str()+'_'+ss2.str()+".txt";
    else if(seednum>=1000 && seednum<10000)
      str ="EigCum0"+ss.str()+'_'+ss2.str()+".txt";
    else
      str ="EigCum"+ss.str()+'_'+ss2.str()+".txt";
    return;
  }
  inline void setOFSmode(int seednum,double PHI,int modenum,string &str)
  {
    stringstream ss,ss1,ss2;
    JT::ssInput(ss,seednum);
    JT::ssInput(ss1,PHI);
    JT::ssInput(ss1,modenum);
    str="AngularDistribution"+ss.str()+"_"+ss1.str()+"_"+ss2.str()+"THmode.txt";
    return;
  }
  
}


#endif
