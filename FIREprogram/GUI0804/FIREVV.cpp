#include "FIREVV.h"
#include "MT.h"
#include "jt.h"
#include <iomanip>
#include <QFileDialog>
#include <Eigen/Sparse>

//#include "ENTERev.h"

FIREVV::FIREVV(QWidget *parent):QWidget(parent),zahyo(0.0),vel(0.0),Force(0.0),Forcetmp(0.0),ratio(1.0),PHI(1.0),Rad(0.0),Leng_x(0.0),Leng_y(0.0),func(0.0),functmp(0.0),alpha(2.0),PN(100),Pratio1(1),Pratio2(1),DMPt(1.0e-1),Tstep(1.0e-2),paintcnt(-1),fra_I(1.1),fra_D(0.5),fra_A(0.99),DMPt_I(1.0e-1),Tstep_M(0.5),ITER_FIRE(5),openum(-2),opedist(0.0),E_mat(0,0),E_val(0.0),eignum(-1),cL(),attribute(Vec_INT(100,PN)),pC(false),isModeCalculated(false),Nc(0),MDcount(0)
{
  Set_ratio(1.4);
  Set_Lengx(400);
  Set_Lengy(400);

  Set_PN(1024);
  Initialize_contactList(PN);
  //Gen_zahyo(0,PN);
  Gen_zahyo_cry(PN,Leng_x);

  emit GenInit();
  emit repaint();
  emit created();
}

FIREVV::~FIREVV()
{
}

inline void FIREVV::PaintWaku(QPainter &painter,DP Yx,DP Yy,DP Lx,DP Ly)
{
  painter.drawLine(QPointF(Yx,Yy),QPointF(Yx,Yy+Ly));
  painter.drawLine(QPointF(Yx,Yy),QPointF(Yx+Lx,Yy));
  painter.drawLine(QPointF(Yx,Yy+Ly),QPointF(Yx+Lx,Yy+Ly));
  painter.drawLine(QPointF(Yx+Lx,Yy),QPointF(Yx+Lx,Yy+Ly));
  return;
}
inline void FIREVV::PaintWaku(QPainter *painter,DP Yx,DP Yy,DP Lx,DP Ly)
{
  painter->drawLine(QPointF(Yx,Yy),QPointF(Yx,Yy+Ly));
  painter->drawLine(QPointF(Yx,Yy),QPointF(Yx+Lx,Yy));
  painter->drawLine(QPointF(Yx,Yy+Ly),QPointF(Yx+Lx,Yy+Ly));
  painter->drawLine(QPointF(Yx+Lx,Yy),QPointF(Yx+Lx,Yy+Ly));
  return;
}

inline void FIREVV::PaintParticles(QPainter &painter,DP Yx,DP Yy,DP &Radi,DP &Radj,int N)
{
  int I;
  Radi=Radj=Rad; //initialize
  for(int i=0; i<N;i+=2)
    {
      I=i/2;
      painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
	  switch(attribute[I]) {
	  case 0:
        painter.setBrush(QBrush(QColor(200,200,200),Qt::SolidPattern));//
	    break;
	  case 1:
        painter.setBrush(QBrush(QColor(0,225,80),Qt::SolidPattern));//green like
	    break;
	  case 2:
        painter.setBrush(QBrush(QColor(255,255,120),Qt::SolidPattern));//
	    break;
	  case 3:
        painter.setBrush(QBrush(QColor(100,255,200),Qt::SolidPattern));//
	    break;
	  case 4:
        painter.setBrush(QBrush(QColor(0,170,170),Qt::SolidPattern));//
	    break;
	  case 5:
        painter.setBrush(QBrush(QColor(255,175,0),Qt::SolidPattern));//
	    break;
	  case 6:
        painter.setBrush(QBrush(QColor(167,214,252),Qt::SolidPattern));//
	    break;
	  case 7:
        painter.setBrush(QBrush(QColor(160,0,160),Qt::SolidPattern));//
	    break;
	  case 8:
        painter.setBrush(QBrush(QColor(120,255,255),Qt::SolidPattern));//
	    break;
	  case 9:
        painter.setBrush(QBrush(QColor(200,135,0),Qt::SolidPattern));//
	    break;
	  case 10:
        painter.setBrush(QBrush(QColor(180,150,255),Qt::SolidPattern));//
	    break;
      case 11:
        painter.setBrush(QBrush(QColor(0,170,0),Qt::SolidPattern));// green like
        break;
      case 12:
        painter.setBrush(QBrush(QColor(255,120,255),Qt::SolidPattern));//
        break;
      case 13:
        painter.setBrush(QBrush(QColor(0,175,130),Qt::SolidPattern));//>< green like
        break;
      case 14:
        painter.setBrush(QBrush(QColor(0,146,159),Qt::SolidPattern));//
        break;
      case 15:
        painter.setBrush(QBrush(QColor(0,127,178),Qt::SolidPattern));//
        break;
      case 16:
        painter.setBrush(QBrush(QColor(0,255,255),Qt::SolidPattern));//
        break;
      case 17:
        painter.setBrush(QBrush(QColor(225,255,225),Qt::SolidPattern));
        break;
      case 18:
        painter.setBrush(QBrush(QColor(165,180,0),Qt::SolidPattern));
        break;
      case 19:
        painter.setBrush(QBrush(QColor(255,120,200),Qt::SolidPattern));
        break;
      case 20:
        painter.setBrush(QBrush(QColor(255,210,255),Qt::SolidPattern));//
        break;
      case -1:
        painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));//
        break;
	  default:
	    painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
	    break;
	  }
	  if((Pratio1+Pratio2)*i==Pratio1*N)
	    Radi=ratio*Rad;
	  painter.drawEllipse(QPointF(zahyo[i]+Yx,zahyo[i+1]+Yy),Radi,Radi);
	  if(i==openum)//お遊び.
	    {
	      painter.setPen(QPen(Qt::black,3,Qt::SolidLine,Qt::RoundCap));
	      painter.drawLine(QPointF(zahyo[i]+Yx-Radi*0.5,zahyo[i+1]+Yy-0.25*Radi),QPointF(zahyo[i]+Yx-Radi*0.75,zahyo[i+1]+Yy-0.25*Radi));
	      painter.drawLine(QPointF(zahyo[i]+Yx+Radi*0.5,zahyo[i+1]+Yy-0.25*Radi),QPointF(zahyo[i]+Yx+Radi*0.25,zahyo[i+1]+Yy-0.25*Radi));
	      painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
	    }
	}
    }
