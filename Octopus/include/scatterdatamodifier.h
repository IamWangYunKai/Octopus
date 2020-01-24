#ifndef SCATTERDATAMODIFIER_H
#define SCATTERDATAMODIFIER_H

#include <QtDataVisualization/q3dscatter.h>
using namespace QtDataVisualization;

class ScatterDataModifier{
public:
    explicit ScatterDataModifier(Q3DScatter *scatter);
    ~ScatterDataModifier();
    void addData();
private:
    QVector3D randVector();
    Q3DScatter *m_graph;
};

#endif
