#include "UbImage.h"
#include <iostream>

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
    p.drawImage( 0, 0, m_Image );
}
