#pragma once
#include <QGraphicsObject>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include "UbOutputBlock.h"
#include "UbOutletNode.h"
#include "UbImage.h"
#include "app/_2RealAppData.h"

namespace Uber {
	class UbImageView :public UbOutputBlock
	{
		Q_OBJECT
	public:
		UbImageView( QGraphicsItem *parent );
		~UbImageView(void);

		enum { Type = ImageBlockType };

		virtual	int						type() const { return Type; }
		virtual void					blockIsConnected();
		virtual void					updateData( _2Real::app::AppData const& data	);
	protected:
		virtual void					arrangeNodes();
	private:
		UbImage							*m_Image;
	};
}

