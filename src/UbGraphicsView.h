#pragma once
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QPoint>
#include <iostream>

namespace Uber {
	class UbGraphicsView : public QGraphicsView
	{
		Q_OBJECT
	public:
		UbGraphicsView( QWidget * parent = 0 );
		UbGraphicsView( QGraphicsScene * scene, QWidget * parent = 0 );

		void				contextMenuEvent( QContextMenuEvent *event );
	protected:
		virtual void		resizeEvent( QResizeEvent *event );
		virtual	void		dragEnterEvent(QGraphicsSceneDragDropEvent* event){ std::cout << "Drag Occurred" << std::endl; }
		virtual	void		dragMoveEvent(QGraphicsSceneDragDropEvent* event){}
		virtual	void		dropEvent(QGraphicsSceneDragDropEvent* event){}
	private:
		void				initialize();
		QPoint				m_EventPos; 
	private slots:
		void				addIOBlock();
	};
}