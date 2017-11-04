#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <limits>
#include "nr.h"

using namespace std;


//sampleのデータを集めるだけ。
int main()
{

  int sd_s,sd_e,tmp_i,countdphi=0;
  string rdtmp1,rdtmptmp1="BIPhiEngVV",rdtmp2,rdtmptmp2="EigCum",rdtmp3,rdtmptmp3,rd1,rd2,rd3;
  string dt,disperse,Pnum,dim;
  string wttmp1="PHIJ",wttmp2="EIG",wttmp3="CODDIST",wttmp4="DPHI_DIST",wt1,wt2,wt3,wt4;
  double eps=numeric_limits<double>::epsilon()*1.0e-2;
  
  stringstream ss;
  
  cout<<"本プログラムは,"<<endl;
  cout<<"(1)BIPhiEngVV\"date\"_RANDxxxx_1.txt"<<endl;
  cout<<"(2)EigCum0xxxx_\"phi\".txt"<<endl;
  cout<<"(3)VV\"date\"_CODDISTxxxx_\"phi\".txt"<<endl;
  cout<<"をテキストにまとめるプログラムです.\n"<<endl;

  cout<<"which \"date\" do you execute the FIRE program??"<<endl;
  cout<<"\"date\" (e.g. 0208)-> ";
  cin>>dt;
  cout<<"monodisperse? or bidisperse? (MONO or BI)"<<endl;
  cout<<"->";
  cin>>disperse;
  cout<<"\nHow many particles?? (e.g. 128)"<<endl;
  cout<<"->";
  cin>>Pnum;
  cout<<"\nwhich dimension?? (2D or 3D)";
  cout<<"->";
  cin>>dim;
  wt1=wttmp1+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt2=wttmp2+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt3=wttmp3+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  wt4=wttmp4+'_'+dt+'_'+dim+disperse+'N'+Pnum+".txt";
  
  ofstream ofs1(wt1.data());
  ofstream ofs2(wt2.data());
  ofstream ofs3(wt3.data());
  ofstream ofs4(wt4.data());
    
  //--------------端末表示,seed入力--------------------
  cout<<"seed値のはじまりを入力(intで)おねがいします。->";  
  cin>>sd_s;
  cout<<"\nseed値のおわり(この値のseedは計算しない)を入力(intで)おねがいします。->";  
  cin>>sd_e;
  cout<<'\n'<<sd_s<<"~"<<sd_e<<"までのseed値でテーブルを作成します。\n\n\n";
  //---------------------------------------------------
  
  
  rdtmp1=rdtmptmp1+dt+"_RAND";
  rdtmptmp3="VV"+dt+"_CODDIST";
  cout<<"\n\nsammpling programを開始します..."<<endl;

  //テーブル作成部分
  for(int i=sd_s;i<sd_e;i++) {
    ss.str("");//Initialize.
    ss.clear(stringstream::goodbit);
    ss<<i;
    
    rd1=rdtmp1+ss.str()+"_1.txt";//読み込みデータ名その1
    if(i>=0 && i<10)
      rdtmp2=rdtmptmp2+"0000"+ss.str()+'_';
    else if(i>=10 && i<100)
      rdtmp2=rdtmptmp2+"000"+ss.str()+'_';
    else if(i>=100 && i<1000)
      rdtmp2=rdtmptmp2+"00"+ss.str()+'_';
    else if(i>=1000 && i<10000)
      rdtmp2=rdtmptmp2+'0'+ss.str()+'_';
    else
      rdtmp2=rdtmptmp2+ss.str()+'_';
    rdtmp3=rdtmptmp3+ss.str()+'_';
    
    ifstream ifs1;
    ifs1.open(rd1.data());
    string str1,str2,str3;
    bool detectFile=true;
    //ファイル開けなかったら次のサンプルへ.
    if(ifs1.fail()) {
      rd1=rdtmp1+ss.str()+"_0.8.txt";//読み込みデータ名その1, new版3Dパターン
      ifs1.close();
      ifs1.clear();
      ifs1.open(rd1.data());
    }
    if(ifs1.fail()) {
      cout<<"skipping this RAND"<<i<<'\n';
      detectFile=false;
    }
    if(detectFile) {
      int cnt=0;
      while(getline(ifs1,str1))
	cnt+=1;
      ifs1.clear();//clear fail and eof bits
      ifs1.seekg(0,ios::beg);// back to the start

      const int C=cnt;
      Vec_DP phi(C),eng(C),vviter(C);
      DP PHIJ=0.0;
      cnt=0;
      stringstream ssphi;
      //ostringstream ss_a;
      double phijval[5]={0,0,0,0,0},eigval[7]={0,0,0,0,0,0,0},codval[2]={0,0}; //dummy variable
      //string str_a="";
      while(getline(ifs1,str1)) {
	sscanf(str1.data(),"%lf %lf %lf %lf %lf",&phijval[0],&phijval[1],&phijval[2],&phijval[3],&phijval[4]);

	/*
	//例外処理部(inputするBI...のテキストのPHI値の書き込みおかしくなってる対策)
	ss_a.str("");
	ss_a.clear(stringstream::goodbit);
	ss_a<<phijval[0];
	str_a=ss_a.str();
	if(str_a[str_a.length()-2]=='9' && str_a[str_a.length()-1]=='9') {
	switch(str_a.length()-1) {
	case 2 : phijval[0]+=0.1;
	break;
	case 3 : phijval[0]+=0.01;
	break;
	case 4 : phijval[0]+=0.001;
	break;
	case 5 : phijval[0]+=0.0001;
	break;
	case 6 : phijval[0]+=0.00001;
	break;
	case 7 : phijval[0]+=0.000001;
	break;
	case 8 : phijval[0]+=0.0000001;
	break;
	case 9 : phijval[0]+=0.00000001;
	break;
	case 10 : phijval[0]+=0.000000001;
	break;
	default : ;
	break;
	}
	}
	*/
	
	phi[cnt]=phijval[0];
	eng[cnt]=phijval[1];
	vviter[cnt]=phijval[3];
	cnt++;
      }
      PHIJ=phi[C-1];


      if(eng[C-1]<eps && PHIJ > 0.6) {// if unjammed PHI and valid PHIJ.
	ofs1<<setprecision(10)<<i<<' '<<PHIJ<<endl; //table1への書き込み.
	//その他(Eig,CODDIST書き込みもここのifで行う.)
	////変なPHIJでの書き込みを防ぐため.(本来でないPHIJ)

	for(int j=0;j<C;j++) {
	  ifstream ifs2,ifs3;
	  ssphi.str("");//Initialize.
	  ssphi.clear(stringstream::goodbit);
	  ssphi<<setprecision(10)<<phi[j];

	  rd2=rdtmp2+ssphi.str()+".txt";
	  rd3=rdtmp3+ssphi.str()+".txt";
	  ifs2.open(rd2.data());
	  ifs3.open(rd3.data());
	  
	  //Openできなければスキップ
	  //データベース(マスタ)っぽく書き込む.(table2とtable3)
	  if(ifs2.fail()) {
	    cout<<rd2<<"っていうfile openできなかったよ~."<<endl;
	  }
	  else {
	    while(getline(ifs2,str2)) {
	      sscanf(str2.data(),"%lf %lf %lf %lf %lf %lf %lf",&eigval[0],&eigval[1],&eigval[2],&eigval[3],&eigval[4],&eigval[5],&eigval[6]);
	      ofs2<<setprecision(10)<<i<<' '<<phi[j]-PHIJ<<' '<<eigval[0]<<' '<<eigval[1]<<' '<<eigval[2]<<' '<<eigval[3]<<' '<<eigval[4]<<' '<<eigval[5]<<endl;

	      //0.EVal
	      //1.Freq
	      //2.IPR
	      //3.IPR_1st(small)
	      //4.IPR_2nd(large)
	      //5.the number of the participating particles (1st component)
	      //6.cum dist

	      //    |
	      //    |
	      //    v
	    
	      //0.samplenum
	      //1.DPHI
	      //2.EVal
	      //3.Freq
	      //4.IPR
	      //5.IPR_1st(small)
	      //6.IPR_2nd(large)
	      //7.the number of the participating particles (1st component)
	    }
	  }
	  if(ifs3.fail()) {
	    cout<<rd3<<"っていうfile openできなかったよ~."<<endl;
	  }
	  else {
	    while(getline(ifs3,str3)) {
	      sscanf(str3.data(),"%lf %lf",&codval[0],&codval[1]);
	      ofs3<<setprecision(10)<<i<<' '<<phi[j]-PHIJ<<' '<<codval[0]<<' '<<codval[1]<<endl;
	    }
	  }
	  ifs2.close();
	  ifs3.close();
	  ofs4<<setprecision(10)<<i<<' '<<phi[j]-PHIJ<<endl;
	}
      }
    }
    ifs1.close();
  }
  ofs1.close();
  ofs2.close();
  ofs3.close();
  ofs4.close();
}
