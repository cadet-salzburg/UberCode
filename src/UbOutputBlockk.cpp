#include "UbOutputBlockk.h"
#include <QLabel>
#include "_2RealDatatypes.h"
#include <QPen>
#include <iostream>
#include <QPainter>
using namespace std;
using namespace _2Real;

UbOutputBlock::UbOutputBlock( QGraphicsItem *parent )
	:QGraphicsObject(parent)
	,m_Width(140)
	,m_Height(70)
	,m_CornerRadius(8)
	,m_InletNode(NULL)
{
	constructPath();
}

UbOutputBlock::~UbOutputBlock(void)
{

}
void UbOutputBlock::receiveData(_2Real::app::AppData const& data)
{
	//keep the data around as long as it and it's underlying pointers are needed, it is internally a share_ptr !!!!!
	emit sendData( data );			// since a copy of the incoming data is emitted
									// it does not matter how much time passes 
									// between this and 'updateData':
									// the data will for sure be alive when the pixmap is updated
}

QRectF	UbOutputBlock::boundingRect() const
{
	return QRectF( QPointF(-m_Width/2., -m_Width/2.), QPointF( m_Width/2.,m_Width/2.) );
}

void UbOutputBlock::constructPath()
{
	m_ProxyWidget = new QGraphicsProxyWidget(this);
	QPainterPath path;
	path.addRoundedRect( -m_Width/2, -m_Height/2, m_Width, m_Height, m_CornerRadius, m_CornerRadius );
	m_Path = path;
	m_InletNode  = new UbNode(this);

	QPointF pos = QPointF(-m_Width/2.f, -m_Height/2.f) + m_InletNode->getRadius()*QPointF(1.f,1.f) + QPointF(m_CornerRadius, m_CornerRadius);
	m_InletNode->setPos( pos + 1*(2*m_InletNode->getRadius()+4)*QPointF(1.f, 0.f) );


	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);


}
void UbOutputBlock::setInletNode(  _2Real::app::OutletHandle& handle )
{
	if ( m_InletNode )
		delete m_InletNode;
	m_InletNode = new UbOutletNode( this, handle );
	try
	{
		//if(handle.getTypename().find("skeleton")!=string::npos )
		//{
		//	m_ValueWidget = new QGlSkeletonWidget();
		//	dynamic_cast<QGlSkeletonWidget*>(m_ValueWidget)->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
		//	dynamic_cast<QGlSkeletonWidget*>(m_ValueWidget)->setMinimumSize(80, 60);
		//}
		//else if(handle.getTypename() == "image")
		//{
		//	m_ValueWidget = new QGlTextureImage();
		//	dynamic_cast<QGlTextureImage*>(m_ValueWidget)->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
		//	dynamic_cast<QGlTextureImage*>(m_ValueWidget)->setMinimumSize(80, 60);
		//}
		//else if(handle.getTypename().find("vector")!=string::npos || m_OutletHandle.getTypename().find("list")!=string::npos)
		//{
		//	m_ValueWidget = new QTextBrowser();
		//}
		//else
	//	if ( handle.
		//if ( handle.
		{
			m_ValueWidget = new QLabel();
			m_ProxyWidget->setWidget( dynamic_cast<QLabel*>(m_ValueWidget) );
		}
		
		// register data callback for _2Real Framework
		handle.registerToNewData( *this, &UbOutputBlock::receiveData );

		// note that the moc is quite pedantic with regards to namespaces:
		// you must use the full symbol name here & in the function implementations
		// data between threads has to be sent around through signal and slots in QT !!!!
		qRegisterMetaType< _2Real::app::AppData >( "_2Real::app::AppData" );
		connect( this, SIGNAL( sendData( _2Real::app::AppData ) ), this, SLOT( updateData( _2Real::app::AppData ) ) );
	}
	catch(Exception& e)
	{
		cout << e.message() << e.what() << std::endl;
	}


}

void UbOutputBlock::updateData(_2Real::app::AppData data) 
{
	if ( m_InletNode )
	{
	try
	{
		if( dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "number image" )
		{
			std::cout << "Update Data is Called for image" << std::endl;
			//Image const& img = data.getData< Image >();
			//dynamic_cast<QGlTextureImage*>(m_ValueWidget)->updateTexture( img.getWidth(), img.getHeight(), img.getNumberOfChannels(), img.getImageType(), img.getData() );
		}
		else if( dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "short" ||  dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "unsigned short" ||			// handle numeric types all the same and display the number as string '1234'
			 dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "int" ||    dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "unsigned int" || 
			 dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "long" ||   dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "unsigned long" ||
			 dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "float" ||  dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "double" ||
			 dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "number" || dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "point" ||  
			 dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "string")
		{
			dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString(data.getDataAsString()));
		}
		else if( dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "char")
		{
			stringstream strTmp;
			strTmp << data.getDataAsString() << " : " << data.getData<char>();
			dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString( strTmp.str()));
		}
		else if(dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "unsigned char")
		{
			stringstream strTmp;
			strTmp << data.getDataAsString() << " : " << data.getData<unsigned char>();
			dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString( strTmp.str()));
		}
		else if( dynamic_cast<UbOutletNode*>(m_InletNode)->getHandle().getTypename() == "bool" )
		{
			stringstream strTmp;
			bool bTmp =  data.getData<bool>();
			if(bTmp)
			{
				strTmp << bTmp << " : true";
			}
			else
			{
				strTmp << bTmp << " : false";
			}
			dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString( strTmp.str()));
		}
		update();
	}
	catch(Exception& e)
	{
		cout << e.message() << e.what() << std::endl;
	}
	}
}
void UbOutputBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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