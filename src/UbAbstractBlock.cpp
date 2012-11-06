#include "UbAbstractBlock.h"

namespace Uber {
	UbAbstractBlock::UbAbstractBlock( QGraphicsItem *parent )
		:QGraphicsObject( parent )
		,m_Width(140)
		,m_Height(70)
		,m_CornerRadius(8)
		,m_Rectangle( QPointF(-m_Width/2., -m_Height/2.), QPointF( m_Width/2.,m_Height/2.))
	{
		setFlag(ItemIsMovable);
	}

	UbAbstractBlock::~UbAbstractBlock(void)
	{

	}
	QRectF	UbAbstractBlock::boundingRect() const
	{
		return QRectF( QPointF(-m_Width/2., -m_Height/2.), QPointF( m_Width/2.,m_Height/2.) );
	}

	void UbAbstractBlock::constructPath()
	{
		m_Path.addRoundedRect( m_Rectangle, m_CornerRadius, m_CornerRadius );;
		setFlag(QGraphicsItem::ItemIsMovable);
		setFlag(QGraphicsItem::ItemIsSelectable);
		addNodes(); 
	}

	void UbAbstractBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
	{
		Q_UNUSED(option)
			Q_UNUSED(widget)

			QPen pen;
		pen.setWidthF(1.f);
		pen.setBrush(Qt::black);	
		painter->setPen(pen);
		painter->setBrush(QColor(69,82,80));
		painter->drawPath( m_Path );
	}

	//QVariant UbAbstractBlock::itemChange(GraphicsItemChange change, const QVariant &value)
	//{
	//	return value;
	//}
}