#pragma once
#include "ubnode.h"
#include "DataflowEngineManager.h"

class UbInletNode :public UbNode
{
public:
	enum { Type = QGraphicsItem::UserType + UberCodeItemType::InputNodeType  };
	UbInletNode( QGraphicsItem *parent,const  _2Real::app::InletHandle& handle );
	virtual ~UbInletNode(void);
	virtual int type() const { return Type; }
	virtual bool isInlet(){ return true; }
	const _2Real::app::InletHandle& getHandle()
	{
		return m_Handle;
	}

private:
	_2Real::app::InletHandle		m_Handle;
};