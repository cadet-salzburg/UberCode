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
#include "SettingsItemEditor.h"

#include <QToolButton>
#include <QLineEdit>
#include <QFrame>
#include <QFileDialog>
#include <QLayout>

SettingsItemEditor::SettingsItemEditor( QWidget* parent ) : QWidget( parent )
{
	init();
}

void SettingsItemEditor::init()
{
	m_TextField	= new QLineEdit;
	m_Button	= new QToolButton;
	m_Button->setText("...");
	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->setContentsMargins(0, 0, 0, 0);
	m_TextField->setBackgroundRole(QPalette::Base);

	hLayout->addWidget( m_TextField );
	hLayout->addWidget( m_Button );
	connect( m_Button, SIGNAL(clicked()), this, SLOT( openFileDialog() ));
	setLayout( hLayout );
}

QString SettingsItemEditor::getContent() const
{
	return m_TextField->text();
}

void SettingsItemEditor::setContent( const QString& content )
{
	m_TextField->setText( content );
}

void SettingsItemEditor::openFileDialog()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::DirectoryOnly);
	dialog.setOptions(QFileDialog::ShowDirsOnly);

	int result = dialog.exec();
	QStringList filename = dialog.selectedFiles();
	if(!filename.isEmpty() && result==1)
	{
		m_TextField->setText(filename[0]);
	}
}