inline void FIREVV::PaintParticles(QPainter *painter,DP Yx,DP Yy,DP &Radi,DP &Radj,int N)
{
  int I;
  Radi=Radj=Rad; //initialize
  for(int i=0; i<N;i+=2)
    {
      I=i/2;
      painter->setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
      switch(attribute[I]) {
      case 0:
        painter->setBrush(QBrush(QColor(200,200,200),Qt::SolidPattern));//
        break;
      case 1:
        painter->setBrush(QBrush(QColor(0,225,80),Qt::SolidPattern));//green like
        break;
      case 2:
        painter->setBrush(QBrush(QColor(255,255,120),Qt::SolidPattern));//
        break;
      case 3:
        painter->setBrush(QBrush(QColor(100,255,200),Qt::SolidPattern));//
        break;
      case 4:
        painter->setBrush(QBrush(QColor(0,170,170),Qt::SolidPattern));//
        break;
      case 5:
        painter->setBrush(QBrush(QColor(255,175,0),Qt::SolidPattern));//
        break;
      case 6:
        painter->setBrush(QBrush(QColor(167,214,252),Qt::SolidPattern));//
        break;
      case 7:
        painter->setBrush(QBrush(QColor(160,0,160),Qt::SolidPattern));//
        break;
      case 8:
        painter->setBrush(QBrush(QColor(120,255,255),Qt::SolidPattern));//
        break;
      case 9:
        painter->setBrush(QBrush(QColor(200,135,0),Qt::SolidPattern));//
        break;
      case 10:
        painter->setBrush(QBrush(QColor(180,150,255),Qt::SolidPattern));//
        break;
      case 11:
        painter->setBrush(QBrush(QColor(0,170,0),Qt::SolidPattern));// green like
        break;
      case 12:
        painter->setBrush(QBrush(QColor(255,120,255),Qt::SolidPattern));//
        break;
      case 13:
        painter->setBrush(QBrush(QColor(0,175,130),Qt::SolidPattern));//>< green like
        break;
      case 14:
        painter->setBrush(QBrush(QColor(0,146,159),Qt::SolidPattern));//
        break;
      case 15:
        painter->setBrush(QBrush(QColor(0,127,178),Qt::SolidPattern));//
        break;
      case 16:
        painter->setBrush(QBrush(QColor(0,255,255),Qt::SolidPattern));//
        break;
      case 17:
        painter->setBrush(QBrush(QColor(225,255,225),Qt::SolidPattern));
        break;
      case 18:
        painter->setBrush(QBrush(QColor(165,180,0),Qt::SolidPattern));
        break;
      case 19:
        painter->setBrush(QBrush(QColor(255,120,200),Qt::SolidPattern));
        break;
      case 20:
        painter->setBrush(QBrush(QColor(255,210,255),Qt::SolidPattern));//
        break;
      case -1:
        painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));//
        break;
      default:
        painter->setBrush(QBrush(Qt::green,Qt::SolidPattern));
        break;
      }
      if((Pratio1+Pratio2)*i==Pratio1*N)
        Radi=ratio*Rad;
      painter->drawEllipse(QPointF(zahyo[i]+Yx,zahyo[i+1]+Yy),Radi,Radi);
      if(i==openum)//お遊び.
        {
          painter->setPen(QPen(Qt::black,3,Qt::SolidLine,Qt::RoundCap));
          painter->drawLine(QPointF(zahyo[i]+Yx-Radi*0.5,zahyo[i+1]+Yy-0.25*Radi),QPointF(zahyo[i]+Yx-Radi*0.75,zahyo[i+1]+Yy-0.25*Radi));
          painter->drawLine(QPointF(zahyo[i]+Yx+Radi*0.5,zahyo[i+1]+Yy-0.25*Radi),QPointF(zahyo[i]+Yx+Radi*0.25,zahyo[i+1]+Yy-0.25*Radi));
          painter->setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
        }
    }
    }

  void FIREVV::paintEvent(QPaintEvent *)
  {
    QPainter painter(this);
    QImage* Pimage = new QImage(this->size(),QImage::Format_ARGB32);
    QPainter* painterImg = new QPainter;
    painterImg->begin(Pimage);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painterImg->setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
    painterImg->setPen(QPen(Qt::white,2,Qt::SolidLine,Qt::RoundCap));

    //枠線
    double yohaku_x=Leng_x/20.0,yohaku_y=Leng_y/20.0;
    int N=2*PN;
    DP Radi=Rad,Radj=Rad;

  painterImg->setClipRect(QRect(this->rect()));
  PaintWaku(painter,yohaku_x,yohaku_y,Leng_x,Leng_y);
  PaintWaku(*painterImg,yohaku_x,yohaku_y,Leng_x,Leng_y);
  PaintParticles(painter,yohaku_x,yohaku_y,Radi,Radj,N);
  PaintParticles(*painterImg,yohaku_x,yohaku_y,Radi,Radj,N);
  
  //force network
  double thr=pow((1.0e-16)*alpha*PN,1/alpha);
  Radi=Rad;//初期化

  for(int i=2;i<N;i+=2)
    {
      if((Pratio1+Pratio2)*i==Pratio1*N)
	Radi=ratio*Rad;

      Radj=Rad;//初期化
      for(int j=0;j<i;j+=2)
	{
      if((Pratio1+Pratio2)*j==Pratio1*N)
	    Radj=ratio*Rad;

	  DP sgm=Radi+Radj;
	  DP relrx=zahyo[j]-zahyo[i];
	  DP relry=zahyo[j+1]-zahyo[i+1];
	  int p1=0,p2=0;

	  JT::dim2::OutofPeriodicboundary2D_qt(relrx,relry,Leng_x,Leng_y,sgm,p1,p2);	  
	  DP relr=sqrt(pow(relrx,2)+pow(relry,2));
	  if(relr<sgm)
	    {
	      if(relr>sgm*(1-thr))
		{
		  painter.setPen(QPen(Qt::magenta,1,Qt::SolidLine,Qt::RoundCap));
		  painterImg->setPen(QPen(Qt::magenta,1,Qt::SolidLine,Qt::RoundCap));
		}
	      else if(relr<=sgm*(1-thr) && relr>sgm*(1-thr*1.0e+1))
		{
		  painter.setPen(QPen(Qt::magenta,1.1,Qt::SolidLine,Qt::RoundCap));
		  painterImg->setPen(QPen(Qt::magenta,1.1,Qt::SolidLine,Qt::RoundCap));
		}
	      else if(relr<=sgm*(1-thr*1.0e+1) && relr>sgm*(1-thr*1.0e+2))
		{
		  painter.setPen(QPen(Qt::magenta,1.2,Qt::SolidLine,Qt::RoundCap));
		  painterImg->setPen(QPen(Qt::magenta,1.2,Qt::SolidLine,Qt::RoundCap));
		}
	      else if(relr<=sgm*(1-thr*1.0e+2) && relr>sgm*(1-thr*1.0e+3))
		{
		  painter.setPen(QPen(Qt::magenta,1.7,Qt::SolidLine,Qt::RoundCap));
		  painterImg->setPen(QPen(Qt::magenta,1.7,Qt::SolidLine,Qt::RoundCap));
		}
	      else if(relr<=sgm*(1-thr*1.0e+3) && relr>sgm*(1-thr*1.0e+4))
		{
		  painter.setPen(QPen(Qt::magenta,2.0,Qt::SolidLine,Qt::RoundCap));
		  painterImg->setPen(QPen(Qt::magenta,2.0,Qt::SolidLine,Qt::RoundCap));
		}
	      else
		{
		  painter.setPen(QPen(Qt::red,3,Qt::SolidLine,Qt::RoundCap));
		  painterImg->setPen(QPen(Qt::red,3,Qt::SolidLine,Qt::RoundCap));
		}
	      if(p1 ==0 && p2 ==0)
		{
		  painter.drawLine(QPointF(zahyo[i]+yohaku_x,zahyo[i+1]+yohaku_y),QPointF(zahyo[j]+yohaku_x,zahyo[j+1]+yohaku_y));
		  painterImg->drawLine(QPointF(zahyo[i]+yohaku_x,zahyo[i+1]+yohaku_y),QPointF(zahyo[j]+yohaku_x,zahyo[j+1]+yohaku_y));
		}
	      else
		{
		  painter.drawLine(QPointF(zahyo[j]+yohaku_x-p1*Leng_x,zahyo[j+1]+yohaku_y-p2*Leng_y),QPointF(zahyo[i]+yohaku_x,zahyo[i+1]+yohaku_y));
		  painterImg->drawLine(QPointF(zahyo[j]+yohaku_x-p1*Leng_x,zahyo[j+1]+yohaku_y-p2*Leng_y),QPointF(zahyo[i]+yohaku_x,zahyo[i+1]+yohaku_y));
		  painter.drawLine(QPointF(zahyo[j]+yohaku_x,zahyo[j+1]+yohaku_y),QPointF(zahyo[i]+yohaku_x+p1*Leng_x,zahyo[i+1]+yohaku_y+p2*Leng_y));
          painterImg->drawLine(QPointF(zahyo[j]+yohaku_x,zahyo[j+1]+yohaku_y),QPointF(zahyo[i]+yohaku_x+p1*Leng_x,zahyo[i+1]+yohaku_y+p2*Leng_y));
		}
	    }

	}//j-loop-end
    }//i-loop-end

  if(eignum>=0 && eignum<2*PN && isModeCalculated) {
    //+矢印で描画.
    QPointF M,A,B,pEnd;
    QPointF points[3];
    DP ex,ey;
    painter.setPen(QPen(Qt::blue,4,Qt::SolidLine,Qt::RoundCap));
    painterImg->setPen(QPen(Qt::blue,4,Qt::SolidLine,Qt::RoundCap));
    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
    painterImg->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
    for(int i=0;i<N;i+=2) {
      if((Pratio1+Pratio2)*i==Pratio1*N)
        Radi=ratio*Rad;
      ex=12*Radi*E_mat[i][eignum];//2*半径がマックスの長さ
      ey=12*Radi*E_mat[i+1][eignum];//2*半径がマックスの長さ

      pEnd=QPointF(yohaku_x+zahyo[i]+ex,yohaku_y+zahyo[i+1]+ey);
      painter.drawLine(QPointF(zahyo[i]+yohaku_x,zahyo[i+1]+yohaku_y),pEnd);
      painterImg->drawLine(QPointF(zahyo[i]+yohaku_x,zahyo[i+1]+yohaku_y),pEnd);      
      M=QPointF(yohaku_x+zahyo[i]+0.60*ex,yohaku_y+zahyo[i+1]+0.60*ey);
      points[0]=pEnd;
      points[1]=QPointF(M.x()-0.27*ey,M.y()+0.27*ex);
      points[2]=QPointF(M.x()+0.27*ey,M.y()-0.27*ex);
      painter.drawConvexPolygon(points,3);
      painterImg->drawConvexPolygon(points,3);
    }
  }

  //  painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));

  //  painter.setPen(QPen(Qt::cyan,2,Qt::SolidLine,Qt::RoundCap));
  //painter.drawLine(QPointF(0,0),QPoint(405,405));
  if(paintcnt>=0)
    {
      QString wrname;
      if(paintcnt<10)
	wrname ="TestPic000000"+QString::number(paintcnt)+".png";
      else if(paintcnt>=10 && paintcnt<100)
	wrname ="TestPic00000"+QString::number(paintcnt)+".png";
      else if(paintcnt>=100 && paintcnt<1000)
	wrname ="TestPic0000"+QString::number(paintcnt)+".png";
      else if(paintcnt>=1000 && paintcnt<10000)
	wrname ="TestPic000"+QString::number(paintcnt)+".png";
      else if(paintcnt>=10000 && paintcnt<100000)
	wrname ="TestPic00"+QString::number(paintcnt)+".png";
      else if(paintcnt>=100000 && paintcnt<1000000)
	wrname="TestPic0"+QString::number(paintcnt)+".png";
      else
	wrname="TestPic"+QString::number(paintcnt)+".png";
      //painter.save();
      Pimage->save(wrname);
      //painter.restore();
      Pimage->fill(qRgba(0,0,0,0));
      //painterImg->fillRect(this->rect(),QColor(0,0,0,0));
      //painterImg.eraseRect(-Leng,-Leng,4*Leng,4*Leng);
      //painterImg.end();
      paintcnt+=1;
    }
  delete painterImg;
  delete Pimage;

}

