#pragma once
#include <QGraphicsPathItem>

class UbNode;
class UbLink : public QGraphicsPathItem
{
public:
	UbLink(QGraphicsItem *parent = 0,  QGraphicsScene *scene = 0);
	virtual	~UbLink();

	void		updatePath();
	void		paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
	void		setDragPos( QPointF pos);
	void		setStartNode( UbNode* start );
	void		setEndNode( UbNode* end );

	UbNode*		getStartNode() const;
	UbNode*		getEndNode() const;

	//
	void		setStartPos( QPointF start );
	void		setEndPos( QPointF end );
	//
	void		setNodes( UbNode* start, UbNode* end );

	void		startedChanging();
	void		finishedChanging();
	bool		isChanging() const;

private:


	bool		m_IsSet;
	bool		m_IsChanging;
	UbNode*		m_StartNode;
	UbNode*		m_EndNode;
	QPointF		m_StartPos;
	QPointF		m_EndPos;
};