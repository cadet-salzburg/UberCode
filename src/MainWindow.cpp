#include "MainWindow.h"
#include "DataflowEngineManager.h"

#include "UbLinkController.h"

#include <QObject>
#include <QGraphicsView>

MainWindow::MainWindow()
	: m_SettingsDialog( nullptr ),
	  m_UiBuilderWindow( nullptr )
{
	QApplication::setOrganizationName("CADET");
	QApplication::setOrganizationDomain("cadet.at");
	QApplication::setApplicationName("UberCode");

	m_UiBuilderWindow = new Ui_MainWindow;
	m_UiBuilderWindow->setupUi( this );

	m_SettingsDialog = new SettingsDialog;

	// Block Navigation
	m_BlockNavigationTreeWidget = new BlockNavigationTreeWidget();
	m_UiBuilderWindow->dockWidget->setWidget(m_BlockNavigationTreeWidget);
	// Workbench
	m_WorkbenchGraphicsView = new QGraphicsView();
	m_WorkbenchGraphicsView->setViewport(new QGLWidget( QGLFormat( QGL::SampleBuffers ) ) );
	m_WorkbenchGraphicsView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate);
    m_WorkbenchGraphicsView->setScene(new OpenGLScene);
        view.show();


	m_WorkbenchGraphicsView->setRenderHint(QPainter::Antialiasing);
	QGraphicsScene* s = DataflowEngineManager::getInstance()->addComposition()->getGraphicsScene();
	m_WorkbenchGraphicsView->setScene( s );
	UbLinkController::getInstance()->setScene( s );
	m_UiBuilderWindow->workbenchLayout->addWidget(m_WorkbenchGraphicsView);

	// Connect Slots
	QObject::connect( m_UiBuilderWindow->actionOptions, SIGNAL(activated()), m_SettingsDialog, SLOT(show()));
}

MainWindow::~MainWindow(void)
{
}



