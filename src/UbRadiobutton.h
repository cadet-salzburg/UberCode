#pragma once
#include "UbInputBlock.h"
#include <QGraphicsProxyWidget>
#include "UbNode.h"
#include "UbInletNode.h"
#include <QRadioButton>

namespace Uber {
	class UbRadiobutton : public UbInputBlock
	{
		Q_OBJECT
	public:
		UbRadiobutton( QGraphicsItem *parent );
		virtual	~UbRadiobutton(void);
		enum { Type = RadioButtonBlockType };

		virtual	int					type() const { return Type; }
		virtual void				blockIsConnected();

	public slots:
		void						setValue(int value);
	protected:
		virtual void				arrangeNodes();
	private:
		void						init();	
		QRadioButton*				m_Button;
	};
}