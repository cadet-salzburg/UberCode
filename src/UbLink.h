#pragma once
#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include "UbNode.h"

namespace Uber {
	class UbLink : public QGraphicsPathItem
	{
	public:
		UbLink(QGraphicsItem *parent = 0,  QGraphicsScene *scene = 0);
		virtual	~UbLink();

		void			updatePath();
		void			paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

		void			setStartNode( UbNode* start );
		UbNode*			getStartNode() const;

		void			setEndNode( UbNode* end );
		UbNode*			getEndNode() const;

		void			setStartPos( QPointF start );
		void			setEndPos( QPointF end );
		void			setDragPos( QPointF pos);

		void			setNodes( UbNode* start, UbNode* end );

		void			startedChanging();
		void			finishedChanging();
		bool			isChanging() const;
	protected:
		void			mousePressEvent ( QGraphicsSceneMouseEvent * event );
	private:
		bool			isHardLink();
		bool			m_IsSet;
		bool			m_IsChanging;
		UbNode*			m_StartNode;
		UbNode*			m_EndNode;
		QPointF			m_StartPos;
		QPointF			m_EndPos;
	};
}