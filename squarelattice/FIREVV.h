#ifndef FIREVV_H_
#define FIREVV_H_


#include <QtCore>
#include <QtGui>
#include <QWidget>
#include "nr.h"
//#include "MT.h"
//#include <cmath>



class FIREVV : public QWidget
{
Q_OBJECT

 public:
 FIREVV(QWidget *parent =0);
 ~FIREVV();

 protected:
 void paintEvent(QPaintEvent*);
 void mousePressEvent(QMouseEvent*);
 void mouseMoveEvent(QMouseEvent*);
 void mouseReleaseEvent(QMouseEvent*);



public:
 void RenewVar(Vec_DP &p,Vec_DP &v,Vec_DP &F,Vec_DP &Ftmp,DP r, DP phi, DP R,DP L, DP f,DP ftmp,DP alp,int N,int prt,DP dmpt,DP t,DP fra_inc,DP fra_dec,DP fra_alp,DP dmpt_init,DP t_max,int ITFIRE,int num,DP dist)
 {
   zahyo=p;
   vel=v;
   Force=F;
   Forcetmp=Ftmp;
   ratio=r;
   PHI=phi;
   Rad=R;
   Leng=L;
   func=f;
   functmp=ftmp;
   alpha=alp;
   PN=N;
   Pratio=prt;
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

 }


 void Gen_zahyo(int seed,int N);
 void Gen_PHI(double phi,DP Len,DP rt,int PNum);
 void Inc_PHI(double inc,DP Len,DP rt,int PNum);
 int Modenumber();

 void Set_zahyo(Vec_DP p);
void Set_vel(Vec_DP);
void Set_Force(Vec_DP);
void Set_Forcetmp(Vec_DP);
 void Set_ratio(double rt);
 void Set_PHI(double phi);
 void Set_Rad(double R);
 void Set_Leng(double lng);
 void Set_func(double f);
 void Set_functmp(double ftmp);
 void Set_alpha(double alp);
 void Set_PN(int N);
 void Set_Pratio(int Pratio);
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
 
 Vec_DP Show_zahyo(){return zahyo;}
 Vec_DP Show_vel(){return vel;}
 Vec_DP Show_Force(){return Force;}
 Vec_DP Show_Forcetmp(){return Forcetmp;}
 DP Show_ratio(){return ratio;}
 DP Show_PHI(){return PHI;}
 DP Show_Rad(){return Rad;}
 DP Show_Leng(){return Leng;}
 DP Show_func(){return func;}
 DP Show_functmp(){return functmp;}
 DP Show_alpha(){return alpha;}
 int Show_PN(){return PN;}
 int Show_Pratio(){return Pratio;}
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
 

public slots:
 void VerletDO();
 void Tapping();
 void Noise();

signals:
 void VVfin();
 void minfunc();
 void GenInit();
 void PHIChanged();
 void M_varChanged();
 void EngChanged();
 void pluseig();
 void minuseig();


 private:
 Vec_DP zahyo;
 Vec_DP vel;
 Vec_DP Force;
 Vec_DP Forcetmp;
 DP ratio;
 DP PHI;
 DP Rad;
 DP Leng;
 DP func;
 DP functmp;
 DP alpha;
 int PN;
 int Pratio;
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
};


#endif // FIREVV.h
