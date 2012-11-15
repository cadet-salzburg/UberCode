#include "UbInputBlock.h"
#include "UbInletNode.h"
namespace Uber {
	UbInputBlock::UbInputBlock( QGraphicsItem *parent )
		:UbInterfaceBlock(parent)
	{
		UbInletNodeRef node( new UbInletNode(this) );
		m_Inlets.push_back( node );
		m_Node = node.toWeakRef();
	}

	UbInputBlock::~UbInputBlock(void)
	{

	}
}