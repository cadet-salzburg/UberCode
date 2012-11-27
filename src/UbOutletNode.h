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
#pragma once
#include "UbNode.h"
#include "UbTypes.h"
#include <QSharedPointer>
#include <QWeakPointer>
#include "_2RealApplication.h"


namespace Uber {
	typedef QSharedPointer<class UbOutletNode>	UbOutletNodeRef;
	typedef QWeakPointer<class UbOutletNode>	UbOutletNodeWeakRef;
	class UbOutletNode :public UbNode
	{
	public:
		UbOutletNode(  QGraphicsItem *parent );
		UbOutletNode(  QGraphicsItem *parent,const _2Real::app::OutletHandle& handle );
		virtual ~UbOutletNode(void);
		enum { Type = OutputNodeType  };

		virtual int							type() const { return Type; }

		_2Real::app::OutletHandle&			getHandle();
		void								setHandle( const _2Real::app::OutletHandle& handle );
	private:
		_2Real::app::OutletHandle			m_Handle;
	};
}