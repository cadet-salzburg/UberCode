#pragma once

#include "DataflowEngineManager.h"

#include <QGraphicsObject>
#include <QPainter>
#include <QRectF>


class UbAbstractBlock :public QGraphicsObject
{
	enum { Type = Uber::AbstractBlockType };

public:
	UbAbstractBlock( QGraphicsItem *parent );
	virtual ~UbAbstractBlock( void );
	virtual int		type() const = 0;
	virtual void	paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF			boundingRect() const;

protected:
	//QVariant						itemChange(GraphicsItemChange change, const QVariant &value);
	virtual void					addNodes() = 0;
	virtual void					constructPath();
	qreal							m_Width;
	qreal							m_Height;
	int								m_CornerRadius;
	float							m_fDefaultFps;
	virtual void mousePressEvent ( QGraphicsSceneMouseEvent * e )
	{
		QGraphicsObject::mousePressEvent(e);
	};

private:
	QPainterPath					m_Path;
	QRectF							m_Rectangle;
};