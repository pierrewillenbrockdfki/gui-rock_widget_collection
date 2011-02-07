/*
 * File:   SonarViewGL.h
 * Author: Matthias Goldhoorn (matthias.goldhoorn@dfki.de)
 *
 */

#ifndef SONARVIEWGL_H
#define	SONARVIEWGL_H

#include "image_view/ImageViewGL.h"
#include <QTimer>
#include <QMutex>

class SonarViewGL : public ImageViewGL
{
    Q_OBJECT
    Q_CLASSINFO("Author", "Matthias Goldhoorn")

static const float ZOOM_MAX = 6000.0;
static const float ZOOM_MIN = -6000.0;


public:
    SonarViewGL(ImageView &parent, unsigned int maximumBearings=6400);
    virtual ~SonarViewGL();
     QSize minimumSizeHint() const;
     QSize sizeHint() const;
     void setPosition(int xRot,int yRot, int zRot, int xMove, int yMove, int zMove, float zoom, int width, int height);
     void setData(const std::vector<uint8_t> data, int bearing);
     void reset(double currentScale);
     void setGroundTrue(double sizeX,double sizeY,double posX,double posY,double rot);
     void setWallDist(int bearing, int dist,int dist2);

public slots:
     void repaintFunc();
     void setXRotation(int angle);
     void setYRotation(int angle);
     void setZRotation(int angle);
     void setxPosition(int value);
     void setyPosition(int value);
     void setzPosition(int value);
     void keyPressEvent ( QKeyEvent * event );

protected:
     void initializeGL();
     void paintGL();
     void resizeGL(int width, int height);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void wheelEvent(QWheelEvent *event);
     void checkGL(const char*);
     bool deleteSurfaces;
     void drawList();
     void drawFaces();
     void drawSurfaces();
     int cloudSize;
     void paintSonar(); 
     double factor;
     GLuint makeObject();
     GLuint show_pointcloud();
     GLuint groundPlane;
     void normalizeAngle(int *angle);
     void createAvalon(); 
     float zoom;
     int lastBearing;
     int lastWallBearing;

     inline double max(double a,double b){
     	return (a>b)?a:b;
     }
     const unsigned int maximumBearings;

     std::vector<std::pair<GLuint, QColor> > colorList; 
     GLuint *wallDist, *bearingList;
     GLuint groundTrue,avalon;
     bool *bearingChanged, *listValid;
     bool dataChanged;     
     bool paintGroundTrue,paintWall;

     int xRot;
     int yRot;
     int zRot;
     int xShift;
     int yShift;
     int zShift;
     int medium_ableitung;
     int overlay_border;
     double currentScale;

     unsigned int oldSize;
     volatile GLuint *indices;
     volatile GLubyte *colors;
     volatile GLfloat *vertecies;
     QPoint lastPos;
     QPoint lastPosTrans;
     QTimer repaintTimer;
     QMutex mutex;

signals:
     void xRotationChanged(int angle);
     void yRotationChanged(int angle);
     void zRotationChanged(int angle);
     void xPositionChanged(int value);
     void yPositionChanged(int value);
     void zPositionChanged(int value);

};

#endif	

