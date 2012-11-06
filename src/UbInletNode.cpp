#include "UbInletNode.h"

namespace Uber {

	UbInletNode::UbInletNode( QGraphicsItem *parent,const _2Real::app::InletHandle& handle )
		:UbNode(parent)
		,m_Handle(handle)

	{
		m_NodeName = QString::fromStdString( m_Handle.getName() );
	}

	UbInletNode::~UbInletNode(void)
	{

	}
}