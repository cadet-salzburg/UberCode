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