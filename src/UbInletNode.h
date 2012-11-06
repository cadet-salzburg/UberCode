#pragma once
#include "UbNode.h"
#include "UbTypes.h"
#include "_2RealApplication.h"

namespace Uber {
	class UbInletNode :public UbNode
	{
	public:
		UbInletNode( QGraphicsItem *parent,const  _2Real::app::InletHandle& handle );
		virtual ~UbInletNode(void);

		enum { Type = InputNodeType  };

		virtual int							type() const { return Type; }
		virtual bool						isInlet(){ return true; }
		const _2Real::app::InletHandle&		getHandle(){ return m_Handle; }

	private:
		_2Real::app::InletHandle			m_Handle;
	};
}