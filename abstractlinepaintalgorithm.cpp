#include "abstractlinepaintalgorithm.h"

CAbstractLinePaintAlgorithm::CAbstractLinePaintAlgorithm(QPoint startPoint, QPoint endPoint)
     : m_startPoint(startPoint), m_endPoint(endPoint)
{

}


CAbstractLinePaintAlgorithm::~CAbstractLinePaintAlgorithm()
{

}


void CAbstractLinePaintAlgorithm::setEndPos(QPoint pos)
{
    m_endPoint = pos;
}


void CAbstractLinePaintAlgorithm::setStartPos(QPoint pos)
{
    m_startPoint = pos;
}
