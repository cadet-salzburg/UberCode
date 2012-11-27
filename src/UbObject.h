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
#include <QGraphicsObject>
#include <QColor>
#include <QPainter>
#include <QRect>
#include "UbTypes.h"

namespace Uber {
	class UbObject : public QGraphicsObject 
	{
	public:
		UbObject( QGraphicsItem *parent );
		virtual ~UbObject( void );
		enum { Type = ObjectType };

		virtual int						type() const { return Type; }
		virtual void					paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
		virtual QRectF					boundingRect() const;
		const qreal&					getWidth() const { return m_Width; }
		const qreal&					getHeight() const { return m_Height; }
		void							setColor(QColor color);
		void							setName( const QString& name );
		const QString&					getName() const;
	protected:

		virtual void					constructPath() = 0;
		
		QColor							m_Color;
		qreal							m_Width;
		qreal							m_Height;
		QPainterPath					m_Path;
		QString							m_Name;
	};
}