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
#include "UbInletNode.h"

namespace Uber {
	UbInletNode::UbInletNode( QGraphicsItem *parent )
		:UbNode(parent)
	{

	}
	UbInletNode::UbInletNode( QGraphicsItem *parent,const _2Real::app::InletHandle& handle )
		:UbNode(parent)
		,m_Handle(handle)

	{
		setName( QString::fromStdString( m_Handle.getName() ) );
	}

	UbInletNode::~UbInletNode(void)
	{

	}
	void UbInletNode::setHandle( const  _2Real::app::InletHandle& handle )
	{ 
		m_Handle = handle;
		setName( QString::fromStdString( m_Handle.getName() ) );
	}

	_2Real::app::InletHandle& UbInletNode::getHandle()
	{ 
		return m_Handle; 
	}
}