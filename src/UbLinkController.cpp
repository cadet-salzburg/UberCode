#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QObject>
#include "UbLinkController.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
#include "UbIOBlock.h"

namespace Uber {
	UbLinkController*	UbLinkController::m_Instance = 0;
	QGraphicsScene*		UbLinkController::m_Scene	 = 0;

	UbLinkController* UbLinkController::getInstance()
	{
		if ( !m_Instance )
		{
			m_Instance = new UbLinkController; 
		}
		return m_Instance;
	}

	void UbLinkController::setScene( QGraphicsScene * scene )
	{
		m_Scene = scene;
		m_Scene->installEventFilter(m_Instance);
	}

	void UbLinkController::addLink( UbNode* start, UbNode* end )
	{
		UbLink *link = new UbLink( 0, m_Scene );
		link->setNodes( start, end );
		if ( m_Scene )
			m_Scene->addItem( link );
	}

	void UbLinkController::addLink( UbLink * link )
	{
		//m_Links.append( link );
		if ( m_Scene )
			m_Scene->addItem( link );
	}

	void UbLinkController::removeLink( UbLink* const link )
	{
		m_Scene->removeItem( link );
		delete link;

		//QList<UbLink*>::iterator iter = m_Links.begin();
		//for ( ;iter!= m_Links.end(); ++iter )
		//{
		//	if ( *iter == link )
		//	{
		//		if ( m_Scene ) 
		//			m_Scene->removeItem( link );
		//		//ToDo: Do we actually need to hold a list of links??
		//		delete *iter;
		//		iter = m_Links.erase( iter, iter );
		//		break;
		//	}
		//}
	}

	QGraphicsItem*	UbLinkController::itemAt(const QPointF &pos)
	{
		QList<QGraphicsItem*> items = m_Scene->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

		foreach(QGraphicsItem *item, items)
			if (item->type() > QGraphicsItem::UserType)
				return item;

		return nullptr;
	}

	bool UbLinkController::processStartLink(QGraphicsSceneMouseEvent *e)
	{
		QGraphicsItem *item = itemAt(e->scenePos());
		switch ( (int) e->button() ) {
		case Qt::LeftButton:
			if(item)
			{
				int t = item->type();
				if ( ( item->type() == UbNode::Type ) || ( item->type() == UbInletNode::Type ) || ( item->type() == UbOutletNode::Type ) )
					//if (item && item->type() == UbNode::Type)
				{
					m_CurrentLink = new UbLink( 0, m_Scene );
					m_CurrentLink->startedChanging();
					m_CurrentLink->setStartNode( (UbNode*) item );
					m_CurrentLink->setStartPos( item->scenePos() );
					m_CurrentLink->setEndPos( e->scenePos() );
					m_CurrentLink->updatePath();
					return true;
				} 
			}
			break;
		case Qt::RightButton:
			//if (item && (item->type() == QNEConnection::Type || item->type() == QNEBlock::Type))
			//	delete item;
			// if (selBlock == (QNEBlock*) item)
			// selBlock = 0;
			break;
		}
		return false;
	}

	bool UbLinkController::processUpdateLink( QGraphicsSceneMouseEvent * e )
	{
		if ( m_CurrentLink )
		{
			m_CurrentLink->setEndPos( e->scenePos() );
			m_CurrentLink->updatePath();
			return true;
		}
		return false;
	}

	bool UbLinkController::processEndLink( QGraphicsSceneMouseEvent *e )
	{
		if ( m_CurrentLink && e->button() == Qt::LeftButton)
		{
			QGraphicsItem *item = itemAt(e->scenePos());
			if ( eventHappenedAtNode( e ) )
			{
				UbNode *startNode = m_CurrentLink->getStartNode();
				UbNode *endNode	  = static_cast<UbNode*>(item);

				if ( nodesCanBeConnected( startNode, endNode ) )
				{
					UbInletNode* inlet = getInletNode(startNode, endNode );
					UbOutletNode* outlet = getOutletNode(startNode, endNode );
					m_CurrentLink->setStartNode(outlet);
					m_CurrentLink->setEndNode(inlet);
					m_CurrentLink->finishedChanging();
					return true;
				} else if ( nodesHaveDifferentParents(startNode, endNode) )
				{
					if ( isBundleBlockNode( startNode ) ^ isBundleBlockNode( endNode ) )
					{
						if ( bothNodesAreOutlets(startNode, endNode ) )
						UbNode* node = startNode;
						if ( isBundleBlockNode(startNode) )
							node = endNode;
						//Check if they can be connected.

						//Connect them.
					}
				}
			}
		}
	}













