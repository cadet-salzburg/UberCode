#include <QLabel>
#include <QPen>
#include <QPainter>
#include <QSizePolicy>
#include <iostream>
#include "UbIOBlock.h"
#include "_2RealDatatypes.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"


#include <QGRoupBox>
#include <QLineEdit>
#include <QHBoxLayout>

using namespace std;
using namespace _2Real;

UbIOBlock::UbIOBlock( QGraphicsItem *parent )
	:QGraphicsObject(parent)
	,m_Width(140)
	,m_Height(70)
	,m_CornerRadius(8)
	,m_Node(NULL)
{
	constructPath();
}

UbIOBlock::~UbIOBlock(void)
{

}
void UbIOBlock::receiveData(_2Real::app::AppData const& data)
{
	//keep the data around as long as it and it's underlying pointers are needed, it is internally a share_ptr !!!!!
	emit sendData( data );			// since a copy of the incoming data is emitted
	// it does not matter how much time passes 
	// between this and 'updateData':
	// the data will for sure be alive when the pixmap is updated
}

QRectF	UbIOBlock::boundingRect() const
{
	return QRectF( QPointF(-m_Width/2., -m_Width/2.), QPointF( m_Width/2.,m_Width/2.) );
}

void UbIOBlock::constructPath()
{
	//m_ProxyWidget = new QGraphicsProxyWidget(this);
	m_ProxyWidget = new QGraphicsProxyWidget(this);
	QPainterPath path;
	path.addRoundedRect( -m_Width/2, -m_Height/2, m_Width, m_Height, m_CornerRadius, m_CornerRadius );
	m_Path = path;
	m_Node  = new UbNode(this);

	QPointF pos = QPointF(-m_Width/2.f, -m_Height/2.f) + m_Node->getRadius()*QPointF(1.f,1.f) + QPointF(m_CornerRadius, m_CornerRadius);
	m_Pos =  pos + 1*(2*m_Node->getRadius()+4)*QPointF(1.f, 0.f);
	m_Node->setPos( m_Pos );

	QPointF ppos = m_Node->pos();
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);


}
void UbIOBlock::setInputNode( const _2Real::app::OutletHandle& handle )
{
	//if ( m_Node )
	//	delete m_Node;
	m_Node = new UbOutletNode( this, handle );
	m_Node->setPos( m_Pos );
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
		{
			m_ValueWidget = new QLabel();
			//m_ProxyWidget->setWidget( dynamic_cast<QLabel*>(m_ValueWidget) );
			dynamic_cast<QLabel*>(m_ValueWidget)->setText("Something");
			 //QGroupBox *groupBox = new QGroupBox("Contact Details");
			 QWidget *widget = new QWidget;
			 //QLabel *numberLabel = new QLabel("Telephone number");
			 //QLineEdit *numberEdit = new QLineEdit;
			 QHBoxLayout *layout = new QHBoxLayout;
			 layout->addWidget( dynamic_cast<QLabel*>(m_ValueWidget));
			 widget->setLayout(layout);
			 //QGraphicsScene scene;
			// QGraphicsProxyWidget *proxy = new  QGraphicsProxyWidget(this);
			 //proxy->setLayout(layout);
			 m_ProxyWidget->setWidget( widget );
			 //QGraphicsView view(&scene);
			 // view.show();





		}

		// register data callback for _2Real Framework
		handle.registerToNewData( *this, &UbIOBlock::receiveData );

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
void UbIOBlock::setOutputNode(const  _2Real::app::InletHandle& handle )
{
	//if ( m_Node )
	//	delete m_Node;
	m_Node = new UbInletNode( this, handle );
	m_Node->setPos( m_Pos );
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
		{
			m_ValueWidget = new QLabel();
			m_ProxyWidget->setWidget( dynamic_cast<QLabel*>(m_ValueWidget) );
			m_ProxyWidget->setMinimumSize(140, 80);
			m_ProxyWidget->setPos(0,0);
			 dynamic_cast<QLabel*>(m_ValueWidget)->setText("Something");
			 //QSizePolicy sizePolicy;
			 //sizePolicy.setHorData(QSizePolicy::Minimum);
			 dynamic_cast<QLabel*>(m_ValueWidget)->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
			 dynamic_cast<QLabel*>(m_ValueWidget)->setMinimumSize(80, 60);
		}






		// register data callback for _2Real Framework
		//handle.registerToNewData( *this, &UbOutputBlock::receiveData );

		// note that the moc is quite pedantic with regards to namespaces:
		// you must use the full symbol name here & in the function implementations
		// data between threads has to be sent around through signal and slots in QT !!!!
		//qRegisterMetaType< _2Real::app::AppData >( "_2Real::app::AppData" );
		//connect( this, SIGNAL( sendData( _2Real::app::AppData ) ), this, SLOT( updateData( _2Real::app::AppData ) ) );
	}
	catch(Exception& e)
	{
		cout << e.message() << e.what() << std::endl;
	}


}
void UbIOBlock::updateData(_2Real::app::AppData data) 
{
	if ( m_Node && m_Node->type() == QGraphicsItem::UserType + UberCodeItemType::OutputNodeType )
	{
		UbOutletNode *m_OutletNode = 0;
		m_OutletNode =  dynamic_cast<UbOutletNode*>(m_Node);
		//UbInletNode  *m_InletNode = 0;
		//if ( m_Node->type() == MainWindow::InputNodeType )
		//{
		//	m_InletNode =  dynamic_cast<UbInletNode*>(m_Node);
		//} 
		//else if ( m_Node->type() == MainWindow::OutputNodeType )
		//{
		//	m_OutletNode =  dynamic_cast<UbOutletNode*>(m_Node);
		//}

		try
		{
			if( m_OutletNode->getHandle().getTypename() == "image" )
			{
				//Image const& img = data.getData< Image >();
				//dynamic_cast<QGlTextureImage*>(m_ValueWidget)->updateTexture( img.getWidth(), img.getHeight(), img.getNumberOfChannels(), img.getImageType(), img.getData() );
			}
			else if( m_OutletNode->getHandle().getTypename() == "short" ||  m_OutletNode->getHandle().getTypename() == "unsigned short" ||			// handle numeric types all the same and display the number as string '1234'
				m_OutletNode->getHandle().getTypename() == "int" ||    m_OutletNode->getHandle().getTypename() == "unsigned int" || 
				m_OutletNode->getHandle().getTypename() == "long" ||   m_OutletNode->getHandle().getTypename() == "unsigned long" ||
				m_OutletNode->getHandle().getTypename() == "float" ||  m_OutletNode->getHandle().getTypename() == "double" ||
				m_OutletNode->getHandle().getTypename() == "number" || m_OutletNode->getHandle().getTypename() == "point" ||  
				m_OutletNode->getHandle().getTypename() == "string")
			{
				dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString(data.getDataAsString()));
			}
			else if( m_OutletNode->getHandle().getTypename() == "char")
			{
				stringstream strTmp;
				strTmp << data.getDataAsString() << " : " << data.getData<char>();
				dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString( strTmp.str()));
			}
			else if(m_OutletNode->getHandle().getTypename() == "unsigned char")
			{
				stringstream strTmp;
				strTmp << data.getDataAsString() << " : " << data.getData<unsigned char>();
				dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString( strTmp.str()));
			}
			else if( m_OutletNode->getHandle().getTypename() == "bool" )
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
void UbIOBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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