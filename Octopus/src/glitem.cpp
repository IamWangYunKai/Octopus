#include "glitem.h"
#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QRandomGenerator>

namespace {
    QRandomGenerator grandom;

    GLuint colorUniformLoc;
    GLuint vertexAttribLoc;
    GLuint mvpMatrixUniLoc;
//    QVector<GLfloat> vertices;
}

GLItem::GLItem()
    : m_t(0)
    , m_renderer(nullptr){
    connect(this, &QQuickItem::windowChanged, this, &GLItem::handleWindowChanged);
}

void GLItem::setT(qreal t){
    if (t == m_t) return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void GLItem::handleWindowChanged(QQuickWindow *win){
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &GLItem::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &GLItem::cleanup, Qt::DirectConnection);
        // Ensure we start with cleared to black. The squircle's blend mode relies on this.
        win->setColor(Qt::black);
    }
}

void GLItem::cleanup(){
    delete m_renderer;
    m_renderer = nullptr;
}

void GLItem::releaseResources(){
    window()->scheduleRenderJob(new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
    m_renderer = nullptr;
}

void GLItem::sync(){
    if (!m_renderer) {
        m_renderer = new GLRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &GLRenderer::init, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &GLRenderer::paint, Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setWindow(window());
}

GLRenderer::~GLRenderer(){
    delete m_program;
}

void GLRenderer::init(){

    if (!m_program) {
        QSGRendererInterface *rif = m_window->rendererInterface();
        Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL || rif->graphicsApi() == QSGRendererInterface::OpenGLRhi);

        initializeOpenGLFunctions();

        m_program = new QOpenGLShaderProgram();
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                                    "attribute vec4 a_vertex;"
//                                                    "uniform mat4 u_mvpMatrix;"
                                                    "void main() {"
                                                    "   gl_Position = a_vertex;"
                                                    "}");
        m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                                    "uniform vec3 u_color;"
                                                    "void main() {"
                                                    "   gl_FragColor = vec4(u_color, 1.0);"
                                                    "}");


//        for (int i=0;i<5000;i++) {
//            auto theta = 2*grandom.generateDouble()-1;
//            vertices.append(0.0f);
//            vertices.append(theta);
//            vertices.append(sin(theta));
//        }

        m_program->link();

        colorUniformLoc = m_program->uniformLocation("u_color");
        vertexAttribLoc = m_program->attributeLocation("a_vertex");
        mvpMatrixUniLoc = m_program->uniformLocation("u_mvpMatrix");

    }
}

void GLRenderer::paint(){
    m_window->beginExternalCommands();

    m_program->bind();
    m_program->enableAttributeArray(0);

    glDisableVertexAttribArray(0);//Disable all vertex attributes


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear screen and depth buffer
    m_program->enableAttributeArray(vertexAttribLoc);

//    QMatrix4x4 pmvMatrix;
//    m_program->setUniformValue(mvpMatrixUniLoc, pmvMatrix);
//    m_program->setAttributeArray(vertexAttribLoc, GL_FLOAT, vertices.data(), 3);

    QVector3D color(grandom.generateDouble(),grandom.generateDouble(),grandom.generateDouble());
    m_program->setUniformValue("u_color", color);

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glEnableVertexAttribArray(0);
    glDisable(GL_DEPTH_TEST);
//    glEnable(GL_DEPTH_TEST);
//    glClearDepth(1.0);
//    glDepthFunc(GL_LEQUAL);//Type of depth test performed

    glDisable(GL_BLEND);
    glLoadIdentity();//Reset the current model observation matrix

    glPointSize(15.0f);
    if (!glIsEnabled(GL_POINT_SMOOTH)) glEnable(GL_POINT_SMOOTH);

    QMatrix4x4 mvpMatrix;
    m_program->setUniformValue(mvpMatrixUniLoc, mvpMatrix);

    glDrawArrays(GL_POINTS, 0, 5);
    glBegin(GL_POINTS);
    for (int i=0;i<500;i++) {
        auto theta = 2*grandom.generateDouble()-1;
        glVertex3f(theta+grandom.generateDouble()*0.3,
                   sin(theta)*fabs(theta),
                   sin(theta)
                   );
    }
    glEnd();

    m_program->release();

    m_window->resetOpenGLState();
    m_window->endExternalCommands();
}
