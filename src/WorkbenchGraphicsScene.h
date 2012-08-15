#ifndef WorkbenchGraphicsScene_H
#define WorkbenchGraphicsScene_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>

class WorkbenchGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	WorkbenchGraphicsScene();
	~WorkbenchGraphicsScene();

	void addBlock(QString strBlockName);

protected:
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
	void dragMoveEvent(QGraphicsSceneDragDropEvent* event);
	void dropEvent(QGraphicsSceneDragDropEvent* event);

private:
	
};

#endif // WorkbenchGraphicsScene_H
