#include <QMenu>
#include "UbGraphicsView.h"
#include "UbIOBlock.h"
#include "DataflowEngineManager.h"

namespace Uber {
	UbGraphicsView::UbGraphicsView( QWidget * parent)
		:QGraphicsView(parent)
	{
		initialize();
	}

	UbGraphicsView::UbGraphicsView( QGraphicsScene * scene, QWidget * parent )
		:QGraphicsView( scene, parent )
	{
		initialize();
	}

	void UbGraphicsView::initialize()
	{
		setAlignment(Qt::AlignCenter );
		//setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
		setAcceptDrops(true);
		setSceneRect(0,0,640,480);
	}
	void UbGraphicsView::resizeEvent( QResizeEvent * event )
	{
		std::cout << "Resize event was called" << std::endl;
	}

	void UbGraphicsView::addIOBlock( )
	{
		std::cout << "Add IOBlock was triggered" << std::endl;
		UbIOBlock *ioblock = new UbIOBlock(0);
		ioblock->setPos( m_EventPos );
		DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(ioblock);
	}

	void UbGraphicsView::contextMenuEvent( QContextMenuEvent *event )
	{
		QMenu menu(this);
		m_EventPos = event->pos();
		QAction *action( new QAction("Add IOBlock", this));
		connect( action, SIGNAL(triggered()), this, SLOT( addIOBlock() ) );
		menu.addAction( action );
		menu.exec(event->globalPos());
		std::cout << " The x-position is: " << m_EventPos.x() << " and the y-position is: " << m_EventPos.y() << std::endl; 
	}
}