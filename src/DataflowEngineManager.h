#pragma once
#include <vector>
#include <QStringList>
#include <QGraphicsItem>
#include "_2RealApplication.h"
#include "UbComposition.h"

namespace Uber {
enum  {
		NodeType = QGraphicsItem::UserType + 1,
		InputNodeType = QGraphicsItem::UserType + 2,
		OutputNodeType = QGraphicsItem::UserType + 3,
		AbstractBlockType = QGraphicsItem::UserType + 4,
		BundleBlockType	  = QGraphicsItem::UserType + 5,
		InputBlockType    = QGraphicsItem::UserType + 6,
		OutputBlockType   = QGraphicsItem::UserType + 7,
		IOBlockType   = QGraphicsItem::UserType + 8
	};
};

typedef std::pair<QString, _2Real::app::BundleHandle>	BlockInstancingInfo;
typedef std::vector<BlockInstancingInfo>				BlockInstancingInfos;

class DataflowEngineManager
{
public:
	~DataflowEngineManager();
	static DataflowEngineManager*		getInstance();
	QStringList							loadBundles();
	UbComposition*						addComposition();
	void								removeComposition(UbComposition* comp);
	UbComposition*						getComposition();

	const BlockInstancingInfos&			getBlockInstancingInfos(); 
	_2Real::app::Engine&				getEngine();
private:
	DataflowEngineManager();
	QStringList findBundlesInDirectory();

	static DataflowEngineManager*			m_pInstance;
	_2Real::app::Engine&					m_Engine;
	BlockInstancingInfos					m_BlockInstancingInfos;
	std::vector<UbComposition*>				m_UbCompositions;
};