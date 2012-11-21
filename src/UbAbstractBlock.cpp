#include "UbAbstractBlock.h"
#include <iostream>
namespace Uber {
	UbAbstractBlock::UbAbstractBlock( QGraphicsItem *parent )
		:UbObject( parent )
		,m_CornerRadius(8)
	{
		m_Width = 110;
		m_Height = 40;
		constructPath();
		m_PropertyAnimation = new QPropertyAnimation(this, "opacity");
		m_PropertyAnimation->setDuration(1000);
		m_PropertyAnimation->setStartValue(0.5f);
		m_PropertyAnimation->setEndValue(1.0f);
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
			std::cout << "The position of the node is: " << (*iter)->pos().x() << " " << (*iter)->pos().y() << std::endl; 
			if ((*iter)->isUnderMouse() )
			{
				m_PropertyAnimation->start();
				return *iter;
				
			}
		}
		iter = m_Outlets.begin();
		for (; iter!=m_Outlets.end();++iter)
		{
			if ((*iter)->isUnderMouse() )
			{
				m_PropertyAnimation->start();
				return *iter;
			}
		}
		return UbNodeRef();
	}
	//Uber::UbNodeRef UbAbstractBlock::getNodeAtPosition(QPointF p)
	//{
	//	QVector<UbNodeRef>::iterator iter = m_Inlets.begin();
	//	for (; iter!=m_Inlets.end();++iter)
	//	{
	//		if ((*iter)->rect )
	//		{
	//			m_PropertyAnimation->start();
	//			return *iter;

	//		}
	//	}
	//	iter = m_Outlets.begin();
	//	for (; iter!=m_Outlets.end();++iter)
	//	{
	//		if ((*iter)->isUnderMouse() )
	//		{
	//			m_PropertyAnimation->start();
	//			return *iter;
	//		}
	//	}
	//	return UbNodeRef();
	//}
}