#include <QFileDialog>
#include <QObject>
#include <QString>
#include <QPoint>
#include "MainWindow.h"
#include "DataflowEngineManager.h"
#include "UbLinkController.h"
#include "UbXMLWriter.h"
#include "UbXMLReader.h"
#include "helpers/_2RealException.h"

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
	m_WorkbenchGraphicsView->setScene( s );
	UbLinkController::getInstance()->setScene( s );
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
		QMap<QString, QPoint> data = xmlLoader->getData();
		QMap<QString, QPoint>::const_iterator it = data.constBegin();
		while ( it!= data.constEnd() )
		{
			UbBundleBlock *block = new UbBundleBlock( 0, it.key() );
			block->setPos( it.value() );
			DataflowEngineManager::getInstance()->getComposition()->getGraphicsScene()->addItem(block);
			++it;
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
		Ubercode::xml::UbXMLWriter* ubXML = new Ubercode::xml::UbXMLWriter(fileNames.at(0));

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

