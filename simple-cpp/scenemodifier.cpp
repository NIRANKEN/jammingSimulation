#include "scenemodifier.h"

SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity,FIREVV3D *firevv)
{
  const int n=firevv->show_ParticleNum();
  m_rootEntity=new Qt3DCore::QEntity();
  m_particleEntities = new Qt3DCore::QEntity*[n];
  m_forcelineEntities = new Qt3DCore::QEntity*[n];
  m_eigvecEntities = new Qt3DCore::QEntity*[n];
  m_cubeEntities = new Qt3DCore::QEntity*[24];

  //initial set...
  boxSetting(firevv);
  sphereSetting(firevv);

  m_rootEntity->setParent(rootEntity);
}

SceneModifier::~SceneModifier()
{
  delete m_rootEntity;
  delete[](m_particleEntities);
  delete[](m_forcelineEntities);
  delete[](m_eigvecEntities);
  delete[] m_cubeEntities;

}

Qt3DCore::QEntity* SceneModifier::show_rootEntity()
{
  return m_rootEntity;
}

void SceneModifier::enablePeriodicBox(bool enabled)
{
  for(int i=0;i<24;i++) {
    m_cubeEntities[i]->setParent(enabled ? m_rootEntity : nullptr);
  }
}

void SceneModifier::enableParticles(bool enabled)
{
  for(int i=0;i<N;i++) {
    m_particleEntities[i]->setParent(enabled ? m_rootEntity : nullptr);
  }

}

void SceneModifier::enableForceNetwork(bool enabled)
{
  for(int i=0;i<N;i++) {
    m_forcelineEntities[i]->setParent(enabled ? m_rootEntity : nullptr);
  }
}

void SceneModifier::enableEigenVector(bool enabled)
{
  for(int i=0;i<N;i++) {
    m_eigvecEntities[i]->setParent(enabled ? m_rootEntity : nullptr);
  }
}

void SceneModifier::repaint(Qt3DCore::QEntity *rootEntity,FIREVV3D *firevv)
{
  const int n=firevv->show_ParticleNum();
  qDebug()<<n<<" "<<endl;

  delete m_rootEntity;
  delete[](m_particleEntities);
  delete[](m_forcelineEntities);
  delete[](m_eigvecEntities);
  delete[] (m_cubeEntities);

  m_rootEntity=new Qt3DCore::QEntity();
  m_particleEntities = new Qt3DCore::QEntity*[n];
  m_forcelineEntities = new Qt3DCore::QEntity*[n];
  m_eigvecEntities = new Qt3DCore::QEntity*[n];
  m_cubeEntities = new Qt3DCore::QEntity*[24];

  //initial set...
  boxSetting(firevv);
  sphereSetting(firevv);
  eigvecSetting(firevv);

  m_rootEntity->setParent(rootEntity);
  //qDebug()<<"=*=*=*=*=*=*=*=\nrepainted Scene...=*=*=*=*=*=*=*=\n"<<endl;

}

