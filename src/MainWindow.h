#pragma once

#include <QMainWindow>

//windows
#include <iostream>
#include <tuple>

// ubercode includes
#include "ui_uberCode.h"
#include "SettingsDialog.h"
#include "BlockNavigationTreeWidget.h"

class MainWindow  : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow( );
	~MainWindow(void);
protected:
	bool event ( QEvent * event );

private:
	int										m_iInstances;
	std::string								m_strBlockName;
	Ui_MainWindow*							m_UiBuilderWindow;
	SettingsDialog*						    m_SettingsDialog;
	BlockNavigationTreeWidget*				m_BlockNavigationTreeWidget;
	QGraphicsView*							m_WorkbenchGraphicsView;
};