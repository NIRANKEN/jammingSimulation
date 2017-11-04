#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>
#include <cstdio>
#include <iomanip>
#include "MT.h"
#include "jt.h"

using namespace std;

///////////////
//attention!!//
///////////////
//DMPtは速度比例の抵抗定数gammaに(Delta t)をかけたalphaの値(FIRE参照)。
//ここで使われているF,Ftmp,Fnextなどは力の次元ではなく、(力)x(Delta t)/(2m)となっている。

//----------------------------------------------------
//CG法を用いたgranular packingの構築(本体)------------
//----------------------------------------------------

int main(int argc,char* argv[])
{
  if(JT::errArguments_re(argc))
    return 1;

  //----------------------------------------------------
  //---Simulation of the Jamming Systemのパラメータ-----
  //----------------------------------------------------
  
  int sd_restart=atoi(argv[1]);//sd_sは乱数seedのreスタート値
  int sd_e=atoi(argv[2]);//sd_eは乱数seedループのend値
  DP PHIstart =atof(argv[3]),PHIrestart;//初期PHI
  DP TargetPHI =atof(argv[4]);//目的地PHI
  //!!下げの場合はunjammedで結局breakするので十分に低ければok
  DP DeltaPHIinit=atof(argv[5]);//PHIの上げ下げ刻み幅
  //-----------------
  int PNum;//=atoi(argv[6]);//粒子数
  int dim;//=atoi(argv[7]);//次元
  DP ratio;//=atof(argv[8]);//粒子のサイズ比1.0(要素1):ratio(要素2)
  int Pratio1;//=atoi(argv[9]);//粒子の混合比 Pratio(半径R):1(半径R*ratio)
  int Pratio2;//=atoi(argv[10]);//粒子の混合比 Pratio(半径R):1(半径R*ratio)
  double Leng;// box-length
  
  string strdate="0524"; //DATE
  const DP ftol=numeric_limits<double>::epsilon();
  
  ifstream BIdata,zahyodata;
  stringstream ss_BI;
  ss_BI<<"BIPhiEngVV"<<strdate<<"_RAND"<<sd_restart<<"_"<<PHIstart<<".txt";
  BIdata.open(ss_BI.str().data());
  string line;
  const int Ndata=5,Nzahyo=10;//if 2D=>Nzahyo=9　でもboxならこのままでok
  double DeltaPHIre;
  double *data;
  data= new double[Nzahyo];
  
  //determine initial PHI...
  while(getline(BIdata,line)) {
    DeltaPHIre=data[0];
    stringstream ss_BI2(line);
    for(int i=0;i<Ndata;i++) {
      ss_BI2>>setprecision(10)>>data[i];      
    }
  }
  BIdata.close();
  ss_BI.str("");
  ss_BI.clear(stringstream::goodbit);

  //-------------------------------------------//

  //-----
  DP pot,Rad,PHI,DeltaPHI,CRadBI;//potential energy
  const DP alpha =2.0;//potential exponent
  Vec_DP distcod(20);//接触数分布
  stringstream ss,ss2,ss3,sserr,ss_simerr;
  ofstream kakikoPHIJ,kakikoSingle,kakikoCODDIST,kakikoJCBERR,kakikoSIMERR;
  int cnter=0;//sample-counter
  const DP eps=1.0; //potentialのオーダー

  if(fabs(data[1])<ftol) {
    cerr<<"Seed Number you select is invalid(maybe you have already selected finished one.)"<<endl;
    delete data;
    exit(1);
  }
  PHIrestart=data[0];
  DeltaPHIre=PHIrestart-DeltaPHIre;
   
  ss_BI<<setprecision(10)<<"QtOutputZahyo"<<sd_restart<<"_"<<PHIrestart<<".txt";
  zahyodata.open(ss_BI.str().data());
  if(!zahyodata) {
    cerr<<"Cannot open Zahyodata \\></ "<<endl;
    exit(1);
  }
  getline(zahyodata,line);
  stringstream ss_BI2(line);
  for(int i=0;i<Nzahyo;i++) {
    ss_BI2>>setprecision(10)>>data[i];
  }
  //imagined 3D, but 2D is also ok
  dim=(int)data[0];
  PNum=(int)data[1];
  //Rad=data[2];
  ratio=data[4];
  Pratio1=data[5];
  Pratio2=data[6];
  Leng=data[7];

  PHIrestart+=DeltaPHIre;//充填率を一個分変化させた状態からリスタートする.
  cout<<PHIrestart<<"の充填率から"<<DeltaPHIre<<"の刻み幅でリスタートします."<<endl;
  PHI=PHIrestart;//data[3];

  //-------------------------------------------
  //----------------MDパラメータ---------------
  //-------------------------------------------
  //!(ratio)が異なる場合,2番目のmassは(MASS*ratio)になる.
  //!同じ球形でmassが異なる構成要素については,この場で考えてない.
  //!BIdisperseの場合のmassは各々のroutineでmass処理している.
  //!ここを変える場合はHessian matrixやMDfuncも変えねばならない.
  //kb=1.38064852*1.0e-23;
  DP Tstep=1.0e-2;
  const DP MASS=1.0,fftol=ftol*1.0e-3;
  const int DNum=PNum*dim;//Configurational Dimension Number
  Vec_DP zahyo(DNum),zahyotmp(DNum);
  Vec_DP sokudo(DNum);
  NRVec<vector<int> > contactList=NRVec<vector<int> >(PNum);
  bool pluseig=true,invalidflag,iprerror,isInit;//scheduling var
  int notrelaxeig=0,VViter,loopcnt=0;//scheduling var
  int inputzahyoCnt=0;
  //-------------------------------------------
  //--------------FIREパラメータ---------------
  //-------------------------------------------
  const DP fra_inc=1.1,fra_dec=0.5,fra_alp=0.99,dmpt_init=1.0e-1;
  DP DMPt,tstep_max,n_strength;
  int ITFIRE,relaxation_times;
  const int iter_times=1000000*pow(2,((int)(PNum/64)));//MDのステップ回数上限.
  //DMPt = (damping factor)*(delta t) 


    
  //zahyo代入.    
  while(getline(zahyodata,line)) {
    ss_BI2.clear(stringstream::goodbit);
    ss_BI2.str(line);
    for(int i=0;i<dim;i++) {
      ss_BI2>>setprecision(10)>>data[i];
      zahyotmp[dim*inputzahyoCnt+i]=zahyo[dim*inputzahyoCnt+i]=data[i];
    }
    inputzahyoCnt++;
  }
  if(inputzahyoCnt!=PNum) {
    cerr<<"座標の代入に失敗."<<endl;
    exit(1);
  }
  delete data;
  

  //CRadBIは半径更新のための定数
  //fftolはunjammed stateを評価するための値(pot~0と見なす.)
  //

  if(JT::errPN(PNum) || JT::errDim(dim) || JT::errPratio(Pratio1,Pratio2,PNum))
    return 1;
  JT::startingMessage(sd_restart,sd_e,PHIstart,TargetPHI,DeltaPHIinit);
  ss2<<"VV"<<strdate<<"_R"<<sd_restart<<"to"<<sd_e<<"_PNum"<<PNum<<"_alpha"<<alpha<<'_'<<PHIstart<<".txt";//1個だけ採取版
  kakikoPHIJ.open(ss2.str().data());
  
 
  //
  //////////////////////////////////////////////
  ///////////////     本体     /////////////////
  //////////////////////////////////////////////
  if(dim==2)//2D method
    {
      for(int l=sd_restart;l<sd_e;l++)//sample loop
	{
	  //Initialize FIRE parameter
	  //JT::InitializeSimulationparameter(PHI,PHIstart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad,isInit);

	  if(l==sd_restart) {
	    JT::InitializeSimulationparameter(PHI,PHIrestart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad,isInit,relaxation_times);
	    JT::setOFSsingle_re(kakikoSingle,strdate,l,PHIstart);
	    JT::InitializeFIREparameter(Tstep,DMPt,tstep_max,DeltaPHI,DeltaPHIre,n_strength,ITFIRE);
	  }
	  else {
	    JT::InitializeSimulationparameter(PHI,PHIstart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad,isInit,relaxation_times);
	    JT::setOFSsingle(kakikoSingle,strdate,l,PHIstart);
	    JT::InitializeFIREparameter(Tstep,DMPt,tstep_max,DeltaPHI,DeltaPHIinit,n_strength,ITFIRE);
	    MT::init_genrand(l);
	    for(int i=0;i<DNum;i++)
	      zahyotmp[i]=zahyo[i]=MT::genrand_real1()*Leng;
	  }
	  
	  
	  for(int i=0;i<99999;i++)//PHI loop
	    {
	      JT::ReRelaxation(VViter,n_strength,loopcnt,iter_times);
	      JT::noise(zahyo,Rad,Leng,n_strength);
	      JT::dim2::fastVVF2D(zahyo,sokudo,DMPt,MASS,Tstep,JT::dim2::fastPot2D,ftol,Leng,Leng,Rad,ratio,alpha,eps,Pratio1,Pratio2,l,PHI,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,dim,VViter,contactList,isInit);//
	      pot=JT::dim2::fastPot2D(zahyo,Leng,Rad,ratio,alpha,Pratio1,Pratio2,dim,eps,contactList);//
	      relaxation_times+=VViter;
	      if(loopcnt>0)
	        JT::loopErrWrite(sserr,l,i,PHI,pot,ftol,relaxation_times,n_strength);
	      
	      if(pot<fftol && fabs(DeltaPHI)>1.0e-6)
		//一個前の座標とPHIに戻す
		JT::dim2::backtoPreviousPHI2D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,tstep_max,loopcnt,dim,relaxation_times);
	      else
		{
		  if(pot<fftol) {
		    JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    JT::dim2::fastDCod2D(zahyo,distcod,Rad,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);//
		    for(int i=0;i<20;i+=1)
		      kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		    JT::dim2::OutputForQt(zahyo,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    break;
		  }
		  JT::dim2::fastMC2D(zahyo,Leng,Leng,Rad,ratio,alpha,Pratio1,Pratio2,l,PHI,dim,pluseig,invalidflag,iprerror,contactList);//
		  /*
		    if(invalidflag==true) {
		    JT::jacobiErrWrite(sserr,kakikoJCBERR,l,i,PHI,pot,ftol,VViter);
		    break;
		    }
		  */
		  if(pluseig==true && iprerror==false && invalidflag==false) { //modify!
		    JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    JT::dim2::fastDCod2D(zahyo,distcod,Rad,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);//
		    for(int i=0;i<20;i+=1)
		      kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		    JT::dim2::OutputForQt(zahyo,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    if(DeltaPHI==0.0)
		      break;
		    JT::dim2::forwardtoPHI2D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,loopcnt,dim,relaxation_times);
		  }
		  else {
		    //負の固有値が出てきたのでノイズかけてもういっかい.
		    /*
		      if(pluseig==true && iprerror==true)
		      JT::OutputForQt(zahyo,dim,PNum,PHI,ratio,Pratio,l);
		    */
		    if(invalidflag==true) {
		      JT::jacobiErrWrite(sserr,kakikoJCBERR,l,i,PHI,pot,ftol,relaxation_times);
		    }
		    if(loopcnt>=25 && loopcnt<30) {
		      JT::simErrWrite(ss_simerr,kakikoSIMERR,zahyo,dim,PNum,PHI,ratio,Pratio1,Pratio2,l,loopcnt,pot,relaxation_times,pluseig,iprerror,invalidflag);
		    }
		    if(loopcnt==30) {
		      break;
		    }
		    loopcnt+=1;
		  }
		}
	    }//PHI-loop-end
	  kakikoSingle.close();
	  kakikoPHIJ<<setprecision(10)<<l<<' '<<PHI<<' '<<notrelaxeig<<endl;
	  cnter+=1;
	  cout<<cnter<<"回目のRAND"<<l<<"の反復操作が終了しました\n"<<endl;
	}
      kakikoPHIJ.close();
    }
  else if(dim==3)//3D method
    {
      for(int l=sd_restart;l<sd_e;l++)
	{

	  if(l==sd_restart) {
	    JT::InitializeSimulationparameter(PHI,PHIrestart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad,isInit,relaxation_times);
	    JT::setOFSsingle_re(kakikoSingle,strdate,l,PHIstart);
	    JT::InitializeFIREparameter(Tstep,DMPt,tstep_max,DeltaPHI,DeltaPHIre,n_strength,ITFIRE);
	  }
	  else {
	    JT::InitializeSimulationparameter(PHI,PHIstart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad,isInit,relaxation_times);
	    JT::setOFSsingle(kakikoSingle,strdate,l,PHIstart);
	    JT::InitializeFIREparameter(Tstep,DMPt,tstep_max,DeltaPHI,DeltaPHIinit,n_strength,ITFIRE);
	    MT::init_genrand(l);
	    for(int i=0;i<DNum;i++)
	      zahyotmp[i]=zahyo[i]=MT::genrand_real1()*Leng;
	  }
	  //JT::InitializeSimulationparameter(PHI,PHIstart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad,isInit);
	  //JT::InitializeFIREparameter(Tstep,DMPt,tstep_max,DeltaPHI,DeltaPHIinit,n_strength,ITFIRE);
	  //JT::setOFSsingle(kakikoSingle,strdate,l,PHIstart);
	  // MT::init_genrand(l);
	  // for(int i=0;i<DNum;i++)
	  //   zahyotmp[i]=zahyo[i]=MT::genrand_real1()*Leng;
	  
	  for(int i=0;i<99999;i++)//99999はテキトー.
	    {
	      JT::ReRelaxation(VViter,n_strength,loopcnt,iter_times);
	      JT::noise(zahyo,Rad,Leng,n_strength);
	      JT::dim3::fastVVF3D(zahyo,sokudo,DMPt,MASS,Tstep,JT::dim3::fastPot3D,ftol,Leng,Leng,Leng,Rad,ratio,alpha,eps,Pratio1,Pratio2,l,PHI,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,dim,VViter,contactList,isInit);//
	      pot=JT::dim3::fastPot3D(zahyo,Leng,Rad,ratio,alpha,Pratio1,Pratio2,dim,eps,contactList);//
	      relaxation_times+=VViter;
	      if(loopcnt>0)
		JT::loopErrWrite(sserr,l,i,PHI,pot,ftol,VViter,n_strength);
	      if(pot<fftol && fabs(DeltaPHI)>1.0e-6)
		//一個前の座標とPHIに戻す
		JT::dim3::backtoPreviousPHI3D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,tstep_max,loopcnt,dim,relaxation_times);
	      else
		{
		  if(pot<fftol) {
		    JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    //JT::dim3::modifyContactList_test(contactList,zahyo,Leng,Leng,Leng,Rad,ratio,Pratio1,Pratio2,dim,99999);
		    JT::dim3::fastDCod3D(zahyo,distcod,Rad,Leng,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);//
		    for(int i=0;i<20;i+=1)
		      kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		    JT::dim3::OutputForQt(zahyo,Leng,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    break;
		  }
		  JT::dim3::fastMC3D(zahyo,Leng,Leng,Leng,Rad,ratio,alpha,Pratio1,Pratio2,l,PHI,dim,pluseig,invalidflag,iprerror,contactList);//
		  if(pluseig==true && iprerror==false && invalidflag==false) {
		    JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    JT::dim3::fastDCod3D(zahyo,distcod,Rad,Leng,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);
		    for(int i=0;i<20;i+=1)
		      kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		    JT::dim3::OutputForQt(zahyo,Leng,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    if(DeltaPHI==0.0)
		      break;
		    JT::dim3::forwardtoPHI3D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,loopcnt,dim,relaxation_times);
		  }
		  else {
		    if(invalidflag==true) {
		      JT::jacobiErrWrite(sserr,kakikoJCBERR,l,i,PHI,pot,ftol,relaxation_times);
		    }
		    if(loopcnt>=25 && loopcnt<30) {
		      JT::simErrWrite(ss_simerr,kakikoSIMERR,zahyo,dim,PNum,PHI,ratio,Pratio1,Pratio2,l,loopcnt,pot,relaxation_times,pluseig,iprerror,invalidflag);
		    }
		    if(loopcnt==30) {
		      break;
		    }
		    loopcnt+=1;
		  }
		}
	    }//phi-loop-end
	  kakikoSingle.close();
	  kakikoPHIJ<<setprecision(10)<<l<<' '<<PHI<<' '<<notrelaxeig<<endl;
	  cnter+=1;
	  cout<<cnter<<"回目のRAND"<<l<<"の反復操作が終了しました\n"<<endl;
      	}
      kakikoPHIJ.close();
    }
  else {
    cerr<<"Cannot calculate except for 2D and 3D systems!!\n\n"<<endl;
    exit(1);
  }
  JT::showCL(contactList,dim);
  return 0;
}
