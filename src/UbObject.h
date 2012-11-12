#pragma once
#include <QGraphicsObject>
#include <QColor>
#include <QPainter>
#include <QRect>
#include "UbTypes.h"

class UbObject : public QGraphicsObject 
{
public:
	UbObject( QGraphicsItem *parent );
	virtual ~UbObject(void);
	enum { Type = ObjectType };

	virtual int						type() const { return Type; }
	virtual void					paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF							boundingRect() const;

protected:

	virtual void					constructPath() = 0;
	QColor							m_Color;
	qreal							m_Width;
	qreal							m_Height;
	QPainterPath					m_Path;
};

