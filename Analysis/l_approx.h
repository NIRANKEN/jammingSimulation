#ifndef _L_APPROX_
#define _L_APPROX_

#include <vector>

using namespace std;

struct DOSset
{
  double omega;
  double dos;
  bool validData;
};
struct DOSfitter
{
  vector<DOSset> Dset;
  int enableAddomega;
  int rangeLength;
  bool addedDiscontinuousPlot;
};
struct binset
{
  double begin;
  double middle;
  double end;
  double range_m;
  double range_e;
};

void insertDOSData(vector<DOSset> &v, double o,double d,bool b)
{
  DOSset ds;
  ds.omega=o;
  ds.dos=d;
  ds.validData=b;
  v.push_back(ds);

  return;
}
void insertLineData(vector<DOSfitter> &v,vector<DOSset> ds,int en,int l)
{
  en=0;
  if(l==1) {
    DOSfitter df={ds,en,l,false};
    v.push_back(df);
  }
  else {
    DOSfitter df={ds,en,l,true};
    v.push_back(df);
  }
  return;
}
void modifyDOSfitter(vector <DOSfitter> &v,int num,double o,double d,bool b,int haba)
{
  insertDOSData(v[num].Dset,o,d,b);
  v[num].enableAddomega=0;
  v[num].rangeLength+=haba;
  if(haba>1)
    v[num].addedDiscontinuousPlot=true;
  return;
}


#endif
