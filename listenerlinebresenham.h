#ifndef LISTENERLINEBRESENHAM_H
#define LISTENERLINEBRESENHAM_H

#include "abstractlinelistener.h"
#include "algorithmbresenham.h"

class CListenerLineBresenham : public CAbstractLineListener
{
public:
    explicit CListenerLineBresenham(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);

private:
    void initialize();

};

#endif // LISTENERLINEBRESENHAM_H
