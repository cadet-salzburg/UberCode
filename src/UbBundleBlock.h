#pragma once
#include "UbAbstractBlock.h"

class UbBundleBlock : public UbAbstractBlock
{
	enum { Type = QGraphicsItem::UserType + UberCodeItemType::BundleBlockType };
public:
	UbBundleBlock( QGraphicsItem *parent,  _2Real::app::BundleHandle handle, QString blockName );
	virtual ~UbBundleBlock(void);
	virtual int type() const { return Type; }

	//void	paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	void	setup();
	void	addNodes();

	_2Real::app::BundleHandle		m_BundleHandle;
	_2Real::app::BlockHandle		m_BlockHandle;	
	QString							m_BlockName;
};