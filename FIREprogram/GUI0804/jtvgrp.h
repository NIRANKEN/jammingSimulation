#ifndef _JTVGRP_H_
#define _JTVGRP_H_

#include "jttool.h"
#include "nr.h"
#include "MT.h"
#include <vector>
#include <limits>

namespace JT
{
  struct NNset
  {
    int child;
    int parent;
  };
  //--------------------//
  //-------JT func------//
  //----(jtfunc.cpp)----//
  //--------------------//
  
  namespace dim2
  {
    void searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,vector<int> &NN,int num_p_pre);
    void searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,vector<int> &NN,vector<int> exList);
    void searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,vector<NNset> &NN,vector<int> exList);
    void searchCoCluster(Vec_I_DP &p,Mat_I_DP &Em,int modenum,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,Vec_IO_INT &att,int &Ncluster);
  }

  namespace dim3
  {
    void searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,DP Lz,vector<int> &NN,int num_p_pre);
    void searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,DP Lz,vector<int> &NN,vector<int> exList);
    void searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,DP Lz,vector<NNset> &NN,vector<int> exList);
    void searchCoCluster(Vec_I_DP &p,Mat_I_DP &Em,int modenum,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,DP Lz,Vec_IO_INT &att,int &Ncluster);
  }
  
  bool isExcludedParticle(int num,vector<int> v);
  bool isSearchedParticle(int num,vector<int> v);
  bool isSearchedParticle(int num,vector<NNset> v);
  void classifySoftCluster(vector<int> &soft,int groupNum,vector<vector<int> >nnset);
  inline void vGrp_setExcludedParticles(Mat_I_DP &Em,Vec_IO_DP &Ev,Vec_IO_INT &att,int D,int n,int modenum,vector<int> &exclusionList_init);
  inline void vGrp_grouping(Vec_IO_INT &att,vector<int> &classifiedList,vector<int> searchedList,int &group,int n, int D);
  inline void vGrp_searchCVC(Vec_I_DP &Ev,int D,vector<NNset> &NN_root,vector<int> &NN,vector<int> exclusionList,vector<int> &searchedList);
  inline void vGrp_write(Vec_I_INT &att,ofstream &ofs,int n);
  inline void vGrp_initErrCheck(int modenum,int dn,int n,int N);
  //void selectWorkingParticle(int num,vector<int> &v);
}


