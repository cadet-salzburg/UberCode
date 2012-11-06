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
#include "helpers/_2RealException.h"

using namespace Uber;
MainWindow::MainWindow()
	: m_SettingsDialog( nullptr ),
	m_UiBuilderWindow( nullptr )
{
	QApplication::setOrganizationName("CADET");
	QApplication::setOrganizationDomain("cadet.at");
	QApplication::setApplicationName("UberCode");

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

	QGraphicsScene* s = DataflowEngineManager::getInstance()->addComposition()->getGraphicsScene();
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
				UbNode *outletNode = 0;
				UbNode *inletNode = 0;

				QList<Uber::UbInletNode*> inletList  = DataflowEngineManager::getInstance()->getInlets( inBlock );
				QList<Uber::UbOutletNode*> outletList = DataflowEngineManager::getInstance()->getOutlets( outBlock );

				QList<Uber::UbInletNode*>::iterator iterInlet = inletList.begin();
				for (;iterInlet!=inletList.end();++iterInlet)
				{
					if ( (*iterInlet)->getName() == inletId )
					{
						inletNode = *iterInlet;
						break;
					}
				}

				QList<Uber::UbOutletNode*>::iterator iterOutlet = outletList.begin();
				for (;iterOutlet!=outletList.end();++iter)
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


		delete xmlLoader;
	}

	catch ( _2Real::XMLFormatException& e )
	{
		std::cout << e.what() << "The xml file you tried to open does not correspond to a _2Real one." << std::endl;
	}
	catch (...)
	{
		std::cout << "A POCO exception was probably thrown." << std::endl;
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
		}
		//ubXML->addUbBlock(b);
		delete ubXML;
	}
}
bool MainWindow::event( QEvent * e )
{
	return QMainWindow::event(e);
}

