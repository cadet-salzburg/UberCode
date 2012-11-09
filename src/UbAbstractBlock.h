#pragma once
#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QRectF>
#include <QPoint>
#include <QColor>
#include "UbTypes.h"

namespace Uber {
	class UbAbstractBlock :public QGraphicsObject
	{	
	public:
		enum { Type = AbstractBlockType };

		UbAbstractBlock( QGraphicsItem *parent );
		virtual ~UbAbstractBlock( void );

		virtual int						type() const { return Type; }
		virtual void					paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		QRectF							boundingRect() const;

	protected:
		QColor							m_Color;
		virtual void					configureNodes() = 0;
		virtual void					constructPath();
		virtual void					mousePressEvent ( QGraphicsSceneMouseEvent * e )
		{
			//TODO: QT dragging seems to have glitches. Not sure if its a QT bug or not.
			m_CurrentPoint = m_PreviousPoint =  e->scenePos();  
		}

		virtual void					mouseMoveEvent ( QGraphicsSceneMouseEvent * e )
		{
			m_CurrentPoint = e->scenePos();
			QPointF diff = m_CurrentPoint - m_PreviousPoint;
			setPos(pos() + diff );
			m_PreviousPoint = m_CurrentPoint;
		}
		qreal							m_Width;
		qreal							m_Height;
		int								m_CornerRadius;
		float							m_fDefaultFps;
	//private:
		QPainterPath					m_Path;
		QRectF							m_Rectangle;

		QPointF							m_CurrentPoint;
		QPointF							m_PreviousPoint;
	};
}