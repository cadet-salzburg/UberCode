#pragma once
#include "UbInterfaceBlock.h"
namespace Uber {
	class UbInputBlock : public UbInterfaceBlock
	{
	public:
		UbInputBlock( QGraphicsItem *parent );
		virtual ~UbInputBlock(void);
		enum { Type = InputBlockType };

		virtual	int				type() const { return Type; }
	};
}