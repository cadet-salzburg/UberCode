#include <QPainter>
#include <iostream>
#include "UbLink.h"
#include "UbNode.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"

namespace Uber {
	UbLink::UbLink( QGraphicsItem *parent,  QGraphicsScene *scene )
		:QGraphicsPathItem(parent, scene),
		m_StartNode( UbNodeRef( new UbNode() ) ),
		m_EndNode( UbNodeRef( new UbNode() ) )
	{

	}

	UbLink::~UbLink()
	{
		std::cout << "UbLink destructor was called" << std::endl;
	}

	void UbLink::updatePath()
	{
		if ( m_StartNode && m_EndNode )
		{
			QPointF startPos = m_StartNode->scenePos();
			QPointF endPos	 = m_EndNode->scenePos();

			QPainterPath bezierPath;
			bezierPath.moveTo( startPos );
			qreal dist   = endPos.x() - startPos.x();
			qreal offset = 0.5f*dist; 
			QPointF cpA  = startPos + QPointF( offset, 0 );
			QPointF cpB  = endPos   - QPointF( offset, 0 );
			bezierPath.cubicTo( cpA, cpB, endPos );
			QPainterPathStroker outliner;
			outliner.setWidth(4.f);
			outliner.setCapStyle( Qt::RoundCap );
			setPath( outliner.createStroke(bezierPath) );
		}
	}

	void UbLink::setStartNode( UbNodeRef start )
	{
		m_StartNode.clear();
		m_StartNode = start;
	}

	void UbLink::setEndNode( UbNodeRef end )
	{
		m_EndNode.clear();
		m_EndNode = end;
	}

	void UbLink::setNodes( UbNodeRef start, UbNodeRef end )
	{
		setStartNode( start );
		setEndNode( end );
		updatePath();
	}


	UbNodeRef UbLink::getStartNode() const
	{
		return m_StartNode;
	}

	UbNodeRef UbLink::getEndNode() const
	{
		return m_EndNode;
	}

	void UbLink::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
	{
		Q_UNUSED(option)
		Q_UNUSED(widget)
		updatePath();
		QPen pen;
		pen.setWidthF(1.f);
		pen.setBrush(Qt::black);	
		painter->setPen(pen);
		painter->setBrush(QColor(177,189,180));
		painter->drawPath(path());
	}

	bool UbLink::nodesAreSet()
	{
		bool res = false;
		if ( m_StartNode->parentObject() && m_EndNode->parentObject() )
			res = true;
		return res;
	}
}