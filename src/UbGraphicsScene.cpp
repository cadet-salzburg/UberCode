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
#include "UbGraphicsScene.h"
#include "BlockNavigationTreeWidget.h"
#include "DataflowEngineManager.h"

namespace Uber {
	UbGraphicsScene::UbGraphicsScene()
	{
		initialize();
	}

	UbGraphicsScene::~UbGraphicsScene()
	{

	}

	void UbGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
	{
		//std::cout << " drag enter scene" << std::endl;
		BlockNavigationTreeWidget* source = qobject_cast<BlockNavigationTreeWidget *>(event->source());
		event->setAccepted(true);
		if(source)
		{
			event->setAccepted(true);
		}
		else
		{
			event->setAccepted(false);
		}
	}

	void UbGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
	{
		//std::cout << " drag  move scene" << std::endl;
		BlockNavigationTreeWidget* source = qobject_cast<BlockNavigationTreeWidget *>(event->source());
		event->setAccepted(true);
		if(source)
		{
			event->setAccepted(true);
		}
		else
		{
			event->setAccepted(false);
		}
	}

	void UbGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent* event)
	{
		//std::cout << " drag drop scene" << std::endl;
		QString blockName = event->mimeData()->text();
		DataflowEngineManager::getInstance()->getComposition()->addBlock(blockName, event->scenePos());
		event->acceptProposedAction();
	}

	void UbGraphicsScene::initialize()
	{
		//setSceneRect(0,0,640, 480);
	}

	void UbGraphicsScene::addItem( UbObject * item )
	{
		m_Items.push_back(item);
		QGraphicsScene::addItem(item);
	}

	void UbGraphicsScene::removeItem( UbObject * item )
	{
		int tt = item->type();
		QGraphicsScene::removeItem(item);
		QList<UbObject*>::iterator iter = m_Items.begin();
		for ( ;iter!=m_Items.end(); )
		{
			if ( *iter==item )
			{
				iter = m_Items.erase(iter);
				if ( item->type()==BundleBlockType )
				{
					UbBundleBlock *obj = static_cast<UbBundleBlock*>(item);
					obj->getHandle().kill();
				}
				delete item;
				break;
			}
			else {
				++iter;
			}
		} 
	}

	UbObject* UbGraphicsScene::getNamedItem( QString name )
	{
		QList<UbObject*>::iterator iter = m_Items.begin();
		for ( ;iter!=m_Items.end(); ++iter )
		{
			if ( (*iter)->getName() == name )
			{
				return *iter;
			}
		}
		return NULL;
	}

}