#pragma once
#include <QGraphicsObject>
#include <QPainter>
#include <QRectF>
#include "UbTypes.h"

namespace Uber {
	class UbAbstractBlock :public QGraphicsObject
	{	
	public:
		enum { Type = AbstractBlockType };

		UbAbstractBlock( QGraphicsItem *parent );
		virtual ~UbAbstractBlock( void );

		virtual int						type() const = 0;
		virtual void					paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		QRectF							boundingRect() const;
	protected:
		virtual void					addNodes() = 0;
		virtual void					constructPath();
		virtual void					mousePressEvent ( QGraphicsSceneMouseEvent * e )
		{
			QGraphicsObject::mousePressEvent(e);
		};
		qreal							m_Width;
		qreal							m_Height;
		int								m_CornerRadius;
		float							m_fDefaultFps;
	private:
		QPainterPath					m_Path;
		QRectF							m_Rectangle;
	};
}