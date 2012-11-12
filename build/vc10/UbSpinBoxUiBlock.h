#pragma once
#pragma once
#include "UbAbstractBlock.h"
#include <QGraphicsProxyWidget>
#include "UbInletNode.h"
#include <QSpinBox>

namespace Uber {
	class UbSpinBoxUiBlock : public UbAbstractBlock
	{
		Q_OBJECT
	public:
		enum { Type = SpinBoxBlockType };
		UbSpinBoxUiBlock( QGraphicsItem *parent );
		virtual	~UbSpinBoxUiBlock(void);

		virtual	int					type() const { return Type; }
		void						nodeIsSet();
		public slots:
			void					setValue(int value);
	protected:
		virtual void				addNodes(){}
		virtual void				configureNodes();
	private:
		void						init();
		QGraphicsProxyWidget*		m_ProxyWidget;
		UbInletNode*				m_Node;		
		QSpinBox*					m_SpinBox;
	};
}