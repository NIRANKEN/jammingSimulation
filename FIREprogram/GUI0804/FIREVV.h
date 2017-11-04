#ifndef FIREVV_H_
#define FIREVV_H_


#include <QtCore>
#include <QtGui>
#include <QWidget>
#include "nr.h"
//#include "MT.h"
#include <vector>



class FIREVV : public QWidget
{
  Q_OBJECT

public:
  FIREVV(QWidget *parent =0);
  ~FIREVV();

protected:
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);



public:
  void RenewVar(Vec_DP &p,Vec_DP &v,Vec_DP &F,Vec_DP &Ftmp,DP r, DP phi, DP R,DP Lx,DP Ly, DP f,DP ftmp,DP alp,int N,int prt1,int prt2,DP dmpt,DP t,DP fra_inc,DP fra_dec,DP fra_alp,DP dmpt_init,DP t_max,int ITFIRE,int num,DP dist,Mat_DP &Em,Vec_DP &Ev,int En)
  {
    zahyo=p;
    vel=v;
    Force=F;
    Forcetmp=Ftmp;
    ratio=r;
    PHI=phi;
    Rad=R;
    Leng_x=Lx;
    Leng_y=Ly;
    func=f;
    functmp=ftmp;
    alpha=alp;
    PN=N;
    Pratio1=prt1;
    Pratio2=prt2;
    DMPt=dmpt;
    Tstep=t;
    paintcnt=0;
    fra_I=fra_inc;
    fra_D=fra_dec;
    fra_A=fra_alp;
    DMPt_I=dmpt_init;
    Tstep_M=t_max;
    ITER_FIRE=ITFIRE;
    openum=num;
    opedist=dist;
    E_mat=Em;
    E_val=Ev;
    eignum=En;
    cL=NRVec<vector<int> >(N);
    pC=false;
    Nc=0;
    MDcount=0;
  }


  void Gen_zahyo(int N);
  void Gen_zahyo(int seed,int N);
  void Gen_zahyo_sq(int N);
  void Gen_zahyo_cry(int N,DP Lx);
  void Gen_PHI(double phi,DP Len,int PNum);
  void Gen_PHI(double phi,DP Lx,DP Ly,int PNum);
  void Inc_PHI(double inc,int PNum);
  int Modenumber(bool plus);
  void Set_EIG(int num);
  void Normalize_EIG();
  inline void PaintWaku(QPainter &painter,DP Yx,DP Yy,DP Lx,DP Ly);
  inline void PaintWaku(QPainter *painter,DP Yx,DP Yy,DP Lx,DP Ly);
  inline void PaintParticles(QPainter &painter,DP Yx,DP Yy,DP &Radi,DP &Radj,int N);
  inline void PaintParticles(QPainter *painter,DP Yx,DP Yy,DP &Radi,DP &Radj,int N);
  void countEigMotion(Mat_I_DP &EigMat, Vec_IO_DP &v, Vec_IO_DP &vall);
  void Initialize_contactList(int N){cL=NRVec<vector<int> >(N);}
 
  void Set_zahyo(Vec_I_DP &p);
  void Set_vel(Vec_I_DP &v);
  void Set_Force(Vec_I_DP &F);
  void Set_Forcetmp(Vec_I_DP &Ftmp);
  void Set_ratio(double rt);
  void Set_PHI(double phi);
  void Set_Rad(double R);
  void Set_Lengx(double lngx);
  void Set_Lengy(double lngy);
  void Set_func(double f);
  void Set_functmp(double ftmp);
  void Set_alpha(double alp);
  void Set_PN(int N);
  void Set_Pratio1(int Pratio1);
  void Set_Pratio2(int Pratio2);
  void Set_DMPt(DP dmpt);
  void Set_Tstep(DP t);
  void Set_Pntcnt(int pntcnt);
  void Set_fraI(DP fra_inc);
  void Set_fraD(DP fra_dec);
  void Set_fraA(DP fra_alp);
  void Set_dmptI(DP dmpt_init);
  void Set_TstepM(DP tmax);
  void Set_ITFIRE(int ITFIRE);
  void Set_Openum(int num);
  void Set_Opedist(DP dist);
  void Set_Emat(Mat_I_DP &Em);
  void Set_Eval(Vec_I_DP &Ev);
  void Set_Enum(int num);
  void Set_contactList(NRVec<vector<int> > &v);
  void Set_attribute(Vec_I_INT &v);
  void Set_paintedCluster(bool b);
 
  Vec_DP Show_zahyo(){return zahyo;}
  Vec_DP Show_vel(){return vel;}
  Vec_DP Show_Force(){return Force;}
  Vec_DP Show_Forcetmp(){return Forcetmp;}
  DP Show_ratio(){return ratio;}
  DP Show_PHI(){return PHI;}
  DP Show_Rad(){return Rad;}
  DP Show_Lengx(){return Leng_x;}
  DP Show_Lengy(){return Leng_y;}
  DP Show_func(){return func;}
  DP Show_functmp(){return functmp;}
  DP Show_alpha(){return alpha;}
  int Show_PN(){return PN;}
  int Show_Pratio1(){return Pratio1;}
  int Show_Pratio2(){return Pratio2;}
  DP Show_DMPt(){return DMPt;}
  DP Show_Tstep(){return Tstep;}
  int Show_Pntcnt(){return paintcnt;}
  DP Show_fraI(){return fra_I;}
  DP Show_fraD(){return fra_D;}
  DP Show_fraA(){return fra_A;}
  DP Show_dmptI(){return DMPt_I;}
  DP Show_TstepM(){return Tstep_M;}
  int Show_ITFIRE(){return ITER_FIRE;}
  int Show_Openum(){return openum;}
  DP Show_Opedist(){return opedist;}
  Mat_DP Show_Emat(){return E_mat;}
  Vec_DP Show_Eval(){return E_val;}
  int Show_Enum(){return eignum;}
  NRVec<vector<int> > Show_contactList(){return cL;}
  Vec_INT Show_Attribute(){return attribute;}
  bool Show_paintedCluster(){return pC;}

  void inputZahyodata();
  void WriteEIGinfo(int num);
  void tsInput(QTextStream &ts,int i);
  void tsInput(QTextStream &ts,double d);

  inline void initializeSystemQuantity(int N);
  inline void initializeSystemQuantity_lattice(int N);

public slots:
  void VerletDO();
  //void VerletDO_endless();
  void Tapping();
  void Noise();
  void SoftAnalysis();
  void initializeParticleColor();

signals:
  void created();
  void VVfin();
  void minfunc();
  void GenInit();
  void PHIChanged();
  void M_varChanged();
  void EngChanged();
  void pluseig();
  void minuseig();
  void eNumchaged();


private:
  Vec_DP zahyo;
  Vec_DP vel;
  Vec_DP Force;
  Vec_DP Forcetmp;
  DP ratio;
  DP PHI;
  DP Rad;
  DP Leng_x;
  DP Leng_y;
  DP func;
  DP functmp;
  DP alpha;
  int PN;
  int Pratio1;
  int Pratio2;
  DP DMPt;
  DP Tstep;
  int paintcnt;
  DP fra_I;
  DP fra_D;
  DP fra_A;
  DP DMPt_I;
  DP Tstep_M;
  int ITER_FIRE;
  int openum;
  DP opedist;
  Mat_DP E_mat;
  Vec_DP E_val;
  int eignum;
  NRVec<vector<int> > cL;
  Vec_INT attribute;
  int Nc;
  bool pC;
  bool isModeCalculated;
  int MDcount;
};


#endif // FIREVV.h
