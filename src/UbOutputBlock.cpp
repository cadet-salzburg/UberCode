/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH
		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include "UbOutputBlock.h"
#include "UbOutletNode.h"
namespace Uber {
	UbOutputBlock::UbOutputBlock( QGraphicsItem* parent )
		:UbInterfaceBlock( parent )
	{
		qRegisterMetaType< _2Real::app::AppData >( "_2Real::app::AppData" );
		connect( this, SIGNAL( sendData( const _2Real::app::AppData& ) ), this, SLOT( updateData( const _2Real::app::AppData& ) ) );
		UbOutletNodeRef node( new UbOutletNode(this) );
		m_Outlets.push_back(node);
		m_Node = node.toWeakRef(); 
	}
	UbOutputBlock::~UbOutputBlock(void)
	{

	}
	void UbOutputBlock::receiveData( _2Real::app::AppData const& data )
	{
		emit sendData(data);
	}
	void UbOutputBlock::updateData( _2Real::app::AppData const& data )
	{
		m_Data = data;
	}
}