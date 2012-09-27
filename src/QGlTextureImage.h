#ifndef QGLTEXTUREIMAGE_H
#define QGLTEXTUREIMAGE_H
#include <QIMAGE>
#include <qgl.h>

namespace _2Real
{
	class ImageType;
}

class QGlTextureImage : public QGLWidget
{
	Q_OBJECT

public:
	QGlTextureImage( QWidget *parent=0);
	~QGlTextureImage();

	void updateTexture( const unsigned int width, const unsigned int height, const unsigned int channels, _2Real::ImageType const& type, void const* data );

protected:

	static void checkGLState( std::string const& msg );

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
	void paintEvent(QPaintEvent*);
private:
	GLuint	m_iTexture;
	bool	m_bIsTextureGenerated;
	QImage	m_Image;
};
#endif // QGLTEXTUREIMAGE_H
