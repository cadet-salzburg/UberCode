#pragma once
#include "UbAbstractBlock.h"
#include <QGraphicsProxyWidget>

namespace Uber {
	class UbSliderUiBlock : public UbAbstractBlock
	{
	public:
		UbSliderUiBlock( QGraphicsItem *parent );
		virtual	~UbSliderUiBlock(void);
	protected:
		virtual void addNodes(){}
		virtual void configureNodes(){}
	private:
		void						init();
		QGraphicsProxyWidget*		m_ProxyWidget;
	};
}