#include "UbOutletNode.h"

namespace Uber {
	UbOutletNode::UbOutletNode( QGraphicsItem *parent )
		:UbNode(parent)
	{

	}
	UbOutletNode::UbOutletNode( QGraphicsItem *parent, const _2Real::app::OutletHandle& handle )
		:UbNode(parent)
		,m_Handle(handle)

	{
		setName( QString::fromStdString( m_Handle.getName() ) );
	}
	UbOutletNode::~UbOutletNode(void)
	{

	}
	_2Real::app::OutletHandle& UbOutletNode::getHandle()
	{
		return m_Handle;
	}
	void UbOutletNode::setHandle( const _2Real::app::OutletHandle& handle )
	{
		m_Handle = handle;
		setName( QString::fromStdString( m_Handle.getName() ) );
	}
}