#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "BIN.h"

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
  
  string rd,rdifs,wt,dt,disperse,Pnum,dim,cfreqtxt,line,lineI,lineC;
  ifstream ifs,ifs_ifreq,ifs_cfreq;
  stringstream ssI,ssC;
  ofstream ofs;
  double omegaI,DOSI,DPHI,omegaC,DOSC;
  cout<<"読み込むCharacteristic Freqの.txtファイル名を入力.\n(e.g. hoge.txt)->";
  cin>>cfreqtxt;
  binstat::InputStr(dt,disperse,Pnum,dim);
  rd=rdtmp+"BR0.05_"+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  rdifs=rd_iFtmp+dt+"_"+dim+disperse+"N"+Pnum+".txt";
  wt="Additional"+rd;
  ifs.open(rd.data());
  ifs_ifreq.open(rdifs.data());
  ifs_cfreq.open(cfreqtxt.data());
  ofs.open(wt.data());

  if(ifs.fail() || ifs_ifreq.fail() || ifs_cfreq.fail()) {
    cerr<<"file開けなかったのだ!"<<endl;
    cerr<<"binData: "<<ifs.fail()<<" IfreqData:"<<ifs_ifreq.fail()<<" CfreqData:"<<ifs_cfreq.fail()<<endl;
    cerr<<"CfreqTXT: "<<wt<<endl;
    return 1;
  }
  else {
    getline(ifs_ifreq,lineI);
    ssI.str(lineI);
    ssI>>setprecision(10)>>omegaI>>DOSI;

    getline(ifs_cfreq,lineC);
    ssC.str(lineC);
    ssC>>setprecision(10)>>DPHI>>omegaC>>DOSC;

    while(getline(ifs,line)) {
      stringstream ss(line);
      ofs<<setprecision(10)<<ss.str()<<" "<<omegaC<<" "<<omegaI<<" "<<DOSI<<endl;
    }
  }
}
