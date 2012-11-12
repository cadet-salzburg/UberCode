#pragma once
#include "UbNode.h"
#include "UbTypes.h"
#include "_2RealApplication.h"

namespace Uber {
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