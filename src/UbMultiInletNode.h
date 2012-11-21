#pragma once
#include "UbNode.h"
#include "UbTypes.h"
#include <QSharedPointer>
#include <QWeakPointer>
#include <QPropertyAnimation>
#include "UbMultiNodeContainer.h"
#include "_2RealApplication.h"

namespace Uber {
	typedef QSharedPointer<class UbMultiInletNode>	UbMultiInletNodeRef;
	typedef QWeakPointer<class UbMultiInletNode>	UbMultiInletNodeWeakRef;
	class UbMultiInletNode :public UbNode
	{
	public:
		UbMultiInletNode( QGraphicsItem *parent );
		UbMultiInletNode( QGraphicsItem *parent,const  _2Real::app::InletHandle& handle );
		virtual ~UbMultiInletNode(void);

		enum { Type = MultiInputNodeType  };

		virtual int							type() const { return Type; }

		void								setHandle( const  _2Real::app::InletHandle& handle );
		_2Real::app::InletHandle&			getHandle();
		virtual QRectF						boundingRect() const;

		void								expand();
		void								close();
		UbNodeRef							getNodeUnderMouse();
		//virtual void						paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
	protected:
		virtual void						hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
		virtual void						hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
		virtual void						hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
	private:
		UbMultiNodeContainer				*m_Container;
		_2Real::app::InletHandle			m_Handle;
		QPropertyAnimation					*m_Animation;


	};
}