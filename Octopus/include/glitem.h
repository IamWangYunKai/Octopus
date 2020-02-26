#ifndef GLITEM_H
#define GLITEM_H

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QtCore/QRunnable>

class GLRenderer : public QObject, protected QOpenGLFunctions{
    Q_OBJECT
public:
    GLRenderer() : m_t(0), m_program(0) { }
    ~GLRenderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }

public slots:
    void init();
    void paint();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram *m_program;
    QQuickWindow *m_window;
};

class GLItem : public QQuickItem{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    GLItem();

    qreal t() const { return m_t; }
    void setT(qreal t);

signals:
    void tChanged();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    void releaseResources() override;

    qreal m_t;
    GLRenderer *m_renderer;
};

class CleanupJob : public QRunnable{
public:
    CleanupJob(GLRenderer *renderer) : m_renderer(renderer) { }
    void run() override { delete m_renderer; }
private:
    GLRenderer *m_renderer;
};

#endif // GLITEM_H
