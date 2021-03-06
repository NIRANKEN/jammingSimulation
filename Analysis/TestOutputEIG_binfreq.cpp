#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <limits>
#include <cmath>

#include "freqBIN.h"

using namespace std;
//0.EVal
//1.Freq
//2.IPR
//3.IPR_1st(small)
//4.IPR_2nd(large)
//5.the number of the participating particles (1st component)
//6.DPHI
//7.DPHI (center point (logscale))

//    ||
//    ||
//    \/

//0.Freq (bin_middle point)
//1.IPR (mean)
//2.IPR_min
//3.IPR_max
//4.IPR_variance -DY(log scale)
//5.IPR_variance +DY(log scale)
//6.IPR_1st component (mean)
//7.IPR_2nd component (mean)
//8.Ratio of small particles component for i-th eigenvector (mean)
//9.DOS (zero eig なし)
//10.DOS (zero eig あり)
//11.cum DOS (zero eig なし)
//12.binに入ったFreqの数
//13.粒子数
//14.DPHIの値(logscale bin middle point)
//15.None
//16.None
//17.None


//sampleのデータを集めるだけ。
int main(int argc, char* argv[])
{
  if(argc!=2)
    {
      // cout<<"引数が"<<argc<<"個宣言されています.\n";
      // cout<<"-----\n引数1...bin幅(log10)\n----------\nになります.(default: 0.05)\n";
      exit(1);
    }
  
  //int dimension,Particlenum;
  double binrange=atof(argv[1]);//,EPS=numeric_limits<double>::epsilon();
  string dt,disperse,Pnum,dim;
  string wt,rdtmp="EIGEnsAve_",rd,str;
  //stringstream ss;
  ifstream ifs;
  ifstream::pos_type pos_tmp;
  ofstream ofs;
  int N;

  binstat::InputStr(dt,disperse,Pnum,dim);
  //dimension=atoi(dim.c_str());
  //Particlenum=atoi(Pnum.c_str());
  
  rd=rdtmp+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ifs.open(rd.data());
  wt=rdtmp+"BR"+argv[1]+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  ofs.open(wt.data());
  N=atoi(Pnum.data());
  // cout<<"\n\nBINでの統計処理を開始します..."<<endl;
  bool detectFile=true;
  //ファイル開けなかったら次のサンプルへ.
  if(ifs.fail()) {
    rd="MScaled_"+rd;//読み込みデータ名その1, new版3Dパターン
    ifs.close();
    ifs.clear();
    ifs.open(rd.data());
  }
  if(ifs.fail()) {
    cerr<<"catnot open your file..."<<endl;
    detectFile=false;
  }
  if(detectFile) {
    int countIFS=0,countNonzeroEIG=0,zeroeig=0;
    double eigTableVal[9]={0,0,0,0,0,0,0,0,0},EPS=numeric_limits<double>::epsilon();
    // cout<<ifs.tellg()<<endl;
    while(getline(ifs,str)) {
      sscanf(str.data(),"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&eigTableVal[0],&eigTableVal[1],&eigTableVal[2],&eigTableVal[3],&eigTableVal[4],&eigTableVal[5],&eigTableVal[6],&eigTableVal[7],&eigTableVal[8]);
      if(fabs(eigTableVal[0])>EPS){ countNonzeroEIG++; }
      else { zeroeig++; }
      countIFS++;
    }
    ifs.clear();//clear fail and eof bits
    ifs.seekg(0,ios::beg);// back to the start
    // cout<<ifs.tellg()<<endl;
    str="";
    /*
      const int C=cnt;
      Vec_DP phi(C),eng(C),vviter(C);
      DP PHIJ=0.0;
    */
    double cum_inv=1.0/countNonzeroEIG,Range_e,Range_s,Range_m,Range_sinit,Range_sln10,Range_mln10,dphi; //Rangetmpはbinの始点,Rangeはbinの終点.
    binstat::iprset ipr_all,ipr_1,ipr_2;//cum_invは1.0/nonzeroデータ数.
    const int countIFS_ALL=countIFS;
    int countIFS_freq=0,countIFS_tmp,countIFS_freq_tmp,countNonzeroEIG_tmp;
    bool zeroEigSearched=false,deviationCalculated=false;
    countNonzeroEIG=countIFS=0;
      
    binstat::InputBINrange(binrange);//引数で入力したbin幅が妥当だったらスルー.
    binstat::initializeBINrange(Range_sinit,Range_s,Range_e,Range_m,Range_sln10,Range_mln10);
    binstat::updateBINrange(Range_s,Range_e,Range_m,Range_sln10,Range_mln10,binrange);
    while(getline(ifs,str)) {
      sscanf(str.data(),"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&eigTableVal[0],&eigTableVal[1],&eigTableVal[2],&eigTableVal[3],&eigTableVal[4],&eigTableVal[5],&eigTableVal[6],&eigTableVal[7],&eigTableVal[8]);

      if(countIFS==0) {	
	//初回の行動
	////DPHI格納、IPR格納(freqがEPSより大きかったらエラー)しなくてもいいか
	//dphi=eigTableVal[7]; //PHIbinのmiddle point(log)
	dphi=eigTableVal[8]; //PHIbinでのmean value
	if(fabs(eigTableVal[0])<=EPS) { binstat::ZeroEigenValprocess(countIFS_freq); }
	else {
	  //cerr<<"初回のFrequencyが大きすぎますです!"<<endl; exit(1);
	  if(eigTableVal[1]>=Range_e) {
	    binstat::conserveCurrentState(countIFS_freq,countNonzeroEIG,countIFS_tmp,countNonzeroEIG_tmp,ifs,pos_tmp);
	    while(eigTableVal[1]>=Range_e) {
	      binstat::updateBINrange(Range_s,Range_e,Range_m,Range_sln10,Range_mln10,binrange);
	    }
	    if(eigTableVal[1]<Range_s||eigTableVal[1]>=Range_e) {
	      cerr<<"range-error!!"<<endl;
	      cerr<<setprecision(10)<<"omega is "<<eigTableVal[1]<<", range is"<<Range_s<<"<= xx <"<<Range_e<<endl;
	      exit(1);
	    }
	    deviationCalculated=true;
	    binstat::InitializeBI_IPRs(ipr_all,ipr_1,ipr_2,eigTableVal[2],eigTableVal[3],eigTableVal[4],eigTableVal[5],countIFS_freq,deviationCalculated);
	    zeroEigSearched=true;
	  }
	  else { cerr<<"zerofreq_mode-False-ver binstat method is invalid."<<endl; exit(1); }
	}
      }
      else {
	//2回目以降
	if(fabs(eigTableVal[0])<=EPS) {
	  binstat::ZeroEigenValprocess(countIFS_freq);
	  //zeroFreq-process
	  // cout<<"zero freq method: "<<eigTableVal[1]<<endl;
	}
	else {
	  if(zeroEigSearched) {
	    //nonzeroFreq-preocess
	    /*
	      if(eigTableVal[1]<Range_sinit || isnan(eigTableVal[1])) {
	      //nonzero-freqが初期のfreq-BINよりも小さい、もしくはNaN.
	      cerr<<"初期のNonzero-freqルーチンで失敗^^"<<endl;
	      exit(1);
	      }
	    */
	    if(eigTableVal[1]>=Range_s && eigTableVal[1]<Range_e) { //freq-bin内処理 IPRの和とbin内カウント更新.
	      binstat::innerBINprocess(ipr_all,ipr_1,ipr_2,eigTableVal[2],eigTableVal[3],eigTableVal[4],eigTableVal[5],N,dphi,Range_s,Range_e,Range_m,countIFS_freq,countIFS_ALL,countIFS,cum_inv,countNonzeroEIG,countIFS_tmp,countIFS_freq_tmp,countNonzeroEIG_tmp,ofs,ifs,pos_tmp,deviationCalculated);
	      // cout<<"bin内method: "<<eigTableVal[1]<<endl;
	    }
	    else { //freq-bin外処理
	      if(eigTableVal[1]<Range_s) { cerr<<"きちんとソートできてないぞい!!"<<endl; exit(1); }
	      binstat::updateBINprocess(ipr_all,ipr_1,ipr_2,eigTableVal[1],eigTableVal[2],eigTableVal[3],eigTableVal[4],eigTableVal[5],N,dphi,Range_s,Range_e,Range_m,Range_sln10,Range_mln10,binrange,countIFS_freq,countIFS_ALL,countIFS,cum_inv,countNonzeroEIG,countIFS_tmp,countIFS_freq_tmp,countNonzeroEIG_tmp,ofs,ifs,pos_tmp,deviationCalculated);
	      // cout<<"bin外method: "<<Range_s<<"<"<<eigTableVal[1]<<"<"<<Range_e<<endl;
	    }
	  }
	  else {
	    if(countNonzeroEIG==0) {
	      binstat::ZeroEigenValWrite(ipr_all,ipr_1,ipr_2,N,dphi,eigTableVal[1],eigTableVal[2],eigTableVal[3],eigTableVal[4],eigTableVal[5],Range_s,Range_e,Range_m,Range_sln10,Range_mln10,binrange,zeroeig,countIFS_freq,countIFS_ALL,countIFS,countNonzeroEIG,countIFS_tmp,countIFS_freq_tmp,countNonzeroEIG_tmp,ofs,ifs,pos_tmp,deviationCalculated,zeroEigSearched);
	      // cout<<"const nonzero eig method: "<<Range_s<<"<"<<eigTableVal[1]<<"<"<<Range_e<<endl;
	    }
	    else { cerr<<"固有振動数のソートがきちんとできていません."<<endl; exit(1); }
	  }
	  countNonzeroEIG++;
	}
      }
      countIFS++;
      if(countIFS>countIFS_ALL) { cerr<<"==========================\n==== counting-error!! ====\n=========================="<<endl; exit(1); }
      else if(countIFS==countIFS_ALL) {	/*cout<<"ifstreamの読み込みが上限に達しました."<<endl;*/ }
    }//while end
    ofs.close();
  }//else(FILE open) end
  ifs.close();
}//end


namespace binstat {
  //テキストR&W用パラメータ代入メソッド.
  //BINrange設定用メソッド.
  void InputBINrange(double &br) {
    int cnt=0;
    while(br<0.0001 || br>0.1) {
      // cout<<"bin幅(log10)が不適切なので再度取ります.入力してください.(MAX:0.1, MIN:0.0001)"<<endl;
      // cout<<"-> ";
      cin>>br;
      cnt+=1;
      if(cnt>20) {
	cerr<<"Invalid binrange for your statistics"<<endl;
	exit(1);
      }
    }    
    return;
  }

  void ZeroEigenValprocess(int &freqC) { freqC++; }

  void ZeroEigenValWrite(iprset &ipr,iprset &ipr1,iprset &ipr2,int N,double DPHI,double b,double c,double d,double e,double sCR,double &S,double &E,double &M,double &Sln10,double &Mln10,double range,int zeroeig,int &freqC,const int allC,int ifsC,int cumcnt,int &ifsC_tmp,int &freqC_tmp,int &cumcnt_tmp,ofstream &ofs,ifstream &ifs,ifstream::pos_type &ps_tmp,bool &d_calc,bool &zero_searched)
  {
    // cout<<ifsC<<" "<<zeroeig<<endl;
    //if(ifsC==zeroeig) {
    d_calc=true;
    double deltaomega_inv=1.0/(E-S),allC_inv=1.0/allC;
    ofs<<M<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<0<<" "<<allC_inv*ifsC*deltaomega_inv<<" "<<0<<" "<<zeroeig<<" "<<N<<" "<<DPHI<<endl;
    //0で埋めているところをどうするかは後で考える.
    binstat::conserveCurrentState(ifsC,cumcnt,ifsC_tmp,cumcnt_tmp,ifs,ps_tmp);

    while(b>=E) {
      //次に書き込みを行うBIN範囲を探索.
      // cout<<setprecision(10)<<S<<" < "<<b<<" < "<<E<<endl;
      updateBINrange(S,E,M,Sln10,Mln10,range);
    }
    if(b<S||b>=E) {
      cerr<<"range-error!!"<<endl;
      cerr<<setprecision(10)<<"omega is "<<b<<", range is"<<S<<"<= xx <"<<E<<endl;
      exit(1);
    }
    binstat::InitializeBI_IPRs(ipr,ipr1,ipr2,c,d,e,sCR,freqC,d_calc);
    zero_searched=true;
    //}
    //else {
    //cerr<<"ゼロ固有値のカウントがきちんとできていません."<<endl;
    //exit(1);
    //}
  }
  
  //bin内処理メソッド.
  void innerBINprocess(iprset &ipr,iprset &ipr1,iprset &ipr2,double c,double d,double e,double sCR,int N,double DPHI,double S,double E,double M,int &freqC,const int allC,int &ifsC,double cum_inv,int &cumcnt,int &ifsC_tmp,int &freqC_tmp,int &cumcnt_tmp,ofstream &ofs,ifstream &ifs,ifstream::pos_type &ps_tmp,bool &d_calc) {
    binstat::ModifyBI_IPRs(ipr,ipr1,ipr2,c,d,e,sCR,freqC,d_calc);
    if(ifsC==allC-1) {
      double T=1.0/freqC;
      if(d_calc) {
	double variance=T*ipr.sgm,dy=pow(10,sqrt(variance));
	//double variance_1=T*ipr1.sgm;
	//double variance_2=T*ipr2.sgm;
	double deltaomega_inv=1.0/(E-S),allC_inv=1.0/allC;
	//FILE末端ならば書き込み sqrtに意味がない.
	ofs<<M<<" "<<ipr.mean<<" "<<ipr.min<<" "<<ipr.max<<" "<<ipr.mean*(1.0/dy)<<" "<<ipr.mean*dy<<" "<<ipr1.mean<<" "<<ipr2.mean<<" "<<T*ipr.smallCR_sum<<" "<<freqC*cum_inv*deltaomega_inv<<" "<<allC_inv*freqC*deltaomega_inv<<" "<<(cumcnt)*cum_inv<<" "<<freqC<<" "<<N<<" "<<DPHI<<endl;
      }
      else {
	binstat::backToPreIFS(ipr,ipr1,ipr2,freqC,ifsC,cumcnt,ifsC_tmp,freqC_tmp,cumcnt_tmp,ifs,ps_tmp,d_calc);	
      }
    }
  }

  //bin更新処理メソッド.
  void updateBINprocess(iprset &ipr,iprset &ipr1,iprset &ipr2,double b,double c,double d,double e,double sCR,int N,double DPHI,double &S,double &E,double &M,double &Sln10,double &Mln10,double range,int &freqC,const int allC,int &ifsC,double cum_inv,int &cumcnt,int &ifsC_tmp,int &freqC_tmp,int &cumcnt_tmp,ofstream &ofs,ifstream &ifs,ifstream::pos_type &ps_tmp,bool &d_calc) {

    double T=1.0/freqC,variance,deltaomega_inv,allC_inv,dy;
    //
    if(d_calc) {
      if(freqC_tmp!=freqC) {
	// cout<<"Before: "<<freqC_tmp<<" After: "<<freqC<<endl;
	// cout<<"Before: "<<cumcnt_tmp<<" After: "<<cumcnt<<endl;
	// cout<<"Before: "<<ifsC_tmp<<" After: "<<ifsC<<endl;
	cerr<<"戻ってもう一回サーチするルーチンに不備があります."<<endl;
	exit(1);
      }
      variance=T*ipr.sgm;
      dy=pow(10,sqrt(variance));
      //double variance_1=T*ipr1.sgm;
      //double variance_2=T*ipr2.sgm;
      deltaomega_inv=1.0/(E-S);
      allC_inv=1.0/allC;

      //........BINrangeミスってなければ必ずこのループに入る.
      ofs<<M<<" "<<ipr.mean<<" "<<ipr.min<<" "<<ipr.max<<" "<<ipr.mean*(1.0/dy)<<" "<<ipr.mean*dy<<" "<<ipr1.mean<<" "<<ipr2.mean<<" "<<T*ipr.smallCR_sum<<" "<<freqC*cum_inv*deltaomega_inv<<" "<<allC_inv*freqC*deltaomega_inv<<" "<<(cumcnt)*cum_inv<<" "<<freqC<<" "<<N<<" "<<DPHI<<endl;

      binstat::conserveCurrentState(ifsC,cumcnt,ifsC_tmp,cumcnt_tmp,ifs,ps_tmp);
      while(b>=E) {
	//次に書き込みを行うBIN範囲を探索.
	//// cout<<setprecision(10)<<b<<' '<<E<<endl;
	updateBINrange(S,E,M,Sln10,Mln10,range);
      }
      if(b<S||b>=E) {
	cerr<<"range-error!!"<<endl;
	cerr<<setprecision(15)<<"omega is "<<b<<", range is"<<S<<"<= xx <"<<E<<endl;
	exit(1);
      }
      binstat::InitializeBI_IPRs(ipr,ipr1,ipr2,c,d,e,sCR,freqC,d_calc);

      //次の処理に対して,1個分のデータ入った状態で初期化.      
      if(ifsC==allC-1) {
	//updateしたあと、読み込みFILEの末端ならば書き込み(パラメータも更新しとく.)
	/*
	  T=1.0;
	  deltaomega_inv=1.0/(E-S);
	  ofs<<M<<" "<<T*ipr.sum<<" "<<ipr.min<<" "<<ipr.max<<" "<<0.0<<" "<<0.0<<" "<<T*ipr1.sum<<" "<<T*ipr2.sum<<" "<<T*ipr.smallCR_sum<<" "<<freqC*cum_inv*deltaomega_inv<<" "<<allC_inv*freqC*deltaomega_inv<<" "<<(cumcnt+1)*cum_inv<<" "<<freqC<<" "<<N<<" "<<DPHI<<endl;
	*/
      }
      else if(ifsC>=allC){
	//例外処理.
	cerr<<"ifstreamの読み込みが上限に達しています.(updateBINrange-method)"<<endl;
	exit(1);
      }
    }
    else {
      binstat::backToPreIFS(ipr,ipr1,ipr2,freqC,ifsC,cumcnt,ifsC_tmp,freqC_tmp,cumcnt_tmp,ifs,ps_tmp,d_calc);
    }
  }//update end
  
  void backToPreIFS(iprset &ipr,iprset &ipr1,iprset &ipr2,int &freqC,int &ifsC,int &cumcnt,int ifsC_tmp,int &freqC_tmp,int cumcnt_tmp,ifstream &ifs,ifstream::pos_type ps_tmp,bool &d_calc) {
    freqC_tmp=freqC;
    ResetBI_IPRs(ipr,ipr1,ipr2,freqC,d_calc);
    ifs.seekg(ps_tmp);
    ifsC=ifsC_tmp;
    cumcnt=cumcnt_tmp;
    d_calc=true;
  }
  void conserveCurrentState(int ifsC,int cumcnt,int &ifsC_tmp,int &cumcnt_tmp,ifstream &ifs,ifstream::pos_type &ps_tmp) {
    ps_tmp=ifs.tellg();
    ifsC_tmp=ifsC;
    cumcnt_tmp=cumcnt;
  }

  void initializeBINrange(double &Sinit,double &S,double &E,double &M,double &Sln10,double &Mln10) {
    E=1.0e-8;//1.0e-6->1.0e-8
    Mln10=Sln10=-8;//-6->-8
    Sinit=S=M=E;
    return;
  }
  void updateBINrange(double &S,double &E,double &M,double &Sln10,double &Mln10,double range) {
    //// cout<<S<<" "<<M<<" "<<E<<endl;
    S=E;
    Sln10+=range;
    E=pow(10,Sln10);
    Mln10=Sln10+0.5*range;
    M=pow(10,Mln10);
    return;
  }

  void writeEIGinfo_EOF();
  
}//namespace binstat end
