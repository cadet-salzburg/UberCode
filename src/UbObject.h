#pragma once
#include <QGraphicsObject>
#include <QColor>
#include <QPainter>
#include <QRect>
#include "UbTypes.h"

namespace Uber {
	class UbObject : public QGraphicsObject 
	{
	public:
		UbObject( QGraphicsItem *parent );
		virtual ~UbObject( void );
		enum { Type = ObjectType };

		virtual int						type() const { return Type; }
		virtual void					paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
		virtual QRectF					boundingRect() const;
		const qreal&					getWidth() const { return m_Width; }
		const qreal&					getHeight() const { return m_Height; }
	protected:

		virtual void					constructPath() = 0;
		QColor							m_Color;
		qreal							m_Width;
		qreal							m_Height;
		QPainterPath					m_Path;
	};
}