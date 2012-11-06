#pragma once
#include <QMainWindow>
//windows
#include <iostream>
#include <tuple>
// ubercode includes
#include "ui_uberCode.h"
#include "SettingsDialog.h"
#include "BlockNavigationTreeWidget.h"
#include "UbGraphicsView.h"

class MainWindow  : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow( );
	~MainWindow(void);
protected:
	bool event ( QEvent * event );
private:
	Ui_MainWindow*							m_UiBuilderWindow;
	SettingsDialog*						    m_SettingsDialog;
	BlockNavigationTreeWidget*				m_BlockNavigationTreeWidget;
	Uber::UbGraphicsView*					m_WorkbenchGraphicsView;
	public slots:
		void open();
		void save();
};