#ifndef _GNP_H_
#define _GNP_H_
#include <fstream>
#include "nrutil.h"
#include "nrtypes.h"
#include "pstream.h"

//----------------------------------------------------
//--------------------更新履歴------------------------
//----------------------------------------------------

//-------------------------------------過去(1/6以前)------------------------------------------
//A.gnuplot描画を関数化すべく、gnp.h作成
//B.Mono2DとBI2Dを分ける。(多重定義しても良かったのだが関数使うときに間違えることを避けるために別々に定義)
//C.TXTzahyo2Dを作成(書き込んだ座標値をVec_DPに格納するため。Vec_IO_DP &pとしたほうが良かったか)
//D.ForceNetworkを色分け(現在yellow->N=100(ここ重要)でのCG法で計算したときの誤差力,red->平均以上(harmonicの場合)の力がはたらく,blue->それ以外)
//E.
//---------------------------------------------------------------------------------------------

//-------------------------------------1/7(Thu)------------------------------------------------
//A.意味不明な線を描画(対象粒子がセル内ではあるが、他セルの相互作用をする場合)のバグを修正。(未確認)
//B.ForceNetworkの色分け条件の粒子数依存を無くしたい。(まだやっていない)
//C.
//
//
//---------------------------------------------------------------------------------------------

namespace gnp
{
  void Gnupstd(Vec_I_DP &p,DP R,DP L,string name);
  void GnupstdBI(Vec_I_DP &p,DP R,DP L,string name,DP ratio);
  void GnupForce(Vec_I_DP &p,DP R,DP L,string name);
  void GnupForceBI(Vec_I_DP &p,DP R,DP L,string name,DP ratio);
  void TXTzahyo2D(Vec_DP &p,string name);
}


//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//-----------------------以下、Gnuplotでの描写に用いる関数である。--------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------


