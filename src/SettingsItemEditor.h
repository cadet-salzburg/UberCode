#pragma once
#include <QLineEdit>
#include <QToolButton>

class SettingsItemEditor : public QWidget
{
	Q_OBJECT

public:
	SettingsItemEditor( QWidget* parent = 0 );
	QString			getContent() const;
	void			setContent( const QString& content );
	QLineEdit*		m_TextField;

private:
	QToolButton*	m_Button;
	void			init();

	private slots:
		void openFileDialog();
};