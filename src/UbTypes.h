#pragma once
#include <QGraphicsItem>
namespace Uber {
	enum  {
		NodeType = QGraphicsItem::UserType + 1,
		InputNodeType = QGraphicsItem::UserType + 2,
		OutputNodeType = QGraphicsItem::UserType + 3,
		AbstractBlockType = QGraphicsItem::UserType + 4,
		BundleBlockType	  = QGraphicsItem::UserType + 5,
		InputBlockType    = QGraphicsItem::UserType + 6,
		OutputBlockType   = QGraphicsItem::UserType + 7,
		IOBlockType   = QGraphicsItem::UserType + 8
	};
};