void JT::dim2::searchCoCluster(Vec_I_DP &p,Mat_I_DP &Em,int modenum,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,Vec_IO_INT &att,int &Ncluster)//num_E=0~3*N-1, num_p = 0~N-1
{
  int dn=p.size();
  int n=dn/D;
  vGrp_initErrCheck(modenum,dn,n,att.size());
  
  Vec_DP Ev(dn);
  int group=1,count;
  vector<int> NN,NN2;
  //vector<vector<int> > NNset;
  vector<int> exclusionList,exclusionList_init,searchedList,classifiedList;
  vector<NNset> NN_root;
  bool searchedSoftCluster;
  //ofstream ofs("test.txt");

  vGrp_setExcludedParticles(Em,Ev,att,D,n,modenum,exclusionList_init);
  
  for(int i=0;i<n;i++) {
    if(!isExcludedParticle(i,exclusionList_init) && !isSearchedParticle(i,classifiedList)) {
       exclusionList=exclusionList_init;
      searchedSoftCluster=false;
      JT::dim2::searchNN(p,i,D,R,rt,Prt1,Prt2,Lx,Ly,NN_root,exclusionList);//NNを調べる.
      searchedList=vector<int>();
      searchedList.push_back(i);
      count=0;
      while(!searchedSoftCluster) {
	if(NN_root.size()==0) {
	  //cout<<"探索する粒子がおらんです."<<endl;
	  break;
	}
	else {
	  vGrp_searchCVC(Ev,D,NN_root,NN,exclusionList,searchedList);
 	  if(NN.size()==0) {
	    //cout<<"探索終了"<<endl;
	    searchedSoftCluster=true;
	    break;
	  }
	  else {
	    NN_root=vector<NNset>();
	    for(unsigned int k=0;k<NN.size();k++) {
	      NN2=vector<int>();
	      JT::dim2::searchNN(p,NN[k],D,R,rt,Prt1,Prt2,Lx,Ly,NN2,exclusionList);
	      //NN2[k]のそれぞれについて,excludedを除いたNNを調べる.
	      //もしそれらのNNでsearchListに引っかかるものがあれば,SoftClusterとして入れちゃう.
	      //なければ次のwhileループに用いる.
	      for(unsigned int l=0;l<NN2.size();l++) {
		  NNset tmp={NN2[l],NN[k]};
		  NN_root.push_back(tmp);
	      }
	    }
	  }
	}//NN_root.size()!=0 - loop
	count+=1;
	//cout<<count<<"階層目の探索が終わったよ!"<<endl;
      }//while !searchedCluster -loop
      vGrp_grouping(att,classifiedList,searchedList,group,n,D);
    }//if-固有値の大きさがthreshold以上-end
    else {
      //cout<<i<<"番目の粒子はソフトモード解析から除外されました."<<endl;
    }
  }
  Ncluster=group-1;
  //vGrp_write(att,ofs,n);
}
void JT::dim3::searchCoCluster(Vec_I_DP &p,Mat_I_DP &Em,int modenum,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,DP Lz,Vec_IO_INT &att,int &Ncluster)
{
  int dn=p.size();
  int n=dn/D;
  vGrp_initErrCheck(modenum,dn,n,att.size());
  
  Vec_DP Ev(dn);
  int group=1,count;
  vector<int> NN,NN2;
  //vector<vector<int> > NNset;
  vector<int> exclusionList,exclusionList_init,searchedList,classifiedList;
  vector<NNset> NN_root;
  bool searchedSoftCluster;
  //ofstream ofs("test.txt");

  vGrp_setExcludedParticles(Em,Ev,att,D,n,modenum,exclusionList_init);
  
  for(int i=0;i<n;i++) {
    if(!isExcludedParticle(i,exclusionList_init) && !isSearchedParticle(i,classifiedList)) {
      exclusionList=exclusionList_init;
      searchedSoftCluster=false;
      JT::dim3::searchNN(p,i,D,R,rt,Prt1,Prt2,Lx,Ly,Lz,NN_root,exclusionList);//NNを調べる.
      searchedList=vector<int>();
      searchedList.push_back(i);
      count=0;
      while(!searchedSoftCluster) {
	if(NN_root.size()==0) {
	  //cout<<"探索する粒子がおらんです."<<endl;
	  break;
	}
	else {
	  vGrp_searchCVC(Ev,D,NN_root,NN,exclusionList,searchedList);
 	  if(NN.size()==0) {
	    //cout<<"探索終了"<<endl;
	    searchedSoftCluster=true;
	    break;
	  }
	  else {
	    NN_root=vector<NNset>();
	    for(unsigned int k=0;k<NN.size();k++) {
	      NN2=vector<int>();
	      JT::dim3::searchNN(p,NN[k],D,R,rt,Prt1,Prt2,Lx,Ly,Lz,NN2,exclusionList);
	      //NN2[k]のそれぞれについて,excludedを除いたNNを調べる.
	      //もしそれらのNNでsearchListに引っかかるものがあれば,SoftClusterとして入れちゃう.
	      //なければ次のwhileループに用いる.
	      for(unsigned int l=0;l<NN2.size();l++) {
		NNset tmp={NN2[l],NN[k]};
		NN_root.push_back(tmp);
	      }
	    }
	  }
	}//NN_root.size()!=0 - loop
	count+=1;
	//cout<<count<<"階層目の探索が終わったよ!"<<endl;
      }//while !searchedCluster -loop
      vGrp_grouping(att,classifiedList,searchedList,group,n,D);
    }//if-固有値の大きさがthreshold以上-end
    else {
      //cout<<i<<"番目の粒子はソフトモード解析から除外されました."<<endl;
    }
  }
  Ncluster=group-1;
  //vGrp_write(att,ofs,n);
}
inline void JT::vGrp_initErrCheck(int modenum,int dn,int n,int attN)
{
  if(modenum<0 || modenum>dn-1) {
    cerr<<""<<endl;
    exit(1);
  }
  if(n!=attN) {
    cerr<<""<<endl;
    exit(1);
  }
}
inline void JT::vGrp_setExcludedParticles(Mat_I_DP &Em,Vec_IO_DP &Ev,Vec_IO_INT &att,int D,int n,int modenum,vector<int> &exclusionList_init)
{
  DP e_mag,e_max=0.0;
  DP threshold_frac=0.05;//要調整.
  
  for(int i=0;i<n;i++) {
    e_mag=0.0;
    att[i]=0; //初期グループはゼロ.
    for(int j=0;j<D;j++) {
      Ev[D*i+j]=Em[D*i+j][modenum];
      e_mag+=Ev[D*i+j]*Ev[D*i+j];
    }
    if(e_max<e_mag) {
      e_max=e_mag;
    }
  }
  e_max=e_max*threshold_frac;
  for(int i=0;i<n;i++) {
    e_mag=0.0;
    for(int j=0;j<D;j++) {
      e_mag+=Ev[D*i+j]*Ev[D*i+j];
    }
    if(e_mag<=e_max) {
      exclusionList_init.push_back(i);
    }
  }

}
inline void JT::vGrp_grouping(Vec_IO_INT &att,vector<int> &classifiedList,vector<int> searchedList,int &group,int n, int D)
{
  int Nc=searchedList.size();
  if(Nc < D+1) { //covibrated clusterとみなす最小の個数(D+1)
    for(int i=0;i<Nc;i++) {
      att[searchedList[i]]=-1;
      classifiedList.push_back(searchedList[i]);
    }
  }
  else {
    //SearchedListに入ってる粒子全てをSoftClusterへ追加する.
    for(unsigned int j=0;j<searchedList.size();j++) {
      for(int k=0;k<n;k++) {
	if(k==searchedList[j]) {
	  if(isSearchedParticle(k,classifiedList)) {
	    cerr<<"既に共振動クラスターに配属されています."<<endl;
	    exit(1);
	  }
	  att[k]=group;
	  classifiedList.push_back(k);
	  break;
	}
      }
      //cout<<group<<endl;
    }
    group+=1;
  }
}
inline void JT::vGrp_searchCVC(Vec_I_DP &Ev,int D,vector<NNset> &NN_root,vector<int> &NN,vector<int> exclusionList,vector<int> &searchedList)
{
  DP inner_p;
  NN=vector<int>();
  while(NN_root.size()!=0) {
    bool B1=!isExcludedParticle(NN_root[0].child,exclusionList);
    bool B2=!isSearchedParticle(NN_root[0].child,searchedList);
    if(B1 && B2) {
      inner_p=0.0;
      for(int l=0;l<D;l++)
	inner_p+=Ev[D*NN_root[0].parent+l]*Ev[D*(NN_root[0].child)+l];//<-こいつ即修正.
      if(inner_p>0) {
	NN.push_back(NN_root[0].child);//次の探索候補として追加.
	searchedList.push_back(NN_root[0].child);//探索済みに変更
      }
      else {
	//内積負の処理
      }
    }
    else {
      //探索済みor排斥済み
    }
    NN_root.erase(NN_root.begin());//NN_rootから現在の探索粒子を除外する操作,
  }//while(NN_root.size()!=0)-loop
}
inline void JT::vGrp_write(Vec_I_INT &att,ofstream &ofs,int n)
{
  cout<<"soft mode解析終了."<<endl;
  //書き込み.
  for(int i=0;i<n;i++) {
    if(att[i]!=0) {
      cout<<i<<"番目の粒子は"<<att[i]<<"のソフトクラスターに配属!^^"<<endl;
    }
    else {
      cout<<i<<"番目の粒子はソフトクラスターに配属されませんでした><"<<endl;
    }
    ofs<<i<<" "<<att[i]<<endl;
  }
}
void JT::dim2::searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,vector<int> &NN,int num_p_pre)
{
  int n=p.size()/D;
  DP relr[3];
  if(num_p<0 || num_p>n) {
    cerr<<""<<endl;
    exit(1);
  }
  double distance,rad=R,rad_p,sgm,r2;
  NN=vector<int>();
  if((Prt1+Prt2)*num_p < Prt1*n) {
    rad_p=R;
  }
  else {
    rad_p=R*rt;
  }
  for(int i=0;i<n;i++) {
    if(i!=num_p && i!=num_p_pre) {
      if((Prt1+Prt2)*i>=Prt1*n) {
	rad=R*rt;
      }
      sgm=rad_p+rad;
      for(int j=0;j<D;j++) {
	relr[j]=p[D*num_p+j]-p[D*i+j];
      }
      JT::dim2::OutofPeriodicboundary2D(relr[0],relr[1],Lx,Ly,sgm);
      distance=0.0;
      for(int j=0;j<D;j++) {
	distance+=relr[j]*relr[j];
      }
      r2=sgm*sgm;
      if(distance < r2) {
	NN.push_back(i);
      }
    }
  }
  return;
}
void JT::dim3::searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,DP Lz,vector<int> &NN,int num_p_pre)
{
  int n=p.size()/D;
  DP relr[3];
  if(num_p<0 || num_p>n) {
    cerr<<""<<endl;
    exit(1);
  }
  double distance,rad=R,rad_p,sgm,r2;
  NN=vector<int>();
  if((Prt1+Prt2)*num_p < Prt1*n) {
    rad_p=R;
  }
  else {
    rad_p=R*rt;
  }
  for(int i=0;i<n;i++) {
    if(i!=num_p && i!=num_p_pre) {
      if((Prt1+Prt2)*i>=Prt1*n) {
	rad=R*rt;
      }
      sgm=rad_p+rad;
      for(int j=0;j<D;j++) {
	relr[j]=p[D*num_p+j]-p[D*i+j];
      }
      JT::dim3::OutofPeriodicboundary3D(relr[0],relr[1],relr[2],Lx,Ly,Lz,sgm);
      distance=0.0;
      for(int j=0;j<D;j++) {
	distance+=relr[j]*relr[j];
      }
      r2=sgm*sgm;
      if(distance < r2) {
	NN.push_back(i);
      }
    }
  }
  return;
}

