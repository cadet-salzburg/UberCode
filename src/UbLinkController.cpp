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
#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QObject>
#include "UbLinkController.h"
#include "UbMultiInletNode.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
#include "UbImageView.h"
#include "UbSlider.h"
#include "UbSpinbox.h"
#include "UbPathBlock.h"
#include "UbBundleBlock.h"
#include "UbTypes.h"
#include "UbLink.h"
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

	QVector<UbLinkRef>	UbLinkController::getLinksWithStartNode( UbNodeRef startNode )
	{
		QVector<UbLinkRef> links;
		QVector<UbLinkRef>::iterator iter =  m_Links.begin();
		for ( ;iter!=m_Links.end(); ++iter )
		{
			if ( (*iter)->getStartNode() == startNode )
				links.push_back(*iter);
		}
		return links;
	}

	QVector<UbLinkRef>	UbLinkController::getLinksWithEndNode( UbNodeRef endNode )
	{
		QVector<UbLinkRef> links;
		QVector<UbLinkRef>::iterator iter =  m_Links.begin();
		for ( ;iter!=m_Links.end(); ++iter )
		{
			if ( (*iter)->getEndNode() == endNode )
				links.push_back(*iter);
		}
		return links;
	}

	void UbLinkController::addLink( UbNodeRef start, UbNodeRef end )
	{
		UbLinkRef link( new UbLink( 0, m_Scene ));
		link->setNodes( start, end );
		m_Links.push_back(link);
		//if ( m_Scene )
		//	m_Scene->addItem( link );
	}

	//void UbLinkController::addLink( UbLink * link )
	//{
	//	//m_Links.append( link );
	//	if ( m_Scene )
	//		m_Scene->addItem( link );
	//}

	void UbLinkController::removeLink( UbNode *in, UbNode *out )
	{
		UbInletNode *inlet = static_cast< UbInletNode * >( in );
		UbOutletNode *outlet = static_cast< UbOutletNode * >( out );

		for ( QVector< UbLinkRef >::Iterator it = m_Links.begin(); it != m_Links.end(); )
		{
			if ( ( *it )->getEndNode().data() == in && ( *it )->getStartNode().data() == out )
			{

				m_Scene->removeItem( ( *it ).data() );
				delete ( *it ).data();
				it = m_Links.erase( it );
				if ( in->type() != out->type() ) in->unlink( out );
			}
			else if ( ( *it )->getEndNode().data() == out && ( *it )->getStartNode().data() == in )
			{

				m_Scene->removeItem( ( *it ).data() );
				delete ( *it ).data();
				it = m_Links.erase( it );

				if ( in->type() != out->type() ) in->unlink( out );
			}
			else ++it;
		}
	}

	void UbLinkController::removeLinksWith( UbNodeRef node )
	{
		for ( QVector< UbLinkRef >::Iterator it = m_Links.begin(); it != m_Links.end(); )
		{
			if ( ( *it )->getEndNode() == node || ( *it )->getStartNode() == node )
			{
				m_Scene->removeItem( ( *it ).data() );
				delete ( *it ).data();
				it = m_Links.erase( it );

			}
			else ++it;
		}
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
		switch ( (int) e->button() )
		{
		case Qt::LeftButton:
			if( eventHappenedAtNode(e))
			{
				QGraphicsItem *item = itemAt(e->scenePos());
				UbNodeRef nd;
				if ( item->parentObject()->type() == MultiInputNodeContainer )
				{
					UbMultiNodeContainer *parent = static_cast<UbMultiNodeContainer*>( item->parentObject() );
					nd = parent->getNodeUnderMouse();
				} else {
					UbBundleBlock *parent = static_cast<UbBundleBlock*>( item->parentObject() );
					nd = parent->getNodeUnderMouse();
				}
				if ( nd )
				{
					m_CurrentLink = UbLinkRef( new UbLink( 0, m_Scene ) );
					m_CurrentLink->setStartNode(nd);
					m_CurrentLink->getEndNode()->setPos(e->scenePos() );
					m_CurrentLink->updatePath();
					//return true;
				}
				return true;
			}
			else return false;
		case Qt::RightButton:

			if( eventHappenedAtNode( e ) )
			{
				QGraphicsItem *item = itemAt( e->scenePos() );
				UbNodeRef nd;
				if ( item->parentObject()->type() == MultiInputNodeContainer )
				{
					UbMultiNodeContainer *parent = static_cast< UbMultiNodeContainer * >( item->parentObject() );
					nd = parent->getNodeUnderMouse();
				}
				else
				{
					UbBundleBlock *parent = static_cast< UbBundleBlock* >( item->parentObject() );
					nd = parent->getNodeUnderMouse();
				}
				if ( nd )
				{
					for ( QVector< UbLinkRef >::iterator it = m_Links.begin(); it != m_Links.end(); )
					{
						if ( ( *it )->getStartNode() == nd || ( *it )->getEndNode() == nd )
						{
							UbNodeRef start = ( *it )->getStartNode();
							UbNodeRef end = ( *it )->getEndNode();
							std::cout << "found a link" << std::endl;
							if ( !( bothNodesAreInlets( start, end ) || bothNodesAreOutlets( start, end ) ) )
							{
								start->unlink( end.data() );
							}
							m_Scene->removeItem( ( *it ).data() );
							delete ( *it ).data();
							it = m_Links.erase( it );

						}
						else ++it;
					}
				}
				return true;
			}
			else return false;
		default:
			return false;
		}
	}

	bool UbLinkController::processUpdateLink( QGraphicsSceneMouseEvent * e )
	{
		switch ( (int) e->button() )
		{
		case Qt::LeftButton:
			if ( m_CurrentLink )
			{
				if ( !m_CurrentLink->nodesAreSet() )
				{
					m_CurrentLink->getEndNode()->setPos( e->scenePos() );
					m_CurrentLink->updatePath();
					return true;
				} else {
					//std::cout << "Node are set" << std::endl;
				}
			}
		}
		return false;
	}

	bool UbLinkController::processEndLink( QGraphicsSceneMouseEvent *e )
	{
		switch ( (int) e->button() )
		{
		case Qt::LeftButton:
			if ( m_CurrentLink && ( e->button() == Qt::LeftButton) )
			{
				QGraphicsItem *item = itemAt(e->scenePos());
				if ( eventHappenedAtNode( e ) )
				{
					UbNodeRef startNode = m_CurrentLink->getStartNode();
					//UbBundleBlock *parent = static_cast<UbBundleBlock*>( item->parentObject() );
					UbAbstractBlock *parent = static_cast<UbAbstractBlock*>( item->parentObject() );

					UbNodeRef endNode = parent->getNodeUnderMouse();
					if ( tryConnecting(startNode, endNode) )
						return true;
				}
				//We didn't complete the linking, so remove the linkage.
				if ( !m_CurrentLink->nodesAreSet() )
				{
					m_CurrentLink.clear();
				}
				//			m_CurrentLink = 0;
			}
		}
		return false;
	}
	bool UbLinkController::tryConnecting(UbNodeRef startNode, UbNodeRef endNode)
	{
		if ( nodesCanBeConnected( startNode, endNode ) )
		{
			UbInletNodeRef inlet = getInletNode(startNode, endNode );
			UbOutletNodeRef outlet = getOutletNode(startNode, endNode );
			m_CurrentLink->setStartNode(outlet);
			m_CurrentLink->setEndNode(inlet);
			startNode->link(endNode.data());
			m_Links.push_back(m_CurrentLink);
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
							//m_CurrentLink = UbLinkRef( new UbLink( 0, m_Scene ) );
							m_CurrentLink->setStartNode( blockNode);
							m_CurrentLink->setEndNode( uiNode);
							m_Links.push_back( m_CurrentLink );
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
						int type = uiInlet->parentObject()->type();
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
						} else if ( obj->type() == Uber::PathBlockType )
						{
							UbPathBlock* pathBlock = static_cast<UbPathBlock*>(obj);
							pathBlock->blockIsConnected();
						}
						//create link
						//m_CurrentLink = UbLinkRef( new UbLink( 0, m_Scene ) );
						m_CurrentLink->setStartNode( blockNode);
						m_CurrentLink->setEndNode( uiNode);
						m_Links.push_back( m_CurrentLink );
						return true;
					}	
				}
				//return true;
			}
		}// end
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
		int t = node->parentItem()->type();
		if ( node )
		{
			if ( node->parentItem()->type() == Uber::BundleBlockType || node->parentItem()->type() == Uber::MultiInputNodeContainer )
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
		std::string typen = node->getHandle().getTypename();
		if ( ( ( node->getHandle().getTypename() == "int" ) && ( type == SliderBlockType ) ) 
			|| ( ( node->getHandle().getTypename() == "int" ) && ( type == SpinBoxBlockType ) ) 
			|| ( ( node->getHandle().getTypename() == "string" ) && ( type == PathBlockType ) ) )
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