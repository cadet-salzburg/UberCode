#ifndef BlockNavigationTreeWidget_H
#define BlockNavigationTreeWidget_H

#include <QTreeWidget>
#include <QMouseEvent>
#include <QPoint>

class BlockNavigationTreeWidget : public QTreeWidget
{
	Q_OBJECT

public slots:
	void	onDoubleClickAddBlock( QTreeWidgetItem*, int);

public:
	BlockNavigationTreeWidget(QWidget *parent=0);
	~BlockNavigationTreeWidget();

protected:
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	
private:
	void addBlockNames();
	void performDrag();

	QPoint		m_StartPos;
};

#endif // BlockNavigationTreeWidget_H