void FIREVV::mousePressEvent(QMouseEvent* event)
{
  if(event->button()==Qt::LeftButton)
    {
      QPoint* mousept= new QPoint(this->mapFromGlobal(QCursor::pos()));
      double yohaku_x=Leng_x/20.0,yohaku_y=Leng_y/20.0;
      int N=zahyo.size(),minnum;
      DP mindist,disttmp,relrx,relry,R=Rad;
      for(int i=0;i<N;i+=2)
	{
      if(i*(Pratio1+Pratio2)==N*Pratio1)
            R=Rad*ratio;
	  relrx=mousept->x()-zahyo[i];
	  relry=mousept->y()-zahyo[i+1];

	  if(i==0)
	    {
	      minnum=i;
	      mindist=sqrt(relrx*relrx+relry*relry);
	    }
	  else
	    {
	      disttmp=sqrt(relrx*relrx+relry*relry);
	      if(disttmp<R)
		{
		  if(disttmp<mindist)
		    {
		      mindist=disttmp;
		      minnum=i;
		    }
		}
	    }
	}

      zahyo[minnum]=mousept->x()-yohaku_x;
      zahyo[minnum+1]=mousept->y()-yohaku_y;
      openum=minnum;
      opedist=mindist;
      emit repaint();
    }
  else if(event->button()==Qt::RightButton)
    {
      openum=-2;
      emit repaint();
    }
}

