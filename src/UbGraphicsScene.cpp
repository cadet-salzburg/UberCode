#include "UbGraphicsScene.h"
#include "BlockNavigationTreeWidget.h"
#include "DataflowEngineManager.h"
#include "UbIOBlock.h"
UbGraphicsScene::UbGraphicsScene()
{
	initialize();
}

UbGraphicsScene::~UbGraphicsScene()
{

}

void UbGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
	std::cout << " drag enter scene" << std::endl;
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
	std::cout << " drag  move scene" << std::endl;
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
	std::cout << " drag drop scene" << std::endl;
	QString blockName = event->mimeData()->text();
	DataflowEngineManager::getInstance()->getComposition()->addBlock(blockName, event->scenePos());
	event->acceptProposedAction();
		//UbIOBlock *b = new UbIOBlock(nullptr);
	//b->setPos(event->scenePos());
	//DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(b);
	//DataflowEngineManager::getInstance()->getComposition()->addBlock(blockName, event->scenePos());
}

void UbGraphicsScene::initialize()
{
	//setSceneRect(0,0,640, 480);
}