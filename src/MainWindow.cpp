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
#include <QFileDialog>
#include <QObject>
#include <QString>
#include <QPoint>
#include "MainWindow.h"
#include "DataflowEngineManager.h"
#include "UbLinkController.h"
#include "UbXMLWriter.h"
#include "UbXMLReader.h"
#include "UbLink.h"

#include "UbImageView.h"
#include "UbPathBlock.h"
#include "UbRadioButton.h"
#include "UbSlider.h"
#include "UbSpinbox.h"


#include "helpers/_2RealException.h"

using namespace Uber;
MainWindow::MainWindow()
	: m_SettingsDialog( nullptr ),
	m_UiBuilderWindow( nullptr ),
	m_InterfaceIdData(DataflowEngineManager::getInstance()->getInterfaceBlockData())
{
	QApplication::setOrganizationName("CADET");
	QApplication::setOrganizationDomain("cadet.at");
	QApplication::setApplicationName("UberCode");

	//setAttribute(Qt::WA_TranslucentBackground);
	//setWindowFlags(Qt::FramelessWindowHint);

	m_UiBuilderWindow = new Ui_MainWindow;
	m_UiBuilderWindow->setupUi( this );

	connect(m_UiBuilderWindow->actionOpen_UberCode, SIGNAL(triggered()), this, SLOT(open()));
	connect( m_UiBuilderWindow->actionSave_UberBlock, SIGNAL(triggered()), this, SLOT(save()));

	m_SettingsDialog = new SettingsDialog;
	m_BlockNavigationTreeWidget = new BlockNavigationTreeWidget();
	m_UiBuilderWindow->dockWidget->setWidget(m_BlockNavigationTreeWidget);
	// workbench
	m_WorkbenchGraphicsView = new UbGraphicsView();
	m_WorkbenchGraphicsView->setRenderHint(QPainter::Antialiasing);

	UbGraphicsScene* s = DataflowEngineManager::getInstance()->addComposition()->getGraphicsScene();
	DataflowEngineManager::getInstance()->setGraphicsView(m_WorkbenchGraphicsView);
	m_WorkbenchGraphicsView->setScene( s );
	
	Uber::UbLinkController::getInstance()->setScene( s );
	m_UiBuilderWindow->workbenchLayout->addWidget(m_WorkbenchGraphicsView);
	
	// connect slots
	QObject::connect( m_UiBuilderWindow->actionOptions, SIGNAL(activated()), m_SettingsDialog, SLOT(show()));
}

MainWindow::~MainWindow(void)
{

}