void FIREVV::mouseMoveEvent(QMouseEvent* event)
{
  if(event->button()==Qt::LeftButton)
    {
      QPoint* mousept= new QPoint(this->mapFromGlobal(QCursor::pos()));
      double yohaku_x=Leng_x/20.0,yohaku_y=Leng_y/20.0;

      if(openum>0)
	{
	  zahyo[openum]=mousept->x()-yohaku_x;
	  zahyo[openum+1]=mousept->y()-yohaku_y;
	  emit repaint();
	}
    }
}
void FIREVV::mouseReleaseEvent(QMouseEvent* event)
{
  openum=-2;
}

inline void FIREVV::initializeSystemQuantity(int N)
{
  PN=N;
  Vec_DP Fpot(2*N);
  DP mass=1.0;
  bool relax=true;
  isModeCalculated=false;
  vel=Force=Vec_DP(0.0,2*N);
  Set_attribute(Vec_INT(100,N));
  Rad=JT::dim2::CtoDerivePHI2D(Leng_x,Leng_y,ratio,N,Pratio1,Pratio2,2)*sqrt(PHI);
  JT::dim2::modifyContactList(cL,zahyo,Leng_x,Leng_y,Rad,ratio,Pratio1,Pratio2,2);
  func=functmp=JT::dim2::fastPot2D(zahyo,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,1.0,cL);
  JT::dim2::fastVVFForce2D(zahyo,vel,Force,Fpot,DMPt,mass,Tstep,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,relax,cL);
  Forcetmp=Force;
  openum=-2;
  eignum=-1;
  MDcount=0;
  emit EngChanged();
  emit M_varChanged();
  emit repaint();
}
inline void FIREVV::initializeSystemQuantity_lattice(int N)
{
  Vec_DP Fpot(2*N);
  DP mass=1.0;
  bool relax=true;
  isModeCalculated=false;
  vel=Force=Vec_DP(0.0,2*N);
  Set_attribute(Vec_INT(100,N));
  JT::dim2::modifyContactList(cL,zahyo,Leng_x,Leng_y,Rad,ratio,Pratio1,Pratio2,2);
  func=functmp=JT::dim2::fastPot2D(zahyo,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,1.0,cL);
  JT::dim2::fastVVFForce2D(zahyo,vel,Force,Fpot,DMPt,mass,Tstep,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,relax,cL);
  Forcetmp=Force;
  openum=-2;
  eignum=-1;
  MDcount=0;
  emit EngChanged();
  emit M_varChanged();
  emit repaint();
}

