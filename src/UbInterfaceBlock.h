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
		void							setName( const QString& name );
		const QString&					getName() const;

	protected:
		virtual void					arrangeNodes() = 0;
		QGraphicsProxyWidget*			m_ProxyWidget;
		QString							m_Name;
		UbNodeWeakRef					m_Node;
	};
}