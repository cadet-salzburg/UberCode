#include "UbInputBlock.h"
#include "UbInletNode.h"
namespace Uber {
	UbInputBlock::UbInputBlock( QGraphicsItem *parent )
		:UbInterfaceBlock(parent)
	{
		m_Node = new UbInletNode(this);
	}

	UbInputBlock::~UbInputBlock(void)
	{

	}
}