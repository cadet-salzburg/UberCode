#pragma once

#include <QSettings>
#include <QStringList>

class SettingsManager
{
public:
	~SettingsManager();
	static SettingsManager* getInstance();

	QStringList			getBundleDirectories();
	void				setBundleDirectories(QStringList& paths);

private:
	SettingsManager();

	static SettingsManager*		m_pInstance;
	QSettings*					m_pSettings;
};