#pragma once
#include <QGraphicsItem>
namespace Uber {
	enum  {
		ObjectType			= QGraphicsItem::UserType + 1,
		AbstractBlockType	= QGraphicsItem::UserType + 2,
		BundleBlockType		= QGraphicsItem::UserType + 3,
		NodeType			= QGraphicsItem::UserType + 4,
		InputNodeType		= QGraphicsItem::UserType + 5,
		OutputNodeType		= QGraphicsItem::UserType + 6,
		InterfaceBlockType	= QGraphicsItem::UserType + 7,
		InputBlockType		= QGraphicsItem::UserType + 8,
		OutputBlockType		= QGraphicsItem::UserType + 9,
		ImageBlockType		= QGraphicsItem::UserType + 10,
		SliderBlockType		= QGraphicsItem::UserType + 11,
		SpinBoxBlockType	= QGraphicsItem::UserType + 12
	};
};