				//if ( nodesHaveDifferentParents(startNode, endNode) )
				//{
				//	if ( nodesHaveDifferentType(startNode, endNode ) )
				//	{
				//		if ( (startNode->type() == Uber::OutputNodeType ) && ( endNode->type() == Uber::InputNodeType) )
				//		{
				//			if ( dynamic_cast<UbOutletNode*>(startNode)->getHandle().getTypename() == dynamic_cast<UbInletNode*>(endNode)->getHandle().getTypename() )
				//			{
				//				m_CurrentLink->setStartNode(endNode);
				//				m_CurrentLink->setEndNode(startNode);
				//				m_CurrentLink->finishedChanging();
				//				m_CurrentLink->updatePath();
				//				return true;
				//			}
				//		} else if ( ( startNode->type() == Uber::InputNodeType ) && ( endNode->type() == Uber::OutputNodeType ) )
				//		{
				//			if ( dynamic_cast<UbInletNode*>(startNode)->getHandle().getTypename() == dynamic_cast<UbOutletNode*>(endNode)->getHandle().getTypename() )
				//			{
				//				m_CurrentLink->setStartNode(startNode);
				//				m_CurrentLink->setEndNode(endNode);
				//				m_CurrentLink->finishedChanging();
				//				m_CurrentLink->updatePath();
				//				return true;
				//			}
				//		}
				//	} else {

