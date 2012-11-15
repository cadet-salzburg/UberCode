#pragma once

#include "UbGraphicsScene.h"
#include "UbBundleBlock.h"

namespace Uber {
	class UbComposition
	{
	public:
		UbComposition();
		~UbComposition();

		UbGraphicsScene*	getGraphicsScene();
		void	addBlock(QString strBlockName, QPointF pos );
		void	addBlock( UbBundleBlock *block );
	private:
		UbGraphicsScene*	m_UbGraphicsScene;
	};
}