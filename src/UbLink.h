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
#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include <QSharedPointer>
#include <QWeakPointer>
#include "UbNode.h"
#include "UbTypes.h"

namespace Uber {

	class UbLink : public QGraphicsPathItem
	{
	public:
		UbLink(QGraphicsItem *parent = 0,  QGraphicsScene *scene = 0);
		virtual	~UbLink();

		void				updatePath();
		void				paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

		void				setStartNode( UbNodeRef start );
		UbNodeRef			getStartNode() const;

		void				setEndNode( UbNodeRef end );
		UbNodeRef			getEndNode() const;

		void				setNodes( UbNodeRef start, UbNodeRef end );
		bool				nodesAreSet();
		bool				isHardLink();
	protected:
		UbNodeRef			m_StartNode;
		UbNodeRef			m_EndNode;

	};
	typedef QSharedPointer<UbLink>	UbLinkRef;
	typedef QWeakPointer<UbLink>		UbLinkWeakRef;	
}