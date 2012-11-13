#pragma once
#pragma once
#include "UbInputBlock.h"
#include "UbInletNode.h"
#include <QSpinBox>

namespace Uber {
	class UbSpinbox : public UbInputBlock
	{
		Q_OBJECT
	public:
		enum { Type = SpinBoxBlockType };
		UbSpinbox( QGraphicsItem *parent );
		virtual	~UbSpinbox(void);

		virtual	int					type() const { return Type; }
		virtual void				blockIsConnected();

	public slots:
		void						setValue(int value);

	protected:
		virtual void				arrangeNodes();

	private:
		void						init();
		QSpinBox*					m_SpinBox;
	};
}