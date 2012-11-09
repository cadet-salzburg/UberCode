#include "UbSliderUiBlock.h"
#include <QSlider>
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
		QSlider *slider = new QSlider(Qt::Vertical);
		m_ProxyWidget = new QGraphicsProxyWidget(this);
		m_ProxyWidget->setWidget(slider);
		QRectF  sliderRect = m_ProxyWidget->boundingRect();
		m_ProxyWidget->setPos( -sliderRect.width()/2.f, -sliderRect.height()/2.f );
		QPalette pal  = m_ProxyWidget->palette();
		pal.setColor( QPalette::Background, m_Color );
		m_ProxyWidget->setPalette(pal);
		m_Width =sliderRect.width() + 15;
		m_Height= sliderRect.height() + 15;
		constructPath();
		update();
	}
}