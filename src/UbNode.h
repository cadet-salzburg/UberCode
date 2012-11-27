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
#include <QString>
#include <QSharedPointer>
#include <QWeakPointer>
#include "UbObject.h"
#include "UbTypes.h"

class UbLink;
namespace Uber {
	typedef QSharedPointer<class UbNode>	UbNodeRef;
	typedef QWeakPointer<class UbNode>		UbNodeWeakRef;
	class UbNode :public UbObject
	{
	public:
		UbNode( QGraphicsItem *parent = 0 );
		enum { Type = NodeType  };

		virtual int				type() const { return Type; }

		void					constructPath();

		void					setName( QString name );
		const QString&			getName() const;
		virtual bool			link( UbNode* node );

		void					unlink( UbNode* node );

		virtual UbObject*		getParentBlock();
	protected:
		virtual void			hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
		virtual void			hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
		virtual void			mousePressEvent ( QGraphicsSceneMouseEvent * e );
	private:
		QString					m_NodeName;
	};
}