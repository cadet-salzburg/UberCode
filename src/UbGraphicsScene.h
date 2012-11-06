#ifndef UbGraphicsScene_H
#define UbGraphicsScene_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>

namespace Uber {
	class UbGraphicsScene : public QGraphicsScene
	{
		Q_OBJECT
	public:
		UbGraphicsScene();
		~UbGraphicsScene();
	protected:
		void		dragEnterEvent(QGraphicsSceneDragDropEvent* event);
		void		dragMoveEvent(QGraphicsSceneDragDropEvent* event);
		void		dropEvent(QGraphicsSceneDragDropEvent* event);
	private:
		void		initialize();
	};
}
#endif // UbGraphicsScene_H
