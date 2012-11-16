#pragma once
#include "UbNode.h"
#include "UbTypes.h"
#include <QSharedPointer>
#include <QWeakPointer>
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

		enum { Type = InputNodeType  };

		virtual int							type() const { return Type; }

		void								setHandle( const  _2Real::app::InletHandle& handle );
		_2Real::app::InletHandle&			getHandle();

	private:
		_2Real::app::InletHandle			m_Handle;
	};
}