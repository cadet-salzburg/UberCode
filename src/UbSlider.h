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
#include "UbInputBlock.h"
#include <QGraphicsProxyWidget>
#include "UbNode.h"
#include "UbInletNode.h"
#include <QSlider>
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"

namespace Uber {
	class UbSlider : public UbInputBlock
	{
		Q_OBJECT
	public:
		UbSlider( QGraphicsItem *parent );
		virtual	~UbSlider(void);
		enum { Type = SliderBlockType };

		virtual	int							type() const { return Type; }
		void								initPropertyEditor();
	public slots:
		void								setValue(int value);
		void								valueChanged(QtProperty *property, double value);
	protected:	
		virtual void						arrangeNodes();
	private:
		void								init();	
		QSlider*							m_Slider;
		qreal								m_MinimumValue;
		qreal								m_MaximumValue;
		qreal								m_CurrentValue;
		QtTreePropertyBrowser				*m_PropertyEditor;
		QtDoublePropertyManager				*m_DoubleManager;
		QMap<QtProperty *, QString>			propertyToId;
		QMap<QString, QtProperty *>			idToProperty;
		QMap<QString, bool>					idToExpanded;
	};
}