/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH
		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include "UbSlider.h"
#include <QPalette>
namespace Uber {
	UbSlider::UbSlider( QGraphicsItem *parent )
		:UbInputBlock(parent)
	{
		init();
		setName(QString("Slider"));
	}

	UbSlider::~UbSlider(void)
	{

	}

	void UbSlider::init()
	{
		m_Slider = new QSlider(Qt::Vertical);
		m_Slider->setMinimum(0);
		m_Slider->setMaximum(1);
		m_ProxyWidget->setWidget(m_Slider);
		m_ProxyWidget->setMinimumWidth(20);
		QRectF  sliderRect = m_ProxyWidget->boundingRect();
		m_ProxyWidget->setPos( -sliderRect.width()/2.f+1.f, -sliderRect.height()/2.f + m_CornerRadius/2.f );
		QPalette pal  = m_ProxyWidget->palette();
		pal.setColor( QPalette::Background, m_Color );
		m_ProxyWidget->setPalette(pal);
		m_Width =sliderRect.width() + 15;
		m_Height= sliderRect.height() + 20;
		arrangeNodes();
		constructPath();
		update();
	}

	void UbSlider::arrangeNodes()
	{
		UbNodeRef node = m_Node.toStrongRef();
		if ( node )
		{
			QPointF pos = QPointF(0, -m_Height/2.f) +  node->getHeight()*QPointF(0.f,2.f);
			node->setPos(pos);
		}
	}

	void UbSlider::blockIsConnected()
	{
		connect( m_Slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	}
	void UbSlider::setValue(int value)
	{
		UbNodeRef node = m_Node.toStrongRef();
		if ( node )
		{
			qSharedPointerCast<UbInletNode>(node)->getHandle().setValue( value );
		}
	}
}