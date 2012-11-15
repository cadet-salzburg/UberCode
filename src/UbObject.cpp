#include "UbObject.h"

namespace Uber {
	UbObject::UbObject( QGraphicsItem *parent )
		:QGraphicsObject( parent ),
		m_Color(69,82,80),
		m_Width(0.f),
		m_Height(0.f)
	{

	}

	UbObject::~UbObject(void)
	{

	}

	void UbObject::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
	{
		Q_UNUSED(option)
		Q_UNUSED(widget)
		QPen pen;
		pen.setWidthF(0.5f);
		pen.setBrush(Qt::black);	
		painter->setPen(pen);
		painter->setBrush(m_Color);
		painter->drawPath( m_Path );
	}

	QRectF UbObject::boundingRect() const
	{
		return QRectF( QPointF(-m_Width/2.-1 , -m_Height/2.-1), QPointF( m_Width/2.+1,m_Height/2.+1) );
	}

}