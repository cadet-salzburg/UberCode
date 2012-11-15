#pragma once
#include "UbInputBlock.h"
#include <QGraphicsProxyWidget>
#include "UbNode.h"
#include "UbInletNode.h"
#include <QSlider>

namespace Uber {
	class UbSlider : public UbInputBlock
	{
		Q_OBJECT
	public:
		UbSlider( QGraphicsItem *parent );
		virtual	~UbSlider(void);
		enum { Type = SliderBlockType };

		virtual	int					type() const { return Type; }
		virtual void				blockIsConnected();
	public slots:
		void						setValue(int value);
	protected:
		virtual void				arrangeNodes();
	private:
		void						init();	
		QSlider*					m_Slider;
	};
}