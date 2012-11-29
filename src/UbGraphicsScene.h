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
#ifndef UbGraphicsScene_H
#define UbGraphicsScene_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include "UbObject.h"
namespace Uber {
	class UbGraphicsScene : public QGraphicsScene
	{
		Q_OBJECT
	public:
		UbGraphicsScene();
		~UbGraphicsScene();
		void 					addItem( UbObject * item );
		void					removeUbObject( UbObject* item );
		UbObject*				getNamedItem( QString name );
	protected:
		void					dragEnterEvent(QGraphicsSceneDragDropEvent* event);
		void					dragMoveEvent(QGraphicsSceneDragDropEvent* event);
		void					dropEvent(QGraphicsSceneDragDropEvent* event);
	private:
		void					initialize();
		QList<UbObject*>			m_Items;
	};
}
#endif // UbGraphicsScene_H
