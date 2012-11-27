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
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "UbLink.h"
#include "UbNode.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
#include <QVector>

namespace Uber {
	class UbLinkController : public QObject
	{
		Q_OBJECT
	public:
		static	UbLinkController*	getInstance();
		static	void				setScene( QGraphicsScene * scene );
		void						addLink( UbNodeRef start, UbNodeRef end ); 
		void						removeLink( UbLink* const link );
		bool						eventFilter(QObject * obj, QEvent * e );
		void						render();

		QGraphicsItem*				itemAt(const QPointF &pos);
		QVector<UbLinkRef>			getLinksWithStartNode( UbNodeRef startNode );
		QVector<UbLinkRef>			getLinksWithEndNode( UbNodeRef endNode );

		bool						tryConnecting( UbNodeRef start, UbNodeRef end);
	private:
		UbLinkController(void);
		~UbLinkController(void);
		bool						nodesHaveDifferentParents( UbNodeRef nodeA, UbNodeRef nodeB );
		bool						nodesHaveDifferentType( UbNodeRef nodeA, UbNodeRef nodeB );
		UbInletNodeRef				getInletNode( UbNodeRef nodeA, UbNodeRef nodeB );
		UbOutletNodeRef				getOutletNode( UbNodeRef nodeA, UbNodeRef nodeB );
		bool						nodesCanBeConnected( UbNodeRef nodeA, UbNodeRef nodeB );
		bool						isBundleBlockNode( UbNodeRef node );
		bool						bothNodesAreOutlets( UbNodeRef nodeA, UbNodeRef nodeB );
		bool						bothNodesAreInlets( UbNodeRef nodeA, UbNodeRef nodeB );
		bool						canConnectInputNodeToUiBlockOfType( UbInletNodeRef node, int type );
		bool						canConnectOutputNodeToUiBlockOfType( UbOutletNodeRef node, int type );

		bool						processStartLink( QGraphicsSceneMouseEvent * e );
		bool						processUpdateLink( QGraphicsSceneMouseEvent * e );
		bool						processEndLink( QGraphicsSceneMouseEvent *e );
		bool						eventHappenedAtNode( QGraphicsSceneMouseEvent * e );

		static UbLinkController*	m_Instance;
		static QGraphicsScene*		m_Scene;

		UbLinkRef					m_CurrentLink;
		QVector<UbLinkRef>			m_Links;
	};
}