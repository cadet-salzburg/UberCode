#pragma once
#include <QGraphicsPathItem>
#include <QGraphicsObject>

#include "DataflowEngineManager.h"

class UbLink;
class UbNode :public QGraphicsObject
{
public:
	enum { Type = QGraphicsItem::UserType + UberCodeItemType::NodeType  };
	UbNode( QGraphicsItem *parent = 0 );
	void				constructPath();
	void				paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void				setRadius( qreal radius );
	const qreal&		getRadius();
	void				setName(QString name );

	virtual bool		isInlet()
	{
		return false;
	};

	QRectF				boundingRect() const;
	virtual int type() const { return Type; }

	void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
	void hoverMoveEvent ( QGraphicsSceneHoverEvent * event );

	QString				m_NodeName;

private:
	qreal				m_Radius;
	QPainterPath		m_Path;
	UbLink*				link;
};