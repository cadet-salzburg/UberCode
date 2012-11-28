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
#include <QGraphicsItem>
namespace Uber {
	enum  {
		ObjectType				= QGraphicsItem::UserType + 1,
		AbstractBlockType		= QGraphicsItem::UserType + 2,
		BundleBlockType			= QGraphicsItem::UserType + 3,
		NodeType				= QGraphicsItem::UserType + 4,
		InputNodeType			= QGraphicsItem::UserType + 5,
		OutputNodeType			= QGraphicsItem::UserType + 6,
		MultiInputNodeType		= QGraphicsItem::UserType + 7,
		InterfaceBlockType		= QGraphicsItem::UserType + 8,
		InputBlockType			= QGraphicsItem::UserType + 9,
		OutputBlockType			= QGraphicsItem::UserType + 10,
		ImageBlockType			= QGraphicsItem::UserType + 11,
		SliderBlockType			= QGraphicsItem::UserType + 12,
		SpinBoxBlockType		= QGraphicsItem::UserType + 13,
		RadioButtonBlockType	= QGraphicsItem::UserType + 14,
		MultiInputNodeContainer = QGraphicsItem::UserType + 15,
		PathBlockType			= QGraphicsItem::UserType + 16,

		//LinkType			=	QGraphicsItem::UserType + 17
	};
};