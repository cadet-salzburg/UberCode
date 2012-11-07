#pragma once
#include <QGraphicsObject>
#include "UbOutletNode.h"
#include "UbImage.h"
#include "app/_2RealAppData.h"

namespace UberCode {
	class UbImageBlock :public QGraphicsObject
	{
	public:
		UbImageBlock( QGraphicsItem *parent );
		~UbImageBlock(void);
		void			setNode(UbOutletNode *node );

	private:
		UbOutletNode			*m_Node;
		UbImage					*m_Image;
		_2Real::app::AppData	m_Data;
	public slots:
			void					updateData(_2Real::app::AppData data);
	signals:
			void					sendData(_2Real::app::AppData data);
	};
}

