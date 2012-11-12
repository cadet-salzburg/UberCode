#include "UbSpinBoxUiBlock.h"
#include <QPalette>
namespace Uber {
	UbSpinBoxUiBlock::UbSpinBoxUiBlock( QGraphicsItem *parent )
		:UbAbstractBlock(parent)
	{
		init();
	}

	UbSpinBoxUiBlock::~UbSpinBoxUiBlock(void)
	{

	}

	void UbSpinBoxUiBlock::init()
	{
		m_SpinBox = new QSpinBox;
		m_SpinBox->setMinimum(0);
		m_SpinBox->setMaximum(1);
		m_ProxyWidget = new QGraphicsProxyWidget(this);
		m_Node = new UbInletNode(this);
		m_ProxyWidget->setWidget(m_SpinBox);
		m_ProxyWidget->setMinimumWidth(20);
		QRectF  spinBoxRect = m_ProxyWidget->boundingRect();
		m_ProxyWidget->setPos( -spinBoxRect.width()/2.f+1.f, -spinBoxRect.height()/2.f + m_CornerRadius/2.f );
		QPalette pal  = m_ProxyWidget->palette();
		pal.setColor( QPalette::Background, m_Color );
		m_ProxyWidget->setPalette(pal);
		m_Width =spinBoxRect.width() + 15;
		m_Height= spinBoxRect.height() + 20;
		configureNodes();
		constructPath();
		update();
	}

	void UbSpinBoxUiBlock::configureNodes()
	{
		//QPointF pos = QPointF(0, -m_Height/2.f) + m_Node->getRadius()*QPointF(1.f,1.f) + QPointF(m_CornerRadius, m_CornerRadius);
		QPointF pos = QPointF(0, -m_Height/2.f) +  m_Node->getHeight()*QPointF(0.f,2.f);
		m_Node->setPos(pos);
	}
	void UbSpinBoxUiBlock::nodeIsSet()
	{
		connect( m_SpinBox, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	}
	void UbSpinBoxUiBlock::setValue(int value)
	{
		m_Node->getHandle().setValue( value );
	}
}