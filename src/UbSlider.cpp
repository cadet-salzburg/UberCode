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
		:UbInputBlock(parent),
		m_MinimumValue(-10.),
		m_MaximumValue(40.),
		m_CurrentValue(0.)
	{
		init();
		setName(QString("Slider"));
		connect( m_Slider, SIGNAL(sliderMoved(int)), this, SLOT(setValue(int)));
		initPropertyEditor();
	}

	UbSlider::~UbSlider(void)
	{
		delete m_PropertyEditor;
	}

	void UbSlider::init()
	{
		m_Slider = new QSlider(Qt::Vertical);
		m_Slider->setMinimum(m_MinimumValue*100);
		m_Slider->setMaximum(m_MinimumValue*100);
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

	void UbSlider::initPropertyEditor()
	{
		m_PropertyEditor = new QtTreePropertyBrowser();
		QtDoubleSpinBoxFactory *doubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
		m_DoubleManager = new QtDoublePropertyManager(this);
		m_PropertyEditor->setFactoryForManager(m_DoubleManager, doubleSpinBoxFactory);
		connect(m_DoubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(propertyValueChanged(QtProperty *, double)));
		//
		m_ValueProperty= m_DoubleManager->addProperty(tr("Value"));
		m_DoubleManager->setRange(m_ValueProperty, -1000, 1000);
		m_DoubleManager->setValue(m_ValueProperty, m_CurrentValue);
		m_PropertyEditor->addProperty(m_ValueProperty);
		m_MinimumValueProperty = m_DoubleManager->addProperty(tr("Minimum"));
		m_DoubleManager->setValue(m_MinimumValueProperty, m_MinimumValue);
		m_PropertyEditor->addProperty(m_MinimumValueProperty);
		m_MaximumValueProperty = m_DoubleManager->addProperty(tr("Maximum"));
		m_DoubleManager->setValue(m_MaximumValueProperty,m_MaximumValue);
		m_PropertyEditor->addProperty(m_MaximumValueProperty);
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
	void UbSlider::displayOptions()
	{
		m_PropertyEditor->show();
	}
	qreal UbSlider::getValue() const
	{
		return m_CurrentValue;
	}
	void UbSlider::setValue(int value)
	{
		m_CurrentValue = value/100.;
		m_DoubleManager->setValue(m_ValueProperty, m_CurrentValue);
	}
	void UbSlider::propertyValueChanged(QtProperty *property, double value)
	{
		if ( property == m_ValueProperty)
		{
			m_CurrentValue = value;
			int newVal = value*100;
			std::cout << "How Many " << m_CurrentValue << std::endl;
			m_Slider->setValue(newVal);
			if ( m_BlockIsConnected )
			{
				UbNodeRef node = m_Node.toStrongRef();
				if ( node )
				{
					qSharedPointerCast<UbInletNode>(node)->getHandle().setValue( m_CurrentValue );
				}
			}
		} else if (property == m_MinimumValueProperty )
		{
			m_Slider->setMinimum((int)value*100);
		} else if (property == m_MaximumValueProperty)
		{
			m_Slider->setMaximum((int)value*100);
		}
	}
}