#include "WorkbenchGraphicsScene.h"
#include "BlockNavigationTreeWidget.h"
#include "DataflowEngineManager.h"

WorkbenchGraphicsScene::WorkbenchGraphicsScene()
{
}

WorkbenchGraphicsScene::~WorkbenchGraphicsScene()
{
}

void WorkbenchGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{ 
	BlockNavigationTreeWidget* source = qobject_cast<BlockNavigationTreeWidget *>(event->source());
	if(source)
	{
		event->setAccepted(true);
	}
	else
	{
		event->setAccepted(false);
	}
}

void WorkbenchGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
	BlockNavigationTreeWidget* source = qobject_cast<BlockNavigationTreeWidget *>(event->source());
	if(source)
	{
		event->setAccepted(true);
	}
	else
	{
		event->setAccepted(false);
	}
}

void WorkbenchGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
	QString blockName = event->mimeData()->text();
	event->acceptProposedAction();
	DataflowEngineManager::getInstance()->getComposition()->addBlock(blockName);
}

	