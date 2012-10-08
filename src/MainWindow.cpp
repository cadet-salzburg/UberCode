#include <QFileDialog>
#include <QObject>
#include "MainWindow.h"
#include "DataflowEngineManager.h"
#include "UbLinkController.h"


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
	// block navigation
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
	{
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)") );
	};
}
void MainWindow::save()
{
	std::cout << "Save was pressed" << std::endl;
}

bool MainWindow::event( QEvent * e )
{
	return QMainWindow::event(e);
}

