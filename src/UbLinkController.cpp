#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QObject>
#include "UbLinkController.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
#include "UbImageView.h"
#include "UbSlider.h"
#include "UbSpinbox.h"
#include "UbBundleBlock.h"
#include "UbTypes.h"
#include <string>

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
	}

	void UbLinkController::addLink( UbNodeRef start, UbNodeRef end )
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
		//UbNodeRef item = 
		switch ( (int) e->button() ) {
		case Qt::LeftButton:
			if( eventHappenedAtNode(e))
			{
				QGraphicsItem *item = itemAt(e->scenePos());
				UbBundleBlock *parent = static_cast<UbBundleBlock*>( item->parentObject() );
				UbNodeRef nd = parent->getNodeUnderMouse();
				if ( nd )
				{
					m_CurrentLink = new UbLink( 0, m_Scene );
					m_CurrentLink->setStartNode(nd);
					m_CurrentLink->getEndNode()->setPos(e->scenePos() );
					m_CurrentLink->updatePath();
					//return true;
				}
				return true;
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
			if ( !m_CurrentLink->nodesAreSet() )
			{
				m_CurrentLink->getEndNode()->setPos( e->scenePos() );
				m_CurrentLink->updatePath();
				return true;
			} else {
				std::cout << "Node are set" << std::endl;
			}
		}
		return false;
	}

	bool UbLinkController::processEndLink( QGraphicsSceneMouseEvent *e )
	{
		if ( m_CurrentLink && ( e->button() == Qt::LeftButton) )
		{
			QGraphicsItem *item = itemAt(e->scenePos());
			if ( eventHappenedAtNode( e ) )
			{
				UbNodeRef startNode = m_CurrentLink->getStartNode();
				UbBundleBlock *parent = static_cast<UbBundleBlock*>( item->parentObject() );
				UbNodeRef endNode = parent->getNodeUnderMouse();

				if ( nodesCanBeConnected( startNode, endNode ) )
				{
					UbInletNodeRef inlet = getInletNode(startNode, endNode );
					UbOutletNodeRef outlet = getOutletNode(startNode, endNode );
					m_CurrentLink->setStartNode(outlet);
					m_CurrentLink->setEndNode(inlet);
					startNode->link(endNode.data());
					return true;
				} else if ( nodesHaveDifferentParents(startNode, endNode) )
				{
					if ( isBundleBlockNode( startNode ) ^ isBundleBlockNode( endNode ) )
					{
						if ( bothNodesAreOutlets(startNode, endNode ) )
						{
							//We have an output node and ui block
							UbNodeRef blockNode = endNode;
							UbNodeRef uiNode = startNode;
							if ( isBundleBlockNode(startNode) )
							{
								blockNode = startNode;
								uiNode	  = endNode;
							}
							//Check if they can be connected.

							UbOutletNodeRef blockOutlet = qSharedPointerCast<UbOutletNode>(blockNode);
							UbOutletNodeRef uiOutlet = qSharedPointerCast<UbOutletNode>(uiNode);
							if ( canConnectOutputNodeToUiBlockOfType(blockOutlet,uiOutlet->parentObject()->type() ) )
							{
								//set handle for the node of the ui block
								uiOutlet->setHandle(blockOutlet->getHandle());
								QGraphicsObject *obj = uiOutlet->parentObject();
								if ( obj->type() == ImageBlockType )
								{
									UbImageView* imgBlock  = static_cast<UbImageView*>(obj);
									imgBlock->blockIsConnected();

									//create link
									m_CurrentLink->setStartNode( blockNode);
									m_CurrentLink->setEndNode( uiNode);
									return true;
								}
							}	
						}
						if ( bothNodesAreInlets( startNode, endNode ) )
						{
							//We have an input node and ui block
							UbNodeRef blockNode = endNode;
							UbNodeRef uiNode = startNode;
							if ( isBundleBlockNode(startNode) )
							{
								blockNode = startNode;
								uiNode	  = endNode;
							}
							//Check if they can be connected.
							UbInletNodeRef blockInlet = qSharedPointerCast<UbInletNode>(blockNode);
							UbInletNodeRef uiInlet = qSharedPointerCast<UbInletNode>(uiNode);

							if ( canConnectInputNodeToUiBlockOfType(blockInlet,uiInlet->parentObject()->type() ) )
							{
								//set handle for the node of the ui block
								uiInlet->setHandle(blockInlet->getHandle());
								QGraphicsObject *obj = uiInlet->parentObject();
								if ( obj->type() == Uber::SliderBlockType )
								{
									UbSlider* sliderBlock = static_cast<UbSlider*>(obj);
									sliderBlock->blockIsConnected();
								} else if ( obj->type() == Uber::SpinBoxBlockType )
								{
									UbSpinbox* spinboxBlock = static_cast<UbSpinbox*>(obj);
									spinboxBlock->blockIsConnected();
								}
								//create link
								m_CurrentLink->setStartNode( blockNode);
								m_CurrentLink->setEndNode( uiNode);
								return true;
							}	
						}
						return true;
					}
				}
			}
		//We didn't complete the linking, so remove the linkage.
		if ( !m_CurrentLink->nodesAreSet() )
		{
			delete m_CurrentLink;
		}
		m_CurrentLink = 0;
		}
		return false;
	}

	bool UbLinkController::nodesHaveDifferentParents( UbNodeRef nodeA, UbNodeRef nodeB )
	{
		if( nodeA->parentItem() != nodeB->parentItem() )
			return true;
		return false;
	}

	bool UbLinkController::nodesHaveDifferentType( UbNodeRef nodeA, UbNodeRef nodeB )
	{
		if ( nodeA && nodeB )
		{
			if ( nodeA->type() != nodeB->type() )
				return true;
		}
		return false;
	}

	UbInletNodeRef UbLinkController::getInletNode( UbNodeRef nodeA, UbNodeRef nodeB )
	{		
		UbInletNodeRef node = UbInletNodeRef();
		if ( nodeA && nodeB )
		{
			if ( nodeA->type() == Uber::InputNodeType )
			{
				node = qSharedPointerCast<UbInletNode>(nodeA);
			} else if ( nodeB->type() == Uber::InputNodeType )
			{
				node = qSharedPointerCast<UbInletNode>(nodeB);
			}
		}
		return node;
	}

	UbOutletNodeRef UbLinkController::getOutletNode( UbNodeRef nodeA, UbNodeRef nodeB )
	{
		UbOutletNodeRef node = UbOutletNodeRef();
		if ( nodeA && nodeB )
		{
			if ( nodeA->type() == Uber::OutputNodeType )
			{
				node = qSharedPointerCast<UbOutletNode>(nodeA);
			} else if ( nodeB->type() == Uber::OutputNodeType )
			{
				node = qSharedPointerCast<UbOutletNode>(nodeB);
			}
		}

		return node;
	}

	bool UbLinkController::nodesCanBeConnected( UbNodeRef nodeA, UbNodeRef nodeB )
	{
		if ( nodeA && nodeB )
		{
			if ( ( ( isBundleBlockNode(nodeA) && isBundleBlockNode(nodeB) ) && ( nodesHaveDifferentParents(nodeA, nodeB ) ) && nodesHaveDifferentType( nodeA, nodeB ) ) )
			{
				UbInletNodeRef inlet = getInletNode(nodeA, nodeB);
				UbOutletNodeRef outlet = getOutletNode(nodeA, nodeB);
				std::string typeNameA = inlet->getHandle().getTypename();
				std::string typeNameB = outlet->getHandle().getTypename();
				if ( inlet->getHandle().getTypename() == outlet->getHandle().getTypename() )
					return true;
			}
		}
		return false;
	}

	bool UbLinkController::isBundleBlockNode( UbNodeRef node )
	{
		if ( node )
		{
			if ( node->parentItem()->type() == Uber::BundleBlockType )
				return true;
		}
		return false;
	}
	bool UbLinkController::bothNodesAreInlets( UbNodeRef nodeA, UbNodeRef nodeB )
	{
		if ( !(nodeA && nodeB) )
			return false;
		if ( ( nodeA->type() == nodeB->type() )  && ( nodeA->type() == Uber::InputNodeType ))
		{
			return true;
		}
		return false;
	}
	bool UbLinkController::bothNodesAreOutlets( UbNodeRef nodeA, UbNodeRef nodeB )
	{
		if ( !(nodeA && nodeB) )
			return false;
		if ( ( nodeA->type() == nodeB->type() )  && ( nodeA->type() == Uber::OutputNodeType ))
		{
			return true;
		}
		return false;
	}


	bool UbLinkController::eventHappenedAtNode( QGraphicsSceneMouseEvent * e )
	{
		QGraphicsItem *item = itemAt(e->scenePos());
		if ( item != nullptr ){
			return ( item->type() == UbNode::Type || item->type() == UbInletNode::Type || item->type() == UbOutletNode::Type )?true:false;
		}
		return false;

	}

	bool UbLinkController::eventFilter( QObject *obj, QEvent *e )
	{
		if ( ( e->type() == QEvent::GraphicsSceneMouseMove ) || ( e->type() == QEvent::GraphicsSceneMousePress ) || ( e->type() == QEvent::GraphicsSceneMouseRelease ) ) 
		{
			QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent*>(e);
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
			return ret;
		} else {
			// standard event processing
			return QObject::eventFilter(obj, e);
		}
	}

	bool UbLinkController::canConnectOutputNodeToUiBlockOfType( UbOutletNodeRef node, int type )
	{
		if ( ( node->getHandle().getTypename() == "number image" ) && ( type == ImageBlockType ) )
		{
			return true;
		} 
		return false;
	}
	bool UbLinkController::canConnectInputNodeToUiBlockOfType( UbInletNodeRef node, int type )
	{
		if ( ( ( node->getHandle().getTypename() == "int" ) && ( type == SliderBlockType ) ) || ( ( node->getHandle().getTypename() == "int" ) && ( type == SpinBoxBlockType ) ) )
		{
			return true;
		}
		return false;
	}

	void UbLinkController::render()
	{

	}

	UbLinkController::UbLinkController(void)
		:m_CurrentLink(0)
	{

	}

	UbLinkController::~UbLinkController(void)
	{

	}
}