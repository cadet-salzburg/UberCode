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
		void						addLink( UbLink* const link );
		void						removeLink( UbLink* const link );
		bool						eventFilter(QObject * obj, QEvent * e );
		void						render();

		QGraphicsItem*				itemAt(const QPointF &pos);

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
		UbLink*						m_CurrentLink;
		QVector<UbLinkWeakRef>		m_Links;
	};
}