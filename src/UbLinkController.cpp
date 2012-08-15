#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QEvent>
#include <QObject>
#include "UbLinkController.h"
#include "UbLink.h"
#include "UbNode.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
#include "UbIOBlock.h"


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

	return 0;
}

bool UbLinkController::itemIs( QGraphicsItem * item, int type )
{
	bool res = item && item->type() == type;
	return  res;
}

bool UbLinkController::eventFilter( QObject *obj, QEvent *e )
{
	QGraphicsSceneMouseEvent *me = (QGraphicsSceneMouseEvent*) e;
	switch ((int) e->type())
	{
	case QEvent::GraphicsSceneMousePress:
		{
			switch ((int) me->button())
			{
			case Qt::LeftButton:
				{
					QGraphicsItem *item = itemAt(me->scenePos());
					if(item)
					{
						int t = item->type();
						if ( itemIs(item, UbNode::Type ) || itemIs(item, UbInletNode::Type) || itemIs(item, UbOutletNode::Type ) )
						//if (item && item->type() == UbNode::Type)
						{
							m_CurrentLink = new UbLink( 0, m_Scene );
							m_CurrentLink->startedChanging();
							m_CurrentLink->setStartNode( (UbNode*) item );
							m_CurrentLink->setStartPos( item->scenePos() );
							m_CurrentLink->setEndPos( me->scenePos() );
							m_CurrentLink->updatePath();
							return true;
						} 
					}
					break;
				}
			case Qt::RightButton:
				{
					QGraphicsItem *item = itemAt( me->scenePos() );
					//if (item && (item->type() == QNEConnection::Type || item->type() == QNEBlock::Type))
					//	delete item;
					// if (selBlock == (QNEBlock*) item)
					// selBlock = 0;
					break;
				}
			}
		}
	case QEvent::GraphicsSceneMouseMove:
		{
			if ( m_CurrentLink )
			{
				m_CurrentLink->setEndPos( me->scenePos() );
				m_CurrentLink->updatePath();
				return true;
			}
			break;
		}
	case QEvent::GraphicsSceneMouseRelease:
		{
			if ( m_CurrentLink && me->button() == Qt::LeftButton)
			{
				QGraphicsItem *item = itemAt(me->scenePos());
				
				if ( itemIs(item, UbNode::Type ) || itemIs(item, UbInletNode::Type) || itemIs(item, UbOutletNode::Type ) )
				{
					UbNode *startNode = m_CurrentLink->getStartNode();
					UbNode *endNode	  = (UbNode*) item;

					if ( startNode != endNode && startNode->parentItem() != endNode->parentItem() )
					{
						int s  = startNode->type();
						int e  = endNode->type();
						if ( startNode->type() == QGraphicsItem::UserType + UberCodeItemType::NodeType )
						{
							if ( endNode->type() == QGraphicsItem::UserType + UberCodeItemType::OutputNodeType )
							{
								QGraphicsObject *obj = startNode->parentObject();
								UbOutletNode *_node =  dynamic_cast<UbOutletNode*>(endNode);
								dynamic_cast<UbIOBlock*>(obj)->setInputNode(_node->getHandle());
							}
						}
						else if ( endNode->type() == QGraphicsItem::UserType + UberCodeItemType::NodeType )
						{
							if ( startNode->type() == QGraphicsItem::UserType + UberCodeItemType::OutputNodeType )
							{
								QGraphicsObject *obj = startNode->parentObject();
								UbOutletNode *_node =  dynamic_cast<UbOutletNode*>(startNode);
								dynamic_cast<UbIOBlock*>(obj)->setInputNode(_node->getHandle());
							}
						}

						int typeStart  = startNode->type();
						int typeEnd    = endNode->type();
						m_CurrentLink->setEndNode(endNode);
						m_CurrentLink->finishedChanging();
						m_CurrentLink->updatePath();
						return true;
					}
				}
				if ( m_CurrentLink->isChanging() )
					delete m_CurrentLink;
				m_CurrentLink = 0;
				return true;
			}
			break;
		}
	}
	return QObject::eventFilter(obj, e);
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