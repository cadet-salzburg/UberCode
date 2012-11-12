#include "UbSliderUiBlock.h"
#include <QPalette>
namespace Uber {
	UbSliderUiBlock::UbSliderUiBlock( QGraphicsItem *parent )
		:UbAbstractBlock(parent)
	{
		init();
	}

	UbSliderUiBlock::~UbSliderUiBlock(void)
	{

	}

	void UbSliderUiBlock::init()
	{
		m_Slider = new QSlider(Qt::Vertical);
		m_Slider->setMinimum(0);
		m_Slider->setMaximum(1);
		m_ProxyWidget = new QGraphicsProxyWidget(this);
		m_Node = new UbInletNode(this);
		m_ProxyWidget->setWidget(m_Slider);
		m_ProxyWidget->setMinimumWidth(20);
		QRectF  sliderRect = m_ProxyWidget->boundingRect();
		m_ProxyWidget->setPos( -sliderRect.width()/2.f+1.f, -sliderRect.height()/2.f + m_CornerRadius/2.f );
		QPalette pal  = m_ProxyWidget->palette();
		pal.setColor( QPalette::Background, m_Color );
		m_ProxyWidget->setPalette(pal);
		m_Width =sliderRect.width() + 15;
		m_Height= sliderRect.height() + 20;
		configureNodes();
		constructPath();
		update();
	}

	void UbSliderUiBlock::configureNodes()
	{
		//QPointF pos = QPointF(0, -m_Height/2.f) + m_Node->getRadius()*QPointF(1.f,1.f) + QPointF(m_CornerRadius, m_CornerRadius);
		QPointF pos = QPointF(0, -m_Height/2.f) +  m_Node->getHeight()*QPointF(0.f,2.f);
		m_Node->setPos(pos);
	}
	void UbSliderUiBlock::nodeIsSet()
	{
		connect( m_Slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	}
	void UbSliderUiBlock::setValue(int value)
	{
		m_Node->getHandle().setValue( value );
	}
}