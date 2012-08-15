#pragma once
#include "_2RealApplication.h"
#include "Composition.h"

#include <vector>

#include <QStringList>


namespace UberCodeItemType {
enum  {
		NodeType = 1,
		InputNodeType = 2,
		OutputNodeType = 3,
		AbstractBlockType = 4,
		BundleBlockType	  = 5,
		InputBlockType    = 6,
		OutputBlockType   = 7,
		IOBlockType   = 8
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
	Composition*						addComposition();
	void								removeComposition(Composition* comp);
	Composition*						getComposition();

	const BlockInstancingInfos&			getBlockInstancingInfos(); 

private:
	DataflowEngineManager();
	QStringList findBundlesInDirectory();

	static DataflowEngineManager*			m_pInstance;
	_2Real::app::Engine&					m_Engine;
 	BlockInstancingInfos					m_BlockInstancingInfos;
	std::vector<Composition*>				m_Compositions;
};