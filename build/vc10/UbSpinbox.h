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
#pragma once
#pragma once
#include "UbInputBlock.h"
#include "UbInletNode.h"
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"
#include <QSpinBox>

namespace Uber {
	class UbSpinbox : public UbInputBlock
	{
		Q_OBJECT
		Q_PROPERTY(int value READ getValue WRITE setValue)
	public:
		enum { Type = SpinBoxBlockType };
		UbSpinbox( QGraphicsItem *parent );
		virtual	~UbSpinbox(void);

		virtual	int					type() const { return Type; }
		void						initPropertyEditor();
		int							getValue() const;
		virtual void				displayOptions();

	public slots:
		void						setValue(int value);

	protected:
		virtual void				arrangeNodes();

	private:
		void						init();
		QSpinBox*					m_SpinBox;
		int							m_MinimumValue;
		int							m_MaximumValue;
		int							m_CurrentValue;
		int							m_Step;

		QtTreePropertyBrowser		*m_PropertyEditor;
		QtIntPropertyManager		*m_IntManager;
		QtProperty					*m_ValueProperty;
		QtProperty					*m_MinimumValueProperty;
		QtProperty					*m_MaximumValueProperty;
		QtProperty					*m_StepProperty;
	};
}