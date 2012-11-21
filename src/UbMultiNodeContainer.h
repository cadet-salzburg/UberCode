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
		QVector<UbNodeRef>					getNodes();				
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
		QVector<UbNodeRef>					m_Nodes;
		QVector<QPointF>					m_TargetPositions;
	public slots:
		virtual void						createPath();
	};
}

