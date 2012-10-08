#include "Composition.h"
#include "DataflowEngineManager.h"
#include "UbBundleBlock.h"
#include "UbIOBlock.h"
#include "UbLink.h"
#include "UbLinkController.h"

Composition::Composition()
{
	m_WorkbenchGraphicsScene = new WorkbenchGraphicsScene();
}

Composition::~Composition()
{
	delete m_WorkbenchGraphicsScene;
}

WorkbenchGraphicsScene* Composition::getGraphicsScene()
{
	return m_WorkbenchGraphicsScene;
}

void Composition::addBlock(QString strBlockName)
{
	BlockInstancingInfos blockInfos = DataflowEngineManager::getInstance()->getBlockInstancingInfos();

	auto it = blockInfos.begin();
	while ( it != blockInfos.end() )
	{
		if ( std::get<0>(*it) == strBlockName )
		{
			UbBundleBlock *block = new UbBundleBlock( 0, std::get<1>(*it), strBlockName );
			block->setPos(0, 0);
			m_WorkbenchGraphicsScene->addItem(block);
			break;
		}
		++it;
	}
}