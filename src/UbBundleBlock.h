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
#include "UbAbstractBlock.h"
#include "_2RealApplication.h"
#include "UbNode.h"
#include <QVector>
#include <QGraphicsSceneMouseEvent>

namespace Uber {
	class UbBundleBlock : public UbAbstractBlock
	{
	public:
		UbBundleBlock( QGraphicsItem *parent,  _2Real::app::BundleHandle handle, QString blockName );
		UbBundleBlock( QGraphicsItem *parent, QString blockInstanceId );
		virtual ~UbBundleBlock(void);

		enum { Type = BundleBlockType };

		virtual int					type() const { return Type; }
		_2Real::app::BlockHandle	getHandle(){ return m_BlockHandle;}
		QString						getBlockId(){ return m_BlockId; }
		QVector<UbNodeRef> const&	getInlets() const;
		QVector<UbNodeRef> const&	getOutlets() const;
	protected:
		virtual void				hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
	private:
		void						arrangeNodes();
		_2Real::app::BlockHandle	m_BlockHandle;
		QString						m_BlockId;
	};
}