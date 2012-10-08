#pragma once
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QPoint>

class UbGraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	UbGraphicsView( QWidget * parent = 0 );
	UbGraphicsView( QGraphicsScene * scene, QWidget * parent = 0 );
	void contextMenuEvent( QContextMenuEvent *event );
protected:
	virtual void resizeEvent( QResizeEvent *event ); 
private:
	QPoint m_EventPos; 
	void initialize();
private slots:
	void addIOBlock();
};

