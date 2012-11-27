/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH
		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include "UbMultiNodeContainer.h"
#include <QPen>
#include <QPainter>
#include "UbBundleBlock.h"
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Uber {
	UbMultiNodeContainer::UbMultiNodeContainer( QGraphicsItem *parent )
	{
		m_Zvalue = zValue();
		addNodes();
		setOpacity(0);
	}
	UbMultiNodeContainer::UbMultiNodeContainer(QGraphicsItem *parent, const  _2Real::app::InletHandle& handle)
		:QGraphicsObject(parent)
	{
		m_Handle = handle;
		m_Zvalue = zValue();
		addNodes();
		setOpacity(0);
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
		//Get parent

		QGraphicsObject* objA = parentObject();
		QGraphicsObject* objB = objA->parentObject();
		UbBundleBlock *parentBlock;
		if ( objB )
		{
			parentBlock = static_cast<UbBundleBlock*>(objB);
		}

		for ( int i=0; i<m_Handle.getSize(); ++i )
		{
			UbInletNodeRef node( new UbInletNode(this, m_Handle[i]));
			m_TargetPositions.push_back(QPoint(0,-i*length/m_NumNodes-10));
			node->setColor(QColor(130,130,130));
			m_Nodes.push_back(node);
			if ( parentBlock )
			{
				parentBlock->m_Inlets.push_back(node);
			}
			
			//node->setOpacity(0);
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