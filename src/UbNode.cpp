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
	UbNode::UbNode( QGraphicsItem *parent ) :UbObject( parent ),
		m_NodeName("")
	{
		m_Height = 8;
		m_Width = 8;
		m_Color = QColor(153,135,141);
		constructPath();
		setAcceptHoverEvents( true ); 
		installEventFilter(UbLinkController::getInstance());
	}

	void UbNode::constructPath()
	{
		//QPath path;
		m_Path = QPainterPath();
		m_Path.addEllipse( -m_Width/2, -m_Height/2, m_Width, m_Height );
	}

	void UbNode::setName( QString name )
	{
		m_NodeName = name;
		setToolTip( m_NodeName );
	}

	const QString&	UbNode::getName() const 
	{ 
		return m_NodeName;
	}

	bool UbNode::link( UbNode* node )
	{
		//We can only link inlet to outlets
		bool res = false;
		if ( ( type() == InputNodeType ) && ( node->type() == OutputNodeType ) )
		{
			//qSharedPointerCast<UbOutletNode>(this)
			res = static_cast<UbInletNode*>(this)->getHandle().link( static_cast<UbOutletNode*>(node)->getHandle() );

		} else if ( ( type() == OutputNodeType ) && ( node->type() == InputNodeType ) )
		{
			res = static_cast<UbOutletNode*>(this)->getHandle().link( static_cast<UbInletNode*>(node)->getHandle() );
		}
		return res;
	}

	void UbNode::hoverMoveEvent ( QGraphicsSceneHoverEvent * event )
	{
		//std::cout << " Hover is happening" << std::endl;
		QPointF pos = event->lastScreenPos();
		QToolTip::showText( QPoint(pos.x(),pos.y()), QString(m_NodeName) );

	}
	void UbNode::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
	{
		//std::cout << " Hover stopped happening" << std::endl;
	}

	UbObject* UbNode::getParentBlock()
	{
		QGraphicsObject* parent = parentObject();
		if ( parent )
		{
			if ( parent->type()!=MultiInputNodeContainer )
			{
				return static_cast<UbObject*>(parent);
			} 
			else
			{
				QGraphicsObject* wantedParent = parent->parentObject();
				QGraphicsObject* grandFather = wantedParent->parentObject();
				return static_cast<UbObject*>(grandFather);
			}
		}
		return NULL;
	}
}