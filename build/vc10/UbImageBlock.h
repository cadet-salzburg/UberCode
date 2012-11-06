#pragma once
#include <QGraphicsObject>
#include "UbOutletNode.h"
namespace UberCode {
	class UbImageBlock :public QGraphicsObject
	{
	public:
		UbImageBlock( QGraphicsItem *parent );
		~UbImageBlock(void);
	};
}

