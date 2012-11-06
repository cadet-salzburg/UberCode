#pragma once
#include "UbAbstractBlock.h"
#include "_2RealApplication.h"
#include <QGraphicsSceneMouseEvent>

namespace Uber {
	class UbBundleBlock : public UbAbstractBlock
	{
	public:
		UbBundleBlock( QGraphicsItem *parent,  _2Real::app::BundleHandle handle, QString blockName );
		UbBundleBlock( QGraphicsItem *parent, QString blockInstanceId );
		virtual ~UbBundleBlock(void);

		enum { Type = BundleBlockType };

		virtual int					type() const { return Type; }
		_2Real::app::BlockHandle	getHandle(){ return m_BlockHandle;}
	protected:
		virtual void				mousePressEvent ( QGraphicsSceneMouseEvent * e )
		{
			//TODO: QT dragging seems to have glitches. Not sure if its a QT bug or not.
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
		void						addNodes();
		_2Real::app::BlockHandle	m_BlockHandle;
		QPointF						m_CurrentPoint;
		QPointF						m_PreviousPoint;
	};
}