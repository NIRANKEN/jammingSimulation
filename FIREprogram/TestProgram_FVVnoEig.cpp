#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>
#include <cstdio>
#include "MT.h"
#include "jt.h"

using namespace std;

///////////////
//attention!!//
///////////////

//noEigは1.0e-5がDPHIのthresholdである(1.0e-6ではない.)

//DMPtは速度比例の抵抗定数gammaに(Delta t)をかけたalphaの値(FIRE参照)。
//ここで使われているF,Ftmp,Fnextなどは力の次元ではなく、(力)x(Delta t)/(2m)となっている。

//----------------------------------------------------
//CG法を用いたgranular packingの構築(本体)------------
//----------------------------------------------------

int main(int argc,char* argv[])
{
  if(JT::errArguments(argc))
    return 1;

  //----------------------------------------------------
  //---Simulation of the Jamming Systemのパラメータ-----
  //----------------------------------------------------
  
  int sd_s=atoi(argv[1]);//sd_sは乱数seedのスタート値
  int sd_e=atoi(argv[2]);//sd_eは乱数seedループのend値
  DP PHIstart =atof(argv[3]);//初期PHI
  DP TargetPHI =atof(argv[4]);//目的地PHI
  //!!下げの場合はunjammedで結局breakするので十分に低ければok
  DP DeltaPHIinit=atof(argv[5]);//PHIの上げ下げ刻み幅
  const int PNum=atoi(argv[6]);//粒子数
  const int dim=atoi(argv[7]);//次元
  const DP ratio=atof(argv[8]);//粒子のサイズ比1.0(要素1):ratio(要素2)
  const int Pratio1=atoi(argv[9]);//粒子の混合比 Pratio(半径R):1(半径R*ratio)
  const int Pratio2=atoi(argv[10]);//粒子の混合比 Pratio(半径R):1(半径R*ratio)
  //-------------------------------------------//
  //-----------Box size 可変スタイル-----------//
  double Lr;//Leng ratio (N128 as standard size)
  if(dim==2) {
    Lr=(1.0e+2)*sqrt(PNum/128.0); // Leng変更してシミュレーション.
  }
  else if(dim==3) {
    Lr=(1.0e+2)*pow(PNum/128.0,0.3333333333333333); // Leng変更してシミュレーション.
  }
  else {
    cerr<<"invalid dimension case...(must be 2 or 3) yours:"<<dim<<endl;
    exit(1);
  }
  const DP Leng=Lr;//立方体の一辺の長さ
  //-------------------------------------------//

  
  string strdate="0524"; //DATE
  const DP ftol=numeric_limits<double>::epsilon()*1e+4;
  
  DP pot,Rad,PHI,CRadBI,DeltaPHI;//potential energy
  const DP alpha =2.0;//potential exponent
  Vec_DP distcod(20);//接触数分布
  stringstream ss,ss2,ss3,sserr,ss_simerr;
  ofstream kakikoPHIJ,kakikoSingle,kakikoCODDIST,kakikoJCBERR,kakikoSIMERR;
  int cnter=0;//sample-counter
  
  const DP eps=1.0; //potentialのオーダー
  if(JT::errPN(PNum) || JT::errDim(dim) || JT::errPratio(Pratio1,Pratio2,PNum))
    return 1;
  JT::startingMessage(sd_s,sd_e,PHIstart,TargetPHI,DeltaPHIinit);
  ss2<<"VV"<<strdate<<"_R"<<sd_s<<"to"<<sd_e<<"_PNum"<<PNum<<"_alpha"<<alpha<<'_'<<PHIstart<<".txt";
  kakikoPHIJ.open(ss2.str().data());
  
  

  //-------------------------------------------
  //----------------MDパラメータ---------------
  //-------------------------------------------
  //!(ratio)が異なる場合,2番目のmassは(MASS*ratio)になる.
  //!同じ球形でmassが異なる構成要素については,この場で考えてない.
  //!BIdisperseの場合のmassは各々のroutineでmass処理している.
  //!ここを変える場合はHessian matrixやMDfuncも変えねばならない.
  //kb=1.38064852*1.0e-23;
  DP Tstep=1.0e-2;
  const DP MASS=1.0,fftol=numeric_limits<double>::epsilon()*1.0e-3;
  const int DNum=PNum*dim;//Configurational Dimension Number
  Vec_DP zahyo(DNum),zahyotmp(DNum),sokudo(DNum);
  NRVec<vector<int> > contactList=NRVec<vector<int> >(PNum);
  bool pluseig=true,invalidflag,iprerror,isInit;//scheduling var
  int notrelaxeig=0,VViter,loopcnt=0;//scheduling var

  //CRadBIは半径更新のための定数
  //fftolはunjammed stateを評価するための値(pot~0と見なす.)
  //

  //-------------------------------------------
  //--------------FIREパラメータ---------------
  //-------------------------------------------
  const DP fra_inc=1.1,fra_dec=0.5,fra_alp=0.99,dmpt_init=1.0e-1;
  DP DMPt,tstep_max,n_strength;
  int ITFIRE,relaxation_times;
  int itt=numeric_limits<int>::max();
  // if(PNum<=128) {
  //   itt=300000;
  // }
  // else if(PNum>128 && PNum<=pow(2,19)) {
  //   itt=400000*(int)(PNum/128);
  // }
  // else {
  //   itt=numeric_limits<int>::max();
  // }
  const int iter_times=itt;//MDのステップ回数上限.
  // INT_MAX: 2,147,483,647
  //DMPt = (damping factor)*(delta t) 

  //
  //////////////////////////////////////////////
  ///////////////     本体     /////////////////
  //////////////////////////////////////////////
  if(dim==2)//2D method
    {
      for(int l=sd_s;l<sd_e;l++)//sample loop
	{
	  //Initialize FIRE parameter
	  JT::InitializeSimulationparameter(PHI,PHIstart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad,isInit,relaxation_times);
	  JT::InitializeFIREparameter(Tstep,DMPt,tstep_max,DeltaPHI,DeltaPHIinit,n_strength,ITFIRE);
	  JT::setOFSsingle(kakikoSingle,strdate,l,PHIstart);
	  MT::init_genrand(l);
	  for(int i=0;i<DNum;i++)
	    zahyotmp[i]=zahyo[i]=MT::genrand_real1()*Leng;
      
	  for(int i=0;i<99999;i++)//PHI loop
	    {
	      JT::ReRelaxation(VViter,n_strength,loopcnt,iter_times);
	      //JT::noise(zahyo,Rad,Leng,n_strength);
	      cout<<"do FIRE calculation..."<<endl;	      
	      JT::dim2::fastVVF2D(zahyo,sokudo,DMPt,MASS,Tstep,JT::dim2::fastPot2D,ftol,Leng,Leng,Rad,ratio,alpha,eps,Pratio1,Pratio2,l,PHI,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,dim,VViter,contactList,isInit);//
	      pot=JT::dim2::fastPot2D(zahyo,Leng,Rad,ratio,alpha,Pratio1,Pratio2,dim,eps,contactList);//
	      relaxation_times+=VViter;
	      cout<<"PN:"<<PNum<<", sample:"<<l<<", PHI:"<<PHI<<", ENG;"<<pot<<", 緩和にかかった時間:"<<relaxation_times<<endl;	      
	      if(loopcnt>0)
	        JT::loopErrWrite(sserr,l,i,PHI,pot,ftol,relaxation_times,n_strength);
	      
	      if(pot<fftol && fabs(DeltaPHI)>1.0e-5) {
		//一個前の座標とPHIに戻す
		JT::dim2::backtoPreviousPHI2D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,tstep_max,loopcnt,dim,relaxation_times);
	      }
	      else
		{
		  if(pot<fftol) {
		    //JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    //JT::dim2::fastDCod2D(zahyo,distcod,Rad,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);//
		    //for(int i=0;i<20;i+=1)
		    //  kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    //kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		    JT::dim2::OutputForQt(zahyo,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    break;
		  }
		  else {
		    if(VViter != iter_times) {
		      //JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		      //JT::dim2::fastDCod2D(zahyo,distcod,Rad,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);//
		      //for(int i=0;i<20;i+=1)
			//kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		      //kakikoCODDIST.close();
		      kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		      JT::dim2::OutputForQt(zahyo,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		      if(DeltaPHI==0.0)
			break;
		      JT::dim2::forwardtoPHI2D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,loopcnt,dim,relaxation_times);
		    }
		    else {
		      // if(loopcnt>=25 && loopcnt<30) {
		      // 	JT::dim2::simErrWrite(ss_simerr,kakikoSIMERR,zahyo,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l,loopcnt,pot,relaxation_times,pluseig,iprerror,invalidflag);
		      // }
		      if(loopcnt==30) {
			break;
		      }
		      loopcnt+=1;
		    }
		  }
		  // JT::dim2::fastMC2D(zahyo,Leng,Leng,Rad,ratio,alpha,Pratio1,Pratio2,l,PHI,dim,pluseig,invalidflag,iprerror,contactList);//
		  // /*
		  // if(invalidflag==true) {
		  //   JT::jacobiErrWrite(sserr,kakikoJCBERR,l,i,PHI,pot,ftol,VViter);
		  //   break;
		  // }
		  // */
		  // if(pluseig==true && iprerror==false && invalidflag==false) { //modify!
		  //   JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		  //   JT::dim2::fastDCod2D(zahyo,distcod,Rad,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);//
		  //   for(int i=0;i<20;i+=1)
		  //     kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		  //   kakikoCODDIST.close();
		  //   kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		  //   JT::dim2::OutputForQt(zahyo,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		  //   if(DeltaPHI==0.0)
		  //     break;
		  //   JT::dim2::forwardtoPHI2D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,loopcnt,dim,relaxation_times);
		  // }
		  // else {
		  //   //負の固有値が出てきたのでノイズかけてもういっかい.
		  //   /*
		  //   if(pluseig==true && iprerror==true)
		  //     JT::OutputForQt(zahyo,dim,PNum,PHI,ratio,Pratio,l);
		  //   */
		  //   if(invalidflag==true) {
		  //     JT::jacobiErrWrite(sserr,kakikoJCBERR,l,i,PHI,pot,ftol,relaxation_times);
		  //   }
		  //   if(loopcnt>=25 && loopcnt<30) {
		  //     JT::dim2::simErrWrite(ss_simerr,kakikoSIMERR,zahyo,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l,loopcnt,pot,relaxation_times,pluseig,iprerror,invalidflag);
		  //   }
		  //   if(loopcnt==30) {
		  //     break;
		  //   }
		  //   loopcnt+=1;
		  // }
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
      for(int l=sd_s;l<sd_e;l++)
	{
	  //Initialize parameter
	  JT::InitializeSimulationparameter(PHI,PHIstart,pluseig,notrelaxeig,loopcnt,CRadBI,Leng,ratio,PNum,Pratio1,Pratio2,dim,Rad,isInit,relaxation_times);
	  JT::InitializeFIREparameter(Tstep,DMPt,tstep_max,DeltaPHI,DeltaPHIinit,n_strength,ITFIRE);
	  JT::setOFSsingle(kakikoSingle,strdate,l,PHIstart);
	  
	  MT::init_genrand(l);
	  for(int i=0;i<DNum;i++)
	    zahyotmp[i]=zahyo[i]=MT::genrand_real1()*Leng;
	  
	  for(int i=0;i<99999;i++)//99999はテキトー.
	    {
	      JT::ReRelaxation(VViter,n_strength,loopcnt,iter_times);
	      //JT::noise(zahyo,Rad,Leng,n_strength);
	      cout<<"===TEST==="<<endl;
	      cout<<DMPt<<", "<<MASS<<", "<<Tstep<<", "<<ftol<<", "<<Leng<<", "<<Leng<<", "<<Leng<<", "<<Rad<<", "<<ratio<<", "<<alpha<<", "<<eps<<", "<<Pratio1<<", "<<Pratio2<<", "<<l<<", "<<PHI<<", "<<fra_inc<<", "<<fra_dec<<", "<<fra_alp<<", "<<dmpt_init<<", "<<tstep_max<<", "<<ITFIRE<<", "<<dim<<", "<<VViter<<", "<<isInit<<endl;
	      cout<<"===TEST==="<<endl;
	      cout<<"do FIRE calculation..."<<endl;
	      JT::dim3::fastVVF3D(zahyo,sokudo,DMPt,MASS,Tstep,JT::dim3::fastPot3D,ftol,Leng,Leng,Leng,Rad,ratio,alpha,eps,Pratio1,Pratio2,l,PHI,fra_inc,fra_dec,fra_alp,dmpt_init,tstep_max,ITFIRE,dim,VViter,contactList,isInit);//
	      pot=JT::dim3::fastPot3D(zahyo,Leng,Rad,ratio,alpha,Pratio1,Pratio2,dim,eps,contactList);//
	      relaxation_times+=VViter;
	      cout<<"PN:"<<PNum<<", sample:"<<l<<", PHI:"<<PHI<<", ENG;"<<pot<<", 緩和にかかった時間:"<<relaxation_times<<endl;
	      if(loopcnt>0)
		JT::loopErrWrite(sserr,l,i,PHI,pot,ftol,relaxation_times,n_strength);
	      if(pot<fftol && fabs(DeltaPHI)>1.0e-5) {
		//一個前の座標とPHIに戻す
		JT::dim3::backtoPreviousPHI3D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,tstep_max,loopcnt,dim,relaxation_times);
	      }
	      else
		{
		  if(pot<fftol) {
		    //JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		    //JT::dim3::modifyContactList_test(contactList,zahyo,Leng,Leng,Leng,Rad,ratio,Pratio1,Pratio2,dim,99999);
		    //JT::dim3::fastDCod3D(zahyo,distcod,Rad,Leng,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);//
		    //for(int i=0;i<20;i+=1)
		    //  kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		    //kakikoCODDIST.close();
		    kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		    JT::dim3::OutputForQt(zahyo,Leng,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		    break;
		  }
		  else {
		    if(VViter != iter_times) {
		      //緩和していたら.
		      //JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		      //JT::dim3::fastDCod3D(zahyo,distcod,Rad,Leng,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);
		      //for(int i=0;i<20;i+=1)
			//kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		      //kakikoCODDIST.close();
		      kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		      JT::dim3::OutputForQt(zahyo,Leng,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		      if(DeltaPHI==0.0)
			break;
		      JT::dim3::forwardtoPHI3D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,loopcnt,dim,relaxation_times);
		    }
		    else {
		      //緩和してない判定の場合.
		      if(loopcnt>=25 && loopcnt<30) {
			// JT::dim3::simErrWrite(ss_simerr,kakikoSIMERR,zahyo,Leng,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l,loopcnt,pot,relaxation_times,pluseig,iprerror,invalidflag);
		      }
		      if(loopcnt==30) {
			break;
		      }
		      loopcnt+=1;
		    }
		  }

		  // JT::dim3::fastMC3D(zahyo,Leng,Leng,Leng,Rad,ratio,alpha,Pratio1,Pratio2,l,PHI,dim,pluseig,invalidflag,iprerror,contactList);//
		  // if(pluseig==true && iprerror==false && invalidflag==false) {
		  //   JT::setOFScoddist(kakikoCODDIST,strdate,l,PHI);
		  //   JT::dim3::fastDCod3D(zahyo,distcod,Rad,Leng,Leng,Leng,ratio,Pratio1,Pratio2,dim,contactList);
		  //   for(int i=0;i<20;i+=1)
		  //     kakikoCODDIST<<i<<' '<<distcod[i]<<endl;
		  //   kakikoCODDIST.close();
		  //   kakikoSingle<<setprecision(10)<<PHI<<' '<<pot<<' '<<ftol<<' '<<relaxation_times<<' '<<(int)pluseig<<endl;
		  //   JT::dim3::OutputForQt(zahyo,Leng,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l);
		  //   if(DeltaPHI==0.0)
		  //     break;
		  //   JT::dim3::forwardtoPHI3D(zahyo,zahyotmp,PHI,DeltaPHI,Rad,CRadBI,loopcnt,dim,relaxation_times);
		  // }
		  // else {
		  //   if(invalidflag==true) {
		  //     JT::jacobiErrWrite(sserr,kakikoJCBERR,l,i,PHI,pot,ftol,relaxation_times);
		  //   }
		  //   if(loopcnt>=25 && loopcnt<30) {
		  //     JT::dim3::simErrWrite(ss_simerr,kakikoSIMERR,zahyo,Leng,Leng,Leng,dim,PNum,Rad,PHI,ratio,Pratio1,Pratio2,l,loopcnt,pot,relaxation_times,pluseig,iprerror,invalidflag);
		  //   }
		  //   if(loopcnt==30) {
		  //     break;
		  //   }
		  //   loopcnt+=1;
		  // }
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
