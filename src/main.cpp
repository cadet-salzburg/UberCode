#include "MainWindow.h"

#include <windows.h>

#include <QApplication>
#include <QFile>

QString	readStyleSheet()
{
	QFile File("./data/ubercode.qss");
	File.open(QFile::ReadOnly);
	return  QLatin1String(File.readAll());
}

int main(int argc, char *argv[])
{
	QApplication* app = new QApplication(argc, argv);
	MainWindow*	m_UberCode = new MainWindow();

	// icon and style settings
	//app->setStyleSheet( readStyleSheet() );
	app->setWindowIcon(  QIcon("./data/logo.ico") );

	m_UberCode->show();
	int iRet = app->exec();
	return iRet;
};