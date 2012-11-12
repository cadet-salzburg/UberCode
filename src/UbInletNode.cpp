#include "UbInletNode.h"

namespace Uber {
	UbInletNode::UbInletNode( QGraphicsItem *parent )
		:UbNode(parent)
	{

	}
	UbInletNode::UbInletNode( QGraphicsItem *parent,const _2Real::app::InletHandle& handle )
		:UbNode(parent)
		,m_Handle(handle)

	{
		setName( QString::fromStdString( m_Handle.getName() ) );
	}

	UbInletNode::~UbInletNode(void)
	{

	}
	void UbInletNode::setHandle( const  _2Real::app::InletHandle& handle )
	{ 
		m_Handle = handle;
		setName( QString::fromStdString( m_Handle.getName() ) );
	}

	_2Real::app::InletHandle& UbInletNode::getHandle()
	{ 
		return m_Handle; 
	}
}