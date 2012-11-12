#pragma once
#include <QGraphicsObject>
#include <QGraphicsProxyWidget>
#include "UbAbstractBlock.h"
#include "UbNode.h"
#include "UbTypes.h"

namespace Uber {
	class UbInterfaceBlock : public  UbAbstractBlock
	{
		UbInterfaceBlock( QGraphicsItem *parent );
		virtual ~UbInterfaceBlock(void);

		enum { Type = InterfaceBlockType };

		virtual int						type() const { return Type; }
	protected:
		void							configureNodes(){};
		UbNode*							m_Node;
		QGraphicsProxyWidget*			m_ProxyWidget;
	};
}