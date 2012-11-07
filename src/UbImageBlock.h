#pragma once
#include <QGraphicsObject>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include "UbOutletNode.h"
#include "UbImage.h"
#include "app/_2RealAppData.h"

namespace Uber {
	class UbImageBlock :public QGraphicsObject
	{
		Q_OBJECT
	public:
		enum { Type = ImageBlockType };
		UbImageBlock( QGraphicsItem *parent );
		~UbImageBlock(void);
		virtual	int					type() const { return Type; }
		QRectF						boundingRect() const;
		void						paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		void						constructPath();
		void						updatePath();

		void						setNode( UbOutletNode *node );
		void						receiveData(_2Real::app::AppData const& data);
	public slots:
		void						updateData(_2Real::app::AppData data);
	signals:
		void						sendData(_2Real::app::AppData data);
	protected:
		virtual void				mousePressEvent ( QGraphicsSceneMouseEvent * e )
		{
			m_CurrentPoint = m_PreviousPoint =  e->scenePos();  
		};
		virtual void				mouseMoveEvent ( QGraphicsSceneMouseEvent * e )
		{
			m_CurrentPoint = e->scenePos();
			QPointF diff = m_CurrentPoint - m_PreviousPoint;
			setPos(pos() + diff );
			m_PreviousPoint = m_CurrentPoint;
		};
	private:
		UbOutletNode				*m_Node;
		UbImage						*m_Image;
		_2Real::app::AppData		m_Data;
		QGraphicsProxyWidget*		m_ProxyWidget;
		QPointF						m_Pos;
		QPainterPath				m_Path;
		qreal						m_Width;
		qreal						m_Height;
		int							m_CornerRadius;
		QPointF						m_CurrentPoint; 
		QPointF						m_PreviousPoint;
	};
}

