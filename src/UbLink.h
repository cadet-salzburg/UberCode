#pragma once
#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include <QSharedPointer>
#include <QWeakPointer>
#include "UbNode.h"
#include "UbTypes.h"

namespace Uber {
	typedef QSharedPointer<class UbLink>	UbLinkRef;
	typedef QWeakPointer<class UbLink>		UbLinkWeakRef;	
	class UbLink : public QGraphicsPathItem
	{
	public:
		UbLink(QGraphicsItem *parent = 0,  QGraphicsScene *scene = 0);
		virtual	~UbLink();

		void				updatePath();
		void				paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

		void				setStartNode( UbNodeRef start );
		UbNodeRef			getStartNode() const;

		void				setEndNode( UbNodeRef end );
		UbNodeRef			getEndNode() const;

		void				setNodes( UbNodeRef start, UbNodeRef end );
		bool				nodesAreSet();
		bool				isHardLink();
	protected:
		UbNodeRef			m_StartNode;
		UbNodeRef			m_EndNode;

	};
}