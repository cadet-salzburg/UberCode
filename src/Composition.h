#pragma once

#include "WorkbenchGraphicsScene.h"


class Composition
{
public:
	Composition();
	~Composition();

	WorkbenchGraphicsScene* getGraphicsScene();
	void					addBlock(QString strBlockName);

private:
	WorkbenchGraphicsScene*					m_WorkbenchGraphicsScene;
};