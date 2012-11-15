#pragma once
#include "UbAbstractBlock.h"
#include "_2RealApplication.h"
#include "UbNode.h"
#include <QVector>
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
		QString						getBlockId(){ return m_BlockId; }
		QVector<UbNodeRef>			getInlets();
		QVector<UbNodeRef>			getOutlets();
	private:
		void						arrangeNodes();
		_2Real::app::BlockHandle	m_BlockHandle;
		QString						m_BlockId;
	};
}