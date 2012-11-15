#pragma once
#include <QGraphicsPathItem>
#include <QString>
#include <QSharedPointer>
#include <QWeakPointer>
#include "UbObject.h"
#include "UbTypes.h"

class UbLink;
namespace Uber {
	typedef QSharedPointer<class UbNode>	UbNodeRef;
	typedef QWeakPointer<class UbNode>		UbNodeWeakRef;
	class UbNode :public UbObject
	{
	public:
		UbNode( QGraphicsItem *parent = 0 );
		enum { Type = NodeType  };

		virtual int				type() const { return Type; }

		void					constructPath();

		void					setName( QString name );
		const QString&			getName() const;				
		virtual bool			link( UbNode *node );
	protected:

		void					hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
		void					hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
	private:
		QString					m_NodeName;
	};
}