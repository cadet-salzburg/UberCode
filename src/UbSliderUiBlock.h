#pragma once
#include "UbAbstractBlock.h"
#include <QGraphicsProxyWidget>
#include "UbInletNode.h"
#include <QSlider>

namespace Uber {
	class UbSliderUiBlock : public UbAbstractBlock
	{
		Q_OBJECT
	public:
		enum { Type = SliderBlockType };
		UbSliderUiBlock( QGraphicsItem *parent );
		virtual	~UbSliderUiBlock(void);

		virtual	int					type() const { return Type; }
		void						nodeIsSet();
	public slots:
		void						setValue(int value);
	protected:
		virtual void				addNodes(){}
		virtual void				configureNodes();
	private:
		void						init();
		QGraphicsProxyWidget*		m_ProxyWidget;
		UbInletNode*				m_Node;		
		QSlider*					m_Slider;
	};
}