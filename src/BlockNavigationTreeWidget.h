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
	//	std::cout << " Drag Move Event" << std::endl;
	//}
	//void	dragEnterEvent( QDragEnterEvent * event )
	//{
	//	std::cout << "Drag Enter Event" << std::endl;
	//}
	//void	dropEvent(QDropEvent * event )
	//{
	//	std::cout << "Drag Drop Event" << std::endl;
	//}
private:
	void	addBlockNames();
	void	performDrag();
	QPoint		m_StartPos;
	Qt::DropAction m_DropAction;
};

#endif // BlockNavigationTreeWidget_H