void JT::dim2::searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,vector<int> &NN,vector<int> exList)
{
  int n=p.size()/D;
  DP relr[3];
  if(num_p<0 || num_p>n) {
    cerr<<""<<endl;
    exit(1);
  }
  double distance,rad=R,rad_p,sgm,r2;
  NN=vector<int>();
  if((Prt1+Prt2)*num_p < Prt1*n) {
    rad_p=R;
  }
  else {
    rad_p=R*rt;
  }
  for(int i=0;i<n;i++) {
    if(i!=num_p && !isExcludedParticle(i,exList)) {
      if((Prt1+Prt2)*i>=Prt1*n) {
	rad=R*rt;
      }
      sgm=rad_p+rad;
      for(int j=0;j<D;j++) {
	relr[j]=p[D*num_p+j]-p[D*i+j];
      }
      JT::dim2::OutofPeriodicboundary2D(relr[0],relr[1],Lx,Ly,sgm);
      distance=0.0;
      for(int j=0;j<D;j++) {
	distance+=relr[j]*relr[j];
      }
      r2=sgm*sgm;
      if(distance < r2) {
	NN.push_back(i);
      }
    }
  }
  return;
}
void JT::dim3::searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,DP Lz,vector<int> &NN,vector<int> exList)
{
  int n=p.size()/D;
  DP relr[3];
  if(num_p<0 || num_p>n) {
    cerr<<""<<endl;
    exit(1);
  }
  double distance,rad=R,rad_p,sgm,r2;
  NN=vector<int>();
  if((Prt1+Prt2)*num_p < Prt1*n) {
    rad_p=R;
  }
  else {
    rad_p=R*rt;
  }
  for(int i=0;i<n;i++) {
    if(i!=num_p && !isExcludedParticle(i,exList)) {
      if((Prt1+Prt2)*i>=Prt1*n) {
	rad=R*rt;
      }
      sgm=rad_p+rad;
      for(int j=0;j<D;j++) {
	relr[j]=p[D*num_p+j]-p[D*i+j];
      }
      JT::dim3::OutofPeriodicboundary3D(relr[0],relr[1],relr[2],Lx,Ly,Lz,sgm);
      distance=0.0;
      for(int j=0;j<D;j++) {
	distance+=relr[j]*relr[j];
      }
      r2=sgm*sgm;
      if(distance < r2) {
	NN.push_back(i);
      }
    }
  }
  return;
}

