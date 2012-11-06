#include <QPainter>
#include <QStyleOption>
#include <iostream>
#include "UbNode.h"
#include "UbLink.h"
#include "UbLinkController.h"
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QToolTip>

namespace Uber {
	UbNode::UbNode( QGraphicsItem *parent )
		:QGraphicsObject( parent )
		,m_Radius( 4 )
	{
		constructPath();
		setAcceptHoverEvents( true ); 
	}

	void UbNode::constructPath()
	{
		m_Path.addEllipse( -m_Radius, -m_Radius, 2*m_Radius, 2*m_Radius );

		//setFlag(QGraphicsItem::ItemIsMovable);
		//setFlag(QGraphicsItem::ItemIsSelectable);
	}

	QRectF UbNode::boundingRect() const
	{
		return QRectF(QPointF(-m_Radius, -m_Radius), QPointF( m_Radius, m_Radius));
	}

	void UbNode::setRadius( qreal radius )
	{
		m_Radius = radius;
	}

	const qreal&	UbNode::getRadius()  const
	{
		return m_Radius;
	}
	void UbNode::setName( QString name )
	{
		m_NodeName = name;
		setToolTip( m_NodeName );
	}

	void UbNode::hoverMoveEvent ( QGraphicsSceneHoverEvent * event )
	{
		std::cout << " Hover is happening" << std::endl;
		QPointF pos = event->lastScreenPos();
		QToolTip::showText( QPoint(pos.x(),pos.y()), QString(m_NodeName) );
	}
	void UbNode::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
	{
		std::cout << " Hover stopped happening" << std::endl;
	}

	void UbNode::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
	{
		Q_UNUSED(option)
			Q_UNUSED(widget)
			QPen pen;
		pen.setWidthF(1.f);
		pen.setBrush(Qt::black);	
		painter->setPen(pen);
		painter->setBrush(QColor(177,189,180));
		painter->drawPath( m_Path );
	}
}