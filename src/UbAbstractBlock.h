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
#pragma once
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include "UbObject.h"
#include "UbTypes.h"
#include "UbNode.h"
#include <QPropertyAnimation>

namespace Uber {
	class UbAbstractBlock :public UbObject
	{
	public:

		enum { Type = AbstractBlockType };

		UbAbstractBlock( QGraphicsItem *parent );
		virtual ~UbAbstractBlock( void );

		virtual int						type() const { return Type; }
		UbNodeRef						getNodeUnderMouse();
		/*UbNodeRef						getNodeAtPosition(QPointF p);*/

		QVector<UbNodeRef>				m_Inlets;
		QVector<UbNodeRef>				m_Outlets;
	protected:
		
		virtual void					constructPath();
		virtual void					arrangeNodes() = 0;
		virtual void					mousePressEvent ( QGraphicsSceneMouseEvent * e );
		virtual void					mouseMoveEvent ( QGraphicsSceneMouseEvent * e )
		{
			m_CurrentPoint = e->scenePos();
			QPointF diff = m_CurrentPoint - m_PreviousPoint;
			setPos(pos() + diff );
			m_PreviousPoint = m_CurrentPoint;
		}

		int								m_CornerRadius;
	private:
		QPointF							m_CurrentPoint;
		QPointF							m_PreviousPoint;
		QPropertyAnimation*				m_PropertyAnimation;
	};
}