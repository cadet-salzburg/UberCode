#pragma once
#include <QGraphicsPathItem>
#include <QString>
#include "UbObject.h"
#include "UbTypes.h"

class UbLink;
namespace Uber {
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