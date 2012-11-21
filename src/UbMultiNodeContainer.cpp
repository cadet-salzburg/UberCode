#include "UbMultiNodeContainer.h"
#include <QPen>
#include <QPainter>
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Uber {
	UbMultiNodeContainer::UbMultiNodeContainer( QGraphicsItem *parent )
	{
		m_Zvalue = zValue();
		addNodes();
	}
	UbMultiNodeContainer::UbMultiNodeContainer(QGraphicsItem *parent, const  _2Real::app::InletHandle& handle)
		:QGraphicsObject(parent)
	{
		m_Handle = handle;
		m_Zvalue = zValue();
		addNodes();
	}

	UbMultiNodeContainer::~UbMultiNodeContainer(void)
	{

	}

	void UbMultiNodeContainer::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
	{
		QPen pen;
		pen.setWidthF(0.5f);
		pen.setBrush(QColor(200,200,200));	
		painter->setPen(pen);
		painter->setBrush(QColor(200,200,200));
		painter->drawPath( m_ExpandedPath );
	}

	QRectF UbMultiNodeContainer::boundingRect() const
	{
		if ( m_Nodes.size() )
		{	QRectF r;
			QRectF  rectA	= m_Nodes.front()->boundingRect();
			QPointF	centerA	= m_Nodes.front()->pos();
			QRectF  rectB	= m_Nodes.back()->boundingRect();
			QPointF	centerB	= m_Nodes.back()->pos();
			r.setTopLeft( rectB.topLeft()+centerB );
			r.setTopRight( rectB.topRight()+centerB );
			r.setBottomLeft( rectA.bottomLeft()+centerA);
			r.setBottomRight( rectA.bottomRight()+centerA);
			return r;
		}
		return m_ExpandedPath.boundingRect();
	}

	void UbMultiNodeContainer::createPath()
	{
		for ( int i=0; i< m_Handle.getSize(); ++i)
		{
			QPointF pos = (m_Percent/100.)*m_TargetPositions[i];
			m_Nodes[i]->setPos(pos);
			setOpacity(m_Percent/100.);
		}
		update();
	}

	qreal UbMultiNodeContainer::getPercent()
	{
		return m_Percent;
	}

	void UbMultiNodeContainer::setPercent( qreal percent )
	{
		m_Percent = percent;
	}

	//void UbMultiNodeContainer::setNumNodes( int numNodes )
	//{
	//	m_NumNodes = numNodes;
	//}

	void UbMultiNodeContainer::setRingWidth( qreal ringWidth )
	{
		m_RingWidth = ringWidth;
	}

	void UbMultiNodeContainer::addNodes()
	{
		m_Offset = 8;
		m_NumNodes = m_Handle.getSize();
		float length = 8*( m_NumNodes + 3 );
		for ( int i=0; i<m_Handle.getSize(); ++i )
		{
			UbInletNodeRef node( new UbInletNode(this, m_Handle[i]));
			m_TargetPositions.push_back(QPoint(0,-i*length/m_NumNodes-10));
			node->setColor(QColor(130,130,130));
			m_Nodes.push_back(node);
		}
	}

	Uber::UbNodeRef UbMultiNodeContainer::getNodeUnderMouse()
	{
		QVector<UbNodeRef>::iterator iter = m_Nodes.begin();
		for (; iter!=m_Nodes.end();++iter)
		{
			if ((*iter)->isUnderMouse() )
			{
				return *iter;

			}
		}
		return UbNodeRef();
	}

	QVector<UbNodeRef> UbMultiNodeContainer::getNodes()
	{
		return m_Nodes;
	}

}