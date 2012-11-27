/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH
		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include "BlockNavigationTreeWidget.h"
#include "DataflowEngineManager.h"
#include <QApplication>

BlockNavigationTreeWidget::BlockNavigationTreeWidget(QWidget *parent)
	: QTreeWidget(parent)
{
	setMinimumWidth(120);
	setColumnCount(1);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setDragEnabled(true);
	addBlockNames();
	connect( this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onDoubleClickAddBlock(QTreeWidgetItem*, int)));
}

BlockNavigationTreeWidget::~BlockNavigationTreeWidget()
{

}

void BlockNavigationTreeWidget::mousePressEvent( QMouseEvent* e )
{
	const QModelIndex index = indexAt(e->pos());
	if ( index.isValid() )
	{
		setCurrentItem(QTreeWidget::itemFromIndex(index) );
	}
	if(e->button() == Qt::LeftButton)
		m_StartPos = e->pos();
	QTreeWidget::mousePressEvent( e );
}

void BlockNavigationTreeWidget::mouseMoveEvent( QMouseEvent* e ) 
{
	if( e->buttons() & Qt::LeftButton)
	{
		int diff = ( m_StartPos - e->pos() ).manhattanLength();
		if( diff >= QApplication::startDragDistance())
			performDrag();
	}
	QTreeWidget::mouseMoveEvent( e );
}

void BlockNavigationTreeWidget::performDrag()
{
	QTreeWidgetItem *item = currentItem();
	if(item)
	{
		QMimeData *mimeData = new QMimeData;
		QString text = item->text(0);
		mimeData->setText(item->text(0));
		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		m_DropAction = drag->exec( Qt::CopyAction );
	}
}

void BlockNavigationTreeWidget::onDoubleClickAddBlock( QTreeWidgetItem* item, int column)
{
	QString blockName = item->text( column );
	DataflowEngineManager::getInstance()->getComposition()->addBlock(blockName, QPointF(100,100));
}

void BlockNavigationTreeWidget::addBlockNames()
{
	QStringList list = DataflowEngineManager::getInstance()->loadBundles();

	//QTreeWidgetItem* category = new QTreeWidgetItem(this);
	//category->setText( 0, QString("Bundles") );

	QList<QTreeWidgetItem *> blockItems;
	for( QStringList::const_iterator iter = list.constBegin(); iter != list.constEnd(); ++iter )
	{
		//QTreeWidgetItem *block = new QTreeWidgetItem( this);
		//block->setText(0, *iter );
		//blockItems.append(block);
		blockItems.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(*iter)));
	}

	insertTopLevelItems(0, blockItems);
	QStringList columnName;
	columnName  << "Elements";
	setHeaderLabels(columnName);

	//QList<QTreeWidgetItem *> ubercodeItems;
	//QTreeWidgetItem *block = new QTreeWidgetItem( this);


	//ubercodeItems.append( )


}