void gnp::Gnupstd(Vec_I_DP &p,DP R,DP L,string name)
{

  ps::pipestream gnup("gnuplot");
  gnup<<"set terminal postscript color"<<ps::endl;
  gnup<<"set size square"<<ps::endl;
  gnup<<"set parametric"<<ps::endl;
  gnup<<"set grid"<<ps::endl;
  gnup<<"plot "<<R<<"*cos(t)+("<<p[0]<<"),"<<R<<"*sin(t)+("<<p[1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

  int Xb=(p[0]-R<0)-(p[0]+R>L);//False -> 0,True -> それ以外になることを利用。
  int Yb=(p[1]-R<0)-(p[1]+R>L);//同様にy座標も。
  if(Xb)//つまりXb条件のどちらかを満たすとき。横セルについて
    gnup<<"replot "<<R<<"*cos(t)+("<<p[0]+Xb*L<<"),"<<R<<"*sin(t)+("<<p[1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
  if(Yb)//Yb条件のどちらかを満たすとき。縦セルについて
    gnup<<"replot "<<R<<"*cos(t)+("<<p[0]<<"),"<<R<<"*sin(t)+("<<p[1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
  if(Xb&&Yb)//斜めセルについて
    gnup<<"replot "<<R<<"*cos(t)+("<<p[0]+Xb*L<<"),"<<R<<"*sin(t)+("<<p[1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

  const int N=p.size();
  for(int i=2;i<N;i+=2)
    {
  gnup<<"replot "<<R<<"*cos(t)+("<<p[i]<<"),"<<R<<"*sin(t)+("<<p[i+1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

      //--------------------------------------------------------
      //以下目視しやすさのため他セルから
      //自セルに割り込んでいる粒子もプロットする。
      //--------------------------------------------------------
      Xb=(p[i]-R<0)-(p[i]+R>L);//False -> 0,True -> それ以外になることを利用。
      Yb=(p[i+1]-R<0)-(p[i+1]+R>L);//同様にy座標も。
      if(Xb)//つまりXb条件のどちらかを満たすとき。横セルについて
	gnup<<"replot "<<R<<"*cos(t)+("<<p[i]+Xb*L<<"),"<<R<<"*sin(t)+("<<p[i+1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
      if(Yb)//Yb条件のどちらかを満たすとき。縦セルについて
	gnup<<"replot "<<R<<"*cos(t)+("<<p[i]<<"),"<<R<<"*sin(t)+("<<p[i+1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
      if(Xb&&Yb)//斜めセルについて
	gnup<<"replot "<<R<<"*cos(t)+("<<p[i]+Xb*L<<"),"<<R<<"*sin(t)+("<<p[i+1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

    }

  gnup<<"set xrange [0:"<<L<<"]"<<ps::endl;
  gnup<<"set yrange [0:"<<L<<"]"<<ps::endl;
  //  gnup<<"set trange [0:"<<Leng<<"]"<<ps::endl;
  gnup<<"set output '"<<name<<".eps'"<<ps::endl;
  gnup<<"replot"<<ps::endl;
  gnup.close();
}



//--------------------------------------------------------------
//-------------------------2DBIver------------------------------
//--------------------------------------------------------------

void gnp::GnupstdBI(Vec_I_DP &p,DP R,DP L,string name,DP ratio)
{
  DP Ri=R;//disk num:[0~(N/2)-1]->"R",[(N/2)~N-1]->"1.4*R"


  ps::pipestream gnup("gnuplot");
  gnup<<"set terminal postscript color"<<ps::endl;
  gnup<<"set size square"<<ps::endl;
  gnup<<"set parametric"<<ps::endl;
  gnup<<"set grid"<<ps::endl;
  gnup<<"plot "<<Ri<<"*cos(t)+("<<p[0]<<"),"<<Ri<<"*sin(t)+("<<p[1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

  int Xb=(p[0]-Ri<0)-(p[0]+Ri>L);//False -> 0,True -> それ以外になることを利用。
  int Yb=(p[1]-Ri<0)-(p[1]+Ri>L);//同様にy座標も。
  if(Xb)//つまりXb条件のどちらかを満たすとき。横セルについて
    gnup<<"replot "<<Ri<<"*cos(t)+("<<p[0]+Xb*L<<"),"<<Ri<<"*sin(t)+("<<p[1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
  if(Yb)//Yb条件のどちらかを満たすとき。縦セルについて
    gnup<<"replot "<<Ri<<"*cos(t)+("<<p[0]<<"),"<<Ri<<"*sin(t)+("<<p[1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
  if(Xb&&Yb)//斜めセルについて
    gnup<<"replot "<<Ri<<"*cos(t)+("<<p[0]+Xb*L<<"),"<<Ri<<"*sin(t)+("<<p[1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

  const int N=p.size();
  for(int i=2;i<N;i+=2)
    {
      if(2*i==N)
	Ri*=ratio;
  gnup<<"replot "<<Ri<<"*cos(t)+("<<p[i]<<"),"<<Ri<<"*sin(t)+("<<p[i+1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

      //--------------------------------------------------------
      //以下目視しやすさのため他セルから
      //自セルに割り込んでいる粒子もプロットする。
      //--------------------------------------------------------
      Xb=(p[i]-Ri<0)-(p[i]+Ri>L);//False -> 0,True -> それ以外になることを利用。
      Yb=(p[i+1]-Ri<0)-(p[i+1]+Ri>L);//同様にy座標も。
      if(Xb)//つまりXb条件のどちらかを満たすとき。横セルについて
	gnup<<"replot "<<Ri<<"*cos(t)+("<<p[i]+Xb*L<<"),"<<Ri<<"*sin(t)+("<<p[i+1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
      if(Yb)//Yb条件のどちらかを満たすとき。縦セルについて
	gnup<<"replot "<<Ri<<"*cos(t)+("<<p[i]<<"),"<<Ri<<"*sin(t)+("<<p[i+1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
      if(Xb&&Yb)//斜めセルについて
	gnup<<"replot "<<Ri<<"*cos(t)+("<<p[i]+Xb*L<<"),"<<Ri<<"*sin(t)+("<<p[i+1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

    }

  gnup<<"set xrange [0:"<<L<<"]"<<ps::endl;
  gnup<<"set yrange [0:"<<L<<"]"<<ps::endl;
  //  gnup<<"set trange [0:"<<Leng<<"]"<<ps::endl;
  gnup<<"set output '"<<name<<".eps'"<<ps::endl;
  gnup<<"replot"<<ps::endl;
  gnup.close();
}






//-------------------------------------------------------------------
//--------------------------GnupForce--------------------------------
//-------------------------------------------------------------------

void gnp::GnupForce(Vec_I_DP &p,DP R,DP L,string name)
{


  ps::pipestream gnup("gnuplot");
  gnup<<"set terminal postscript color"<<ps::endl;
  gnup<<"set size square"<<ps::endl;
  gnup<<"set parametric"<<ps::endl;
  gnup<<"set grid"<<ps::endl;
  gnup<<"plot "<<R<<"*cos(t)+("<<p[0]<<"),"<<R<<"*sin(t)+("<<p[1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

  int Xb=(p[0]-R<0)-(p[0]+R>L);//False -> 0,True -> それ以外になることを利用。
  int Yb=(p[1]-R<0)-(p[1]+R>L);//同様にy座標も。
  if(Xb)//つまりXb条件のどちらかを満たすとき。横セルについて
    gnup<<"replot "<<R<<"*cos(t)+("<<p[0]+Xb*L<<"),"<<R<<"*sin(t)+("<<p[1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
  if(Yb)//Yb条件のどちらかを満たすとき。縦セルについて
    gnup<<"replot "<<R<<"*cos(t)+("<<p[0]<<"),"<<R<<"*sin(t)+("<<p[1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
  if(Xb&&Yb)//斜めセルについて
    gnup<<"replot "<<R<<"*cos(t)+("<<p[0]+Xb*L<<"),"<<R<<"*sin(t)+("<<p[1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

  const int N=p.size();
  for(int i=2;i<N;i+=2)
    {
  gnup<<"replot "<<R<<"*cos(t)+("<<p[i]<<"),"<<R<<"*sin(t)+("<<p[i+1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

      //--------------------------------------------------------
      //以下目視しやすさのため他セルから
      //自セルに割り込んでいる粒子もプロットする。
      //--------------------------------------------------------
      Xb=(p[i]-R<0)-(p[i]+R>L);//False -> 0,True -> それ以外になることを利用。
      Yb=(p[i+1]-R<0)-(p[i+1]+R>L);//同様にy座標も。
      if(Xb)//つまりXb条件のどちらかを満たすとき。横セルについて
	gnup<<"replot "<<R<<"*cos(t)+("<<p[i]+Xb*L<<"),"<<R<<"*sin(t)+("<<p[i+1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
      if(Yb)//Yb条件のどちらかを満たすとき。縦セルについて
	gnup<<"replot "<<R<<"*cos(t)+("<<p[i]<<"),"<<R<<"*sin(t)+("<<p[i+1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
      if(Xb&&Yb)//斜めセルについて
	gnup<<"replot "<<R<<"*cos(t)+("<<p[i]+Xb*L<<"),"<<R<<"*sin(t)+("<<p[i+1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

    }


  //---------------Force Networkの図示----------------------
  DP xlow,xhigh,ylow,yhigh,dumm,sgm,relrx,relry,relr,tmphx,tmphy,eps=numeric_limits<double>::epsilon()*1e+9,relrtot=0.0;//eps is small value in frprmn,1CG method atari O(1e-6)no gosa dattanode 1e+(4+5) wo kaketeiru
  int slope,extcnt,chng,bndnm=0;
  string red="16711680",green="44200",blue="255",yellow="13816320",clr,lb="1";


  /*
  for(int i=2;i<N;i+=2)
    {
      for(int j=0;j<i;j+=2)
	{
	  sgm=R+R;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];


	  if(fabs(relrx)>L-sgm || fabs(relry)>L-sgm)
	    //上記の条件でポテンシャルに寄与するので
	    //隣接セルとの評価をおこなう(i粒子を固定して下の解釈である)
	    // A B C
	    // D x E
	    // F G H
	    //xを自セルとして上記の他セルとの評価を行う。
	    {
	      if(fabs(relrx-L)<sgm)//A or D or F
		relrx-=L;
	      else if(fabs(relrx+L)<sgm)// C or E or H
		relrx+=L;
	      //なにもしない otherwise (B or G)

	      if(fabs(relry-L)<sgm)//F or G or H
		relry-=L;
	      else if(fabs(relry+L)<sgm)//A or B or C
		relry+=L;
	      //なにもしない　otherwise (D or E)
	    }
	  relr=sqrt(pow(relrx,2)+pow(relry,2));
	  if(relr<sgm)
	    {
	      relrtot+=relr;
	      bndnm+=1;
	    }
	}
    }

  relrtot/=bndnm;// half of mean internal distance 
*/

  for(int i=2;i<N;i+=2)
    {
      for(int j=0;j<i;j+=2)
	{
	  extcnt=0;

	  tmphx=p[j];
	  tmphy=p[j+1];

	  sgm=R+R;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];


	  if(fabs(relrx)>L-sgm || fabs(relry)>L-sgm)
	    //上記の条件でポテンシャルに寄与するので
	    //隣接セルとの評価をおこなう(i粒子を固定して下の解釈である)
	    // A B C
	    // D x E
	    // F G H
	    //xを自セルとして上記の他セルとの評価を行う。
	    {
	      if(fabs(relrx-L)<sgm)//A or D or F
		{
		  tmphx=p[j]-L;
		  relrx-=L;
		}
	      else if(fabs(relrx+L)<sgm)// C or E or H
		{
		  tmphx=p[j]+L;
		  relrx+=L;
		}
	      //なにもしない otherwise (B or G)

	      if(fabs(relry-L)<sgm)//F or G or H
		{
		  tmphy=p[j+1]-L;
		  relry-=L;
		}
	      else if(fabs(relry+L)<sgm)//A or B or C
		{
		  tmphy=p[j+1]+L;
		  relry+=L;
		}
	      //なにもしない　otherwise (D or E)
	      extcnt=1;//余分にラインを引かなければならないのでカウントを増やして対応する。
	    }
	  relr=sqrt(pow(relrx,2)+pow(relry,2));

	  clr=blue; // force line color

	  /*
	  if(fabs(relr-sgm)<sgm*eps)// the internal force is extremely small.
	    clr=yellow;
	  else if(relr<relrtot)// if the internal force is larger than mean one(but not mean force if not harmonic potential)
	    clr=red;
	  else//otherwise
	    clr=blue;

	  */

	  if(fabs(relr-sgm)<1e-10)
	    lb="1";
	  else if(fabs(relr-sgm)>=1e-10 && fabs(relr-sgm)<1e-9)
	    lb="2";
	  else if(fabs(relr-sgm)>=1e-9 && fabs(relr-sgm)<1e-8)
	    lb="3";
	  else if(fabs(relr-sgm)>=1e-8 && fabs(relr-sgm)<1e-7)
	    lb="4";
	  else if(fabs(relr-sgm)>=1e-7 && fabs(relr-sgm)<1e-6)
	    lb="5";
	  else if(fabs(relr-sgm)>=1e-6 && fabs(relr-sgm)<1e-5)
	    lb="6";
	  else if(fabs(relr-sgm)>=1e-5 && fabs(relr-sgm)<1e-4)
	    lb="7";
	  else if(fabs(relr-sgm)>=1e-4 && fabs(relr-sgm)<1e-3)
	    lb="8";
	  else if(fabs(relr-sgm)>=1e-3 && fabs(relr-sgm)<1e-2)
	    lb="9";
	  else if(fabs(relr-sgm)>=1e-2 && fabs(relr-sgm)<1e-1)
	    lb="10";
	  else if(fabs(relr-sgm)>=1e-1 && fabs(relr-sgm)<1)
	    lb="11";
	  else
	    lb="12";

	  if(relr<sgm)
	    {
	      xhigh=tmphx;//仮にhighのほうにj粒子座標を代入
	      yhigh=tmphy;
	      xlow=p[i];//仮にlowのほうにi粒子座標を代入
	      ylow=p[i+1];

	      slope=1;
	      chng=0;
	      if(xhigh<-sgm || xhigh>L+sgm)//j粒子が枠外の場合は粒子間距離の描写をしないようにする。
		chng+=2;

	      if(fabs(relry/relrx)>1)//傾きの大きさが1よりも大きい場合、y=tの媒介変数でx=at+bの直線を描く。
		{
		  if(yhigh<ylow)
		    {
		      dumm=ylow;//後のgnuplotのt制限のためにyのみを入れ替える
		      ylow=yhigh;
		      yhigh=dumm;
		      slope=-1;
		      chng+=1;
		    }
		  if(chng==0)
		    gnup<<"replot ("<<slope*(xhigh-xlow)/(yhigh-ylow)<<")*(t-"<<ylow<<")+"<<xlow<<",((t<"<<ylow<<")?NaN:((t>"<<yhigh<<")?NaN:t))"<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		  else if(chng==1)
		    gnup<<"replot ("<<slope*(xhigh-xlow)/(yhigh-ylow)<<")*(t-"<<yhigh<<")+"<<xlow<<",((t<"<<ylow<<")?NaN:((t>"<<yhigh<<")?NaN:t))"<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		}
	      else//傾きが1以下のとき、x=tの媒介変数でy=at+bの直線を描く。
		{
		  if(xhigh<xlow)
		    {
		      dumm=xlow;
		      xlow=xhigh;
		      xhigh=dumm;
		      slope=-1;
		      chng=+1;
		    }
		  //i粒子固定の描写である。
		  if(chng==0)
		    gnup<<"replot ((t<"<<xlow<<")?NaN:((t>"<<xhigh<<")?NaN:t)),("<<slope*(yhigh-ylow)/(xhigh-xlow)<<")*(t-"<<xlow<<")+"<<ylow<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		  else if(chng==1)
		    gnup<<"replot ((t<"<<xlow<<")?NaN:((t>"<<xhigh<<")?NaN:t)),("<<slope*(yhigh-ylow)/(xhigh-xlow)<<")*(t-"<<xhigh<<")+"<<ylow<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		}


	      if(extcnt==1)//逆側にも描写しなければならない。
		{
		  //----------j粒子を元に戻し、i粒子を移動させる。----------------
		  if(tmphx<0)
		    {
		      xhigh=p[j];
		      xlow=p[i]+L;
		    }
		  else if(tmphx>L)
		    {
		      xhigh=p[j];
		      xlow=p[i]-L;
		    }
		  else
		    {
		      xhigh=p[j];
		      xlow=p[i];
		    }

		  if(tmphy<0)
		    {
		      yhigh=p[j+1];
		      ylow=p[i+1]+L;
		    }
		  else if(tmphy>L)
		    {
		      yhigh=p[j+1];
		      ylow=p[i+1]-L;
		    }
		  else
		    {
		      yhigh=p[j+1];
		      ylow=p[i+1];
		    }
		  //--------------------------------------------------------------
		  slope=1;
		  chng=0;
		  if(xlow<-sgm || xlow>L+sgm)//先ほどと同様にこのときは描画しない。
		    chng+=2;

		  if(fabs(relry/relrx)>1)//傾きの大きさが1よりも大きい場合、y=tの媒介変数でx=直線を描く。
		    {
		      if(yhigh<ylow)
			{
			  dumm=ylow;
			  ylow=yhigh;
			  yhigh=dumm;
			  slope=-1;
			  chng+=1;
			}
		      if(chng==0)
			gnup<<"replot ("<<slope*(xhigh-xlow)/(yhigh-ylow)<<")*(t-"<<ylow<<")+"<<xlow<<",((t<"<<ylow<<")?NaN:((t>"<<yhigh<<")?NaN:t))"<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		      else if(chng==1)
			gnup<<"replot ("<<slope*(xhigh-xlow)/(yhigh-ylow)<<")*(t-"<<yhigh<<")+"<<xlow<<",((t<"<<ylow<<")?NaN:((t>"<<yhigh<<")?NaN:t))"<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		    }
		  else
		    {
		      if(xhigh<xlow)
			{
			  dumm=xlow;
			  xlow=xhigh;
			  xhigh=dumm;
			  slope=-1;
			  chng=+1;
			}
		      //i粒子固定の描写である。
		      if(chng==0)
			gnup<<"replot ((t<"<<xlow<<")?NaN:((t>"<<xhigh<<")?NaN:t)),("<<slope*(yhigh-ylow)/(xhigh-xlow)<<")*(t-"<<xlow<<")+"<<ylow<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		      else if(chng==1)
			gnup<<"replot ((t<"<<xlow<<")?NaN:((t>"<<xhigh<<")?NaN:t)),("<<slope*(yhigh-ylow)/(xhigh-xlow)<<")*(t-"<<xhigh<<")+"<<ylow<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		    }
		}//逆側描画end(if extcnt==1)

	    }//if relr<sgm end

	}//for-j-end
    }//for-i-end
  //---------------------Force Network図示end-------------------------------
  gnup<<"set xrange [0:"<<L<<"]"<<ps::endl;
  gnup<<"set yrange [0:"<<L<<"]"<<ps::endl;
  gnup<<"set trange [0:"<<L<<"]"<<ps::endl;
  gnup<<"set output '"<<name<<".eps'"<<ps::endl;
  gnup<<"replot"<<ps::endl;
  gnup.close();
}






//-------------------------------------------------------------------
//--------------------------GnupForce(2DBI)--------------------------
//-------------------------------------------------------------------

void gnp::GnupForceBI(Vec_I_DP &p,DP R,DP L,string name,DP ratio)
{
  DP Ri=R,Rj;//disk num:[0~(N/2)-1]->"R",[(N/2)~N-1]->"1.4*R"


  ps::pipestream gnup("gnuplot");
  gnup<<"set terminal postscript color"<<ps::endl;
  gnup<<"set size square"<<ps::endl;
  gnup<<"set parametric"<<ps::endl;
  gnup<<"set grid"<<ps::endl;
  gnup<<"plot "<<Ri<<"*cos(t)+("<<p[0]<<"),"<<Ri<<"*sin(t)+("<<p[1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

  int Xb=(p[0]-Ri<0)-(p[0]+Ri>L);//False -> 0,True -> それ以外になることを利用。
  int Yb=(p[1]-Ri<0)-(p[1]+Ri>L);//同様にy座標も。
  if(Xb)//つまりXb条件のどちらかを満たすとき。横セルについて
    gnup<<"replot "<<Ri<<"*cos(t)+("<<p[0]+Xb*L<<"),"<<Ri<<"*sin(t)+("<<p[1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
  if(Yb)//Yb条件のどちらかを満たすとき。縦セルについて
    gnup<<"replot "<<Ri<<"*cos(t)+("<<p[0]<<"),"<<Ri<<"*sin(t)+("<<p[1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
  if(Xb&&Yb)//斜めセルについて
    gnup<<"replot "<<Ri<<"*cos(t)+("<<p[0]+Xb*L<<"),"<<Ri<<"*sin(t)+("<<p[1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

  const int N=p.size();
  for(int i=2;i<N;i+=2)
    {
      if(2*i==N)
	Ri*=ratio;
  gnup<<"replot "<<Ri<<"*cos(t)+("<<p[i]<<"),"<<Ri<<"*sin(t)+("<<p[i+1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

      //--------------------------------------------------------
      //以下目視しやすさのため他セルから
      //自セルに割り込んでいる粒子もプロットする。
      //--------------------------------------------------------
      Xb=(p[i]-Ri<0)-(p[i]+Ri>L);//False -> 0,True -> それ以外になることを利用。
      Yb=(p[i+1]-Ri<0)-(p[i+1]+Ri>L);//同様にy座標も。
      if(Xb)//つまりXb条件のどちらかを満たすとき。横セルについて
	gnup<<"replot "<<Ri<<"*cos(t)+("<<p[i]+Xb*L<<"),"<<Ri<<"*sin(t)+("<<p[i+1]<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
      if(Yb)//Yb条件のどちらかを満たすとき。縦セルについて
	gnup<<"replot "<<Ri<<"*cos(t)+("<<p[i]<<"),"<<Ri<<"*sin(t)+("<<p[i+1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;
      if(Xb&&Yb)//斜めセルについて
	gnup<<"replot "<<Ri<<"*cos(t)+("<<p[i]+Xb*L<<"),"<<Ri<<"*sin(t)+("<<p[i+1]+Yb*L<<") w l lt 1 lc rgb 0 notitle"<<ps::endl;

    }



  //---------------Force Networkの図示----------------------
  DP xlow,xhigh,ylow,yhigh,dumm,sgm,relrx,relry,relr,tmphx,tmphy,eps=numeric_limits<double>::epsilon()*1e+9,relrtot=0.0;//eps is small value in frprmn,1CG method atari O(1e-6)no gosa dattanode 1e+(4+5) wo kaketeiru
  int slope,extcnt,chng,bndnm=0;
  string red="16711680",green="44200",blue="255",yellow="13816320",clr,lb="1";


  /*
  Ri=R;//initialize Ri value
  for(int i=2;i<N;i+=2)
    {
      if(2*i==N)
	Ri*=ratio;
      Rj=R;
      for(int j=0;j<i;j+=2)
	{
	  if(2*j==N)
	    Rj*=ratio;
	  sgm=Ri+Rj;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];


	  if(fabs(relrx)>L-sgm || fabs(relry)>L-sgm)
	    //上記の条件でポテンシャルに寄与するので
	    //隣接セルとの評価をおこなう(i粒子を固定して下の解釈である)
	    // A B C
	    // D x E
	    // F G H
	    //xを自セルとして上記の他セルとの評価を行う。
	    {
	      if(fabs(relrx-L)<sgm)//A or D or F
		relrx-=L;
	      else if(fabs(relrx+L)<sgm)// C or E or H
		relrx+=L;
	      //なにもしない otherwise (B or G)

	      if(fabs(relry-L)<sgm)//F or G or H
		relry-=L;
	      else if(fabs(relry+L)<sgm)//A or B or C
		relry+=L;
	      //なにもしない　otherwise (D or E)
	    }
	  relr=sqrt(pow(relrx,2)+pow(relry,2));
	  if(relr<sgm)
	    {
	      relrtot+=relr;
	      bndnm+=1;
	    }
	}
    }
  relrtot/=bndnm;// half of mean internal distance 

*/

  Ri=R;//initialize Ri value
  for(int i=2;i<N;i+=2)
    {
      if(2*i==N)
	Ri*=ratio;
      Rj=R;
      for(int j=0;j<i;j+=2)
	{
	  if(2*j==N)
	    Rj*=ratio;
	  extcnt=0;

	  tmphx=p[j];
	  tmphy=p[j+1];

	  sgm=Ri+Rj;
	  relrx=p[j]-p[i];
	  relry=p[j+1]-p[i+1];


	  if(fabs(relrx)>L-sgm || fabs(relry)>L-sgm)
	    //上記の条件でポテンシャルに寄与するので
	    //隣接セルとの評価をおこなう(i粒子を固定して下の解釈である)
	    // A B C
	    // D x E
	    // F G H
	    //xを自セルとして上記の他セルとの評価を行う。
	    {
	      if(fabs(relrx-L)<sgm)//A or D or F
		{
		  tmphx=p[j]-L;
		  relrx-=L;
		}
	      else if(fabs(relrx+L)<sgm)// C or E or H
		{
		  tmphx=p[j]+L;
		  relrx+=L;
		}
	      //なにもしない otherwise (B or G)

	      if(fabs(relry-L)<sgm)//F or G or H
		{
		  tmphy=p[j+1]-L;
		  relry-=L;
		}
	      else if(fabs(relry+L)<sgm)//A or B or C
		{
		  tmphy=p[j+1]+L;
		  relry+=L;
		}
	      //なにもしない　otherwise (D or E)
	      extcnt=1;//余分にラインを引かなければならないのでカウントを増やして対応する。
	    }
	  relr=sqrt(pow(relrx,2)+pow(relry,2));

	  clr=blue; // force line color

	  //force line width
	  if(fabs(relr-sgm)<1e-8)
	    lb="1";
	  else if(fabs(relr-sgm)>=1e-8 && fabs(relr-sgm)<1e-6)
	    lb="4";
	  else if(fabs(relr-sgm)>=1e-6 && fabs(relr-sgm)<1e-4)
	    lb="8";
	  else if(fabs(relr-sgm)>=1e-4 && fabs(relr-sgm)<1e-3)
	    lb="12";
	  else if(fabs(relr-sgm)>=1e-3 && fabs(relr-sgm)<1e-2)
	    lb="16";
	  else if(fabs(relr-sgm)>=1e-2 && fabs(relr-sgm)<1e-1)
	    lb="20";
	  else if(fabs(relr-sgm)>=1e-1 && fabs(relr-sgm)<1)
	    lb="24";
	  else
	    lb="30";
/*

	  if(fabs(relr-sgm)<sgm*eps)// the internal force is extremely small.
	    clr=yellow;
	  else if(relr<relrtot)// if the internal force is larger than mean one(but not mean force if not harmonic potential)
	    clr=red;
	  else//otherwise
	    clr=blue;
*/
	  if(relr<sgm)
	    {
	      xhigh=tmphx;
	      yhigh=tmphy;
	      xlow=p[i];
	      ylow=p[i+1];

	      slope=1;
	      chng=0;
	      if(xhigh<-sgm || xhigh>L+sgm)
		chng+=2;

	      if(fabs(relry/relrx)>1)//傾きの大きさが1よりも大きい場合、y=tの媒介変数でx=直線を描く。
		{
		  if(yhigh<ylow)
		    {
		      dumm=ylow;
		      ylow=yhigh;
		      yhigh=dumm;
		      slope=-1;
		      chng+=1;
		    }
		  if(chng==0)
		    gnup<<"replot ("<<slope*(xhigh-xlow)/(yhigh-ylow)<<")*(t-"<<ylow<<")+"<<xlow<<",((t<"<<ylow<<")?NaN:((t>"<<yhigh<<")?NaN:t))"<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		  else if(chng==1)
		    gnup<<"replot ("<<slope*(xhigh-xlow)/(yhigh-ylow)<<")*(t-"<<yhigh<<")+"<<xlow<<",((t<"<<ylow<<")?NaN:((t>"<<yhigh<<")?NaN:t))"<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		}
	      else
		{
		  if(xhigh<xlow)
		    {
		      dumm=xlow;
		      xlow=xhigh;
		      xhigh=dumm;
		      slope=-1;
		      chng=+1;
		    }
		  //i粒子固定の描写である。
		  if(chng==0)
		    gnup<<"replot ((t<"<<xlow<<")?NaN:((t>"<<xhigh<<")?NaN:t)),("<<slope*(yhigh-ylow)/(xhigh-xlow)<<")*(t-"<<xlow<<")+"<<ylow<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		  else if(chng==1)
		    gnup<<"replot ((t<"<<xlow<<")?NaN:((t>"<<xhigh<<")?NaN:t)),("<<slope*(yhigh-ylow)/(xhigh-xlow)<<")*(t-"<<xhigh<<")+"<<ylow<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		}


	      if(extcnt==1)//逆側にも描写しなければならない。
		{
		  //----------j粒子の座標を元に戻してi粒子を動かす。------------
		  if(tmphx<0)
		    {
		      xhigh=p[j];
		      xlow=p[i]+L;
		    }
		  else if(tmphx>L)
		    {
		      xhigh=p[j];
		      xlow=p[i]-L;
		    }
		  else
		    {
		      xhigh=p[j];
		      xlow=p[i];
		    }

		  if(tmphy<0)
		    {
		      yhigh=p[j+1];
		      ylow=p[i+1]+L;
		    }
		  else if(tmphy>L)
		    {
		      yhigh=p[j+1];
		      ylow=p[i+1]-L;
		    }
		  else
		    {
		      yhigh=p[j+1];
		      ylow=p[i+1];
		    }
		  //------------------------------------------------------------
		  slope=1;
		  chng=0;
		  if(xlow<-sgm || xlow>L+sgm)
		    chng+=2;

		  if(fabs(relry/relrx)>1)//傾きの大きさが1よりも大きい場合、y=tの媒介変数でx=直線を描く。
		    {
		      if(yhigh<ylow)
			{
			  dumm=ylow;
			  ylow=yhigh;
			  yhigh=dumm;
			  slope=-1;
			  chng+=1;
			}
		      if(chng==0)
			gnup<<"replot ("<<slope*(xhigh-xlow)/(yhigh-ylow)<<")*(t-"<<ylow<<")+"<<xlow<<",((t<"<<ylow<<")?NaN:((t>"<<yhigh<<")?NaN:t))"<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		      else if(chng==1)
			gnup<<"replot ("<<slope*(xhigh-xlow)/(yhigh-ylow)<<")*(t-"<<yhigh<<")+"<<xlow<<",((t<"<<ylow<<")?NaN:((t>"<<yhigh<<")?NaN:t))"<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		    }
		  else
		    {
		      if(xhigh<xlow)
			{
			  dumm=xlow;
			  xlow=xhigh;
			  xhigh=dumm;
			  slope=-1;
			  chng=+1;
			}
		      //i粒子固定の描写である。
		      if(chng==0)
			gnup<<"replot ((t<"<<xlow<<")?NaN:((t>"<<xhigh<<")?NaN:t)),("<<slope*(yhigh-ylow)/(xhigh-xlow)<<")*(t-"<<xlow<<")+"<<ylow<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		      else if(chng==1)
			gnup<<"replot ((t<"<<xlow<<")?NaN:((t>"<<xhigh<<")?NaN:t)),("<<slope*(yhigh-ylow)/(xhigh-xlow)<<")*(t-"<<xhigh<<")+"<<ylow<<" w l lt 1 lc rgb "<<clr<<" lw "<<lb<<" notitle"<<ps::endl;
		    }

		}//追加描画end(if extcnt==1)
	    }//if relr<sgm end

	}//for-j-end
    }//for-i-end
  //---------------------Force Network図示end-------------------------------
  gnup<<"set xrange [0:"<<L<<"]"<<ps::endl;
  gnup<<"set yrange [0:"<<L<<"]"<<ps::endl;
  gnup<<"set trange [0:"<<L<<"]"<<ps::endl;
  gnup<<"set output '"<<name<<".eps'"<<ps::endl;
  gnup<<"replot"<<ps::endl;
  gnup.close();
}






//--------------------------------------------------------------
//----------------------text reader-----------------------------
//--------------------------------------------------------------

void TXTzahyo2D(Vec_DP &p,string name)//(2Dver.)
{
  string hey=name+".txt";
  ifstream ifs(hey.data());
  string str;

  if(ifs.fail())
    {
      cerr<<"File do not exist.\n";
      exit(0);
    }

  DP a=0,b=0; //dummy variable
  int tmp=0;
  while(getline(ifs,str))
    {
      //      cout<<str;
      sscanf(str.data(),"%lf %lf",&a,&b);
      //      cout<<"a="<<a<<", b="<<b<<'\n';
      tmp+=2;
    }
  Vec_DP hello(tmp);

  a=b=0;
  tmp=0;
  while(getline(ifs,str))
    {
      sscanf(str.data(),"%lf %lf",&a,&b);
      hello[tmp]=a;
      hello[tmp+1]=b;
      tmp+=2;
    }

  p=hello;//return zahyo value read in hoge.txt

}



#endif // _GNP_H_ //
