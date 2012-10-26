#ifndef CLISTENERLINEDDA_H
#define CLISTENERLINEDDA_H

#include "abstractlinelistener.h"
#include "algorithmdda.h"

class CListenerLineDDA : public CAbstractLineListener
{
public:
    explicit CListenerLineDDA(CCoordinateView *view, CDebugModeBox *box, QColor mainColor, QColor secondaryColor);


private:
    void initialize();

};

#endif // CLISTENERLINEDDA_H
