#ifndef _NR_H_
#define _NR_H_
#include <fstream>
#include <complex>
#include "nrutil.h"
#include "nrtypes.h"

namespace NR
{
	void scrsho(DP fx(const DP));
	void gaussj(Mat_IO_DP &a,Mat_IO_DP &b);
	void piksrt(Vec_IO_DP &arr);
	void piksr2(Vec_IO_DP &arr, Vec_IO_DP &brr);
	void shell(const int m, Vec_IO_DP &a);
	void sort(Vec_IO_DP &arr);
	void sort2(Vec_IO_DP &arr, Vec_IO_DP &brr);
	void sift_down(Vec_IO_DP &ra, const int l, const int r);
	void hpsort(Vec_IO_DP &ra);
	void indexx(Vec_I_DP &arr, Vec_O_INT &indx);
	void indexx(Vec_I_INT &arr, Vec_O_INT &indx);
	void sort3(Vec_IO_DP &ra, Vec_IO_DP &rb, Vec_IO_DP &rc);
	void rank(Vec_I_INT &indx, Vec_O_INT &irank);
	void select(const int k, Vec_IO_DP &arr);
	void selip(const int k, Vec_I_DP &arr);
	void hpsel(Vec_I_DP &arr, Vec_O_DP &heap);
	void eclass(Vec_O_INT &nf, Vec_I_INT &lista, Vec_I_INT &listb);
	void eclazz(Vec_O_INT &nf, bool equiv(const int, const int));
	void four1(Vec_IO_DP &data, const int isign);
	void twofft(Vec_I_DP &data1, Vec_I_DP &data2, Vec_O_DP &fft1, Vec_O_DP &fft2);
	void realft(Vec_IO_DP &data,const int isign);
	void sinft(Vec_IO_DP &y);
	void cosft1(Vec_IO_DP &y);
	void cosft2(Vec_IO_DP &y,const int isign);
	void fourn(Vec_IO_DP &data,Vec_I_INT &nn,const int isign);
	void rlft3(Mat3D_IO_DP &data,Mat_IO_DP &speq,const int isign);
	void fourfs(Vec_FSTREAM_p &file,Vec_I_INT &nn,const int isign);

	void tqli(Vec_IO_DP &d, Vec_IO_DP &e, Mat_IO_DP &z);
	void tred2(Mat_IO_DP &a, Vec_O_DP &d, Vec_O_DP &e);
	DP pythag(const DP a, const DP b);
	
//-------------------------
//以下10章の関数を並べる。
//-------------------------
	//void frprmn(Vec_IO_DP &p, const DP ftol, int &iter, DP &fret, DP func(Vec_I_DP &), void dfunc(Vec_I_DP &, Vec_O_DP &)); default function

