#include "FIREVV3D.h"
#include <QFileDialog>
#include <QTextStream>
#include "jteig.h"

FIREVV3D::FIREVV3D(QObject *parent) : QObject(parent),seed(0),zahyo(0),ratio(1.4),PHI(1.0),Rad(1.0),Leng_x(100.0),Leng_y(100.0),Leng_z(100.0),PN(128),Prt1(1),Prt2(1),E_mat(0,0),E_val(0.0),E_num(0),eigmode(false),eigN(0),eigmax(0.0),eigN_threshold(0.0)
{
  //initial parameters
  int const N=128;
  Vec_DP z(3*N);

  for(int i=0;i<N;i++) {
    z[3*i]=0.0+0.5*i;
    z[3*i+1]=0.0+0.5*i;
    z[3*i+2]=0.0+0.5*i;
  }
  set_Zahyo(z);
  set_ParticleNum(N);
  set_Radii(3.0);
  set_Lengx(100.0);
  set_Lengy(100.0);
  set_Lengz(100.0);

}
FIREVV3D::~FIREVV3D()
{

}


void FIREVV3D::inputZahyoData3D() {
  QFileDialog testdialog;
  QString filename = QFileDialog::getOpenFileName(&testdialog,QFileDialog::tr("Open Text"), "~/", QFileDialog::tr("Text Files (*.txt *.csv)"));
  qDebug()<<filename<<endl;

  int d,prt1,prt2,N,cnt=0;
  double phi,rt,R,lx,ly,lz;
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QTextStream in(&file);
  QString line = in.readLine();
  QTextStream in2(&line);
  in2>>d>>N>>R>>phi>>rt>>prt1>>prt2>>lx>>ly>>lz;
  qDebug()<<d<<' '<<N<<' '<<R<<' '<<phi<<' '<<rt<<' '<<prt1<<' '<<prt2<<' '<<lx<<' '<<ly<<' '<<lz<<endl;
  if(d!=3) {
    qDebug()<<"Error!!"<<endl;
    exit(1);
  }
  else {
    Vec_DP z(d*N);
    while (!in.atEnd()) {
      line=in.readLine();
      qDebug()<<line<<endl;
      QTextStream in3(&line);
      if(3*cnt<d*N) {
	in3>>z[cnt*3]>>z[cnt*3+1]>>z[cnt*3+2];
	qDebug()<<z[cnt*3]<<' '<<z[cnt*3+1]<<' '<<z[cnt*3+2]<<endl;
	//z[cnt*3]*=Leng_x/(100.0*sqrt(N/128));//Qt no length scale ni change.
	//z[cnt*3+1]*=Leng_y/(100.0*sqrt(N/128));
	//z[cnt*3+2]*=Leng_z/(100.0*sqrt(N/128));
      }
      cnt+=1;
    }

    if(z.size()>0) {
      set_Zahyo(z);
      //bool relax;
      //Force=Forcetmp=vel=zahyo=z;
      //Force=Forcetmp=vel=0.0;
      //JT::dim2::VVforce_F(zahyo,vel,Force,Forcetmp,DMPt,1.0,Tstep,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,relax);
      //Forcetmp=Force;
      //func=functmp=JT::dim2::potential(zahyo,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,1.0);
    }
    set_ParticleNum(N);
    set_Radii(R);
    set_PackingFraction(phi);
    set_SizeRatio(rt);
    set_ParticleRatio1(prt1);
    set_ParticleRatio2(prt2);
    set_Lengx(lx);
    set_Lengy(ly);
    set_Lengz(lz);
    set_CalculatedEigMode(false);
    //Gen_PHI(phi,Leng_x,Leng_y,rt,N);
    emit getZahyo();

  }


}

void FIREVV3D::calculateEigData3D() {

  bool eigplus=true,jacobi,ipr;
  int N=zahyo.size(),n;
  Mat_DP Hes(N,N),EigMat(N,N);
  Vec_DP Eigval(N),Eigvec(N);
  int cnt=0;
  DP EPS=numeric_limits<double>::epsilon(),halfm,eps=1.0;
  double sq,max;
  bool invalidflag=false;
  JT::dim3::Hesspot3D(zahyo,Hes,Leng_x,Rad,ratio,2.0,Prt1,Prt2,3,eps);
  NR::jacobi(Hes,Eigval,EigMat,cnt,invalidflag);
  if(invalidflag==true)
    return;
  if(ratio!=1.0) {
    //BIdisperseのときは本来の固有ベクターに変換しなければならない。
    halfm=1.0/sqrt(ratio*ratio*ratio);
    for(int i=0;i<N;i++) {
      for(int j=(Prt1*N)/(Prt1+Prt2);j<N;j++)
        EigMat[j][i]*=halfm;
    }
  }
  NR::eigsrt(Eigval,EigMat); //固有値の大きい順番でソートされる.
  JT::RenomalizeEigvec(EigMat);
  for(int j=0;j<N;j++) {
      n=0;
    for(int i=0;i<PN;i++) {
      sq=EigMat[3*i][j]*EigMat[3*i][j]+EigMat[3*i+1][j]*EigMat[3*i+1][j]+EigMat[3*i+2][j]*EigMat[3*i+2][j];
      if(i==0) {
        max=sq;
      }
      else {
        if(max<sq)
          max=sq;
      }
    }
    set_MaximumEigVecComponent(max,j);
    for(int i=0;i<PN;i++) {
      sq=EigMat[3*i][j]*EigMat[3*i][j]+EigMat[3*i+1][j]*EigMat[3*i+1][j]+EigMat[3*i+2][j]*EigMat[3*i+2][j];
      if(sq>eigN_threshold*eigmax[j]) {
        n++;
      }
    }

    qDebug()<<"===\nSet EigInfo.\n==="<<endl;
    set_ParticipatingParticles(n,j);
    if(Eigval[j]<-EPS)
      eigplus=false;
  }
  //JT::WriteEigInfo(EigMat,Eigval,seed,PHI,3,Prt1,Prt2,ipr);

  set_EigMatrix(EigMat);
  set_EigValue(Eigval);
  set_CalculatedEigMode(true);
  set_EigNum(0);

  emit getEigenVector();

}
