#pragma once

#include <QtGui/QDialog>
#include <QtGui/QListWidget>

class SettingsDialog : public QDialog 
{
	Q_OBJECT
		
public slots:
	void				onAddItemSlot();
	void				onRemoveSelectedItems();
	void				onAccept();

public:
	SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();

private:
	void				initUI();
	void				loadSettings();

	QListWidget*		m_OptionsWidget;

protected:
	void closeEvent(QCloseEvent *event);
	void showEvent(QShowEvent *event);
};