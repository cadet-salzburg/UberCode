#pragma once
#include <QGraphicsObject>
#include <QGraphicsProxyWidget>
#include "UbAbstractBlock.h"
#include "UbNode.h"
#include "UbTypes.h"

namespace Uber {
	class UbInterfaceBlock : public  UbAbstractBlock
	{
	public:
		UbInterfaceBlock( QGraphicsItem *parent );
		virtual ~UbInterfaceBlock(void);
		enum { Type = InterfaceBlockType };

		virtual int						type() const { return Type; }
		virtual void					blockIsConnected() = 0;
	protected:
		virtual void					arrangeNodes() = 0;
		UbNode*							m_Node;
		QGraphicsProxyWidget*			m_ProxyWidget;
	};
}