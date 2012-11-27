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
	QMap<int,int>&							m_InterfaceIdData;
	public slots:
		void open();
		void save();
};