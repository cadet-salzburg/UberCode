#pragma once
#include "UbAbstractBlock.h"

class UbBundleBlock : public UbAbstractBlock
{
	enum { Type = Uber::BundleBlockType };
public:
	UbBundleBlock( QGraphicsItem *parent,  _2Real::app::BundleHandle handle, QString blockName );
	UbBundleBlock( QGraphicsItem *parent, QString blockInstanceId );
	virtual ~UbBundleBlock(void);
	virtual int type() const { return Type; }
	_2Real::app::BlockHandle getHandle()
	{
		return m_BlockHandle;
	}
protected:
	virtual void mousePressEvent ( QGraphicsSceneMouseEvent * e )
	{
		//Rolling our own dragging, since there seems to be a bug

		//std::cout << "-----------------------------------------------------------" << std::endl;
		//std::cout << "Mouse Pressed on Block " << std::endl;
		//std::cout << "Object Coordinates: " <<e->pos().x() << "," << e->pos().y() << std::endl;
		//std::cout << "Scene Coordinates: " <<e->scenePos().x() << "," << e->scenePos().y() << std::endl;
		//std::cout << "Object Position Coordinates: " << pos().x() << "," << pos().y() << std::endl;
		//std::cout << "-----------------------------------------------------------" << std::endl;
		//e->accept();
		//UbAbstractBlock::mousePressEvent(e);
		//if ( e->button()== Qt::RightButton )
		//{
		//	return;
		//}
		m_CurrentPoint = m_PreviousPoint =  e->scenePos();  
	};
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * e )
	{
		//std::cout << "-----------------------------------------------------------" << std::endl;
		//std::cout << "Mouse Moved on Block " << std::endl;
		//std::cout << "Object Coordinates: " <<e->pos().x() << "," << e->pos().y() << std::endl;
		//std::cout << "Scene Coordinates: " <<e->scenePos().x() << "," << e->scenePos().y() << std::endl;
		//std::cout << "Object Position Coordinates: " << pos().x() << "," << pos().y() << std::endl;
		//std::cout << "-----------------------------------------------------------" << std::endl;
		//e->accept();
		m_CurrentPoint = e->scenePos();
		QPointF diff = m_CurrentPoint - m_PreviousPoint;
		setPos(pos() + diff );
		m_PreviousPoint = m_CurrentPoint;
		//QGraphicsObject::mouseMoveEvent(e);
	};
private:
	void	addNodes();
	_2Real::app::BlockHandle		m_BlockHandle;
	QPointF m_CurrentPoint;
	QPointF m_PreviousPoint;
};