/****************************************************************************
 **
 ** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the Qt3D module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL3$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and The Qt Company. For licensing terms
 ** and conditions see http://www.qt.io/terms-conditions. For further
 ** information use the contact form at http://www.qt.io/contact-us.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 3 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPLv3 included in the
 ** packaging of this file. Please review the following information to
 ** ensure the GNU Lesser General Public License version 3 requirements
 ** will be met: https://www.gnu.org/licenses/lgpl.html.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 2.0 or later as published by the Free
 ** Software Foundation and appearing in the file LICENSE.GPL included in
 ** the packaging of this file. Please review the following information to
 ** ensure the GNU General Public License version 2.0 requirements will be
 ** met: http://www.gnu.org/licenses/gpl-2.0.html.
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include <QApplication>

#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qcameralens.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DExtras/qt3dwindow.h>
#include <QOrbitCameraController>

#include "FIREVV3D.h"
#include "scenemodifier.h"
#include "mainwindow.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  Qt3DExtras::Qt3DWindow *view=new Qt3DExtras::Qt3DWindow();
  //Qt3DCore::QEntity *scene = createScene();
  //view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
  //Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
  //view->registerAspect(input);

  // Root entity
  Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
  //Qt3D::QEntity *rootEntity = new Qt3D::QEntity();
  MainWindow *mWin = new MainWindow;
  SceneModifier *SM = new SceneModifier(rootEntity,mWin->show_FIREVV3D());
  QObject::connect(mWin->show_FIREVV3D(),&FIREVV3D::getZahyo,[SM,mWin,rootEntity](){SM->repaint(rootEntity,mWin->show_FIREVV3D());});
  QObject::connect(mWin->show_FIREVV3D(),&FIREVV3D::getEigenVector,[SM,mWin,rootEntity](){SM->repaint(rootEntity,mWin->show_FIREVV3D());});
  QObject::connect(mWin,&MainWindow::repaintEIG,[SM,mWin,rootEntity](){SM->repaint(rootEntity,mWin->show_FIREVV3D());});

  // Camera
  Qt3DRender::QCamera *cameraEntity = view->camera();
  cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
  cameraEntity->setPosition(QVector3D(0, 0, -150.0f));
  cameraEntity->setUpVector(QVector3D(0, 1, 0));
  cameraEntity->setViewCenter(QVector3D(0, 0, 0));

  Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
  Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
  light->setColor("white");
  light->setIntensity(1);
  lightEntity->addComponent(light);
  Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
  lightTransform->setTranslation(cameraEntity->position());
  lightEntity->addComponent(lightTransform);

  Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
  camController->setLookSpeed( 90.0f );
  camController->setLinearSpeed( 30.0f );
  camController->setCamera(cameraEntity);
  /*
  Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
  camController->setLinearSpeed( 50.0f );
  camController->setLookSpeed( 180.0f );
  camController->setCamera(cameraEntity);
  */
  // Material
  //Qt3D::QMaterial *material = new Qt3D::QPhongMaterial(rootEntity);
  //Qt3D::QPhongMaterial * pmat = new Qt3D::QPhongMaterial();
  //Qt3D::QPhongMaterial *sphereMaterial = new Qt3D::QPhongMaterial();

  //pmat->setDiffuse(QColor(QRgb(0x000000)));
  //pmat->setAmbient(QColor(QRgb(0x665423)));
  //sphereMaterial->setAmbient(QColor(QRgb(0x47EA7E)));
  //sphereMaterial->setDiffuse(QColor(QRgb(0x47EA7E)));

  //QWidget *qwin = new QWidget;
  //FIREVV3D *fire3d_obj= new FIREVV3D;

  //QObject::connect(mWin->show_FIREVV3D(),SIGNAL(getZahyo()),SM,SLOT(repaint(rootEntity,mWin->show_FIREVV3D())));

  // Sphere
  //Qt3D::QEntity *sphereEntity = new Qt3D::QEntity(rootEntity);
  //Qt3D::QSphereMesh *sphereMesh = new Qt3D::QSphereMesh;
  //sphereMesh->setRadius(3);

  //Qt3D::QTransform *sphereTransform = new Qt3D::QTransform;
  //Qt3D::QTranslateTransform *sphereTranslateTransform = new Qt3D::QTranslateTransform;
  //sphereTranslateTransform->setTranslation(QVector3D(5, 5, 5));

  /*
    Qt3D::QRotateTransform *sphereRotateTransform = new Qt3D::QRotateTransform;
    QPropertyAnimation *sphereRotateTransformAnimation = new QPropertyAnimation(sphereRotateTransform);
    sphereRotateTransformAnimation->setTargetObject(sphereRotateTransform);
    sphereRotateTransformAnimation->setPropertyName("angle");
    sphereRotateTransformAnimation->setStartValue(QVariant::fromValue(0));
    sphereRotateTransformAnimation->setEndValue(QVariant::fromValue(360));
    sphereRotateTransformAnimation->setDuration(10000);
    sphereRotateTransformAnimation->setLoopCount(-1);
    sphereRotateTransformAnimation->start();

    sphereRotateTransform->setAxis(QVector3D(0, 1, 0));
    sphereRotateTransform->setAngleDeg(0);
  */
  //sphereTransform->addTransform(sphereTranslateTransform);
  //sphereTransform->addTransform(sphereRotateTransform);

  //sphereEntity->addComponent(sphereMesh);
  //sphereEntity->addComponent(sphereTransform);
  //sphereEntity->addComponent(material);


  QObject::connect(mWin,SIGNAL(quit()),&app,SLOT(quit()));

  view->setRootEntity(rootEntity);
  view->show();

  return app.exec();
}