void SceneModifier::boxSetting(FIREVV3D *firevv)
{

  qDebug()<<"Now box painting..."<<endl;
  int c;
  //Box painting
  Qt3DExtras::QPhongMaterial *m_cubeMaterial = new Qt3DExtras::QPhongMaterial();
  m_cubeMaterial->setDiffuse(QColor(QRgb(0xE7E8E2)));
  Qt3DExtras::QCuboidMesh **m_cubeMeshes;
  Qt3DCore::QTransform **m_cubeTransforms;
  //Qt3D::QTranslateTransform **m_cubeTranslateTransforms; //
  //Qt3D::QScaleTransform **m_cubeScaleTransforms; //
  m_cubeMeshes = new Qt3DExtras::QCuboidMesh*[24];
  m_cubeTransforms = new Qt3DCore::QTransform*[24];
  //m_cubeTranslateTransforms = new Qt3D::QTranslateTransform*[24]; //
  //m_cubeScaleTransforms = new Qt3D::QScaleTransform*[24]; //
  for(int i=0;i<6;i++) {
    for(int j=0;j<4;j++) {
      c=4*i+j;
      m_cubeEntities[c]=new Qt3DCore::QEntity(m_rootEntity);
      m_cubeMeshes[c]=new Qt3DExtras::QCuboidMesh(m_rootEntity);
      m_cubeTransforms[c]=new Qt3DCore::QTransform(m_rootEntity);
      //m_cubeTranslateTransforms[c] = new Qt3D::QTranslateTransform; //
      //m_cubeScaleTransforms[c] = new Qt3D::QScaleTransform; //
    }
    c=4*i;
    switch(i) {
    case 0:
      m_cubeTransforms[c]->setTranslation(QVector3D(0,0.025*firevv->show_Lengy(),0.5*firevv->show_Lengz()));
      //m_cubeScaleTransforms[i]->setScale3D(QVector3D(0.001*firevv->show_Lengx(),firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c]->setXExtent(0.001*firevv->show_Lengx());
      m_cubeMeshes[c]->setYExtent(0.05*firevv->show_Lengy());
      m_cubeMeshes[c]->setZExtent(firevv->show_Lengz());

      m_cubeTransforms[c+1]->setTranslation(QVector3D(0,0.975*firevv->show_Lengy(),0.5*firevv->show_Lengz()));
      //m_cubeScaleTransforms[i]->setScale3D(QVector3D(0.001*firevv->show_Lengx(),firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+1]->setXExtent(0.001*firevv->show_Lengx());
      m_cubeMeshes[c+1]->setYExtent(0.05*firevv->show_Lengy());
      m_cubeMeshes[c+1]->setZExtent(firevv->show_Lengz());

      m_cubeTransforms[c+2]->setTranslation(QVector3D(0,0.5*firevv->show_Lengy(),0.025*firevv->show_Lengz()));
      //m_cubeScaleTransforms[i]->setScale3D(QVector3D(0.001*firevv->show_Lengx(),firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+2]->setXExtent(0.001*firevv->show_Lengx());
      m_cubeMeshes[c+2]->setYExtent(firevv->show_Lengy());
      m_cubeMeshes[c+2]->setZExtent(0.05*firevv->show_Lengz());

      m_cubeTransforms[c+3]->setTranslation(QVector3D(0,0.5*firevv->show_Lengy(),0.975*firevv->show_Lengz()));
      //m_cubeScaleTransforms[i]->setScale3D(QVector3D(0.001*firevv->show_Lengx(),firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+3]->setXExtent(0.001*firevv->show_Lengx());
      m_cubeMeshes[c+3]->setYExtent(firevv->show_Lengy());
      m_cubeMeshes[c+3]->setZExtent(0.05*firevv->show_Lengz());

      break;
    case 1:
      m_cubeTransforms[c]->setTranslation(QVector3D(firevv->show_Lengx(),0.025*firevv->show_Lengy(),0.5*firevv->show_Lengz()));
      //m_cubeScaleTransforms[i]->setScale3D(QVector3D(0.001*firevv->show_Lengx(),firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c]->setXExtent(0.001*firevv->show_Lengx());
      m_cubeMeshes[c]->setYExtent(0.05*firevv->show_Lengy());
      m_cubeMeshes[c]->setZExtent(firevv->show_Lengz());

      m_cubeTransforms[c+1]->setTranslation(QVector3D(firevv->show_Lengx(),0.975*firevv->show_Lengy(),0.5*firevv->show_Lengz()));
      //m_cubeScaleTransforms[i]->setScale3D(QVector3D(0.001*firevv->show_Lengx(),firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+1]->setXExtent(0.001*firevv->show_Lengx());
      m_cubeMeshes[c+1]->setYExtent(0.05*firevv->show_Lengy());
      m_cubeMeshes[c+1]->setZExtent(firevv->show_Lengz());

      m_cubeTransforms[c+2]->setTranslation(QVector3D(firevv->show_Lengx(),0.5*firevv->show_Lengy(),0.025*firevv->show_Lengz()));
      //m_cubeScaleTransforms[i]->setScale3D(QVector3D(0.001*firevv->show_Lengx(),firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+2]->setXExtent(0.001*firevv->show_Lengx());
      m_cubeMeshes[c+2]->setYExtent(firevv->show_Lengy());
      m_cubeMeshes[c+2]->setZExtent(0.05*firevv->show_Lengz());

      m_cubeTransforms[c+3]->setTranslation(QVector3D(firevv->show_Lengx(),0.5*firevv->show_Lengy(),0.975*firevv->show_Lengz()));
      //m_cubeScaleTransforms[i]->setScale3D(QVector3D(0.001*firevv->show_Lengx(),firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+3]->setXExtent(0.001*firevv->show_Lengx());
      m_cubeMeshes[c+3]->setYExtent(firevv->show_Lengy());
      m_cubeMeshes[c+3]->setZExtent(0.05*firevv->show_Lengz());

      break;
    case 2:
      m_cubeTransforms[c]->setTranslation(QVector3D(0.5*firevv->show_Lengx(),0,0.025*firevv->show_Lengz()));
      // m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),0.001*firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c]->setXExtent(firevv->show_Lengx());
      m_cubeMeshes[c]->setYExtent(0.001*firevv->show_Lengy());
      m_cubeMeshes[c]->setZExtent(0.05*firevv->show_Lengz());

      m_cubeTransforms[c+1]->setTranslation(QVector3D(0.5*firevv->show_Lengx(),0,0.975*firevv->show_Lengz()));
      // m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),0.001*firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+1]->setXExtent(firevv->show_Lengx());
      m_cubeMeshes[c+1]->setYExtent(0.001*firevv->show_Lengy());
      m_cubeMeshes[c+1]->setZExtent(0.05*firevv->show_Lengz());

      m_cubeTransforms[c+2]->setTranslation(QVector3D(0.025*firevv->show_Lengx(),0,0.5*firevv->show_Lengz()));
      // m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),0.001*firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+2]->setXExtent(0.05*firevv->show_Lengx());
      m_cubeMeshes[c+2]->setYExtent(0.001*firevv->show_Lengy());
      m_cubeMeshes[c+2]->setZExtent(firevv->show_Lengz());

      m_cubeTransforms[c+3]->setTranslation(QVector3D(0.975*firevv->show_Lengx(),0,0.5*firevv->show_Lengz()));
      // m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),0.001*firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+3]->setXExtent(0.05*firevv->show_Lengx());
      m_cubeMeshes[c+3]->setYExtent(0.001*firevv->show_Lengy());
      m_cubeMeshes[c+3]->setZExtent(firevv->show_Lengz());

      break;
    case 3:
      m_cubeTransforms[c]->setTranslation(QVector3D(0.5*firevv->show_Lengx(),firevv->show_Lengy(),0.025*firevv->show_Lengz()));
      // m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),0.001*firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c]->setXExtent(firevv->show_Lengx());
      m_cubeMeshes[c]->setYExtent(0.001*firevv->show_Lengy());
      m_cubeMeshes[c]->setZExtent(0.05*firevv->show_Lengz());

      m_cubeTransforms[c+1]->setTranslation(QVector3D(0.5*firevv->show_Lengx(),firevv->show_Lengy(),0.975*firevv->show_Lengz()));
      // m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),0.001*firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+1]->setXExtent(firevv->show_Lengx());
      m_cubeMeshes[c+1]->setYExtent(0.001*firevv->show_Lengy());
      m_cubeMeshes[c+1]->setZExtent(0.05*firevv->show_Lengz());

      m_cubeTransforms[c+2]->setTranslation(QVector3D(0.025*firevv->show_Lengx(),firevv->show_Lengy(),0.5*firevv->show_Lengz()));
      // m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),0.001*firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+2]->setXExtent(0.05*firevv->show_Lengx());
      m_cubeMeshes[c+2]->setYExtent(0.001*firevv->show_Lengy());
      m_cubeMeshes[c+2]->setZExtent(firevv->show_Lengz());

      m_cubeTransforms[c+3]->setTranslation(QVector3D(0.975*firevv->show_Lengx(),firevv->show_Lengy(),0.5*firevv->show_Lengz()));
      // m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),0.001*firevv->show_Lengy(),firevv->show_Lengz()));
      m_cubeMeshes[c+3]->setXExtent(0.05*firevv->show_Lengx());
      m_cubeMeshes[c+3]->setYExtent(0.001*firevv->show_Lengy());
      m_cubeMeshes[c+3]->setZExtent(firevv->show_Lengz());

      break;

    case 4:
      m_cubeTransforms[c]->setTranslation(QVector3D(0.025*firevv->show_Lengx(),0.5*firevv->show_Lengy(),0));
      //   m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),firevv->show_Lengy(),0.001*firevv->show_Lengz()));
      m_cubeMeshes[c]->setXExtent(0.05*firevv->show_Lengx());
      m_cubeMeshes[c]->setYExtent(firevv->show_Lengy());
      m_cubeMeshes[c]->setZExtent(0.001*firevv->show_Lengz());

      m_cubeTransforms[c+1]->setTranslation(QVector3D(0.975*firevv->show_Lengx(),0.5*firevv->show_Lengy(),0));
      //   m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),firevv->show_Lengy(),0.001*firevv->show_Lengz()));
      m_cubeMeshes[c+1]->setXExtent(0.05*firevv->show_Lengx());
      m_cubeMeshes[c+1]->setYExtent(firevv->show_Lengy());
      m_cubeMeshes[c+1]->setZExtent(0.001*firevv->show_Lengz());

      m_cubeTransforms[c+2]->setTranslation(QVector3D(0.5*firevv->show_Lengx(),0.025*firevv->show_Lengy(),0));
      //   m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),firevv->show_Lengy(),0.001*firevv->show_Lengz()));
      m_cubeMeshes[c+2]->setXExtent(firevv->show_Lengx());
      m_cubeMeshes[c+2]->setYExtent(0.05*firevv->show_Lengy());
      m_cubeMeshes[c+2]->setZExtent(0.001*firevv->show_Lengz());

      m_cubeTransforms[c+3]->setTranslation(QVector3D(0.5*firevv->show_Lengx(),0.975*firevv->show_Lengy(),0));
      //   m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),firevv->show_Lengy(),0.001*firevv->show_Lengz()));
      m_cubeMeshes[c+3]->setXExtent(firevv->show_Lengx());
      m_cubeMeshes[c+3]->setYExtent(0.05*firevv->show_Lengy());
      m_cubeMeshes[c+3]->setZExtent(0.001*firevv->show_Lengz());

      break;

    case 5:
      m_cubeTransforms[c]->setTranslation(QVector3D(0.025*firevv->show_Lengx(),0.5*firevv->show_Lengy(),firevv->show_Lengz()));
      //   m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),firevv->show_Lengy(),0.001*firevv->show_Lengz()));
      m_cubeMeshes[c]->setXExtent(0.05*firevv->show_Lengx());
      m_cubeMeshes[c]->setYExtent(firevv->show_Lengy());
      m_cubeMeshes[c]->setZExtent(0.001*firevv->show_Lengz());

      m_cubeTransforms[c+1]->setTranslation(QVector3D(0.975*firevv->show_Lengx(),0.5*firevv->show_Lengy(),firevv->show_Lengz()));
      //   m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),firevv->show_Lengy(),0.001*firevv->show_Lengz()));
      m_cubeMeshes[c+1]->setXExtent(0.05*firevv->show_Lengx());
      m_cubeMeshes[c+1]->setYExtent(firevv->show_Lengy());
      m_cubeMeshes[c+1]->setZExtent(0.001*firevv->show_Lengz());

      m_cubeTransforms[c+2]->setTranslation(QVector3D(0.5*firevv->show_Lengx(),0.025*firevv->show_Lengy(),firevv->show_Lengz()));
      //   m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),firevv->show_Lengy(),0.001*firevv->show_Lengz()));
      m_cubeMeshes[c+2]->setXExtent(firevv->show_Lengx());
      m_cubeMeshes[c+2]->setYExtent(0.05*firevv->show_Lengy());
      m_cubeMeshes[c+2]->setZExtent(0.001*firevv->show_Lengz());

      m_cubeTransforms[c+3]->setTranslation(QVector3D(0.5*firevv->show_Lengx(),0.975*firevv->show_Lengy(),firevv->show_Lengz()));
      //   m_cubeScaleTransforms[i]->setScale3D(QVector3D(firevv->show_Lengx(),firevv->show_Lengy(),0.001*firevv->show_Lengz()));
      m_cubeMeshes[c+3]->setXExtent(firevv->show_Lengx());
      m_cubeMeshes[c+3]->setYExtent(0.05*firevv->show_Lengy());
      m_cubeMeshes[c+3]->setZExtent(0.001*firevv->show_Lengz());

      break;

    default :
      break;
    }
    for(int j=0;j<4;j++) {
      //m_cubeTransforms[c+j]->addTransform(m_cubeTranslateTransforms[c+j]);
      //m_cubeTransforms[c+j]->addTransform(m_cubeScaleTransforms[c+j]);
      m_cubeEntities[c+j]->addComponent(m_cubeMeshes[c+j]);
      m_cubeEntities[c+j]->addComponent(m_cubeTransforms[c+j]);
      m_cubeEntities[c+j]->addComponent(m_cubeMaterial);
    }
  }
  //---

  qDebug()<<"END."<<endl;
}

