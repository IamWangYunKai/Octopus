#ifndef GLITEM_H
#define GLITEM_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QQuickItem>
#include <QQuickWindow>

#define DECLRARE_Q_PROPERTY( aType, aProperty ) protected:\
    aType m_ ## aProperty; public:\
    aType aProperty( void ) { return m_ ## aProperty; } \
    void set ## aProperty( aType _ ## aProperty ) {\
        m_ ## aProperty = _ ## aProperty;\
        if ( window( ) != Q_NULLPTR ) {\
            window( )->update( );\
        }\
    }

class GLItem: public QQuickItem{
    Q_OBJECT
    Q_PROPERTY( qreal rotateAngle READ RotateAngle
                WRITE setRotateAngle NOTIFY RotateAngleChanged )
    Q_PROPERTY( QVector3D axis READ Axis
                WRITE setAxis NOTIFY AxisChanged )
public:
    explicit GLItem();
signals:
    void RotateAngleChanged();
    void AxisChanged();
protected slots:
    void Render();
    void OnWindowChanged(QQuickWindow* pWindow);
    void Release();
protected:
    bool RunOnce();

    QMatrix4x4                  m_ModelViewMatrix;
    QMatrix4x4                  m_ProjectionMatrix;
    QOpenGLBuffer               m_VertexBuffer, m_IndexBuffer;
    QOpenGLBuffer               m_ColorBuffer;
    QOpenGLShaderProgram        m_ShaderProgram;

    DECLRARE_Q_PROPERTY( qreal, RotateAngle )
    DECLRARE_Q_PROPERTY( QVector3D, Axis )
};

#endif // GLITEM_H
