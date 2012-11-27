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
#include "UbImage.h"
#include <iostream>

namespace Uber {
	UbImage::UbImage( QWidget* parent )
		: QGLWidget(parent)
	{

	}
	UbImage::~UbImage(void)
	{

	}
	void UbImage::setImage(const QImage& image)
	{
		makeCurrent();
		m_Image = image;
		update();
	}
	void UbImage::paintEvent(QPaintEvent*)
	{
		makeCurrent();	
		QPainter p( this );
		p.setRenderHint( QPainter::SmoothPixmapTransform, 1 );
		p.setBrush(QColor(69,82,80));
		p.drawImage( 0, 0, m_Image );
	}
}
