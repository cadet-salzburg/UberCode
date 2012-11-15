#pragma once
#include "UbNode.h"
#include "UbTypes.h"
#include <QSharedPointer>
#include <QWeakPointer>
#include "_2RealApplication.h"


namespace Uber {
	typedef QSharedPointer<class UbOutletNode>	UbOutletNodeRef;
	typedef QWeakPointer<class UbOutletNode>	UbOutletNodeWeakRef;
	class UbOutletNode :public UbNode
	{
	public:
		UbOutletNode(  QGraphicsItem *parent );
		UbOutletNode(  QGraphicsItem *parent,const _2Real::app::OutletHandle& handle );
		virtual ~UbOutletNode(void);
		enum { Type = OutputNodeType  };

		virtual int							type() const { return Type; }

		_2Real::app::OutletHandle&			getHandle();
		void								setHandle( const _2Real::app::OutletHandle& handle );
	private:
		_2Real::app::OutletHandle			m_Handle;
	};
}