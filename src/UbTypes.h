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
		PathBlockType			= QGraphicsItem::UserType + 16
	};
};