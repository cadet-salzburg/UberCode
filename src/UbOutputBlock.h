#pragma once
#include "UbInterfaceBlock.h"
#include "app/_2RealAppData.h"

namespace Uber {
	class UbOutputBlock :public UbInterfaceBlock
	{
		Q_OBJECT
	public:
		UbOutputBlock( QGraphicsItem *parent );
		virtual ~UbOutputBlock(void);
		enum { Type = OutputBlockType };

		virtual	int				type() const { return Type; }

	protected:
		void					receiveData( _2Real::app::AppData const& data );
		_2Real::app::AppData	m_Data;

	public slots:
		virtual void			updateData(	_2Real::app::AppData data	);
	signals:
		void					sendData(	_2Real::app::AppData data	);
	};
}