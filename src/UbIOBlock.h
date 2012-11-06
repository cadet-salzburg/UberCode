#pragma once
#include <QGraphicsPathItem>
#include <QGraphicsProxyWidget>
#include <QString>
#include "DataflowEngineManager.h"
#include "UbNode.h"

namespace Uber {
	class UbIOBlock : public QGraphicsObject
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
		bool					m_IsInputBlock;			
		UbNode*					m_Node;
		QPainterPath			m_Path;
		qreal					m_Width;
		qreal					m_Height;
		int						m_CornerRadius;
		QWidget*				m_ValueWidget;
		QImage					m_Img;
		QPixmap					m_Pixmap;
		QGraphicsProxyWidget*	m_ProxyWidget;
		QPointF					m_Pos;
		QPointF					m_CurrentPoint;
		QPointF					m_PreviousPoint;
		_2Real::app::AppData	m_Data;
	protected:
		virtual void			mousePressEvent ( QGraphicsSceneMouseEvent * e )
		{
			m_CurrentPoint = m_PreviousPoint =  e->scenePos();  
		};
		virtual void			mouseMoveEvent ( QGraphicsSceneMouseEvent * e )
		{
			m_CurrentPoint = e->scenePos();
			QPointF diff = m_CurrentPoint - m_PreviousPoint;
			setPos(pos() + diff );
			m_PreviousPoint = m_CurrentPoint;
		};
	public slots:
		void					updateData(_2Real::app::AppData data);
	signals:
		void					sendData(_2Real::app::AppData data);
		//void					viewportChanged();
	};
}