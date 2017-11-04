#ifndef __BIN_H
#define __BIN_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace binstat
{
  void InputStr(string &a,string &b,string &c,string &d);
  void InputBINrange(double &br);
  void ZeroEigenValprocess(double S,double E,double M,int zeroeig,double allC,ofstream &ofs,int N);
  void innerBINprocess(double c,double S,double E,double M,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc,double allC,ofstream &ofs,int cnt,double cum,int cumcnt,int N);
  void updateBINprocess(double a,double c,double &S,double &E,double &M,double &Sln10,double &Mln10,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc,double allC,double range,ofstream &ofs,int cnt,double cum,int cumcnt,int N);
  void initializeBINrange(double &Sinit,double &S,double &E,double &M,double &Sln10,double &Mln10);
  void updateBINrange(double &S,double &E,double &M,double &Sln10,double &Mln10,double range);
  void InitializeIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc);
  void ModifyIPRparameter(double c,double &sumc,double &minc,double &maxc,int &tmpC,double &sgmc);
  
}







#endif
