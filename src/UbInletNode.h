#pragma once
#include "UbNode.h"
#include "UbTypes.h"
#include <QSharedPointer>
#include <QWeakPointer>
#include "_2RealApplication.h"

namespace Uber {
	typedef QSharedPointer<class UbInletNode>	UbInletNodeRef;
	typedef QWeakPointer<class UbInletNode>		UbInletNodeWeakRef;
	class UbInletNode :public UbNode
	{
	public:
		UbInletNode( QGraphicsItem *parent );
		UbInletNode( QGraphicsItem *parent,const  _2Real::app::InletHandle& handle );
		virtual ~UbInletNode(void);

		enum { Type = InputNodeType  };
		
		virtual int							type() const { return Type; }

		void								setHandle( const  _2Real::app::InletHandle& handle );
		_2Real::app::InletHandle&			getHandle();

	private:
		_2Real::app::InletHandle			m_Handle;
	};
}