void JT::dim2::searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,vector<NNset> &NN,vector<int> exList)
{
int n=p.size()/D;
  DP relr[3];
  if(num_p<0 || num_p>n) {
    cerr<<""<<endl;
    exit(1);
  }
  double distance,rad=R,rad_p,sgm,r2;
  NN=vector<NNset>();
  if((Prt1+Prt2)*num_p < Prt1*n) {
    rad_p=R;
  }
  else {
    rad_p=R*rt;
  }
  for(int i=0;i<n;i++) {
    if(i!=num_p && !isExcludedParticle(i,exList)) {
      if((Prt1+Prt2)*i>=Prt1*n) {
	rad=R*rt;
      }
      sgm=rad_p+rad;
      for(int j=0;j<D;j++) {
	relr[j]=p[D*num_p+j]-p[D*i+j];
      }
      JT::dim2::OutofPeriodicboundary2D(relr[0],relr[1],Lx,Ly,sgm);
      distance=0.0;
      for(int j=0;j<D;j++) {
	distance+=relr[j]*relr[j];
      }
      r2=sgm*sgm;
      if(distance < r2) {
	NNset tmp={i,num_p};
	NN.push_back(tmp);
      }
    }
  }
  return;
}
void JT::dim3::searchNN(Vec_I_DP &p,int num_p,int D,DP R,DP rt,int Prt1,int Prt2,DP Lx,DP Ly,DP Lz,vector<NNset> &NN,vector<int> exList)
{
int n=p.size()/D;
  DP relr[3];
  if(num_p<0 || num_p>n) {
    cerr<<""<<endl;
    exit(1);
  }
  double distance,rad=R,rad_p,sgm,r2;
  NN=vector<NNset>();
  if((Prt1+Prt2)*num_p < Prt1*n) {
    rad_p=R;
  }
  else {
    rad_p=R*rt;
  }
  for(int i=0;i<n;i++) {
    if(i!=num_p && !isExcludedParticle(i,exList)) {
      if((Prt1+Prt2)*i>=Prt1*n) {
	rad=R*rt;
      }
      sgm=rad_p+rad;
      for(int j=0;j<D;j++) {
	relr[j]=p[D*num_p+j]-p[D*i+j];
      }
      JT::dim3::OutofPeriodicboundary3D(relr[0],relr[1],relr[2],Lx,Ly,Lz,sgm);
      distance=0.0;
      for(int j=0;j<D;j++) {
	distance+=relr[j]*relr[j];
      }
      r2=sgm*sgm;
      if(distance < r2) {
	NNset tmp={i,num_p};
	NN.push_back(tmp);
      }
    }
  }
  return;
}

