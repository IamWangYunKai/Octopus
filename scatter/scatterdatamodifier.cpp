#include "scatterdatamodifier.h"
#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtDataVisualization/qscatter3dseries.h>
#include <QtCore/qmath.h>
#include <QtCore/qrandom.h>

using namespace QtDataVisualization;

const int numberOfItems = 10000;

ScatterDataModifier::ScatterDataModifier(Q3DScatter *scatter)
    : m_graph(scatter){
    m_graph->activeTheme()->setType(Q3DTheme::ThemeEbony);
    QFont font = m_graph->activeTheme()->font();
    font.setPointSize(40.0f);
    m_graph->activeTheme()->setFont(font);
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);

    QScatterDataProxy *proxy = new QScatterDataProxy;
    QScatter3DSeries *series = new QScatter3DSeries(proxy);
    series->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    series->setMeshSmooth(false);
    m_graph->addSeries(series);

    addData();
}

ScatterDataModifier::~ScatterDataModifier(){
    delete m_graph;
}

void ScatterDataModifier::addData(){
    m_graph->axisX()->setTitle("X");
    m_graph->axisY()->setTitle("Y");
    m_graph->axisZ()->setTitle("Z");

    QScatterDataArray *dataArray = new QScatterDataArray;
    dataArray->resize(numberOfItems);
    QScatterDataItem *ptrToDataArray = &dataArray->first();

    for (int i = 0; i < numberOfItems; i++) {
        ptrToDataArray->setPosition(randVector());
        ptrToDataArray++;
    }

    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
}

QVector3D ScatterDataModifier::randVector(){
    return QVector3D(
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f -
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f,
                (float)(QRandomGenerator::global()->bounded(100)) / 100.0f -
                (float)(QRandomGenerator::global()->bounded(100)) / 100.0f,
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f -
                (float)(QRandomGenerator::global()->bounded(100)) / 2.0f);
}
