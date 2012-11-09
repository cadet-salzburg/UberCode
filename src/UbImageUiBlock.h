#pragma once
#include <QGraphicsObject>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include "UbAbstractBlock.h"
#include "UbOutletNode.h"
#include "UbImage.h"
#include "app/_2RealAppData.h"

namespace Uber {
	class UbImageUiBlock :public UbAbstractBlock
	{
		Q_OBJECT
	public:
		enum { Type = ImageBlockType };
		UbImageUiBlock( QGraphicsItem *parent );
		~UbImageUiBlock(void);
		virtual	int						type() const { return Type; }
		void							updatePath();
		//void							setNode( UbOutletNode *node );
		void							receiveData(_2Real::app::AppData const& data);
		void							nodeIsSet();
	protected:
		virtual void					configureNodes();
	private:
		void							init();
		UbOutletNode					*m_Node;
		UbImage							*m_Image;
		_2Real::app::AppData			m_Data;
		QGraphicsProxyWidget*			m_ProxyWidget;
	public slots:
		void							updateData(_2Real::app::AppData data);
	signals:
		void							sendData(_2Real::app::AppData data);
	};
}

