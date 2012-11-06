#pragma once
#include <QGraphicsPathItem>
#include <QGraphicsObject>

#include "UbTypes.h"

class UbLink;

namespace Uber {
	class UbNode :public QGraphicsObject
	{
	public:
		UbNode( QGraphicsItem *parent = 0 );

		enum { Type = NodeType  };

		virtual int			type() const { return Type; }
		QRectF				boundingRect() const;
		void				constructPath();
		void				paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

		void				setRadius( qreal radius );
		const qreal&		getRadius() const;

		void				setName(QString name );
		const QString&		getName() const { return m_NodeName; }				

		virtual bool		isInlet(){ return false; }

		void				hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
		void				hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
		
		QString				m_NodeName;
	private:
		qreal				m_Radius;
		QPainterPath		m_Path;
		UbLink*				link;
	};
}