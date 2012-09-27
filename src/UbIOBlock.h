#pragma once
#include <QGraphicsPathItem>
#include <QGraphicsProxyWidget>
#include <QString>
#include "DataflowEngineManager.h"
#include "UbNode.h"

class UbIOBlock : public QGraphicsObject
{
	Q_OBJECT
public:
	enum { Type = QGraphicsItem::UserType + UberCodeItemType::IOBlockType };
	
	UbIOBlock( QGraphicsItem *parent );
	~UbIOBlock(void);
	
	QRectF		boundingRect() const;
	void		constructPath();
	void		setInputNode( const _2Real::app::OutletHandle& handle );
	void		setOutputNode( const _2Real::app::InletHandle& handle );
	virtual		int type() const 
	{ 
		return Type; 
	}
	void		paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void		receiveData(_2Real::app::AppData const& data);
	bool		isInputBlock();
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
public slots:
	void		updateData(_2Real::app::AppData data);
signals:
	void		sendData(_2Real::app::AppData data);
};