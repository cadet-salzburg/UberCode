#include "UbInterfaceBlock.h"
namespace Uber {
	UbInterfaceBlock::UbInterfaceBlock( QGraphicsItem *parent )
		:UbAbstractBlock( parent ),
		m_ProxyWidget( new QGraphicsProxyWidget(this) ),
		m_Node(0)
	{

	}
	UbInterfaceBlock::~UbInterfaceBlock(void)
	{

	}
}