				//		if ( (startNode->type() == Uber::NodeType ) && ( endNode->type() == Uber::OutputNodeType ) )
				//		{
				//			QGraphicsObject *obj = startNode->parentObject();
				//			UbOutletNode *_node =  dynamic_cast<UbOutletNode*>(endNode);
				//			dynamic_cast<UbIOBlock*>(obj)->setInputNode(_node->getHandle());
				//			m_CurrentLink->setEndNode(endNode);
				//			m_CurrentLink->finishedChanging();
				//			m_CurrentLink->updatePath();
				//			return true;
				//		} else if ( ( startNode->type() == Uber::OutputNodeType ) && (endNode->type() == Uber::NodeType ) )
				//		{
				//			QGraphicsObject *obj = endNode->parentObject();
				//			UbOutletNode *_node =  dynamic_cast<UbOutletNode*>(startNode);
				//			dynamic_cast<UbIOBlock*>(obj)->setInputNode(_node->getHandle());
				//			m_CurrentLink->setEndNode(endNode);
				//			m_CurrentLink->finishedChanging();
				//			m_CurrentLink->updatePath();
				//			return true;
				//		}
					}



					//if ( startNode->type() == QGraphicsItem::UserType + UberCodeItemType::NodeType )
					//{
					//	if ( endNode->type() == QGraphicsItem::UserType + UberCodeItemType::OutputNodeType )
					//	{
					//		QGraphicsObject *obj = startNode->parentObject();
					//		UbOutletNode *_node =  dynamic_cast<UbOutletNode*>(endNode);
					//		dynamic_cast<UbIOBlock*>(obj)->setInputNode(_node->getHandle());
					//	}
					//}
					//else if ( endNode->type() == QGraphicsItem::UserType + UberCodeItemType::NodeType )
					//{
					//	if ( startNode->type() == QGraphicsItem::UserType + UberCodeItemType::OutputNodeType )
					//	{
					//		QGraphicsObject *obj = endNode->parentObject();
					//		UbOutletNode *_node =  dynamic_cast<UbOutletNode*>(startNode);
					//		dynamic_cast<UbIOBlock*>(obj)->setInputNode(_node->getHandle());
					//	}
					//}
					//m_CurrentLink->setEndNode(endNode);
					//m_CurrentLink->finishedChanging();
					//m_CurrentLink->updatePath();
					//return true;
				}
			}
			if ( m_CurrentLink->isChanging() )
			{
				delete m_CurrentLink;
			}
			m_CurrentLink = 0;
			return false;
		}
	}
	bool UbLinkController::nodesHaveDifferentParents( UbNode* nodeA, UbNode *nodeB )
	{
		if( nodeA->parentItem() != nodeB->parentItem() )
			return true;
		return false;
	}
	bool UbLinkController::nodesHaveDifferentType( UbNode* nodeA, UbNode *nodeB )
	{
		if ( nodeA->type() != nodeB->type() )
			return true;
		return false;
	}

	UbInletNode* UbLinkController::getInletNode( UbNode* nodeA, UbNode *nodeB )
	{		
		UbInletNode* node = 0;
		if ( nodeA->type() == Uber::InputNodeType )
		{
			node = static_cast<UbInletNode*>(nodeA);
		} else if ( nodeB->type() == Uber::InputNodeType )
		{
			node = static_cast<UbInletNode*>(nodeB);
		}
		return node;
	}

	UbOutletNode* UbLinkController::getOutletNode( UbNode* nodeA, UbNode *nodeB )
	{
		UbOutletNode* node = 0;
		if ( nodeA->type() == Uber::OutputNodeType )
		{
			node = static_cast<UbOutletNode*>(nodeA);
		} else if ( nodeB->type() == Uber::OutputNodeType )
		{
			node = static_cast<UbOutletNode*>(nodeB);
		}
		return node;
	}

	bool UbLinkController::nodesCanBeConnected( UbNode* nodeA, UbNode* nodeB )
	{
		if ( isBundleBlockNode(nodeA) && isBundleBlockNode(B) && nodesHaveDifferentParents(nodeA, nodeB ) && nodesHaveDifferentType( nodeA, nodeB )  )
		{
			UbInletNode* inlet = getInletNode(nodeA, nodeB);
			UbInletNode* outlet = getInletNode(nodeA, nodeB);
			if ( inlet->getHandle().getTypename() == outlet->getHandle().getTypename() )
				return true;
		}
		return false;
	}

	bool UbLinkController::isBundleBlockNode( UbNode* node )
	{
		if ( node->parentItem()->type() == Uber::BundleBlockType )
			return true;
		return false;
	}

	bool UbLinkController::bothNodesAreOutlets( UbNode *nodeA, UbNode *nodeB )
	{
		if ( ( nodeA->type() == nodeB->type() ) && nodeA->type() = Uber::OutputNodeType )
		{
			return true;
		}
		return false;
	}


	bool UbLinkController::eventHappenedAtNode( QGraphicsSceneMouseEvent * e )
	{
		QGraphicsItem *item = itemAt(e->scenePos());
		if ( item != nullptr ){
			return ( item->type() == UbNode::Type || item->type() == UbInletNode::Type || item->type() == UbInletNode::Type )?true:false;
		}
		return false;

	}

	bool UbLinkController::eventFilter( QObject *obj, QEvent *e )
	{
		QGraphicsSceneMouseEvent *me = (QGraphicsSceneMouseEvent*) e;
		bool ret = false;
		switch ((int) e->type()){
		case QEvent::GraphicsSceneMousePress:
			ret = processStartLink(me);
			break;
		case QEvent::GraphicsSceneMouseMove:
			ret = processUpdateLink(me);
			break;
		case QEvent::GraphicsSceneMouseRelease:
			ret = processEndLink(me);
			break;
		}
		return ( QObject::eventFilter(obj, e) || ret );
	}

	void UbLinkController::render()
	{

	}

	UbLinkController::UbLinkController(void)
		:m_CurrentLink(NULL)
	{

	}

	UbLinkController::~UbLinkController(void)
	{

	}
}