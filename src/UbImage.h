#pragma once
#include <QGLWidget>
#include <QImage>
class UbImage  : public QGLWidget
{
public:
	UbImage( QWidget* parent = NULL );
	virtual ~UbImage(void);
	void setImage(const QImage& image);
	QSize sizeHint() const
	{
		return QSize(320, 240);
	}
protected:
    void paintEvent(QPaintEvent*);
private:
	QImage m_Image;
};