#include "UbOutputBlock.h"
#include "UbOutletNode.h"
namespace Uber {
	UbOutputBlock::UbOutputBlock( QGraphicsItem* parent )
		:UbInterfaceBlock( parent )
	{
		qRegisterMetaType< _2Real::app::AppData >( "_2Real::app::AppData" );
		connect( this, SIGNAL( sendData( _2Real::app::AppData ) ), this, SLOT( updateData( _2Real::app::AppData ) ) );
		m_Node = new UbOutletNode(this);
	}
	UbOutputBlock::~UbOutputBlock(void)
	{

	}
	void UbOutputBlock::receiveData( _2Real::app::AppData const& data )
	{
		emit sendData(data);
	}
	void UbOutputBlock::updateData(_2Real::app::AppData data)
	{
		m_Data = data;
	}

}