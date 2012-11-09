#include <iostream>
#include <QHBoxLayout>
#include "UbImageUiBlock.h"
#include "datatypes/_2RealImage.h"
#include "UbGraphicsView.h"
#include "DataflowEngineManager.h"
#include <QPalette>

namespace Uber {
	UbImageUiBlock::UbImageUiBlock( QGraphicsItem *parent )
		:UbAbstractBlock(parent),
		m_Image( new UbImage() )
	{
		init();
		configureNodes();
	}

	UbImageUiBlock::~UbImageUiBlock(void)
	{

	}

	void UbImageUiBlock::init()
	{
		qRegisterMetaType< _2Real::app::AppData >( "_2Real::app::AppData" );
		connect( this, SIGNAL( sendData( _2Real::app::AppData ) ), this, SLOT( updateData( _2Real::app::AppData ) ) );
		m_ProxyWidget = new QGraphicsProxyWidget(this);
		m_Node = new UbOutletNode(this);
	}

	void UbImageUiBlock::configureNodes()
	{
		QPointF pos = QPointF(-m_Width/2.f, -m_Height/2.f) + m_Node->getRadius()*QPointF(1.f,1.f) + QPointF(m_CornerRadius, m_CornerRadius);
		m_Node->setPos(pos);
	}

	void UbImageUiBlock::receiveData(_2Real::app::AppData const& data)
	{
		emit sendData( data );
	}

	void UbImageUiBlock::nodeIsSet()
	{
		m_Node->getHandle().registerToNewData(*this, &UbImageUiBlock::receiveData );
		try
		{
			m_Image->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
			QWidget *widget = new QWidget();
			QHBoxLayout *layout = new QHBoxLayout;
			layout->addWidget( m_Image );
			widget->setLayout(layout);
			m_ProxyWidget->setWidget( widget );
			QSizeF sz = m_ProxyWidget->size();
			m_ProxyWidget->setPos(-sz.width()/2.f, -sz.height()/2.f);
			QPalette pal  = m_ProxyWidget->palette();
			pal.setColor( QPalette::Background, m_Color );
			m_ProxyWidget->setPalette(pal);
			m_Width = sz.width()+ 15;
			m_Height = sz.height()+ 15;
			constructPath();
			configureNodes();
			update();
			UbGraphicsView *graphicsView = DataflowEngineManager::getInstance()->getGraphicsView();
			if ( graphicsView )
				graphicsView->viewport()->update();
		}
		catch( _2Real::Exception& e)
		{
			std::cout << e.message() << e.what() << std::endl;
		}
	}

	void UbImageUiBlock::updateData(_2Real::app::AppData data) 
	{
		m_Data = data;
		try
		{
			if( m_Node->getHandle().getTypename() == "number image" )
			{
				_2Real::Image const& img = m_Data.getData< _2Real::Image >();
				QImage q( img.getData(), img.getWidth(), img.getHeight(), 3*img.getWidth(), QImage::Format_RGB888 );
				m_Image->setImage(q);
			}
			update();
		}
		catch(_2Real::Exception& e)
		{
			std::cout << e.message() << e.what() << std::endl;
		}
	}
}