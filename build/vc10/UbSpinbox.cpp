#include "UbSpinbox.h"
#include <QPalette>
namespace Uber {
	UbSpinbox::UbSpinbox( QGraphicsItem *parent )
		:UbInputBlock(parent)
	{
		//m_Node = new UbInletNode(this);
		init();
		setName(QString("SpinBox"));
	}

	UbSpinbox::~UbSpinbox(void)
	{

	}

	void UbSpinbox::init()
	{
		m_SpinBox = new QSpinBox;
		m_SpinBox->setMinimum(0);
		m_SpinBox->setMaximum(1);
		m_ProxyWidget->setWidget(m_SpinBox);
		m_ProxyWidget->setMinimumWidth(20);
		QRectF  spinBoxRect = m_ProxyWidget->boundingRect();
		m_ProxyWidget->setPos( -spinBoxRect.width()/2.f+1.f, -spinBoxRect.height()/2.f + m_CornerRadius/2.f );
		QPalette pal  = m_ProxyWidget->palette();
		pal.setColor( QPalette::Background, m_Color );
		m_ProxyWidget->setPalette(pal);
		m_Width =spinBoxRect.width() + 15;
		m_Height= spinBoxRect.height() + 20;
		arrangeNodes();
		constructPath();
		update();
	}

	void UbSpinbox::arrangeNodes()
	{
		UbNodeRef node  = m_Node.toStrongRef();
		if ( node )
		{
			QPointF pos = QPointF(0, -m_Height/2.f) +  node->getHeight()*QPointF(0.f,2.f);
			node->setPos(pos);
		}
	}

	void UbSpinbox::blockIsConnected()
	{
		connect( m_SpinBox, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	}
	void UbSpinbox::setValue(int value)
	{
		qSharedPointerCast<UbInletNode>(m_Node)->getHandle().setValue( value );
	}
}