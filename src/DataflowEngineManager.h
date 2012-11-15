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

private:
	DataflowEngineManager();
	QStringList								findBundlesInDirectory();
	static DataflowEngineManager*			m_pInstance;
	_2Real::app::Engine&					m_Engine;
	BlockInstancingInfos					m_BlockInstancingInfos;
	std::vector<Uber::UbComposition*>		m_UbCompositions;
	Uber::UbGraphicsView					*m_GraphicsView;
};