void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)") );
	try {
		qDeleteAll( DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->items() );
		DataflowEngineManager::getInstance()->getEngine().clearBlockInstances();

		std::string file = fileName.toUtf8().constData();
		DataflowEngineManager::getInstance()->getEngine().loadConfig( file );
		Ubercode::xml::UbXMLReader* xmlLoader = new Ubercode::xml::UbXMLReader(fileName);
		//Add Blocks
		QMap<QString, QPoint> data = xmlLoader->getBlockData();
		QMap<QString, QPoint>::const_iterator it = data.constBegin();
		while ( it!= data.constEnd() )
		{
			Uber::UbBundleBlock *block = new Uber::UbBundleBlock( 0, it.key() );
			block->setPos( it.value() );
			DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(block);
			++it;
		}
		//Add Links
		QList<Ubercode::xml::LinkData> linkData = xmlLoader->getLinkData();
		QList<Ubercode::xml::LinkData>::iterator iter = linkData.begin();
		for ( ;iter!=linkData.end(); ++iter )
		{
			QString outletBlockId = iter->first.first;
			QString outletId = iter->first.second;

			QString inletBlockId = iter->second.first;
			QString inletId = iter->second.second;
			//Get Blocks
			QList<Uber::UbBundleBlock*>	 blockList = DataflowEngineManager::getInstance()->getBundleBlocks();
			QList<Uber::UbBundleBlock*>::iterator iter = blockList.begin();

			UbBundleBlock* outBlock = 0;
			UbBundleBlock* inBlock = 0;

			for (;iter!=blockList.end();++iter)
			{
				if ( outBlock && inBlock )
					break;
				if ( (*iter)->getBlockId() == outletBlockId )
					outBlock = *iter;
				if ( (*iter)->getBlockId() == inletBlockId )
					inBlock = *iter;
			}

			if ( outBlock!=0 && inBlock!=0 )
			{
				UbNodeRef inletNode		= UbNodeRef();
				UbNodeRef outletNode	= UbNodeRef();

				QVector<Uber::UbNodeRef> inlets  = inBlock->getInlets();
				QVector<Uber::UbNodeRef> outlets = outBlock->getOutlets();

				QVector<Uber::UbNodeRef>::iterator iterInlet = inlets.begin();
				for (;iterInlet!=inlets.end();++iterInlet)
				{
					if ( (*iterInlet)->getName() == inletId )
					{
						inletNode = *iterInlet;
						break;
					}
				}

				QVector<Uber::UbNodeRef>::iterator iterOutlet = outlets.begin();
				for (;iterOutlet!=outlets.end();++iterOutlet)
				{
					if ( (*iterOutlet)->getName() == outletId )
					{
						outletNode = *iterOutlet;
						break;
					}
				}
				if ( outletNode && inletNode )
				{
					//We found the nodes, lets add the link
					UbLinkController::getInstance()->addLink(outletNode, inletNode);

					//UbLink* theLink = new UbLink();
					//theLink->setNodes(outletNode, inletNode );


				}
			}
		}
		// Add UI Elements
		QMap<QString, QPair<QPoint,QString> > uiData = xmlLoader->getInterfaceData();
		QMap<QString, QPair<QPoint,QString> >::const_iterator uiIter = uiData.constBegin();
		while ( uiIter!= uiData.constEnd() )
		{
			Uber::UbInterfaceBlock *interfaceBlock = 0;
			QStringList list = uiIter.key().split("_");
			if ( list.at(0) == "ImageView" )
			{
				interfaceBlock = new Uber::UbImageView(0);
			} else if ( list.at(0) == "PathBlock" )
			{
				UbPathBlock* p = new Uber::UbPathBlock(0);
				interfaceBlock = p;
				p->setValue(uiIter.value().second);
				
			} else if ( list.at(0) == "Radiobutton" )
			{
				interfaceBlock = new Uber::UbRadiobutton(0);
			} else if ( list.at(0) == "Slider" )
			{
				interfaceBlock = new Uber::UbSlider(0);
			}  else if ( list.at(0) == "Spinbox" )
			{
				interfaceBlock = new Uber::UbSpinbox(0);
			}
			if ( interfaceBlock )
			{
				interfaceBlock->setName( uiIter.key() );
				interfaceBlock->setPos(uiIter.value().first);
				
				//Ensure that IDs will be correct
				if ( m_InterfaceIdData.contains(interfaceBlock->type()) )
				{
					if ( m_InterfaceIdData[interfaceBlock->type()] < list.back().toInt() )
						m_InterfaceIdData[interfaceBlock->type()] = list.back().toInt();
				} else 
				{
					m_InterfaceIdData[interfaceBlock->type()] = list.back().toInt();
				}

				DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(interfaceBlock);
			}
			++uiIter;
		}
		//// Add UI Links
		QList<Ubercode::xml::UiLinkData>  uiLinkData = xmlLoader->getInterfaceLinkData();
		QList<Ubercode::xml::UiLinkData>::iterator uiLinkIter = uiLinkData.begin();
		for ( ;uiLinkIter!= uiLinkData.end(); ++uiLinkIter )
		{
			//Find Interface element with name  uiLinkIter->first
			UbComposition* comp = DataflowEngineManager::getInstance()->getComposition();
			UbGraphicsScene* scene = comp->getGraphicsScene();
			UbObject *obj = scene->getNamedItem(uiLinkIter->first);
			UbNodeRef nodeA = UbNodeRef();
			UbNodeRef nodeB = UbNodeRef();
			if ( obj )
			{
				UbInterfaceBlock *iBlock = static_cast<UbInterfaceBlock*>(obj);
				nodeA = iBlock->getNode();
				QString blockName = (uiLinkIter->second).first;
				UbObject *block = scene->getNamedItem(blockName);
				UbBundleBlock *b = static_cast<UbBundleBlock*>(block);
				//ToDo: theoretically an inlet and an outlet could have the same id, so we should check for this
				QVector<UbNodeRef> inlets = b->getInlets();
				QVector<UbNodeRef> outlets = b->getOutlets();
				for ( int i=0; i< inlets.size(); ++i )
				{
					if ( inlets[i]->getName()==(uiLinkIter->second).second )
					{
						nodeB = inlets[i];
						break;
					}
				}

				if (!nodeB){
					for ( int i=0; i< outlets.size(); ++i )
					{
						if ( outlets[i]->getName()==(uiLinkIter->second).second )
						{
							nodeB = outlets[i];
							break;
						}
					}
				}


				if ( nodeA && nodeB )
				{
					Uber::UbLinkController::getInstance()->tryConnecting(nodeA, nodeB);
					//iBlock->blockIsConnected();
				}
			}
		}
		delete xmlLoader;
	}

	catch ( _2Real::XMLFormatException& e )
	{
		//std::cout << e.what() << "The xml file you tried to open does not correspond to a _2Real one." << std::endl;
	}
	catch (...)
	{
		//std::cout << "A POCO exception was probably thrown." << std::endl;
	}
}

void MainWindow::save()
{
	QFileDialog dialog(this, "Choose file to save");
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setDefaultSuffix("xml");
	QStringList fileNames;
	if (dialog.exec())
	{
		fileNames = dialog.selectedFiles();
		DataflowEngineManager::getInstance()->getEngine().safeConfig(fileNames.at(0).toUtf8().constData());
		Uber::xml::UbXMLWriter* ubXML = new Uber::xml::UbXMLWriter(fileNames.at(0));

		QList<QGraphicsItem *> items = DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->items();
		QList<QGraphicsItem *>::iterator iter;
		for ( iter = items.begin(); iter!= items.end(); ++iter )
		{
			if ( (*iter)->type() ==  Uber::BundleBlockType )
			{
				ubXML->addUbBlock(*dynamic_cast<UbBundleBlock*>(*iter) );
			} 
			else if ( 
				( (*iter)->type() ==  Uber::ImageBlockType ) ||
				( (*iter)->type() ==  Uber::SliderBlockType ) || 
				( (*iter)->type() ==  Uber::SpinBoxBlockType ) ||
				( (*iter)->type()   ==  Uber::PathBlockType  ))
			{
				ubXML->addInterfaceBlock(*dynamic_cast<UbInterfaceBlock*>(*iter) );
			}
		}
		//ubXML->addUbBlock(b);
		delete ubXML;
	}
}
bool MainWindow::event( QEvent * e )
{
	return QMainWindow::event(e);
}

