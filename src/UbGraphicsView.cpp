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
#include <QMenu>
#include "UbGraphicsView.h"
#include "UbImageView.h"
#include "UbSlider.h"
#include "UbSpinbox.h"
#include "UbRadiobutton.h"
#include "UbPathBlock.h"
#include "DataflowEngineManager.h"

namespace Uber {
	UbGraphicsView::UbGraphicsView( QWidget * parent)
		:QGraphicsView(parent)
	{
		initialize();
		setMouseTracking(true);
		createContextMenu();


	}

	UbGraphicsView::UbGraphicsView( QGraphicsScene * scene, QWidget * parent )
		:QGraphicsView( scene, parent )
	{
		initialize();
		createContextMenu();
	}

	void UbGraphicsView::initialize()
	{
		setAlignment(Qt::AlignCenter );
		//setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
		setAcceptDrops(true);
		setSceneRect(0,0,640,480);
	}
	void UbGraphicsView::createContextMenu()
	{
		m_SignalMapper = new QSignalMapper(this);
		m_ContextMenu = new QMenu(this);
		//
		QAction *imageBlockAction( new QAction("Add ImageBlock", this));
		connect( imageBlockAction, SIGNAL(triggered()), m_SignalMapper, SLOT(map()) );
		m_ContextMenu->addAction( imageBlockAction );
		//
		QAction *pathBlockAction( new QAction("Add PathBlock", this));
		connect( pathBlockAction, SIGNAL(triggered()), m_SignalMapper, SLOT(map()) );
		m_ContextMenu->addAction( pathBlockAction );
		//
		QAction *radiobuttonBlockAction( new QAction("Add RadiobuttonBlock", this));
		connect( radiobuttonBlockAction, SIGNAL(triggered()), m_SignalMapper, SLOT(map()) );
		m_ContextMenu->addAction( radiobuttonBlockAction );
		//
		QAction *sliderBlockAction( new QAction("Add SliderBlock", this));
		connect( sliderBlockAction, SIGNAL(triggered()), m_SignalMapper, SLOT(map()) );
		m_ContextMenu->addAction( sliderBlockAction );
		//
		QAction *spinboxAction( new QAction("Add SpinboxBlock", this));
		connect( spinboxAction, SIGNAL(triggered()), m_SignalMapper, SLOT(map()) );
		m_ContextMenu->addAction( spinboxAction );
		//
		m_SignalMapper->setMapping(imageBlockAction, ImageBlockType );
		m_SignalMapper->setMapping(pathBlockAction, PathBlockType );
		m_SignalMapper->setMapping(radiobuttonBlockAction, RadioButtonBlockType );
		m_SignalMapper->setMapping(sliderBlockAction, SliderBlockType );
		m_SignalMapper->setMapping(spinboxAction, SpinBoxBlockType );
		//
		connect(m_SignalMapper, SIGNAL(mapped(int)), this, SLOT(addInterfaceBlock(int)));
	}
	void UbGraphicsView::resizeEvent( QResizeEvent * event )
	{
		//std::cout << "Resize event was called" << std::endl;
	}
	void UbGraphicsView::addInterfaceBlock( int type )
	{
		UbObject *block = DataflowEngineManager::getInstance()->createInterfaceBlock(type);
		if ( block )
		{
			block->setPos( m_EventPos );
			DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(block);
		}
	}

	void UbGraphicsView::contextMenuEvent( QContextMenuEvent *event )
	{
		m_EventPos = event->pos();

		// this fails oO
		// QGraphicsItem *item = DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->itemAt( m_EventPos );

		// stop context menu if there's sth under the mouse
		QList< QGraphicsItem * > list = DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->items();
		for ( QList< QGraphicsItem * >::iterator it = list.begin(); it != list.end(); ++it )
		{
			if ( ( **it ).isUnderMouse() )
			{
				return;
			}
		}

		m_ContextMenu->exec( event->globalPos() );
	}
}