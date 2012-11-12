#include "UbInterfaceBlock.h"
namespace Uber {
	UbInterfaceBlock::UbInterfaceBlock( QGraphicsItem *parent )
		:UbAbstractBlock( parent ),
		m_ProxyWidget( new QGraphicsProxyWidget )
	{

	}
	UbInterfaceBlock::~UbInterfaceBlock(void)
	{

	}
}

