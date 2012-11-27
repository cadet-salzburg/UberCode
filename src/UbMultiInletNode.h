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
#include <QPropertyAnimation>
#include "UbMultiNodeContainer.h"
#include "_2RealApplication.h"

namespace Uber {
	typedef QSharedPointer<class UbMultiInletNode>	UbMultiInletNodeRef;
	typedef QWeakPointer<class UbMultiInletNode>	UbMultiInletNodeWeakRef;
	class UbMultiInletNode :public UbNode
	{
	public:
		UbMultiInletNode( QGraphicsItem *parent );
		UbMultiInletNode( QGraphicsItem *parent,const  _2Real::app::InletHandle& handle );
		virtual ~UbMultiInletNode(void);

		enum { Type = MultiInputNodeType  };

		virtual int							type() const { return Type; }

		void								setHandle( const  _2Real::app::InletHandle& handle );
		_2Real::app::InletHandle&			getHandle();
		virtual QRectF						boundingRect() const;

		void								expand();
		void								close();
		UbNodeRef							getNodeUnderMouse();
		//virtual void						paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
	protected:
		virtual void						hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
		virtual void						hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
		virtual void						hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
	private:
		UbMultiNodeContainer				*m_Container;
		_2Real::app::InletHandle			m_Handle;
		QPropertyAnimation					*m_Animation;


	};
}