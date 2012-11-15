#include "UbOutputBlock.h"
#include "UbOutletNode.h"
namespace Uber {
	UbOutputBlock::UbOutputBlock( QGraphicsItem* parent )
		:UbInterfaceBlock( parent )
	{
		qRegisterMetaType< _2Real::app::AppData >( "_2Real::app::AppData" );
		connect( this, SIGNAL( sendData( _2Real::app::AppData ) ), this, SLOT( updateData( _2Real::app::AppData ) ) );
		UbOutletNodeRef node( new UbOutletNode(this) );
		m_Outlets.push_back(node);
		m_Node = node.toWeakRef(); 
	}
	UbOutputBlock::~UbOutputBlock(void)
	{

	}
	void UbOutputBlock::receiveData( _2Real::app::AppData const& data )
	{
		m_Data = data;
		emit sendData(data);
	}
	void UbOutputBlock::updateData(_2Real::app::AppData data)
	{
		m_Data = data;
	}

}