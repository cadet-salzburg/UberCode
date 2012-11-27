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
#include "UbObject.h"
#include <iostream>
namespace Uber {
	UbObject::UbObject( QGraphicsItem *parent )
		:QGraphicsObject( parent ),
		m_Color(97,84,87),
		m_Width(0.f),
		m_Height(0.f)
	{

	}

	UbObject::~UbObject(void)
	{

	}

	void UbObject::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
	{
		Q_UNUSED(option)
		Q_UNUSED(widget)
		QPen pen;
		pen.setWidthF(0.5f);
		pen.setBrush(Qt::black);	
		painter->setPen(pen);
		painter->setBrush(m_Color);
		painter->drawPath( m_Path );
		std::cout << "The pos is: " << pos().x() << " " << pos().y() << std::endl;
	}

	QRectF UbObject::boundingRect() const
	{
		return QRectF( QPointF(-m_Width/2.-1 , -m_Height/2.-1), QPointF( m_Width/2.+1,m_Height/2.+1) );
	}

	void UbObject::setColor( QColor color )
	{
		m_Color = color;
	}
	void UbObject::setName( const QString& name )
	{
		m_Name = name;
	}

	const QString& UbObject::getName() const
	{
		return m_Name;
	}
}
