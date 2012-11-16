#include "UbMultiInletNode.h"
namespace Uber {
	UbMultiInletNode::UbMultiInletNode( QGraphicsItem *parent )
		:UbNode(parent)
	{
		m_Color = QColor( 255,0,0);
	}
	UbMultiInletNode::UbMultiInletNode( QGraphicsItem *parent,const _2Real::app::InletHandle& handle )
		:UbNode(parent)
		,m_Handle(handle)
	{
		setName( QString::fromStdString( m_Handle.getName() ) );
	}

	UbMultiInletNode::~UbMultiInletNode(void)
	{

	}
	void UbMultiInletNode::setHandle( const  _2Real::app::InletHandle& handle )
	{ 
		m_Handle = handle;
		setName( QString::fromStdString( m_Handle.getName() ) );
	}

	_2Real::app::InletHandle& UbMultiInletNode::getHandle()
	{ 
		return m_Handle; 
	}
}
