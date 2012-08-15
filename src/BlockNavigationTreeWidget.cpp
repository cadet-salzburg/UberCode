#include "BlockNavigationTreeWidget.h"
#include "DataflowEngineManager.h"

#include <QApplication>

BlockNavigationTreeWidget::BlockNavigationTreeWidget(QWidget *parent)
	: QTreeWidget(parent)
{
	setMinimumWidth(120);
	addBlockNames();
	connect( this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onDoubleClickAddBlock(QTreeWidgetItem*, int)));
}

BlockNavigationTreeWidget::~BlockNavigationTreeWidget()
{
}

void BlockNavigationTreeWidget::mousePressEvent(QMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
		m_StartPos = event->pos();
	QTreeWidget::mousePressEvent( event );
}

void BlockNavigationTreeWidget::mouseMoveEvent(QMouseEvent* event)
{
	if(event->buttons() & Qt::LeftButton)
	{
		int distance = (event->pos() - m_StartPos).manhattanLength();
		if( distance >= QApplication::startDragDistance())
			performDrag();
	}
	QTreeWidget::mouseMoveEvent( event );
}

void BlockNavigationTreeWidget::performDrag()
{
	QTreeWidgetItem *item = currentItem();
	if(item)
	{
		QMimeData *mimeData = new QMimeData;
		mimeData->setText(item->text(0));
		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		Qt::DropAction dropAction = drag->exec(Qt::CopyAction );
	}
}

void BlockNavigationTreeWidget::onDoubleClickAddBlock( QTreeWidgetItem* item, int column)
{
	QString blockName = item->text( column );
	DataflowEngineManager::getInstance()->getComposition()->addBlock(blockName);
}

void BlockNavigationTreeWidget::addBlockNames()
{
	QStringList list = DataflowEngineManager::getInstance()->loadBundles();

	//QTreeWidgetItem* category = new QTreeWidgetItem(this);
	//category->setText( 0, QString("Bundles") );
	for( QStringList::const_iterator iter = list.constBegin(); iter != list.constEnd(); ++iter )
	{
		QTreeWidgetItem *block = new QTreeWidgetItem( this);
		block->setText(0, *iter );
	}
}

