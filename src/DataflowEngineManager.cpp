#include "DataflowEngineManager.h"
#include "SettingsManager.h"

#include <algorithm>
#include <QStringList>
#include <QDir>

using namespace _2Real;
using namespace _2Real::app;
using namespace Uber;

DataflowEngineManager* DataflowEngineManager::m_pInstance = nullptr;

DataflowEngineManager::DataflowEngineManager() : m_Engine( Engine::instance() )
{

}

DataflowEngineManager::~DataflowEngineManager()
{
	if(m_pInstance!=nullptr)
	{
		delete m_pInstance;
	}
}

DataflowEngineManager*	DataflowEngineManager::getInstance()
{
	if(m_pInstance==nullptr)
	{
		m_pInstance = new DataflowEngineManager();
	}
	return m_pInstance;
}

QStringList DataflowEngineManager::findBundlesInDirectory()
{
	QStringList searchPaths = SettingsManager::getInstance()->getBundleDirectories();
	QStringList bundleFilenames;

	QStringList::const_iterator iter;
	for ( iter = searchPaths.constBegin(); iter != searchPaths.constEnd(); ++iter )
	{
		QDir dir(*iter);
		QStringList nameFilters;
		nameFilters << "*.dll" << "*.DLL" << "*.so" << "*.a" << "*.sl" << "*.dylib" << "*.bundle" ;
		QFileInfoList fileInfoList = dir.entryInfoList( nameFilters, QDir::Files | QDir::Readable );
		for ( QFileInfoList::const_iterator fileInfoIter = fileInfoList.constBegin(); fileInfoIter != fileInfoList.constEnd(); ++fileInfoIter )
		{
			bundleFilenames <<  fileInfoIter->canonicalFilePath();
		}
	}
	return bundleFilenames;
}

QStringList DataflowEngineManager::loadBundles()
{
	QStringList bundleNames = findBundlesInDirectory();
	QStringList validBundleNames;

	//Perform preloading and checking if the library is an ubercode one.
	for( QStringList::const_iterator iter = bundleNames.constBegin(); iter != bundleNames.constEnd(); ++iter )
	{
		try
		{
			std::string path = iter->toStdString();
			BundleHandle bundleHandle = m_Engine.loadBundle(path);
			BundleInfo bundleInfo = bundleHandle.getBundleInfo();
			BundleInfo::BlockInfos blocks = bundleInfo.exportedBlocks;

			BundleInfo::BlockInfos::const_iterator iter = blocks.begin();
			for ( ; iter!= blocks.end(); ++iter )
			{
				QString blockName = QString::fromStdString( iter->name );
				if(blockName != "contextblock")		// don't show or use context blocks in ubercode
				{
					validBundleNames << blockName;
					m_BlockInstancingInfos.push_back(std::make_pair(blockName, bundleHandle));
				}
			}
		}
		catch ( NotFoundException& e)
		{
			std::cout << e.what() << " " << e.message() << std::endl;
		}
		catch ( AlreadyExistsException& e)
		{
			std::cout << e.what()  << " " << e.message() << std::endl;
		}
		catch ( ... )
		{
			std::cout << "Other exception" << std::endl;
		}
	}
	return validBundleNames;
}

UbComposition* DataflowEngineManager::addComposition()
{
	m_UbCompositions.push_back(new UbComposition());
	return m_UbCompositions.back();
}

UbComposition* DataflowEngineManager::getComposition()
{
	return m_UbCompositions.back();	// last one, this has to be changed when we want multiple UbCompositions to be useable
}

void DataflowEngineManager::removeComposition(UbComposition* comp)
{
	std::vector<UbComposition*>::iterator it = std::find(m_UbCompositions.begin(), m_UbCompositions.end(), comp);
	if(it != m_UbCompositions.end())
	{
		delete (*it);
		m_UbCompositions.erase(it);
	}
}

const std::vector<BlockInstancingInfo>&	DataflowEngineManager::getBlockInstancingInfos()
{
	return m_BlockInstancingInfos;
}

_2Real::app::Engine& DataflowEngineManager::getEngine()
{
	return m_Engine;
}

QList<UbBundleBlock*> DataflowEngineManager::getBundleBlocks()
{
	QList<UbBundleBlock*> blocks;
	UbComposition* comp = getComposition();
	UbGraphicsScene* scene = comp->getGraphicsScene();
	QList<QGraphicsItem*> qgraphicsItems = scene->items();
	QList<QGraphicsItem*>::iterator iter = qgraphicsItems.begin();
	for( ;iter!=qgraphicsItems.end(); ++iter )
	{
		if ( (*iter)->type() == BundleBlockType )
		{
			//ToDo: Should we use QT qgraphicsitem_cast instead???
			UbBundleBlock *b = static_cast<UbBundleBlock*>(*iter);
			blocks.push_back(b);
		}
	}
	//TODO: Fix this with shared_ptr. It is quite easy to loose object
	return blocks;
}

QList<UbInletNode*>	DataflowEngineManager::getInlets( UbBundleBlock* block )
{
	QList<UbInletNode*> inlets;
	QList<QGraphicsItem *> children = block->childItems();
	QList<QGraphicsItem *>::iterator iter = children.begin();
	for (;iter!=children.end();++iter)
	{
		if ( (*iter)->type() == InputNodeType )
		{
			UbInletNode *n = static_cast<UbInletNode*>(*iter);
			inlets.push_back(n);
		}
	}
	return inlets;
}

QList<UbOutletNode*> DataflowEngineManager::getOutlets( UbBundleBlock* block )
{
	QList<UbOutletNode*> outlets;
	QList<QGraphicsItem *> children = block->childItems();
	QList<QGraphicsItem *>::iterator iter = children.begin();
	for (;iter!=children.end();++iter)
	{
		if ( (*iter)->type() == OutputNodeType )
		{
			UbOutletNode *n = static_cast<UbOutletNode*>(*iter);
			outlets.push_back(n);
		}
	}
	return outlets;
}