#include "glitem.h"

GLItem::GLItem():
    m_VertexBuffer( QOpenGLBuffer::VertexBuffer ),
    m_IndexBuffer( QOpenGLBuffer::IndexBuffer ),
    m_ColorBuffer( QOpenGLBuffer::VertexBuffer ),
    m_RotateAngle( 0.0f ),
    m_Axis( 1.0f, 1.0f, 0.0f ){
    connect( this, SIGNAL( windowChanged( QQuickWindow* ) ),
             this, SLOT( OnWindowChanged( QQuickWindow* ) ) );
}

void GLItem::OnWindowChanged( QQuickWindow* pWindow ){
    if ( pWindow == Q_NULLPTR ) return;
    connect( pWindow, SIGNAL( beforeRendering( ) ),
             this, SLOT( Render( ) ), Qt::DirectConnection );
    pWindow->setClearBeforeRendering( false );
}

void GLItem::Render(){
    static bool runOnce = RunOnce( );
    Q_UNUSED( runOnce );

    m_ModelViewMatrix.setToIdentity( );
    m_ModelViewMatrix.translate( 0.0f, 0.0f, -60.0f );
    m_ModelViewMatrix.rotate( m_RotateAngle, m_Axis.x( ),
                              m_Axis.y( ), m_Axis.z( ) );

    QOpenGLFunctions glFuncs(QOpenGLContext::currentContext());

    glFuncs.glViewport( 0, 0, window( )->width( ), window( )->height( ) );
    glFuncs.glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glFuncs.glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glFuncs.glEnable( GL_DEPTH_TEST );
    glFuncs.glEnable( GL_CULL_FACE );
    glFuncs.glFrontFace( GL_CW );

    m_ShaderProgram.bind( );
    m_VertexBuffer.bind( );
    int posLoc = m_ShaderProgram.attributeLocation( "position" );
    m_ShaderProgram.enableAttributeArray( posLoc );
    m_ShaderProgram.setAttributeBuffer( posLoc,
                                        GL_FLOAT,
                                        0,
                                        3,
                                        0 );

    m_ColorBuffer.bind( );
    int colorLoc = m_ShaderProgram.attributeLocation( "color" );
    m_ShaderProgram.enableAttributeArray( colorLoc );
    m_ShaderProgram.setAttributeBuffer( colorLoc,
                                        GL_FLOAT,
                                        0,
                                        4,
                                        0 );
    m_IndexBuffer.bind( );
    m_ShaderProgram.setUniformValue( "modelViewMatrix", m_ModelViewMatrix );
    m_ShaderProgram.setUniformValue( "projectionMatrix", m_ProjectionMatrix );
    glFuncs.glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, Q_NULLPTR );

    m_ShaderProgram.disableAttributeArray( posLoc );
    m_ShaderProgram.disableAttributeArray( colorLoc );
    m_IndexBuffer.release( );
    m_VertexBuffer.release( );
    m_ShaderProgram.release( );
}

bool GLItem::RunOnce(){
    m_ShaderProgram.addShaderFromSourceFile( QOpenGLShader::Vertex,
                                             ":/shader/Shader.vsh" );
    m_ShaderProgram.addShaderFromSourceFile( QOpenGLShader::Fragment,
                                             ":/shader/Shader.fsh" );
    m_ShaderProgram.link();

    const GLfloat length = 10.0f;
    const GLfloat vertices[] = {
        length, -length, length,
        length, -length, -length,
        -length, -length, -length,
        -length, -length, length,
        length, length, length,
        length, length, -length,
        -length, length, -length,
        -length, length, length
    };

    m_VertexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_VertexBuffer.create( );
    m_VertexBuffer.bind( );
    m_VertexBuffer.allocate( vertices, sizeof( vertices ) );

    const GLfloat colors[] = {
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f
    };
    m_ColorBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_ColorBuffer.create( );
    m_ColorBuffer.bind( );
    m_ColorBuffer.allocate( colors, sizeof( colors ) );


    GLubyte indices[] = {
        0, 1, 2, 0, 2, 3,// down
        7, 6, 4, 6, 5, 4,// up
        7, 4, 3, 4, 0, 3,// left
        5, 6, 1, 6, 2, 1,// right
        4, 5, 0, 5, 1, 0,// front
        3, 2, 6, 3, 6, 7,// back
    };

    m_IndexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_IndexBuffer.create( );
    m_IndexBuffer.bind( );
    m_IndexBuffer.allocate( indices, sizeof( indices ) );

    float aspectRatio  = float( window( )->width( ) ) / float( window( )->height( ) );
    m_ProjectionMatrix.perspective( 45.0f,
                                    aspectRatio,
                                    0.5f,
                                    500.0f );

    connect( window( )->openglContext( ),
             SIGNAL( aboutToBeDestroyed( ) ),
             this, SLOT( Release( ) ),
             Qt::DirectConnection );

    return true;
}

void GLItem::Release( ){
//    qDebug( "Vertex buffer and index buffer are to be destoryed." );
    m_VertexBuffer.destroy( );
    m_IndexBuffer.destroy( );
    m_ColorBuffer.destroy( );
}
