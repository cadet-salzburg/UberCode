#include "SettingsManager.h"
#include "_2RealApplication.h"

SettingsManager* SettingsManager::m_pInstance = nullptr;

SettingsManager::SettingsManager()
{
	m_pSettings = new QSettings("data\\Settings.ini", QSettings::IniFormat);
}

SettingsManager::~SettingsManager()
{
	if(m_pInstance!=nullptr)
	{
		delete m_pSettings;
		delete m_pInstance;
	}
}

SettingsManager* SettingsManager::getInstance()
{
	if(m_pInstance==nullptr)
	{
		m_pInstance = new SettingsManager();
	}
	return m_pInstance;
}

QStringList	SettingsManager::getBundleDirectories()
{
	return m_pSettings->value("BundleDirectories").toStringList();
}

void SettingsManager::setBundleDirectories(QStringList& paths)
{
	m_pSettings->setValue( "BundleDirectories", paths );
	m_pSettings->sync();
}