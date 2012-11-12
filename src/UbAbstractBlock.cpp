#include "UbAbstractBlock.h"

namespace Uber {
	UbAbstractBlock::UbAbstractBlock( QGraphicsItem *parent )
		:UbObject( parent )
		,m_CornerRadius(8)
	{
		m_Width = 140;
		m_Height = 70;
		constructPath();
	}

	UbAbstractBlock::~UbAbstractBlock(void)
	{

	}


	void UbAbstractBlock::constructPath()
	{
		QPainterPath path;
		m_Path = path;
		QRectF rect( QPointF(-m_Width/2., -m_Height/2.), QPointF( m_Width/2.,m_Height/2.) );
		m_Path.addRoundedRect( rect, m_CornerRadius, m_CornerRadius );;
		setFlag(QGraphicsItem::ItemIsSelectable);
	}
}