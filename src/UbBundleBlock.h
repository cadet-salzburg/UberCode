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
		QString						getBlockId(){ return m_BlockId; }

	private:
		void						configureNodes();
		_2Real::app::BlockHandle	m_BlockHandle;
		QString						m_BlockId;
	};
}