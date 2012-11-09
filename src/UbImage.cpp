#include "UbImage.h"
#include <iostream>

namespace Uber {
	UbImage::UbImage( QWidget* parent )
		: QGLWidget(parent)
	{

	}
	UbImage::~UbImage(void)
	{

	}
	void UbImage::setImage(const QImage& image)
	{
		makeCurrent();
		m_Image = image;
		update();
	}
	void UbImage::paintEvent(QPaintEvent*)
	{
		makeCurrent();	
		QPainter p( this );
		p.setRenderHint( QPainter::SmoothPixmapTransform, 1 );
		p.setBrush(QColor(69,82,80));
		p.drawImage( 0, 0, m_Image );
	}
}
