#ifndef __FIREVV__
#define __FIREVV__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "nr.h"

using namespace std;

class fParam // syoujiki private->public de yokunai????
{
 private:
  const double fra_inc;//=1.1,
  const double fra_dec;//=0.5,
  const double fra_alp;//=0.99,
  const double dmpt_init;//=1.0e-1;
  const int iter_times;//=2000000;//MDのステップ回数  
  double DMPt;
  double tstep_max;
  double n_strength;
  int ITFIRE;
  //DMPt = (damping factor)*(delta t) 
 public:
  void set_dmpt(double dmpt);
  void set_tMax(double tm);
  void set_noiseStr(double nstr);
  void set_iterFIRE(int iter);
  double inc();
  double dec();
  double inert();//alp nandakke?
  double dmpt_i();
  int itertimes();
  double dmpt();
  double tMax();
  double noiseStr();
  int iterFIRE();
}

class mdParam
{
 private:// syoujiki private->public de yokunai????

  //!(ratio)が異なる場合,2番目のmassは(MASS*ratio)になる.
  //!同じ球形でmassが異なる構成要素については,この場で考えてない.
  //!BIdisperseの場合のmassは各々のroutineでmass処理している.
  //!ここを変える場合はHessian matrixやMDfuncも変えねばならない.
  //kb=1.38064852*1.0e-23;
  double Tstep;//=1.0e-2;
  const double MASS;//=1.0,
  const double fftol;//=ftol*1.0e-3;
  const int DNum;//=PNum*dim;//Configurational Dimension Number  //md param??
  Vec_DP zahyo; //md param??
  Vec_DP zahyotmp; //md param??
  Vec_DP sokudo;
  NRVec<vector<int> > contactList=NRVec<vector<int> >;//(PNum); //md param??
  bool pluseig;//=true,
  bool invalidflag;
  bool iprerror;
  bool isInit;//scheduling var
  int notrelaxeig;//=0,
  int VViter;
  int loopcnt;//=0;//scheduling var

  //CRadBIは半径更新のための定数
  //fftolはunjammed stateを評価するための値(pot~0と見なす.)
  //

 public:
  void set_tstep(double t);
  void set_velRand();
  void set_velUniform();
  void set_vel(Vec_DP &v);
  void set_jacobiErr(bool b);
  void set_iprErr(bool b);
  void set_unEquib(bool b);
  

}





#endif
