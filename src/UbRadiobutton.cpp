#include "UbRadiobutton.h"
#include <QPalette>
namespace Uber {
	UbRadiobutton::UbRadiobutton( QGraphicsItem *parent )
		:UbInputBlock(parent)
	{
		init();
		setName(QString("Radiobutton"));
	}

	UbRadiobutton::~UbRadiobutton(void)
	{

	}

	void UbRadiobutton::init()
	{
		m_Button = new QRadioButton;
		m_ProxyWidget->setWidget(m_Button);
		m_ProxyWidget->setMinimumWidth(20);
		QRectF  buttonRect = m_ProxyWidget->boundingRect();
		m_ProxyWidget->setPos( -buttonRect.width()/2.f+1.f, -buttonRect.height()/2.f + m_CornerRadius/2.f );
		QPalette pal  = m_ProxyWidget->palette();
		pal.setColor( QPalette::Background, m_Color );
		m_ProxyWidget->setPalette(pal);
		m_Width =buttonRect.width() + 25;
		m_Height= buttonRect.height() + 30;
		arrangeNodes();
		constructPath();
		update();
	}

	void UbRadiobutton::arrangeNodes()
	{
		UbNodeRef node = m_Node.toStrongRef();
		if ( node )
		{
			QPointF pos = QPointF(0, -m_Height/2.f) +  node->getHeight()*QPointF(0.f,2.f);
			node->setPos(pos);
		}
	}

	void UbRadiobutton::blockIsConnected()
	{
		connect( m_Button, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	}
	void UbRadiobutton::setValue(int value)
	{
		UbNodeRef node = m_Node.toStrongRef();
		if ( node )
		{
			qSharedPointerCast<UbInletNode>(node)->getHandle().setValue( value );
		}
	}
}