bool JT::isExcludedParticle(int num,vector<int> v) {
  int n=v.size();
  for(int i=0;i<n;i++) {
    if(num==v[i])
      return true;
  }
  return false;
}
bool JT::isSearchedParticle(int num,vector<int> v) {
  int n=v.size();
  for(int i=0;i<n;i++) {
    if(num==v[i])
      return true;
  }
  return false;
}
bool JT::isSearchedParticle(int num,vector<NNset> v) {
  int n=v.size();
  for(int i=0;i<n;i++) {
    if(num==v[i].child)
      return true;
  }
  return false;
}
void JT::classifySoftCluster(vector<int> &soft,int groupNum,vector<vector<int> >nnset)
{
  int N=nnset.size();
  int M=soft.size();
  int count=0;
  if(nnset[N-1].size()==0) {
    cerr<<"nnsetの格納おかしい"<<endl;
    exit(1);
  }
  bool searched=false;
  int fl=N-1,num=nnset[fl][0];
  while(!searched) {
    for(int i=0;i<M;i++) {
      if(i==num) {
	if(soft[i]!=0 && soft[i]!=groupNum) {
	  cerr<<"複数のソフトクラスターに属する粒子として判定されました."<<endl;
	  exit(1);
	}
	soft[i]=groupNum;
	if(fl>0) {
	  fl-=1;
	  num=nnset[fl][0];
	}
	else {
	  searched=true;
	}
	break;
      }
    }
    count+=1;
    if(count>100000) {
      cerr<<"ソフトクラスターメソッドまわしすぎ."<<endl;
      exit(1);
    }
  }
}
//void searchSoftCluster()
#endif
