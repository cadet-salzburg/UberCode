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
		virtual void					blockIsConnected();
		virtual bool					isConnected();
		UbNodeRef						getNode() const;
	protected:
		virtual void					arrangeNodes() = 0;
		QGraphicsProxyWidget*			m_ProxyWidget;
		UbNodeWeakRef					m_Node;
		bool							m_BlockIsConnected;
	};
}