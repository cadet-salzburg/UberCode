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
#include "UbAbstractBlock.h"
#include <iostream>
namespace Uber {
	UbAbstractBlock::UbAbstractBlock( QGraphicsItem *parent )
		:UbObject( parent )
		,m_CornerRadius(8)
	{
		m_Width = 160;//110;
		m_Height = 80;//40;
		constructPath();
		m_PropertyAnimation = new QPropertyAnimation(this, "opacity");
		m_PropertyAnimation->setDuration(1000);
		m_PropertyAnimation->setStartValue(0.5f);
		m_PropertyAnimation->setEndValue(1.0f);
	}

	UbAbstractBlock::~UbAbstractBlock(void)
	{

	}

	void UbAbstractBlock::constructPath()
	{
		QPainterPath path;
		m_Path = path;
		QRectF rect( QPointF(-m_Width/2., -m_Height/2.), QPointF( m_Width/2.,m_Height/2.) );
		m_Path.addRoundedRect( rect, m_CornerRadius, m_CornerRadius );;
		setFlag(QGraphicsItem::ItemIsSelectable);
	}

	Uber::UbNodeRef UbAbstractBlock::getNodeUnderMouse()
	{
		QVector<UbNodeRef>::iterator iter = m_Inlets.begin();
		for (; iter!=m_Inlets.end();++iter)
		{
			//std::cout << "The position of the node is: " << (*iter)->pos().x() << " " << (*iter)->pos().y() << std::endl; 
			if ((*iter)->isUnderMouse() )
			{
				m_PropertyAnimation->start();
				return *iter;
				
			}
		}
		iter = m_Outlets.begin();
		for (; iter!=m_Outlets.end();++iter)
		{
			if ((*iter)->isUnderMouse() )
			{
				m_PropertyAnimation->start();
				return *iter;
			}
		}
		return UbNodeRef();
	}

	void UbAbstractBlock::mousePressEvent( QGraphicsSceneMouseEvent * e )
	{
		//TODO: QT dragging seems to have glitches. Not sure if its a QT bug or not.
		std::cout << "abstract block received a mouse event" << std::endl;
		m_CurrentPoint = m_PreviousPoint =  e->scenePos();  
	}

	//Uber::UbNodeRef UbAbstractBlock::getNodeAtPosition(QPointF p)
	//{
	//	QVector<UbNodeRef>::iterator iter = m_Inlets.begin();
	//	for (; iter!=m_Inlets.end();++iter)
	//	{
	//		if ((*iter)->rect )
	//		{
	//			m_PropertyAnimation->start();
	//			return *iter;

	//		}
	//	}
	//	iter = m_Outlets.begin();
	//	for (; iter!=m_Outlets.end();++iter)
	//	{
	//		if ((*iter)->isUnderMouse() )
	//		{
	//			m_PropertyAnimation->start();
	//			return *iter;
	//		}
	//	}
	//	return UbNodeRef();
	//}
}