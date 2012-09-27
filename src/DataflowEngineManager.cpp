#include "DataflowEngineManager.h"
#include "SettingsManager.h"

#include <algorithm>
#include <QStringList>
#include <QDir>

using namespace _2Real;
using namespace _2Real::app;

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
		catch ( NotFoundException& )
		{
			std::cout << iter->toStdString() << " is not a _2Real bundle" << std::endl;
		}
		catch ( AlreadyExistsException& )
		{
			std::cout << iter->toStdString() << " has already been loaded." << std::endl;
		}
		catch ( ... )
		{
			std::cout << "Other exception" << std::endl;
		}
	}
	return validBundleNames;
}

Composition* DataflowEngineManager::addComposition()
{
	m_Compositions.push_back(new Composition());
	return m_Compositions.back();
}

Composition* DataflowEngineManager::getComposition()
{
	return m_Compositions.back();	// last one, this has to be changed when we want multiple compositions to be useable
}

void DataflowEngineManager::removeComposition(Composition* comp)
{
	std::vector<Composition*>::iterator it = std::find(m_Compositions.begin(), m_Compositions.end(), comp);
	if(it != m_Compositions.end())
	{
		delete (*it);
		m_Compositions.erase(it);
	}
}

const std::vector<BlockInstancingInfo>&	DataflowEngineManager::getBlockInstancingInfos()
{
	return m_BlockInstancingInfos;
}