#include <QMenu>
#include "UbGraphicsView.h"
#include "UbImageView.h"
#include "UbSlider.h"
#include "UbSpinbox.h"
#include "UbRadiobutton.h"
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

	void UbGraphicsView::addImageBlock()
	{
		UbImageView *imageBlock = new UbImageView(0);
		imageBlock->setPos( m_EventPos );
		DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(imageBlock);
	}
	void UbGraphicsView::addSliderBlock()
	{
		UbSlider *sliderBlock = new UbSlider(0);
		sliderBlock->setPos( m_EventPos );
		DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(sliderBlock);
	}
	void UbGraphicsView::addSpinBoxBlock()
	{
		UbSpinbox *spinboxBlock = new UbSpinbox(0);
		spinboxBlock->setPos( m_EventPos );
		DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(spinboxBlock);
	}

	void UbGraphicsView::addRadioButtonBlock()
	{
		UbRadiobutton* radioButton = new UbRadiobutton(0);
		radioButton->setPos( m_EventPos );
		DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(radioButton);
	}

	void UbGraphicsView::contextMenuEvent( QContextMenuEvent *event )
	{
		QMenu menu(this);
		m_EventPos = event->pos();
		//
		QAction *imageBlockAction( new QAction("Add ImageBlock", this));
		connect( imageBlockAction, SIGNAL(triggered()), this, SLOT( addImageBlock() ) );
		menu.addAction( imageBlockAction );
		//
		QAction *sliderBlockAction( new QAction("Add SliderBlock", this));
		connect( sliderBlockAction, SIGNAL(triggered()), this, SLOT( addSliderBlock() ) );
		menu.addAction( sliderBlockAction );
		//
		QAction *spinboxBlockAction( new QAction("Add SpinBoxBlock", this));
		connect( spinboxBlockAction, SIGNAL(triggered()), this, SLOT( addSpinBoxBlock() ) );
		menu.addAction( spinboxBlockAction );
		//
		QAction *radiobuttonBlockAction( new QAction("Add RadioButtonBlock", this));
		connect( radiobuttonBlockAction, SIGNAL(triggered()), this, SLOT( addRadioButtonBlock() ) );
		menu.addAction( radiobuttonBlockAction );
		//
		menu.exec(event->globalPos());
		std::cout << " The x-position is: " << m_EventPos.x() << " and the y-position is: " << m_EventPos.y() << std::endl; 
	}



}