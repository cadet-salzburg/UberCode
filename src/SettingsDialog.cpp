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
#include "SettingsDialog.h"
#include "SettingsItemEditor.h"
#include "SettingsManager.h"

#include <QDir>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QSpacerItem>

SettingsDialog::SettingsDialog(QWidget *parent ) : QDialog( parent )
{
	this->setWindowFlags( Qt::WindowCloseButtonHint );
	initUI();
	loadSettings();
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::initUI()
{
	setWindowTitle("Choose Bundle Search Paths");

	QVBoxLayout* verticalLayoutOuter = new QVBoxLayout();
	QHBoxLayout* horizontalLayoutTop = new QHBoxLayout();
	QVBoxLayout* verticalLayoutTopRight = new QVBoxLayout();

	QPushButton* pushButtonAdd = new QPushButton( "+" );
	QPushButton* pushButtonRemove = new QPushButton( "-" );
	QDialogButtonBox* buttonBoxBottom = new QDialogButtonBox( QDialogButtonBox::Ok );;

	QSpacerItem* verticalSpacer = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );;

	m_OptionsWidget = new QListWidget();

	verticalLayoutOuter->addLayout( horizontalLayoutTop );
	verticalLayoutOuter->addWidget( buttonBoxBottom, 1, 0 );

	horizontalLayoutTop->addWidget( m_OptionsWidget );
	horizontalLayoutTop->addLayout( verticalLayoutTopRight );

	verticalLayoutTopRight->addWidget( pushButtonAdd, 0, 0 );
	verticalLayoutTopRight->addWidget( pushButtonRemove, 1, 0 );
	verticalLayoutTopRight->addSpacerItem( verticalSpacer );

	this->setLayout( verticalLayoutOuter );
	this->setModal( true );

	connect( buttonBoxBottom, SIGNAL(accepted()), this, SLOT( onAccept()) );
	connect( buttonBoxBottom, SIGNAL(rejected()), this, SLOT( reject()) );
	connect( pushButtonAdd,   SIGNAL(clicked()),  this, SLOT( onAddItemSlot()) );
	connect( pushButtonRemove,SIGNAL(clicked()),  this, SLOT( onRemoveSelectedItems()) );
}

void SettingsDialog::loadSettings()
{
	QStringList dirList = SettingsManager::getInstance()->getBundleDirectories();		// load from settings file

	for(int i=0; i<dirList.size(); i++)
	{
		if(!dirList.at(i).isEmpty())
		{
			SettingsItemEditor *m_ItemEditor = new SettingsItemEditor();
			m_ItemEditor->m_TextField->setText(dirList.at(i));
			QListWidgetItem *item = new QListWidgetItem();
			m_OptionsWidget->addItem(item);
			m_OptionsWidget->setItemWidget(item, m_ItemEditor );
		}
	}
}

void SettingsDialog::onAddItemSlot()
{
	QListWidgetItem* lastItem = m_OptionsWidget->item(m_OptionsWidget->count()-1);
	if(lastItem)
	{
		SettingsItemEditor *widget = dynamic_cast<SettingsItemEditor*>( m_OptionsWidget->itemWidget(lastItem) );
		if(widget)
		{
			QString l_data = widget->m_TextField->text();
			if(l_data.isEmpty())
			{
				return;
			}
		}
	}

	SettingsItemEditor *m_ItemEditor = new SettingsItemEditor();
	QListWidgetItem *item = new QListWidgetItem();
	m_OptionsWidget->addItem(item);
	m_OptionsWidget->setItemWidget(item, m_ItemEditor );
	m_ItemEditor->m_TextField->setFocus();
}

void SettingsDialog::onRemoveSelectedItems()
{
	qDeleteAll(m_OptionsWidget->selectedItems());
	update();
}

void SettingsDialog::onAccept()
{
	QStringList stringlist;

	for(int i=0; i<m_OptionsWidget->count(); i++)
	{
		QListWidgetItem* item = m_OptionsWidget->item(i);
		SettingsItemEditor *widget = dynamic_cast<SettingsItemEditor*>( m_OptionsWidget->itemWidget(item) );

		if(item && widget)
		{
			QString l_data = widget->m_TextField->text();
			QDir path(l_data);
			path.makeAbsolute();

			if(path.exists())
			{
				stringlist.push_back(l_data);
			}
			else
			{
				QMessageBox msg; 
				msg.warning(this, "Warning", "Please write a correct path");
				return; 
			}
		}
	}

	// write to settings file
	SettingsManager::getInstance()->setBundleDirectories(stringlist);

	QDialog::accept();
}

void SettingsDialog::closeEvent( QCloseEvent *event )
{
}

void SettingsDialog::showEvent( QShowEvent *event )
{
	if(m_OptionsWidget->count()<1)
	{
		SettingsItemEditor *m_ItemEditor = new SettingsItemEditor();
		QListWidgetItem *item = new QListWidgetItem();
		m_OptionsWidget->addItem(item);
		m_OptionsWidget->setItemWidget(item, m_ItemEditor );
	}
}