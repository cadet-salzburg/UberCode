#pragma once
#include <QObject>
#include <QGraphicsItem>

class QGraphicsScene;
class UbLink;
class UbNode;
class UbLinkController : public QObject
{
	Q_OBJECT
public:
	static	UbLinkController*	getInstance();
	static	void				setScene( QGraphicsScene * scene );
	void						addLink( UbNode* start, UbNode* end ); 
	void						addLink( UbLink* const link );
	void						removeLink( UbLink* const link );
	bool						eventFilter(QObject * obj, QEvent * e );
	void						render();

	QGraphicsItem*				itemAt(const QPointF &pos);

private:
	UbLinkController(void);
	~UbLinkController(void);
	static UbLinkController*	m_Instance;
	static QGraphicsScene*		m_Scene;
	UbLink*						m_CurrentLink;
	//bool						itemIs( QGraphicsItem * item, int type );
	bool						processStartLink( QGraphicsSceneMouseEvent * e );
	bool						processUpdateLink( QGraphicsSceneMouseEvent * e );
	bool						processEndLink( QGraphicsSceneMouseEvent *e );
	bool						eventHappenedAtNode( QGraphicsSceneMouseEvent * e );
	//QList<UbLink*>			m_Links;
};