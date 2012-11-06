#include "UbOutletNode.h"

namespace Uber {
	UbOutletNode::UbOutletNode( QGraphicsItem *parent, const _2Real::app::OutletHandle& handle )
		:UbNode(parent)
		,m_Handle(handle)

	{
		m_NodeName = QString::fromStdString( m_Handle.getName() );
	}
	UbOutletNode::~UbOutletNode(void)
	{

	}
}