void FIREVV::Gen_zahyo(int seed,int N)
{
  Vec_DP p(2*N);
  zahyo=Forcetmp=p=Vec_DP(0.0,2*N);
  Set_DMPt(DMPt_I);
  Set_Tstep(1.0e-2);
  JT::dim2::PutZahyoRandomly2D(zahyo,p,Leng_x,Leng_y,seed);

  initializeSystemQuantity(N);
}

void FIREVV::Gen_zahyo(int N)
{
  Vec_DP p(2*N);
  zahyo=Forcetmp=p=Vec_DP(0.0,2*N);
  zahyo=p=0.0;
  Set_DMPt(DMPt_I);
  Set_Tstep(1.0e-2);
  JT::dim2::PutZahyoRandomly2D(zahyo,p,Leng_x,Leng_y,0);

  initializeSystemQuantity(N);
}

void FIREVV::Gen_zahyo_sq(int N)//正方格子verだね.
{
  Vec_DP p(2*N);
  zahyo=Forcetmp=p=Vec_DP(0.0,2*N);
  
  DP Ntmpd=sqrt(N);
  int Ntmpi=sqrt(N);
  if(Ntmpd!=Ntmpi)
    NR::nrerror("your the number of the particle is not valid...");

  Set_Rad(100*Leng_x/(199*Ntmpd));
  DP delta=0.01*Rad;
  
  DP CPHI2=pow(JT::dim2::CtoDerivePHI2D(Leng_x,Leng_y,ratio,PN,Pratio1,Pratio2,2),2);
  Set_PHI(Rad*Rad/CPHI2);

  DP plus1=Rad-0.5*delta;
  DP plus2=2*Rad-delta;
  	    
  for(int i=0;i<Ntmpd;i++){
    zahyo[i*2*Ntmpd]=plus1;
    zahyo[i*2*Ntmpd+1]=plus1+i*plus2;
    for(int j=1;j<Ntmpd;j++){
      zahyo[i*2*Ntmpd+2*j]=zahyo[i*2*Ntmpd+2*j-2]+plus2;
      zahyo[i*2*Ntmpd+2*j+1]=zahyo[i*2*Ntmpd+2*j-1];
    }
  }

  initializeSystemQuantity_lattice(N);
}
void FIREVV::Gen_zahyo_cry(int N,DP Lx)
{
  Vec_DP p(2*N);
  zahyo=Forcetmp=p=Vec_DP(0.0,2*N);
  
    DP Ntmpd=sqrt(N);
    int Ntmpi=sqrt(N);
    if(Ntmpd!=Ntmpi)
      NR::nrerror("your the number of the particle is not valid...");
    Set_Lengx(Lx);
    Set_Lengy(0.5*Lx*sqrt(3));


    Set_Rad(100*Leng_x/(199*Ntmpi));
    DP delta=0.01*Rad;

    DP CPHI2=pow(JT::dim2::CtoDerivePHI2D(Leng_x,Leng_y,ratio,PN,Pratio1,Pratio2,2),2);
    Set_PHI(Rad*Rad/CPHI2);

    DP plus1=Rad-0.5*delta;
    DP plus2=(Rad-0.5*delta)*sqrt(3);
    DP plus3=2*plus1;

    for(int i=0;i<Ntmpi;i++) {
        if(i%2==0) {
        zahyo[i*2*Ntmpd]=plus1;
        zahyo[i*2*Ntmpd+1]=plus1+i*plus2;
        }
        else {
            zahyo[i*2*Ntmpd]=2*plus1;
            zahyo[i*2*Ntmpd+1]=plus1+i*plus2;
        }
        for(int j=1;j<Ntmpi;j++) {
            zahyo[i*2*Ntmpi+2*j]=zahyo[i*2*Ntmpd+2*j-2]+plus3;
            zahyo[i*2*Ntmpi+2*j+1]=zahyo[i*2*Ntmpd+2*j-1];
        }
    }

    initializeSystemQuantity_lattice(N);
}

void FIREVV::Gen_PHI(double phi,DP Len,int PNum)//引数phiだけでよくね?
{
  //changing radii of particles by a given phi(packing fraction).
  Set_Lengx(Len);
  Set_Lengy(Len);
  PHI=phi;
  initializeSystemQuantity(PNum);
}
void FIREVV::Gen_PHI(double phi,DP Lx,DP Ly,int PNum)//引数phiだけでよくね?
{
  //changing radii of particles by a given phi(packing fraction).
  Set_Lengx(Lx);
  Set_Lengy(Ly);
  PHI=phi;
  initializeSystemQuantity(PNum);
}
void FIREVV::Inc_PHI(double inc,int PNum)
{
  PHI+=inc;
  initializeSystemQuantity(PNum);
}

