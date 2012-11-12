#include "UbOutputBlock.h"

namespace Uber {
	UbOutputBlock::UbOutputBlock( QGraphicsItem* parent )
		:UbInterfaceBlock( parent ),
		m_ProxyWidget( new QGraphicsProxyWidget(this) );
	{
		qRegisterMetaType< _2Real::app::AppData >( "_2Real::app::AppData" );
		connect( this, SIGNAL( sendData( _2Real::app::AppData ) ), this, SLOT( updateData( _2Real::app::AppData ) ) );
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