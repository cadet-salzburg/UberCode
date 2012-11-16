#include "UbAbstractBlock.h"

namespace Uber {
	UbAbstractBlock::UbAbstractBlock( QGraphicsItem *parent )
		:UbObject( parent )
		,m_CornerRadius(8)
	{
		m_Width = 110;
		m_Height = 40;
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

	Uber::UbNodeRef UbAbstractBlock::getNodeUnderMouse()
	{
		QVector<UbNodeRef>::iterator iter = m_Inlets.begin();
		for (; iter!=m_Inlets.end();++iter)
		{
			if ((*iter)->isUnderMouse() )
			{
				return *iter;
			}
		}
		iter = m_Outlets.begin();
		for (; iter!=m_Outlets.end();++iter)
		{
			if ((*iter)->isUnderMouse() )
			{
				return *iter;
			}
		}
		return UbNodeRef();
	}
}