int FIREVV::Modenumber(bool plus)
{

  int N=zahyo.size();
  DP eps=1.0;
  vector<TripD> HesElements;
  Mat_DP EigMat(N,N);
  spMat Hes(N,N);
  Vec_DP Eigval(N),IPR(N),IPR1(N),IPR2(N),eigvec_cntSmall(N);
  int cnt=0,eigcnt=0;
  DP EPS=numeric_limits<double>::epsilon(),halfm_inv=1.0/(ratio); //dim2

  JT::eigen::dim2::fastHess2D_EIGEN(zahyo,HesElements,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,eps,cL);
  Hes.setFromTriplets(HesElements.begin(),HesElements.end());    
  ESolv_SA Esolver(Hes);    // コストラクタ内の計算後sortもされている。
  Eigen::VectorXd Evals=Esolver.eigenvalues();  
  int firstCompIdx=(Pratio1*N)/(Pratio1+Pratio2);
  for(int i=0;i<N;i++) {//per modenumber
    Eigen::VectorXd Evector = Esolver.eigenvectors().col(i);      
    for(int j=0;j<firstCompIdx;j++) {
      EigMat[j][i]=Evector[j];
    }
    for(int j=firstCompIdx;j<N;j++) {
      //BIdisperseのときは本来の固有ベクターに変換しなければならない。
      EigMat[j][i]=halfm_inv*Evector[j];
    }
    Eigval[i]=Evals[i];
  }
  //FIREVV::Normalize_EIG();
  JT::CollectiveMotionCheck2(EigMat,IPR,IPR1,IPR2,2,Pratio1,Pratio2);
  JT::countEigComponents(EigMat,eigvec_cntSmall,Pratio1,Pratio2);

  //FIREVV::countEigMotion(EigMat,eigvec_cntSmall,eigvec_cnt);

  int EVnum=0;

  qDebug()<<"* "<<0<<' '<<qSetRealNumberPrecision(15)<<Eigval[0]<<' '<<sqrt(Eigval[0])<<' '<<IPR[0]<<' '<<IPR1[0]<<' '<<IPR2[0]<<' '<<eigvec_cntSmall[0]<<endl;
  if(fabs(Eigval[0])<EPS)
    EVnum+=1;
  if(Eigval[0]<-EPS)
    eigcnt+=1;
  for(int i=1;i<N;i++)
    {
      if(fabs(Eigval[i]-Eigval[i-1])<EPS)
    qDebug()<<i<<' '<<qSetRealNumberPrecision(15)<<Eigval[i]<<' '<<sqrt(Eigval[i])<<' '<<IPR[i]<<' '<<IPR1[i]<<' '<<IPR2[i]<<' '<<eigvec_cntSmall[i]<<endl;
      else
    qDebug()<<"* "<<i<<' '<<qSetRealNumberPrecision(15)<<Eigval[i]<<' '<<sqrt(Eigval[i])<<' '<<IPR[i]<<' '<<IPR1[i]<<' '<<IPR2[i]<<' '<<eigvec_cntSmall[i]<<endl;
      if(fabs(Eigval[i])<EPS)
	EVnum+=1;
      if(Eigval[i]<-EPS)
        eigcnt+=1;
    }
  if(eigcnt>0)
plus=false;
  else
    plus=true;

  Set_Emat(EigMat);
  Set_Eval(Eigval);
  Set_Enum(0);
  isModeCalculated=true;

  //JT::searchSoftMode(zahyo,EigMat,2*PN-5,2,Rad,ratio,Pratio1,Pratio2);
  //JT::searchSoftMode(zahyo,EigMat,0,2,Rad,ratio,Pratio1,Pratio2);
  return EVnum;
}
void FIREVV::SoftAnalysis() {
    if(E_mat.ncols()!=0 && E_mat.nrows()!=0 && isModeCalculated) {
    JT::dim2::searchCoCluster(zahyo,E_mat,eignum,2,Rad,ratio,Pratio1,Pratio2,Leng_x,Leng_y,attribute,Nc);//cluster no kosuu wo return suruyouni suru.
    }
    else {
        cerr<<"ERROR"<<endl;
    }
}

void FIREVV::Normalize_EIG() {
  double e_sum,div;
  int N=E_mat.ncols();
  
  for(int j=0;j<N;j++) {
    e_sum=0.0;
    for(int i=0;i<N;i++)
      e_sum+=E_mat[i][j]*E_mat[i][j];
    div=1.0/sqrt(e_sum);
    qDebug()<<j<<"番目: "<<endl;
    for(int i=0;i<N;i++) {
      E_mat[i][j]*=div;
      qDebug()<<E_mat[i][j]<<" ";
    }
    qDebug()<<endl;
  }
}

void FIREVV::initializeParticleColor() {
    Set_attribute(Vec_INT(100,PN));
}

