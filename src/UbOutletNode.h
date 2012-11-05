#pragma once
#include "ubnode.h"
#include "DataflowEngineManager.h"

class UbOutletNode :
	public UbNode
{
public:
	enum { Type = Uber::OutputNodeType  };
	UbOutletNode(  QGraphicsItem *parent,const _2Real::app::OutletHandle& handle );
	virtual ~UbOutletNode(void);
	virtual int type() const { return Type; }
	virtual bool isInlet(){ return false; }
	const _2Real::app::OutletHandle& getHandle()
	{
		return m_Handle;
	}

private:
	_2Real::app::OutletHandle		m_Handle;
};