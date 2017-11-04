#ifndef FIREVV3D_H
#define FIREVV3D_H

#include "nr.h"
#include <QtCore>
#include <QObject>

class FIREVV3D : public QObject
{
  Q_OBJECT
 public:
  explicit FIREVV3D(QObject *parent=0);
  ~FIREVV3D();


  void set_Seed(int s) {
    seed=s;
  }
  void set_Zahyo(Vec_I_DP &p) {
    zahyo=p;
  }
  void set_SizeRatio(double rt) {
    ratio=rt;
  }
  void set_PackingFraction(double phi) {
    PHI=phi;
  }
  void set_Radii(double R) {
    Rad=R;
  }
  void set_Lengx(double lngx) {
    Leng_x=lngx;
  }
  void set_Lengy(double lngy) {
    Leng_y=lngy;
  }
  void set_Lengz(double lngz) {
    Leng_z=lngz;
  }
  void set_ParticleNum(int N) {
    PN=N;
    set_MaximumEigVecComponent(Vec_DP(0.0,3*N));
    set_ParticipatingParticles(Vec_INT(0,3*N));
    set_EigMatrix(Mat_DP(0.0,3*N,3*N));
    set_EigValue(Vec_DP(0.0,3*N));
  }
  void set_ParticleRatio1(int Pratio1) {
    Prt1=Pratio1;
  }
  void set_ParticleRatio2(int Pratio2) {
    Prt2=Pratio2;
  }
  void set_EigMatrix(Mat_I_DP &Em) {
    qDebug()<<"Set eigmat."<<endl;
    E_mat=Em;
  }
  void set_EigValue(Vec_I_DP &Ev) {
    qDebug()<<"Set eigvec."<<endl;
    E_val=Ev;
  }
  void set_EigNum(int num) {
    if(num>=0 && num<3*PN && eigmode) {
      E_num=num;
      emit changedEigenNumber();
    }
    else
      qDebug()<<"Cannot display the EigenVec..."<<endl;
  }
  void set_CalculatedEigMode(bool b) {
    qDebug()<<"CalculatedEigMode was changed."<<endl;
    eigmode=b;
  }
  void set_ParticipatingParticles(Vec_INT evec) {
    for(int i=0;i<evec.size();i++)
      qDebug()<<"the number of the participating particles :"<<evec[i]<<endl;
    eigN=evec;
  }
  void set_ParticipatingParticles(int I,int num) {
      if(num<0 || num>=eigN.size()) {
          qDebug()<<"ERROR of set_ParticipatingParticles - method..."<<endl;
          exit(1);
      }
    eigN[num]=I;
  }

  void set_MaximumEigVecComponent(Vec_DP vec) {
    int N=vec.size();
    for(int i=0;i<N;i++)
    qDebug()<<i<<"-th mode's maximumcomponent of eigvec is :"<<vec[i]<<endl;
    eigmax=vec;
  }
  void set_MaximumEigVecComponent(DP d,int num) {
    int N=eigmax.size();
    if(num<0 || num>=N) {
        qDebug()<<"ERROR of set_MaximumEigVecComponent - method..."<<endl;
        exit(1);
    }
    eigmax[num]=d;
  }
  void set_EigNum_threshold(DP d) {
    eigN_threshold=d;
  }

  int show_seedNum(){return seed;}
  Vec_DP show_Zahyo(){return zahyo;}
  DP show_SizeRatio(){return ratio;}
  DP show_PackingFraction(){return PHI;}
  DP show_Radii(){return Rad;}
  DP show_Lengx(){return Leng_x;}
  DP show_Lengy(){return Leng_y;}
  DP show_Lengz(){return Leng_z;}
  int show_ParticleNum(){return PN;}
  int show_ParticleRatio1(){return Prt1;}
  int show_ParticleRatio2(){return Prt2;}

  Mat_DP show_EigMatrix(){return E_mat;}
  Vec_DP show_EigValue(){return E_val;}
  int show_EigNum(){return E_num;}
  bool show_CalculatedEigMode(){return eigmode;}
  Vec_INT show_ParticipatingParticles(){return eigN;}
  Vec_DP show_MaximumEigVecComponent(){return eigmax;}
  DP show_EigNum_threshold(){return eigN_threshold;}


  public slots:
    void inputZahyoData3D();
    void calculateEigData3D();

 signals:
    void getZahyo();
    void getEigenVector();
    void changedEigenNumber();


 private:
    int seed;
    Vec_DP zahyo;
    DP ratio;
    DP PHI;
    DP Rad;
    DP Leng_x;
    DP Leng_y;
    DP Leng_z;
    int PN;
    int Prt1;
    int Prt2;

    Mat_DP E_mat;
    Vec_DP E_val;
    int E_num; // displaying E_num th eigvec
    bool eigmode; // calculated EigInfo or not
    Vec_INT eigN; // the number of the particles for Eigvec
    Vec_DP eigmax;
    DP eigN_threshold;

};

#endif // FIREVV3D_H
