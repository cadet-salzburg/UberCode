#include "UbInterfaceBlock.h"
namespace Uber {
	UbInterfaceBlock::UbInterfaceBlock( QGraphicsItem *parent )
		:UbAbstractBlock( parent ),
		m_ProxyWidget( new QGraphicsProxyWidget(this) ),
		m_Node(UbNodeRef() ),
		m_Name( QString(""))
	{

	}
	UbInterfaceBlock::~UbInterfaceBlock(void)
	{

	}

	void UbInterfaceBlock::setName( const QString& name )
	{
		m_Name = name;
	}

	const QString& UbInterfaceBlock::getName() const
	{
		return m_Name;
	}

}

