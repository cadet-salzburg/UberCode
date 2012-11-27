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