void SceneModifier::sphereSetting(FIREVV3D *firevv)
{
  qDebug()<<"Now sphere painting..."<<endl;
  const int n=firevv->show_ParticleNum();

  //Sphere painting
  Qt3DExtras::QPhongMaterial *m_particleMaterial1 = new Qt3DExtras::QPhongMaterial();
  m_particleMaterial1->setDiffuse(QColor(QRgb(0x47EA7E)));
  Qt3DExtras::QPhongMaterial *m_particleMaterial2 = new Qt3DExtras::QPhongMaterial();
  m_particleMaterial2->setDiffuse(QColor(QRgb(0xCACCB2)));
  Qt3DExtras::QSphereMesh **m_particleMeshs;
  Qt3DCore::QTransform **m_particleTransforms;
  //Qt3D::QTranslateTransform **m_particleTranslateTransforms; //
  m_particleMeshs = new Qt3DExtras::QSphereMesh*[n];
  m_particleTransforms = new Qt3DCore::QTransform*[n];
  //m_particleTranslateTransforms  = new Qt3D::QTranslateTransform*[n]; //


  int prt1=firevv->show_ParticleRatio1(),prt2=firevv->show_ParticleRatio2();

  double rad=firevv->show_Radii();
  double sq,x,y,z,th=firevv->show_EigNum_threshold(),M;

  if(firevv->show_CalculatedEigMode()) {
      //rad*=1.5; //0913
    int k_th=firevv->show_EigNum();
    for(int i=0;i<n;i++) {
      m_particleEntities[i]= new Qt3DCore::QEntity(m_rootEntity);
      m_particleMeshs[i]= new Qt3DExtras::QSphereMesh(m_rootEntity);
      m_particleTransforms[i] = new Qt3DCore::QTransform(m_rootEntity);
      //m_particleTranslateTransforms[i] = new Qt3D::QTranslateTransform; //
      x=firevv->show_EigMatrix()[3*i][k_th];
      y=firevv->show_EigMatrix()[3*i+1][k_th];
      z=firevv->show_EigMatrix()[3*i+2][k_th];
      M=firevv->show_MaximumEigVecComponent()[k_th];

      sq=x*x+y*y+z*z;

      if(sq>th*M) {
	qDebug()<<"Creating Particles...: "<<i<<endl;
    //if((prt1+prt2)*i>=prt1*n) {
      //rad=10*firevv->show_Radii()*firevv->show_SizeRatio(); //0913
      //rad=1.5*firevv->show_Radii(); //0913
      //rad=firevv->show_Radii(); //0913
    //}
    rad=(sqrt(sq/M))*firevv->show_Radii();
	m_particleMeshs[i]->setRadius(rad);
    m_particleTransforms[i]->setTranslation(QVector3D(firevv->show_Zahyo()[3*i],firevv->show_Zahyo()[3*i+1] , firevv->show_Zahyo()[3*i+2]));
    //m_particleTransforms[i]->addTransform(m_particleTranslateTransforms[i]);
	m_particleEntities[i]->addComponent(m_particleMeshs[i]);
	m_particleEntities[i]->addComponent(m_particleTransforms[i]);
	if((prt1+prt2)*i<prt1*n) {
	  m_particleEntities[i]->addComponent(m_particleMaterial1);
	}
	else {
	  m_particleEntities[i]->addComponent(m_particleMaterial2);
	}
      }
    }
  }
  else {
    for(int i=0;i<n;i++) {
      m_particleEntities[i]= new Qt3DCore::QEntity(m_rootEntity);
      m_particleMeshs[i]= new Qt3DExtras::QSphereMesh(m_rootEntity);
      m_particleTransforms[i] = new Qt3DCore::QTransform(m_rootEntity);
      //m_particleTranslateTransforms[i] = new Qt3D::QTranslateTransform; //

      if((prt1+prt2)*i==prt1*n) {
	rad=firevv->show_Radii()*firevv->show_SizeRatio();
      }
      m_particleMeshs[i]->setRadius(rad);
      m_particleTransforms[i]->setTranslation(QVector3D(firevv->show_Zahyo()[3*i],firevv->show_Zahyo()[3*i+1] , firevv->show_Zahyo()[3*i+2]));
      //m_particleTransforms[i]->addTransform(m_particleTranslateTransforms[i]);
      m_particleEntities[i]->addComponent(m_particleMeshs[i]);
      m_particleEntities[i]->addComponent(m_particleTransforms[i]);
      if((prt1+prt2)*i<prt1*n) {
	m_particleEntities[i]->addComponent(m_particleMaterial1);
      }
      else {
	m_particleEntities[i]->addComponent(m_particleMaterial2);
      }
    }


  }
  //---


  qDebug()<<"END."<<endl;

}