void FIREVV::Set_zahyo(Vec_I_DP &p)
{
  zahyo=p;
}
void FIREVV::Set_vel(Vec_I_DP &v)
{
  vel=v;
}
void FIREVV::Set_Force(Vec_I_DP &F)
{
  Force=F;
}
void FIREVV::Set_Forcetmp(Vec_I_DP &Ftmp)
{
  Forcetmp=Ftmp;
}
void FIREVV::Set_ratio(double rt)
{
  ratio=rt;
  emit M_varChanged();
}
void FIREVV::Set_PHI(double phi)
{
  PHI=phi;
  emit M_varChanged();
}
void FIREVV::Set_Rad(double R)
{
  Rad=R;
}
void FIREVV::Set_Lengx(double lngx)
{
  if(lngx>=100 && lngx<=500)
    {
      Leng_x=lngx;
      emit M_varChanged();
    }
}
void FIREVV::Set_Lengy(double lngy)
{
  if(lngy>=100 && lngy<=500)
    {
      Leng_y=lngy;
      emit M_varChanged();
    }
}
void FIREVV::Set_func(double f)
{
  func=f;
}
void FIREVV::Set_functmp(double ftmp)
{
  functmp=ftmp;
}
void FIREVV::Set_alpha(double alp)
{
  alpha=alp;
  emit M_varChanged();
}
void FIREVV::Set_PN(int N)
{
  PN=N;
  Initialize_contactList(PN);
  zahyo=Forcetmp=Vec_DP(0.0,2*N);
  Set_Enum(-1);
  emit M_varChanged();
}
void FIREVV::Set_Pratio1(int prt1)
{
  Pratio1=prt1;
  emit M_varChanged();
}
void FIREVV::Set_Pratio2(int prt2)
{
  Pratio2=prt2;
  emit M_varChanged();
}
void FIREVV::Set_DMPt(DP dmpt)
{
  DMPt=dmpt;
  emit M_varChanged();
}
void FIREVV::Set_Tstep(DP t)
{
  Tstep=t;
  Set_TstepM(Tstep*50);//defauldでTstepの10倍になる仕様にしておく。
  emit M_varChanged();
}
void FIREVV::Set_Pntcnt(int pntcnt)
{
  paintcnt=pntcnt;
  emit M_varChanged();
}
void FIREVV::Set_fraI(DP fra_inc)
{
  fra_I=fra_inc;
  emit M_varChanged();
}
void FIREVV::Set_fraD(DP fra_dec)
{
  fra_D=fra_dec;
  emit M_varChanged();
}
void FIREVV::Set_fraA(DP fra_alp)
{
  fra_A=fra_alp;
  emit M_varChanged();
}
void FIREVV::Set_dmptI(DP dmpt_init)
{
  DMPt_I=dmpt_init;
  emit M_varChanged();
}
void FIREVV::Set_TstepM(DP tmax)
{
  Tstep_M=tmax;
  emit M_varChanged();
}
void FIREVV::Set_ITFIRE(int ITFIRE)
{
  ITER_FIRE=ITFIRE;
  emit M_varChanged();
}
void FIREVV::Set_Openum(int num) {
  openum=num;
}

void FIREVV::Set_Opedist(DP dist) {
  opedist=dist;
}
void FIREVV::Set_Emat(Mat_I_DP &Em) {
  E_mat=Em;
}
void FIREVV::Set_Eval(Vec_I_DP &Ev) {
  E_val=Ev;
}
void FIREVV::Set_Enum(int num) {
  eignum=num;
  emit repaint();
  emit eNumchaged();
}
void FIREVV::Set_contactList(NRVec<vector<int> > &v) {
  cL=v;
}
void FIREVV::Set_attribute(Vec_I_INT &v) {
    attribute=v;
}
void FIREVV::Set_paintedCluster(bool b) {
    pC=b;
    emit repaint();
}

void FIREVV::inputZahyodata() {
  QFileDialog testdialog;
  QString filename = QFileDialog::getOpenFileName(&testdialog,tr("Open Text"), "~/", tr("Text Files (*.txt *.csv)"));
  qDebug()<<filename<<endl;

  int d,prt1,prt2,N,cnt=0;
  double phi,rt;
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QTextStream in(&file);
  QString line = in.readLine();
  QTextStream in2(&line);
  in2>>d>>N>>phi>>rt>>prt1>>prt2;
  qDebug()<<d<<' '<<N<<' '<<' '<<phi<<' '<<rt<<' '<<prt1<<' '<<prt2<<endl;
  Set_PN(N);
  Set_PHI(phi);
  Set_ratio(rt);
  Set_Pratio1(prt1);
  Set_Pratio1(prt2);
  initializeSystemQuantity(N);
  if(d!=2) {
    qDebug()<<"Error!!"<<endl;
  }
  else {
    Vec_DP z(d*N);
    while (!in.atEnd()) {
      line=in.readLine();
      qDebug()<<line<<endl;
      QTextStream in3(&line);
      if(2*cnt<d*N) {
	in3>>z[cnt*2]>>z[cnt*2+1];
	qDebug()<<z[cnt*2]<<' '<<z[cnt*2+1]<<endl;
    z[cnt*2]*=Leng_x/(100.0*sqrt(N/128));//Qt no length scale ni change.
    z[cnt*2+1]*=Leng_y/(100.0*sqrt(N/128));
    //z[cnt*2]*=Leng_x/(24.2703);// for nakata-kun (N100)
    //z[cnt*2+1]*=Leng_y/(24.2703);
      }
      cnt+=1;
    }

    if(z.size()>0) {
      bool relax;
      Force=Forcetmp=vel=zahyo=z;
      Force=Forcetmp=vel=0.0;
      JT::dim2::VVforce_F(zahyo,vel,Force,Forcetmp,DMPt,1.0,Tstep,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,relax);
      Forcetmp=Force;
      func=functmp=JT::dim2::potential(zahyo,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,1.0);
    }


    //Gen_PHI(phi,Leng_x,Leng_y,N);
  }
}

