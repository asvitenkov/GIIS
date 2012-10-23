#ifndef DEFINES_H
#define DEFINES_H



enum MouseClickState{
    MCS_UNDEFINED,
    MCS_FIRST_CLICK,
    MCS_SECOND_CLICK,

    MCS_LAST_ITEM
};


enum Mode{
    MODE_DEBUG,
    MODE_NORMAL,


    MODE_LAST
};


enum DrawShapeTypes{
    DST_LINE,
    DST_ELLIPSE,

    DST_LAST_TYPE
};

#endif // DEFINES_H
