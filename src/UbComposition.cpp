#include "UbComposition.h"
#include "DataflowEngineManager.h"
#include "UbLink.h"
#include "UbLinkController.h"
namespace Uber {
	UbComposition::UbComposition()
	{
		m_UbGraphicsScene = new UbGraphicsScene();
	}

	UbComposition::~UbComposition()
	{
		delete m_UbGraphicsScene;
	}

	UbGraphicsScene* UbComposition::getGraphicsScene()
	{
		return m_UbGraphicsScene;
	}

	void UbComposition::addBlock(QString strBlockName, QPointF pos )
	{
		BlockInstancingInfos blockInfos = DataflowEngineManager::getInstance()->getBlockInstancingInfos();

		auto it = blockInfos.begin();
		while ( it != blockInfos.end() )
		{
			if ( std::get<0>(*it) == strBlockName )
			{
				UbBundleBlock *block = new UbBundleBlock( 0, std::get<1>(*it), strBlockName );
				int t = block->type();
				block->setPos(pos);
				m_UbGraphicsScene->addItem(block);
				break;
			}
			++it;
		}
	}
	void UbComposition::addBlock( UbBundleBlock *block )
	{
		m_UbGraphicsScene->addItem(block);
	}
}