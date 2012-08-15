#pragma once
#include <QGraphicsPathItem>
#include <QGraphicsProxyWidget>
#include <QString>
#include "DataflowEngineManager.h"
#include "UbNode.h"
#include "UbOutletNode.h"

class UbOutputBlock : public QGraphicsObject
{
	Q_OBJECT
public:
	enum { Type = QGraphicsItem::UserType + UberCodeItemType::OutputBlockType };
	UbOutputBlock( QGraphicsItem *parent );
	~UbOutputBlock(void);
	QRectF						boundingRect() const;
	void						constructPath();
	void						setInletNode( _2Real::app::OutletHandle& handle );
	virtual int type() const { return Type; }
	void						paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	void						receiveData(_2Real::app::AppData const& data);

private:
	UbNode*						m_InletNode;
	QPainterPath				m_Path;
	qreal						m_Width;
	qreal						m_Height;
	int							m_CornerRadius;
	QWidget*					m_ValueWidget;
	QImage						m_Img;
	QPixmap						m_Pixmap;
	QGraphicsProxyWidget*		m_ProxyWidget;
	
public slots:
	void updateData(_2Real::app::AppData data);

signals:
	void sendData(_2Real::app::AppData data);
};