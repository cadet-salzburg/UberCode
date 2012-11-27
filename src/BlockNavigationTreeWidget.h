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
#ifndef BlockNavigationTreeWidget_H
#define BlockNavigationTreeWidget_H

#include <QTreeWidget>
#include <QMouseEvent>
#include <QPoint>
#include <iostream>

class BlockNavigationTreeWidget : public QTreeWidget
{
	Q_OBJECT

		public slots:
			void	onDoubleClickAddBlock( QTreeWidgetItem*, int);

public:
	BlockNavigationTreeWidget(QWidget *parent=0);
	~BlockNavigationTreeWidget();

protected:
	void	mouseMoveEvent( QMouseEvent* e);
	void	mousePressEvent( QMouseEvent* e);
	//void	dragMoveEvent( QDragMoveEvent * event)
	//{
	//	//std::cout << " Drag Move Event" << std::endl;
	//}
	//void	dragEnterEvent( QDragEnterEvent * event )
	//{
	//	//std::cout << "Drag Enter Event" << std::endl;
	//}
	//void	dropEvent(QDropEvent * event )
	//{
	//	//std::cout << "Drag Drop Event" << std::endl;
	//}
private:
	void	addBlockNames();
	void	performDrag();
	QPoint		m_StartPos;
	Qt::DropAction m_DropAction;
};

#endif // BlockNavigationTreeWidget_H
