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
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QSignalMapper>
#include <QPoint>
#include <iostream>
#include <QMenu>

namespace Uber {

	class UbAction : public QObject
	{
		Q_OBJECT
	public:

		enum Interaction
		{
			DELETE_BUNDLE_BLOCK,
			DELETE_INTERFACE_BLOCK,
			//DELETE_LINK,
			//ADD_MULTI_INLET,
			//REMOVE_MULTI_INLET,
		};

		Interaction			code;
		QGraphicsItem		*item1;
		QGraphicsItem		*item2;
	};

	class UbGraphicsView : public QGraphicsView
	{
		Q_OBJECT
	public:
		UbGraphicsView( QWidget * parent = 0 );
		UbGraphicsView( QGraphicsScene * scene, QWidget * parent = 0 );

		void				contextMenuEvent( QContextMenuEvent *event );
	protected:
		virtual void		resizeEvent( QResizeEvent *event );
		virtual	void		dragEnterEvent(QGraphicsSceneDragDropEvent* event)
		{ 
			//std::cout << "Drag Occurred" << std::endl; 
		}
		virtual	void		dragMoveEvent(QGraphicsSceneDragDropEvent* event){}
		virtual	void		dropEvent(QGraphicsSceneDragDropEvent* event){}
	private:
		void				initialize();
		void				createContextMenu();
		QPoint				m_EventPos;
		QSignalMapper		*m_SignalMapper;
		QMenu				*m_ContextMenu;

		QSignalMapper		*mBlockSignals;
		QMenu				*mBlockMenu;
	private slots:
		void				addInterfaceBlock( int type );
		void				bundleBlockAction( QObject *action );
	};
}