	//--うちの作成したCG法用の関数たちなのん！
        DP potential(Vec_I_DP &q, DP Len,DP R,DP rt,DP alp,int Prt,int D);
	DP potential3D(Vec_I_DP &q, DP Len,DP R,DP rt,DP alp,int Prt,int D);
	void Hesspot(Vec_I_DP &p, Mat_O_DP &H,DP Len,DP R,DP rt,DP alp,int Prt,int D);
	void Hesspot3D(Vec_I_DP &p, Mat_O_DP &H,DP Len,DP R,DP rt,DP alp,int Prt,int D);
	//-- Velocity Verlet method
	void VVforce_F(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F,Vec_O_DP &Fpot, DP dmpt,DP mass,DP tstep,DP Len,DP R,DP rt,DP alp,int Prt,int D,bool &relax);
	void VVforce_F3D(Vec_I_DP &p, Vec_I_DP &vel, Vec_IO_DP &F,Vec_O_DP &Fpot, DP dmpt,DP mass,DP tstep,DP Len,DP R,DP rt,DP alp,int Prt,int D,bool &relax);
	void nextcod_F(Vec_IO_DP &zahyo, Vec_I_DP &vel, Vec_I_DP &F, DP tstep,DP Len);
	void nextvel_F(Vec_IO_DP &vel, Vec_I_DP &Fnxt,Vec_I_DP &F);
	void Velocity_Verlet_F(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,int,int),const DP ftol,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV);
	void Velocity_Verlet_F3D(Vec_IO_DP &p, Vec_IO_DP &vel, DP &dmpt,DP mass, DP &tstep, DP func(Vec_I_DP &,DP,DP,DP,DP,int,int),const DP ftol,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV);
	void Gen_MBdist(Vec_IO_DP &vel, DP mass, DP kT,DP rt,DP Prt);
	void jacobi(Mat_IO_DP &a, Vec_O_DP &d, Mat_O_DP &v, int &nrot);
	void eigsrt(Vec_IO_DP &d,Mat_IO_DP &v);
	void FIRE(Vec_IO_DP &vel, Vec_I_DP &Fpot, DP &dmpt,DP &tstep, DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE, int &ITER);
    //void Frms(Vec_I_DP &F, );

	void ModeCalc(Vec_IO_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,int D,bool &minus);
      	void ModeCalc3D(Vec_IO_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,int D,bool &minus);
	void CollectiveMotionCheck(Mat_I_DP &EigMat,Vec_IO_DP &CMnum);
	void InfComp(Vec_IO_DP &zahyo,DP PHI,DP Len,DP R,DP rt,DP alp,int Prt);

	void deriveEigvec(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,Vec_O_DP &out,int D,int vecnum);
	void deriveEigvec3D(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,Vec_O_DP &out,int D,int vecnum);
       	void outputPEL(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,Vec_I_DP &eigvec,int D,int vecnum);
	void outputPEL3D(Vec_I_DP &zahyo,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,Vec_I_DP &eigvec,int D,int vecnum);

	void DISTcod(Vec_I_DP &p,Vec_IO_DP &Dcod,DP R,DP L,DP rt,int Prt,int D);
	void tapping(Vec_IO_DP& EigDispvec,DP eigval,DP eng,DP EPS);

	void WriteEigInfo(Mat_I_DP &Eigmat,Vec_I_DP &Eigval,int num,DP phi);

	void noise(Vec_IO_DP& p,Vec_IO_DP& vel,DP &dmpt,DP mass, DP& tstep,DP func(Vec_I_DP &,DP,DP,DP,DP,int,int),const DP ftol,DP Len,DP R,DP rt,DP alp,int Prt,int num,DP phi,DP fra_inc, DP fra_dec, DP fra_alp, DP dmpt_init, DP tstep_max, int ITFIRE,int D,int &iterVV,DP CRadBI);




	//CGmethodの関数
	void frprmn(Vec_IO_DP &p, const DP ftol, int &iter, DP &fret, DP Len,DP R,DP rt,DP alp,DP Prt,int D,DP func(Vec_I_DP &,DP,DP,DP,DP,int,int), void dfunc(Vec_I_DP &, Vec_O_DP &,DP,DP,DP,DP,int,int));

	void linmin(Vec_IO_DP &p, Vec_IO_DP &xi, DP &fret, DP func(Vec_I_DP &)); 
	void dlinmin(Vec_IO_DP &p, Vec_IO_DP &xi, DP &fret, DP func(Vec_I_DP &,DP,DP,DP,DP,int,int), void dfunc(Vec_I_DP &, Vec_O_DP &,DP,DP,DP,DP,int,int),DP Len,DP R,DP rt,DP alp,int Prt,int D);
	DP f1dim(const DP x,DP Len,DP R,DP rt,DP alp,int Prt,int D);
	DP df1dim(const DP x,DP Len,DP R,DP rt,DP alp,int Prt,int D);
	DP dbrent(const DP ax, const DP bx, const DP cx, DP f(const DP,DP,DP,DP,DP,int,int),DP df(const DP,DP,DP,DP,DP,int,int), const DP tol, DP &xmin,DP Len,DP R,DP rt,DP alp,int Prt,int D);
	void mnbrak(DP &ax, DP &bx, DP &cx, DP &fa, DP &fb, DP &fc,DP func(const DP,DP,DP,DP,DP,int,int),DP Len,DP R,DP rt,DP alp,int Prt,int D);


	void nabV(Vec_I_DP &q, Vec_O_DP &xi,DP Len,DP R,DP rt,DP alp,int Prt,int D);
	void nabV3D(Vec_I_DP &q, Vec_O_DP &xi,DP Len,DP R,DP rt,DP alp,int Prt,int D);


	
	
	
}
#endif /* _NR_H_ */
