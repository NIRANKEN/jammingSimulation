#ifndef SCENEMODIFIER_H
#define SCENEMODIFIER_H

#include <QtCore/QObject>

#include "Qt3DCore/qentity.h"
#include "Qt3DCore/qtransform.h"
#include <Qt3DExtras/QTorusMesh>
//#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
//#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

#include "FIREVV3D.h"

class SceneModifier : public QObject
{
  Q_OBJECT

 public:
  explicit SceneModifier(Qt3DCore::QEntity *rootEntity, FIREVV3D *firevv);
  ~SceneModifier();

  Qt3DCore::QEntity* show_rootEntity();
  void boxSetting(FIREVV3D *firevv);
  void sphereSetting(FIREVV3D *firevv);
  void eigvecSetting(FIREVV3D *firevv);

  public slots:
    void enablePeriodicBox(bool enabled);
    void enableParticles(bool enabled);
    void enableForceNetwork(bool enabled);
    void enableEigenVector(bool enabled);
    void repaint(Qt3DCore::QEntity *rootEntity,FIREVV3D *firevv);

 private:
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DCore::QEntity **m_cubeEntities;
    Qt3DCore::QEntity **m_particleEntities;
    Qt3DCore::QEntity **m_forcelineEntities;
    Qt3DCore::QEntity **m_eigvecEntities;
    int N;

};

#endif // SCENEMODIFIER_H
