#pragma once
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "UbLink.h"
#include "UbNode.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"

namespace Uber {
	class UbLinkController : public QObject
	{
		Q_OBJECT
	public:
		static	UbLinkController*	getInstance();
		static	void				setScene( QGraphicsScene * scene );
		void						addLink( UbNode* start, UbNode* end ); 
		void						addLink( UbLink* const link );
		void						removeLink( UbLink* const link );
		bool						eventFilter(QObject * obj, QEvent * e );
		void						render();

		QGraphicsItem*				itemAt(const QPointF &pos);

	private:
		UbLinkController(void);
		~UbLinkController(void);
		static UbLinkController*	m_Instance;
		static QGraphicsScene*		m_Scene;
		UbLink*						m_CurrentLink;

		bool						nodesHaveDifferentParents( UbNode* nodeA, UbNode *nodeB );
		bool						nodesHaveDifferentType( UbNode* nodeA, UbNode *nodeB );
		UbInletNode*				getInletNode( UbNode* nodeA, UbNode* nodeB );
		UbOutletNode*				getOutletNode( UbNode* nodeA, UbNode* nodeB );
		bool						nodesCanBeConnected( UbNode* nodeA, UbNode* nodeB );
		bool						isBundleBlockNode( UbNode* node );
		bool						bothNodesAreOutlets( UbNode *nodeA, UbNode *nodeB );

		bool						processStartLink( QGraphicsSceneMouseEvent * e );
		bool						processUpdateLink( QGraphicsSceneMouseEvent * e );
		bool						processEndLink( QGraphicsSceneMouseEvent *e );
		bool						eventHappenedAtNode( QGraphicsSceneMouseEvent * e );
	};
}