void FIREVV::WriteEIGinfo(int num)
{
    if(isModeCalculated) {
  //----------------------------------------------------------
  //あるサンプルnumの充填率PHIのときの状態密度の累積をTXT出力.
  //----------------------------------------------------------
  int N=E_val.size();
  Vec_DP CMnumber(N),CMnumber1(N),CMnumber2(N);//,Eigvec(N);
  QString wrname;
  DP cmdist=0.0,cm=1.0,EPS=numeric_limits<double>::epsilon(),eg;

  JT::CollectiveMotionCheck2(E_mat,CMnumber,CMnumber1,CMnumber2,2,Pratio1,Pratio2);// IPR をCMnumberに格納
  if(num<10)
    wrname.append("EigCum0000"+QString::number(num)+'_'+QString::number(PHI)+".txt");
  else if(num>=10 && num<100)
    wrname.append("EigCum000"+QString::number(num)+'_'+QString::number(PHI)+".txt");
  else if(num>=100 && num<1000)
    wrname.append("EigCum00"+QString::number(num)+'_'+QString::number(PHI)+".txt");
  else if(num>=1000 && num<10000)
    wrname.append("EigCum0"+QString::number(num)+'_'+QString::number(PHI)+".txt");
  else
    wrname.append("EigCum"+QString::number(num)+'_'+QString::number(PHI)+".txt");
  for(int i=0;i<N;i++) {
    if(fabs(E_val[i])>EPS)
      cmdist+=1;
  }
  cmdist=1.0/cmdist;

  QFile file(wrname);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
  QTextStream ts3(&file);
  for(int i=0;i<N;i++) {
    if(fabs(E_val[i])>EPS) {
      ts3<<QString::number(E_val[i],'f',10)<<' '<<QString::number(sqrt(E_val[i]),'f',10)<<' '<<QString::number(CMnumber[i],'f',10)<<' '<<QString::number(CMnumber1[i],'f',10)<<' '<<QString::number(CMnumber2[i],'f',10)<<' '<<QString::number(cm,'f',10)<<endl;
      cm-=cmdist;
    }
    else {
      eg=fabs(E_val[i]);
      ts3<<QString::number(eg,'f',10)<<' '<<QString::number(sqrt(eg),'f',10)<<' '<<QString::number(CMnumber[i],'f',10)<<' '<<QString::number(CMnumber1[i],'f',10)<<' '<<QString::number(CMnumber2[i],'f',10)<<' '<<0<<endl;
    }
  }
    }
}

void FIREVV::VerletDO()
{
  DP mass=1.0;
  functmp=func;
  int ITER_F=0;
  JT::dim2::modifyContactList(cL,zahyo,Leng_x,Leng_y,Rad,ratio,Pratio1,Pratio2,2);
  for(int i=0;i<100;i++)
    {
      int N=zahyo.size();
      Vec_DP Fpot(N);
      bool relax=true;
      /*
	for(int j=0;j<N;j++)
	{
	qDebug()<<"zahyo:"<<zahyo[j]<<", vel:"<<vel[j]<<", Force:"<<Force[j]<<'\n';
	}
	qDebug()<<"\n\n=====================================================\n\n\n";
      */
      JT::dim2::nextcod_F(zahyo,vel,Force,Tstep,Leng_x,Leng_y);
      JT::dim2::fastVVFForce2D(zahyo,vel,Force,Fpot,DMPt,mass,Tstep,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,relax,cL);
      JT::nextvel_F(vel,Force,Forcetmp);
      JT::FIRE(vel,Fpot,DMPt,Tstep,fra_I,fra_D,fra_A,DMPt_I,Tstep_M,ITER_FIRE,ITER_F);
      Forcetmp=Force;
    }
  func=JT::dim2::fastPot2D(zahyo,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,1.0,cL);
  MDcount++;
  emit EngChanged();
  emit M_varChanged();
  if(2*fabs(func-functmp)< numeric_limits<double>::epsilon()*fabs(func+functmp)+1.0e-18)
    emit minfunc();
  //何回かに一回emit repaint();する。
  //  nrerror("VValgorithm cannot converge...\n\n");
  emit VVfin();
  if(MDcount%1==0)
  emit repaint();
}


void FIREVV::Tapping()
{
  int N=zahyo.size();
  Mat_DP Hes(N,N),EigMat(N,N);
  Vec_DP Eigval(N),Eigvec(N);
  int cnt=0;
  DP EPS=numeric_limits<double>::epsilon();
  bool invalidflag;
  JT::dim2::Hesspot(zahyo,Hes,Leng_x,Leng_y,Rad,ratio,alpha,Pratio1,Pratio2,2,1.0);
  NR::jacobi(Hes,Eigval,EigMat,cnt,invalidflag);
  NR::eigsrt(Eigval,EigMat);

  for(int i=0;i<N;i++)
    {
      if(Eigval[i]<-EPS)
        {
	  for(int j=0;j<N;j++)
	    Eigvec[j]=EigMat[j][i];
      //JT::tapping(Eigvec,Eigval[i],JT::dim2::potential(zahyo,Leng,Rad,ratio,alpha,Pratio,2,1.0),EPS,Rad,0.01);//この関数で固有ベクターの方向の微小(?)変位ベクトルを作成。(もしかしたら変位の大きさやばいかも)
	  for(int j=0;j<N;i++)
	    zahyo[j]+=Eigvec[j];
        }
    }
}

void FIREVV::Noise()
{
  JT::dim2::noise(zahyo,Rad,Leng_x,Leng_y,0.01);
  emit repaint();
}

void FIREVV::countEigMotion(Mat_I_DP &EigMat, Vec_IO_DP &v, Vec_IO_DP &vall) {

    const int N=v.size();
    Vec_DP eigvec_max(N);
    for(int i=0;i<N;i++) {
        eigvec_max[i]=0.0;
        for(int j=0;j<N;j++) {
            if(fabs(EigMat[j][i])>eigvec_max[i])
                eigvec_max[i]=fabs(EigMat[j][i]);
        }
    }
    for(int i=0;i<N;i++) {
        vall[i]=0;
        v[i]=0;
        int changeParticle=(Pratio1*N)/(Pratio1+Pratio2);
        for(int j=0;j<N;j++) {
            if(fabs(EigMat[j][i])>=0.1*eigvec_max[i]) {//0.01 ha shikiichi
                vall[i]+=1;
            if(j<changeParticle)
                v[i]+=1;
            }
        }
        v[i]/=vall[i];
    }

    return;
}

//----------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------

/*
QString ENTERev::TEXTREADER(QLineEdit *led)
{
    QString a = led->text();
    return a;
}
*/
