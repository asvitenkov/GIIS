#ifndef DEFINES_H
#define DEFINES_H

#include "edge3d.h"
#include "shapeface.h"

typedef QList<CEdge3D*> CEdgeArray;
//typedef QList<CShapeFace> CShapeFaceArray;

enum MouseClickState{
    MCS_UNDEFINED,
    MCS_FIRST_CLICK,
    MCS_SECOND_CLICK,
    MCS_MOVE,
    MCS_PRESS,
    MCS_RELEASE
};


enum Mode{
    MODE_DEBUG,
    MODE_NORMAL
};


enum DrawShapeTypes{
    DST_LINE,
    DST_ELLIPSE
};

#endif // DEFINES_H
