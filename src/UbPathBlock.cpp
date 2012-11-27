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
#include "UbPathBlock.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPalette>
#include <QFileDialog>
#include "UbInletNode.h"
#include <iostream>
namespace Uber {
	UbPathBlock::UbPathBlock( QGraphicsItem *parent )
		:UbInputBlock(parent)
	{
		init();
		setName(QString("PathBlock"));
	}

	UbPathBlock::~UbPathBlock(void)
	{

	}

	void	UbPathBlock::init()
	{

		QHBoxLayout *m_Layout = new QHBoxLayout;
		m_LineEdit = new QLineEdit;
		QPushButton *m_PushButton = new QPushButton("...",0);
		m_PushButton->setMaximumWidth(30);
		m_Widget = new QWidget;
		m_Layout->addWidget(m_LineEdit);
		m_Layout->addWidget(m_PushButton);
		m_Widget->setLayout(m_Layout);
		m_Widget->setMaximumWidth(170);
		m_Widget->setMaximumHeight(70);
		m_ProxyWidget->setWidget(m_Widget);
		m_Width = m_ProxyWidget->rect().width() + 10;
		m_Height = m_ProxyWidget->rect().height() + 5;
		m_ProxyWidget->setPos(-m_Width/2. + 5, -m_Height/2. +3);
		QPalette pal  = m_ProxyWidget->palette();
		pal.setColor( QPalette::Background, m_Color );
		m_ProxyWidget->setPalette(pal);
		connect(m_PushButton,SIGNAL(clicked()),this, SLOT(buttonPressed()));
		m_Inlets[0]->setPos(m_Inlets[0]->pos().x()+m_Width/2- 10, m_Inlets[0]->pos().y());
		arrangeNodes();
		constructPath();
		update();
	}

	void UbPathBlock::blockIsConnected()
	{
		connect( m_LineEdit, SIGNAL(textChanged(QString)), this, SLOT(setValue(QString)));
	}
	void UbPathBlock::buttonPressed()
	{
		m_FilePath = QFileDialog::getOpenFileName();
		m_LineEdit->setText(m_FilePath);

	}
	void UbPathBlock::setValue(QString value)
	{
		std::string path = value.toUtf8().constData();
		//std::cout << path << std::endl;
		UbNodeRef node = m_Node.toStrongRef();
		if ( node )
		{
			qSharedPointerCast<UbInletNode>(node)->getHandle().setValue( path );
		}
	}

	void UbPathBlock::arrangeNodes()
	{

	}

}