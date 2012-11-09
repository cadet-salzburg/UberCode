#pragma once
#include <QGraphicsPathItem>
#include <QGraphicsProxyWidget>
#include <QString>
#include "DataflowEngineManager.h"
#include "UbAbstractBlock.h"

namespace Uber {
	class UbIOBlock : public UbAbstractBlock
	{
		Q_OBJECT
	public:
		UbIOBlock( QGraphicsItem *parent );
		~UbIOBlock(void);

		enum { Type = IOBlockType };
		
		virtual	int				type() const { return Type; }

		QRectF					boundingRect() const;
		void					paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		void					constructPath();
		void					updatePath();

		void					setInputNode( const _2Real::app::OutletHandle& handle );
		void					setOutputNode( const _2Real::app::InletHandle& handle );
		bool					isInputBlock();

		void					receiveData(_2Real::app::AppData const& data);

	private:
		QWidget*				m_ValueWidget;
		QImage					m_Img;
		QGraphicsProxyWidget*	m_ProxyWidget;
		_2Real::app::AppData	m_Data;
	public slots:
		void					updateData(_2Real::app::AppData data);
	signals:
		void					sendData(_2Real::app::AppData data);
		//void					viewportChanged();
	};
}