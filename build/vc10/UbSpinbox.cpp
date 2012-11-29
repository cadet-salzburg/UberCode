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
#include "UbSpinbox.h"
#include <QPalette>
namespace Uber {
	UbSpinbox::UbSpinbox( QGraphicsItem *parent )
		:UbInputBlock(parent),
		m_MinimumValue(3),
		m_MaximumValue(15),
		m_CurrentValue(3),
		m_Step(2)
	{
		init();
		setName(QString("SpinBox"));
		connect( m_SpinBox, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
		initPropertyEditor();
	}

	UbSpinbox::~UbSpinbox(void)
	{
		delete m_PropertyEditor;
	}

	void UbSpinbox::init()
	{
		m_SpinBox = new QSpinBox;
		m_SpinBox->setMinimum(m_MinimumValue);
		m_SpinBox->setMaximum(m_MaximumValue);
		m_SpinBox->setSingleStep(m_Step);
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
	void UbSpinbox::initPropertyEditor()
	{
		m_PropertyEditor = new QtTreePropertyBrowser();
		QtSpinBoxFactory *spinBoxFactory = new QtSpinBoxFactory(this);
		m_IntManager = new QtIntPropertyManager(this);
		m_PropertyEditor->setFactoryForManager(m_IntManager, spinBoxFactory);
		connect(m_IntManager, SIGNAL(valueChanged(QtProperty *, int)), this, SLOT(propertyValueChanged(QtProperty *, int)));
		//
		m_ValueProperty= m_IntManager->addProperty(tr("Value"));
		m_IntManager->setRange(m_ValueProperty, m_MinimumValue, m_MaximumValue);
		m_IntManager->setValue(m_ValueProperty, m_CurrentValue);
		m_PropertyEditor->addProperty(m_ValueProperty);
		m_MinimumValueProperty = m_IntManager->addProperty(tr("Minimum"));
		m_IntManager->setValue(m_MinimumValueProperty, m_MinimumValue);
		m_PropertyEditor->addProperty(m_MinimumValueProperty);
		m_MaximumValueProperty = m_IntManager->addProperty(tr("Maximum"));
		m_IntManager->setValue(m_MaximumValueProperty,m_MaximumValue);
		m_PropertyEditor->addProperty(m_MaximumValueProperty);
		m_StepProperty = m_IntManager->addProperty(tr("Step"));
		m_IntManager->setValue(m_StepProperty,m_Step);
		m_PropertyEditor->addProperty(m_StepProperty);
	}

	void UbSpinbox::arrangeNodes()
	{
		UbNodeRef node  = m_Node.toStrongRef();
		if ( node )
		{
			QPointF pos = QPointF(0, -m_Height/2.f) +  node->getHeight()*QPointF(0.f,0.8f);
			node->setPos(pos);
		}
	}

	void UbSpinbox::displayOptions()
	{
		m_PropertyEditor->show();
	}

	int UbSpinbox::getValue() const
	{
		return m_CurrentValue;
	}

	void UbSpinbox::setValue(int value)
	{
		if ( m_BlockIsConnected )
		{
			qSharedPointerCast<UbInletNode>(m_Node)->getHandle().setValue( uint(value) );
		}
	}

	void	UbSpinbox::propertyValueChanged(QtProperty *property, int value)
	{

	}
}