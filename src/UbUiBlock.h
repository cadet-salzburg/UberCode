#pragma once
#include <QGraphicsObject>
#include "UbOutletNode.h"
#include "UbTypes.h"

//namespace Uber {
//	class UbUiBlock : public QGraphicsObject
//	{
//		Q_OBJECT
//	public:
//		UbUiBlock( QGraphicsObject *parent = 0 );
//		virtual ~UbUiBlock(void);
//
//		enum { Type = UiBlockType };
//
//		virtual	int							type() const { return Type; }
//		virtual QRectF						boundingRect() const;
//		virtual void						paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//		virtual void						constructPath();
//		virtual void						updatePath();
//
//		virtual void						setNode( UbOutletNode *node );
//		virtual void						receiveData(_2Real::app::AppData const& data);
//		virtual void						nodeIsSet();
//
//	protected:
//		virtual void						mousePressEvent ( QGraphicsSceneMouseEvent * e )
//		{
//			m_CurrentPoint = m_PreviousPoint =  e->scenePos();  
//		};
//		virtual void						mouseMoveEvent ( QGraphicsSceneMouseEvent * e )
//		{
//			m_CurrentPoint = e->scenePos();
//			QPointF diff = m_CurrentPoint - m_PreviousPoint;
//			setPos(pos() + diff );
//			m_PreviousPoint = m_CurrentPoint;
//		};
//
//	private:
//		void								init();
//		UbOutletNode						*m_Node;
//		UbImage								*m_Image;
//		_2Real::app::AppData				m_Data;
//		QGraphicsProxyWidget*				m_ProxyWidget;
//		QPointF								m_Pos;
//		QPainterPath						m_Path;
//		qreal								m_Width;
//		qreal								m_Height;
//		int									m_CornerRadius;
//		QPointF								m_CurrentPoint; 
//		QPointF								m_PreviousPoint;
//
//	public slots:
//		virtual void						updateData(_2Real::app::AppData data);
//	signals:
//		void								sendData(_2Real::app::AppData data);
//	};
//
//	};
//}