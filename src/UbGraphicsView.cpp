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
#include "UbMultiInletNode.h"
#include "UbLinkController.h"

namespace Uber {
	UbGraphicsView::UbGraphicsView( QWidget * parent) :
		QGraphicsView( parent ), mBlockSignals( nullptr ), mBlockMenu( nullptr )
	{
		initialize();
		setMouseTracking(true);
		createContextMenu();
		//createBlockMenu();
	}

	UbGraphicsView::UbGraphicsView( QGraphicsScene * scene, QWidget * parent )
		:QGraphicsView( scene, parent )
	{
		initialize();
		createContextMenu();
		//createBlockMenu();
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

	void UbGraphicsView::bundleBlockAction( QObject *a )
	{
		UbGraphicsScene &scene = *DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene();
		UbLinkController &ctrl = *UbLinkController::getInstance();

		UbAction *action = static_cast< UbAction * >( a );
		if ( UbAction::DELETE_BUNDLE_BLOCK == action->code )
		{
			UbBundleBlock * block = static_cast< UbBundleBlock * >( action->item1 );
			UbBundleBlock const* b = block;

			for ( QVector< UbNodeRef >::const_iterator inletIt = b->getInlets().begin(); inletIt != b->getInlets().end(); ++inletIt )
			{
				ctrl.removeLinksWith( *inletIt );
			}

			for ( QVector< UbNodeRef >::const_iterator outletIt = b->getOutlets().begin(); outletIt != b->getOutlets().end(); ++outletIt )
			{
				ctrl.removeLinksWith( *outletIt );
			}

			scene.removeItem( block );

			// deleting this here causes problems for some reason
			// delete b;
			//block->getHandle().kill();

		}
		if ( UbAction::DELETE_INTERFACE_BLOCK == action->code )
		{
			UbInterfaceBlock * block = static_cast< UbInterfaceBlock * >( action->item1 );
			ctrl.removeLinksWith( block->getNode() );
			scene.removeItem( block );
		}
	}

	void UbGraphicsView::contextMenuEvent( QContextMenuEvent *event )
	{
		m_EventPos = event->pos();

		bool showBlockMenu = false;
		std::map< QAction *, UbAction * > actions;

		QList< QGraphicsItem * > list = DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->items();
		for ( QList< QGraphicsItem * >::iterator it = list.begin(); it != list.end(); ++it )
		{
			if ( ( **it ).isUnderMouse() )
			{
				showBlockMenu = true;

				if ( BundleBlockType == ( **it ).type() )
				{
					QString action = "Delete ";
					UbBundleBlock *b = static_cast< UbBundleBlock * >( *it );
					action.append( b->getBlockId() );

					UbAction *a = new UbAction();
					a->code = UbAction::DELETE_BUNDLE_BLOCK;
					a->item1 = *it;
					a->item2 = nullptr;

					QAction *deleteBlockAction( new QAction( action, this ) );
					actions[ deleteBlockAction ] = a;
				}
				if ( InterfaceBlockType <= ( **it ).type() )
				{
					QString action = "Delete ";
					UbInterfaceBlock *b = static_cast< UbInterfaceBlock * >( *it );
					action.append( b->getName() );

					UbAction *a = new UbAction();
					a->code = UbAction::DELETE_INTERFACE_BLOCK;
					a->item1 = *it;
					a->item2 = nullptr;

					QAction *deleteBlockAction( new QAction( action, this ) );
					actions[ deleteBlockAction ] = a;
				}
				//else if ( MultiInputNodeType == ( **it ).type() )
				//{
				//	//std::cout << "multi input node under mouse" << std::endl;

				//	UbMultiInletNode *n = static_cast< UbMultiInletNode * >( *it );

				//	QString actionAdd = "Add to ";
				//	actionAdd.append( n->getName() );

				//	UbAction *aAdd = new UbAction();
				//	aAdd->code = UbAction::ADD_MULTI_INLET;
				//	aAdd->item1 = *it;
				//	aAdd->item2 = nullptr;

				//	QAction *addToMultiinletAction( new QAction( actionAdd, this ) );
				//	actions[ addToMultiinletAction ] = aAdd;

				//	QString actionRemove = "Remove from ";
				//	actionRemove.append( n->getName() );

				//	UbAction *aRemove = new UbAction();
				//	aRemove->code = UbAction::REMOVE_MULTI_INLET;
				//	aRemove->item1 = *it;
				//	aRemove->item2 = nullptr;

				//	QAction *removeFromMultiinletAction( new QAction( actionRemove, this ) );
				//	actions[ removeFromMultiinletAction ] = aRemove;
				//}
				//else if ( InputNodeType == ( **it ).type() )
				//{
				//	//std::cout << "input node under mouse" << std::endl;
				//	UbInletNode *i = static_cast< UbInletNode * >( *it );
				//	for ( QList< UbNode * >::const_iterator lIt = i->getLinks().constBegin(); lIt != i->getLinks().constEnd(); ++lIt )
				//	{
				//		QString action = "Unlink from ";
				//		UbOutletNode *o = static_cast< UbOutletNode * >( *lIt );
				//		action.append( o->getName() );

				//		UbAction *a = new UbAction();
				//		a->code = UbAction::DELETE_LINK;
				//		a->item1 = i;
				//		a->item2 = o;

				//		QAction *addToMultiinletAction( new QAction( action, this ) );
				//		actions[ addToMultiinletAction ] = a;
				//	}
				//}
				//else if ( OutputNodeType == ( **it ).type() )
				//{
				//	//std::cout << "output node under mouse" << std::endl;
				//	UbOutletNode *o = static_cast< UbOutletNode * >( *it );
				//	for ( QList< UbNode * >::const_iterator lIt = o->getLinks().constBegin(); lIt != o->getLinks().constEnd(); ++lIt )
				//	{
				//		QString action = "Unlink from ";
				//		UbInletNode *i = static_cast< UbInletNode * >( *lIt );
				//		action.append( i->getName() );

				//		UbAction *a = new UbAction();
				//		a->code = UbAction::DELETE_LINK;
				//		a->item1 = i;
				//		a->item2 = o;

				//		QAction *addToMultiinletAction( new QAction( action, this ) );
				//		actions[ addToMultiinletAction ] = a;
				//	}
				//}
			}
		}

		// ok, this whol context thing is pretty fucked up :/
		// and i'm sure it could be done easier, however there's not enough time left

		if ( showBlockMenu )
		{
			delete mBlockSignals;
			delete mBlockMenu;
			mBlockSignals = new QSignalMapper( this );
			mBlockMenu = new QMenu( this );

			mBlockMenu;

			for ( std::map< QAction *, UbAction * >::iterator it = actions.begin(); it != actions.end(); ++it )
			{
				connect( it->first, SIGNAL( triggered() ), mBlockSignals, SLOT( map() ) );
				mBlockMenu->addAction( it->first );
				mBlockSignals->setMapping( it->first, static_cast< QObject * >( it->second ) );
			}

			connect( mBlockSignals, SIGNAL( mapped( QObject * ) ), this, SLOT( bundleBlockAction( QObject * ) ) );
			mBlockMenu->exec( event->globalPos() );
		}
		else m_ContextMenu->exec( event->globalPos() );
	}
}