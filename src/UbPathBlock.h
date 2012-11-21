#pragma once
#include "UbInputBlock.h"
#include <QWidget>
#include <QLineEdit>
namespace Uber {
	class UbPathBlock : public UbInputBlock
	{
		Q_OBJECT
	public:
		UbPathBlock( QGraphicsItem *parent );
		virtual ~UbPathBlock(void);
		enum { Type = PathBlockType };

		virtual int			type() const { return Type; }
		virtual void		blockIsConnected();

		public slots:
			void			buttonPressed();
			void			setValue(QString value);

	protected:
		virtual void		arrangeNodes();

	private:
		void				init();
		//QLineEdit*			m_LineEdit;
		//QPushButton*		m_PushButton;
		//QHBoxLayout*		m_Layout;
		QWidget*			m_Widget;
		QString				m_FilePath;
		QLineEdit*			m_LineEdit;
	};
}