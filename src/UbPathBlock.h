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
#include <QWidget>
#include <QLineEdit>
namespace Uber {
	class UbPathBlock : public UbInputBlock
	{
		Q_OBJECT
	public:
		UbPathBlock( QGraphicsItem *parent );
		virtual ~UbPathBlock(void);
		enum { Type = PathBlockType };

		virtual int			type() const { return Type; }
		QString				getValue();
		virtual void		blockIsConnected();
	signals:
		void				editingFinished();
	public slots:
		void				buttonPressed();
		void				setValue( QString value );
		void				sendValue();

	protected:
		virtual void		arrangeNodes();

	private:
		void				init();
		//QLineEdit*			m_LineEdit;
		//QPushButton*		m_PushButton;
		//QHBoxLayout*		m_Layout;
		QWidget*			m_Widget;
		QString				m_Value;
		QLineEdit*			m_LineEdit;
	};
}