#include "UbObject.h"


UbObject::UbObject( QGraphicsItem *parent )
	:QGraphicsObject( parent )
{

}

UbObject::~UbObject(void)
{

}

void UbObject::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{

}

QRectF UbObject::boundingRect() const
{
	return QRectF( QPointF(-m_Width/2., -m_Height/2.), QPointF( m_Width/2.,m_Height/2.) );
}

void UbObject::constructPath()
{

}
