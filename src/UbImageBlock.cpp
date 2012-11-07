#include <iostream>
#include <QHBoxLayout>
#include "UbImageBlock.h"
#include "datatypes/_2RealImage.h"
#include "UbGraphicsView.h"
#include "DataflowEngineManager.h"

namespace Uber {
	UbImageBlock::UbImageBlock( QGraphicsItem *parent )
		:QGraphicsObject(parent),
		m_Node( new UbOutletNode(this) ),
		m_Image( new UbImage() ),
		m_ProxyWidget( new QGraphicsProxyWidget(this) ),
		m_Width(140),
		m_Height(70),
		m_CornerRadius(8)
	{
		qRegisterMetaType< _2Real::app::AppData >( "_2Real::app::AppData" );
		connect( this, SIGNAL( sendData( _2Real::app::AppData ) ), this, SLOT( updateData( _2Real::app::AppData ) ) );
		constructPath();
	}

	UbImageBlock::~UbImageBlock(void)
	{

	}

	QRectF	UbImageBlock::boundingRect() const
	{
		return QRectF( QPointF(-m_Width/2., -m_Height/2.), QPointF( m_Width/2.,m_Height/2.) );
	}

	void	UbImageBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
	{
		Q_UNUSED(option)
		Q_UNUSED(widget)
		QPen pen;
		pen.setWidthF(1.f);
		pen.setBrush(Qt::black);	
		painter->setPen(pen);
		painter->setBrush(QColor(69,82,80));
		painter->drawPath( m_Path );
	}

	void	UbImageBlock::constructPath()
	{
		//m_ProxyWidget = new QGraphicsProxyWidget(this);
		QPainterPath path;
		path.addRoundedRect( -m_Width/2, -m_Height/2, m_Width, m_Height, m_CornerRadius, m_CornerRadius );
		m_Path = path;
		QPointF pos = QPointF(-m_Width/2.f, -m_Height/2.f) + m_Node->getRadius()*QPointF(1.f,1.f) + QPointF(m_CornerRadius, m_CornerRadius);
		m_Pos =  pos + 1*(2*m_Node->getRadius()+4)*QPointF(1.f, 0.f);
		m_Node->setPos( m_Pos );
		setFlag(QGraphicsItem::ItemIsMovable);
		setFlag(QGraphicsItem::ItemIsSelectable);
	}

	void	UbImageBlock::updatePath()
	{

	}

	void UbImageBlock::setNode( UbOutletNode *node )
	{
		m_Node->setHandle( node->getHandle() );
		m_Node->setPos( m_Pos );
		m_Node->getHandle().registerToNewData(*this, &UbImageBlock::receiveData );
		try
		{
			if ( m_Node->getHandle().getTypename() == "number image" )
			{
				m_Image->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
				QWidget *widget = new QWidget();
				QHBoxLayout *layout = new QHBoxLayout;
				layout->addWidget( m_Image );
				widget->setLayout(layout);
				m_ProxyWidget->setWidget( widget );
			}
			QSizeF sz = m_ProxyWidget->size();
			m_ProxyWidget->setPos(-sz.width()/2.f, -sz.height()/2.f);
			m_Width = sz.width()+ 20;
			m_Height = sz.height()+ 20;
			constructPath();
			UbGraphicsView *graphicsView = DataflowEngineManager::getInstance()->getGraphicsView();
			if ( graphicsView )
				graphicsView->viewport()->update();
		}
		catch( _2Real::Exception& e)
		{
			std::cout << e.message() << e.what() << std::endl;
		}
	}
	void UbImageBlock::receiveData(_2Real::app::AppData const& data)
	{
		m_Data = data;
		emit sendData( m_Data );
	}
	void UbImageBlock::updateData(_2Real::app::AppData data) 
	{
		try
		{
			if( m_Node->getHandle().getTypename() == "number image" )
			{
				_2Real::Image const& img = m_Data.getData< _2Real::Image >();
				QImage q( img.getData(), img.getWidth(), img.getHeight(), 3*img.getWidth(), QImage::Format_RGB888 );
				m_Image->setImage(q);
				//m_ProxyWidget->update();
			}
			//update();
		}
		catch(_2Real::Exception& e)
		{
			std::cout << e.message() << e.what() << std::endl;
		}
	}
}