void SceneModifier::eigvecSetting(FIREVV3D *firevv)
{
  if(!firevv->show_CalculatedEigMode()) {
    qDebug()<<"you don't calculate EIG"<<endl;
  }
  else {
    int n=firevv->show_ParticipatingParticles()[firevv->show_EigNum()];
    int PN=firevv->show_ParticleNum();

    if(firevv->show_CalculatedEigMode() && n >= 0) {

      //EigenVector painting

      qDebug()<<"Now eigvec painting..."<<endl;

      Qt3DExtras::QPhongMaterial *m_eigvecMaterial1 = new Qt3DExtras::QPhongMaterial();
      m_eigvecMaterial1->setDiffuse(QColor(QRgb(0x1C05FF)));
      Qt3DExtras::QPhongMaterial *m_eigvecMaterial2 = new Qt3DExtras::QPhongMaterial();
      //m_eigvecMaterial2->setDiffuse(QColor(QRgb(0xBCC8DB)));
      m_eigvecMaterial2->setDiffuse(QColor(QRgb(0x1C05FF)));
      //Qt3D::QCylinderMesh **m_eigvecMeshs;
      Qt3DExtras::QSphereMesh **m_eigvecMeshs;
      Qt3DCore::QTransform **m_eigvecTransforms;
      //Qt3D::QTranslateTransform **m_eigvecTranslateTransforms; //
      //Qt3D::QRotateTransform **m_eigvecRotateTransforms;
      //m_eigvecMeshs = new Qt3D::QCylinderMesh*[n];
      m_eigvecMeshs = new Qt3DExtras::QSphereMesh*[n];
      m_eigvecTransforms = new Qt3DCore::QTransform*[n];
      //m_eigvecTranslateTransforms  = new Qt3D::QTranslateTransform*[n]; //
      //m_eigvecRotateTransforms = new Qt3D::QRotateTransform*[n];

      int prt1=firevv->show_ParticleRatio1(),prt2=firevv->show_ParticleRatio2(),j=0,k_th=firevv->show_EigNum();
      double rad=firevv->show_Radii(),M,eig_len,theta,th=firevv->show_EigNum_threshold(),x,y,z,sq,l;

      Mat_DP EigMat=firevv->show_EigMatrix();
      for(int i=0;i<PN;i++) {
        x=EigMat[3*i][k_th];
        y=EigMat[3*i+1][k_th];
        z=EigMat[3*i+2][k_th];
        sq=x*x+y*y+z*z;
        eig_len=sqrt(sq);
        M=firevv->show_MaximumEigVecComponent()[k_th];

        if(sq>th*M) {
	  qDebug()<<"Creating eigvecEntity num: "<<j<<endl;
      m_eigvecEntities[j]= new Qt3DCore::QEntity(m_rootEntity);
      //m_eigvecMeshs[j]= new Qt3D::QCylinderMesh(m_rootEntity);
      m_eigvecMeshs[j]= new Qt3DExtras::QSphereMesh(m_rootEntity);
      m_eigvecTransforms[j] = new Qt3DCore::QTransform(m_rootEntity);
      //m_eigvecTranslateTransforms[j] = new Qt3D::QTranslateTransform; //
      //m_eigvecRotateTransforms[j] = new Qt3D::QRotateTransform;
      //if((prt1+prt2)*i>=prt1*N) {
            //rad=10*firevv->show_Radii()*firevv->show_SizeRatio();
          //rad=1.5*firevv->show_Radii();
      //}
      //m_eigvecMeshs[j]->setRadius(0.3*rad);
      rad=(sqrt(sq/M))*firevv->show_Radii();
      m_eigvecMeshs[j]->setRadius(rad);
      double eps=0.1*rad;
      //l=sq*10*rad/M;
      //m_eigvecMeshs[j]->setLength(l);

      //m_eigvecRotateTransforms[j]->setAxis(QVector3D(z,0,-x));
      theta=acos(y/eig_len);
      double phi=acos(x/(eig_len*sin(theta)));
      //m_eigvecRotateTransforms[j]->setAngleRad(theta);

      //m_eigvecTranslateTransforms[j]->setTranslation(QVector3D(firevv->show_Zahyo()[3*i]+0.5*l*x/eig_len,firevv->show_Zahyo()[3*i+1]+0.5*l*y/eig_len, firevv->show_Zahyo()[3*i+2]+0.5*l*z/eig_len));
      m_eigvecTransforms[j]->setTranslation(QVector3D(firevv->show_Zahyo()[3*i]+eps*sin(theta)*cos(phi),firevv->show_Zahyo()[3*i+1]+eps*cos(theta), firevv->show_Zahyo()[3*i+2]+eps*sin(theta)*cos(phi)));
      //m_eigvecTransforms[j]->addTransform(m_eigvecRotateTransforms[j]);
      //m_eigvecTransforms[j]->addTransform(m_eigvecTranslateTransforms[j]);
	  m_eigvecEntities[j]->addComponent(m_eigvecMeshs[j]);
	  m_eigvecEntities[j]->addComponent(m_eigvecTransforms[j]);
      if((prt1+prt2)*i<prt1*PN) {
	    m_eigvecEntities[j]->addComponent(m_eigvecMaterial1);
	  }
	  else {
            m_eigvecEntities[j]->addComponent(m_eigvecMaterial2);
	  }
	  j++;
        }
        else {
        }

      }
      qDebug()<<"END."<<endl;
    }
  }
}
