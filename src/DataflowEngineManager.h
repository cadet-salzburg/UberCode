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
#pragma once
#include <vector>
#include <QStringList>
#include <QGraphicsItem>
#include "_2RealApplication.h"
#include "UbComposition.h"
#include "UbBundleBlock.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
#include "UbGraphicsView.h"
#include "UbInterfaceBlock.h"

typedef std::pair<QString, _2Real::app::BundleHandle>	BlockInstancingInfo;
typedef std::vector<BlockInstancingInfo>				BlockInstancingInfos;

class DataflowEngineManager
{
public:
	~DataflowEngineManager();
	static DataflowEngineManager*			getInstance();
	QStringList								loadBundles();

	Uber::UbComposition*					addComposition();
	void									removeComposition(Uber::UbComposition* comp);
	Uber::UbComposition*					getComposition();

	_2Real::app::Engine&					getEngine();
	const BlockInstancingInfos&				getBlockInstancingInfos();

	QList<Uber::UbBundleBlock*>				getBundleBlocks();

	void									setGraphicsView( Uber::UbGraphicsView* view );
	Uber::UbGraphicsView*					getGraphicsView();						

	Uber::UbObject*							createInterfaceBlock( int type );

	QMap<int,int>&							getInterfaceBlockData();
private:
	DataflowEngineManager();
	QStringList								findBundlesInDirectory();
	void									addInterfaceBlockId(int type);
	static DataflowEngineManager*			m_pInstance;
	_2Real::app::Engine&					m_Engine;
	BlockInstancingInfos					m_BlockInstancingInfos;
	std::vector<Uber::UbComposition*>		m_UbCompositions;
	Uber::UbGraphicsView					*m_GraphicsView;
	QMap<int, int>							m_InterfaceBlockIds;
};