#include <iostream>
#include <QLabel>
#include <QPen>
#include <QPainter>
#include <QSizePolicy>
#include <QGRoupBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include "UbIOBlock.h"
#include "_2RealDatatypes.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
#include "UbImage.h"
#include "DataflowEngineManager.h"

using namespace std;
using namespace _2Real;

namespace Uber {
	UbIOBlock::UbIOBlock( QGraphicsItem *parent )
		:UbAbstractBlock(parent)
		,m_Width(140)
		,m_Height(70)
		,m_CornerRadius(8)
		,m_Node(NULL)
		,m_IsInputBlock(false)
	{
		m_Node  = new UbNode(this);
		m_ProxyWidget = new QGraphicsProxyWidget(this);
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
		return QRectF( QPointF(-m_Width/2., -m_Height/2.), QPointF( m_Width/2.,m_Height/2.) );
	}

	void UbIOBlock::constructPath()
	{
		//m_ProxyWidget = new QGraphicsProxyWidget(this);
		QPainterPath path;
		path.addRoundedRect( -m_Width/2, -m_Height/2, m_Width, m_Height, m_CornerRadius, m_CornerRadius );
		m_Path = path;
		QPointF pos = QPointF(-m_Width/2.f, -m_Height/2.f) + m_Node->getRadius()*QPointF(1.f,1.f) + QPointF(m_CornerRadius, m_CornerRadius);
		m_Pos =  pos + 1*(2*m_Node->getRadius()+4)*QPointF(1.f, 0.f);
		m_Node->setPos( m_Pos );

		QPointF ppos = m_Node->pos();
		setFlag(QGraphicsItem::ItemIsMovable);
		setFlag(QGraphicsItem::ItemIsSelectable);
	}
	void UbIOBlock::setInputNode( const _2Real::app::OutletHandle& handle )
	{
		m_Node = new UbOutletNode( this, handle );
		m_Node->setPos( m_Pos );
		try
		{
			if ( handle.getTypename() == "int" )
			{
				m_ValueWidget = new QLabel();
				dynamic_cast<QLabel*>(m_ValueWidget)->setText("Something");
				QWidget *widget = new QWidget;
				QHBoxLayout *layout = new QHBoxLayout;
				layout->addWidget( dynamic_cast<QLabel*>(m_ValueWidget));
				widget->setLayout(layout);
				m_ProxyWidget->setWidget( widget );

			} else if ( handle.getTypename() == "number image" )
			{
				m_ValueWidget = new UbImage();
				dynamic_cast<UbImage*>(m_ValueWidget)->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
				//dynamic_cast<UbImage*>(m_ValueWidget)->setMinimumSize(80, 60);
				QWidget *widget = new QWidget();
				QHBoxLayout *layout = new QHBoxLayout;
				layout->addWidget( dynamic_cast<UbImage*>(m_ValueWidget));
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

			//m_ProxyWidget->setTransformOriginPoint(sz.width()/2.f, sz.height()/2.f );
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
		m_IsInputBlock = true;
		std::cout << "Setting an output node is not implemented yet" << std::endl;
		return;
	}

	void UbIOBlock::updateData(_2Real::app::AppData data) 
	{
		m_Data = data;
		if ( m_Node && m_Node->type() == Uber::OutputNodeType )
		{
			UbOutletNode *m_OutletNode = 0;
			m_OutletNode =  dynamic_cast<UbOutletNode*>(m_Node);


			try
			{
				if( m_OutletNode->getHandle().getTypename() == "number image" )
				{
					Image const& img = m_Data.getData< Image >();
					QImage q( img.getData(), img.getWidth(), img.getHeight(), 3*img.getWidth(), QImage::Format_RGB888 );
					//QImage q2 = q.copy();
					dynamic_cast<UbImage*>(m_ValueWidget)->setImage(q);
					m_ProxyWidget->update();
				}
				else if( m_OutletNode->getHandle().getTypename() == "short" ||  m_OutletNode->getHandle().getTypename() == "unsigned short" ||			// handle numeric types all the same and display the number as string '1234'
					m_OutletNode->getHandle().getTypename() == "int" ||    m_OutletNode->getHandle().getTypename() == "unsigned int" || 
					m_OutletNode->getHandle().getTypename() == "long" ||   m_OutletNode->getHandle().getTypename() == "unsigned long" ||
					m_OutletNode->getHandle().getTypename() == "float" ||  m_OutletNode->getHandle().getTypename() == "double" ||
					m_OutletNode->getHandle().getTypename() == "number" || m_OutletNode->getHandle().getTypename() == "point" ||  
					m_OutletNode->getHandle().getTypename() == "string")
				{
					dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString(m_Data.getDataAsString()));
				}
				else if( m_OutletNode->getHandle().getTypename() == "char")
				{
					stringstream strTmp;
					strTmp << m_Data.getDataAsString() << " : " << m_Data.getData<char>();
					dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString( strTmp.str()));
				}
				else if(m_OutletNode->getHandle().getTypename() == "unsigned char")
				{
					stringstream strTmp;
					strTmp << m_Data.getDataAsString() << " : " << m_Data.getData<unsigned char>();
					dynamic_cast<QLabel*>(m_ValueWidget)->setText(QString::fromStdString( strTmp.str()));
				}
				else if( m_OutletNode->getHandle().getTypename() == "bool" )
				{
					stringstream strTmp;
					bool bTmp =  m_Data.getData<bool>();
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
		//	update();
		Q_UNUSED(option)
		Q_UNUSED(widget)
		QPen pen;
		pen.setWidthF(1.f);
		pen.setBrush(Qt::black);	
		painter->setPen(pen);
		painter->setBrush(QColor(69,82,80));
		painter->drawPath( m_Path );
	}
	bool UbIOBlock::isInputBlock()
	{
		return m_IsInputBlock;
	}
}