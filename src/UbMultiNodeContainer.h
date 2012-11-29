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
#include <QGraphicsObject>
#include <QVector>
#include <QPropertyAnimation>
#include "UbInletNode.h"
#include "_2RealApplication.h"
namespace Uber {
	class UbMultiNodeContainer : public QGraphicsObject
	{
		Q_OBJECT
		Q_PROPERTY(qreal percent READ getPercent WRITE setPercent)
	public:
		UbMultiNodeContainer( QGraphicsItem *parent );
		UbMultiNodeContainer( QGraphicsItem *parent, const  _2Real::app::InletHandle& handle);
		virtual ~UbMultiNodeContainer(void);

		enum { Type = MultiInputNodeContainer  };

		virtual int							type() const { return Type; }

		virtual void						paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
		virtual QRectF						boundingRect() const;
		qreal								getPercent();
		void								setPercent( qreal percent);
		//void								setNumNodes( int numNodes );
		void								setRingWidth( qreal ringWidth );
		void								addNodes();
		UbNodeRef							getNodeUnderMouse();
		QVector<UbNodeWeakRef>				getNodes();				
	protected:
		QColor								m_Color;
		QPainterPath						m_ExpandedPath;
		QPropertyAnimation*					m_PropertyAnimation;
	private:
		qreal								m_Zvalue;
		qreal								m_Offset;
		qreal								m_Percent;
		int									m_NumNodes;
		qreal								m_RingWidth;
		qreal								m_RingRadius;
		_2Real::app::InletHandle			m_Handle;
		QVector<UbNodeWeakRef>				m_Nodes;
		QVector<QPointF>					m_TargetPositions;
	public slots:
		virtual void						createPath();
	};
}

