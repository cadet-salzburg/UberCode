#pragma once
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QPoint>
#include <iostream>

class UbGraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	UbGraphicsView( QWidget * parent = 0 );
	UbGraphicsView( QGraphicsScene * scene, QWidget * parent = 0 );
	void contextMenuEvent( QContextMenuEvent *event );
protected:
	virtual void resizeEvent( QResizeEvent *event );
protected:
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event)
	{
		std::cout << "Drag Occured" << std::endl;
	};
	void dragMoveEvent(QGraphicsSceneDragDropEvent* event){};
	void dropEvent(QGraphicsSceneDragDropEvent* event){};
	//virtual void dragEnterEvent(QDragEnterEvent *event)
	//{
	//	std::cout << "Drag Occured" << std::endl;
	//	 event->acceptProposedAction();
	//}
	//virtual void dropEvent(QDropEvent *event)
	//{
	//	std::cout << " Drop Occured" << std::endl;
	//}
private:
	QPoint m_EventPos; 
	void initialize();
private slots:
	void addIOBlock();
};

