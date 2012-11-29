/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH
		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include "UbMultiInletNode.h"
namespace Uber {
	UbMultiInletNode::UbMultiInletNode( QGraphicsItem *parent )
		:UbNode(parent),
		m_Container(0)
	{
		m_Color = QColor( 126,74,92);
		setAcceptedMouseButtons(Qt::RightButton|Qt::LeftButton);
		m_Container = new UbMultiNodeContainer(this);
		m_Animation = new QPropertyAnimation(m_Container, "percent");
		m_Animation->setDuration(300);
		m_Animation->setStartValue(0);
		m_Animation->setEndValue(100);
		connect(m_Animation,SIGNAL(valueChanged(const QVariant & )),m_Container, SLOT(createPath()) );

	}
	UbMultiInletNode::UbMultiInletNode( QGraphicsItem *parent,const _2Real::app::InletHandle& handle )
		:UbNode(parent)
		,m_Handle(handle),
		m_Container(0)
	{
		m_Color = QColor( 126,74,92);
		setAcceptedMouseButtons(Qt::RightButton|Qt::LeftButton);
		setName( QString::fromStdString( m_Handle.getName() ) );
		if ( m_Handle.getSize()== 0)
		{
			for ( int i=0; i<5; ++i )
			{
				m_Handle.add();
			}
		} 
		m_Container = new UbMultiNodeContainer(this, handle);
		m_Animation = new QPropertyAnimation(m_Container, "percent");
		m_Animation->setDuration(300);
		m_Animation->setStartValue(0);
		m_Animation->setEndValue(100);
		connect(m_Animation,SIGNAL(valueChanged(const QVariant & )),m_Container, SLOT(createPath()) );
	}

	UbMultiInletNode::~UbMultiInletNode(void)
	{
		std::cout << "Deleting  multinode" << std::endl;
	}
	void UbMultiInletNode::setHandle( const  _2Real::app::InletHandle& handle )
	{ 
		m_Handle = handle;
		setName( QString::fromStdString( m_Handle.getName() ) );
	}

	_2Real::app::InletHandle& UbMultiInletNode::getHandle()
	{ 
		return m_Handle; 
	}

	void UbMultiInletNode::expand()
	{
		m_Animation->setDirection(QAbstractAnimation::Forward);
		if (m_Animation->state() == QAbstractAnimation::Stopped )
			m_Animation->start();
	}

	void UbMultiInletNode::close()
	{
		m_Animation->setDirection(QAbstractAnimation::Backward);
		if (m_Animation->state() == QAbstractAnimation::Stopped )
			m_Animation->start();

	}

	void UbMultiInletNode::hoverEnterEvent( QGraphicsSceneHoverEvent * event )
	{
		//std::cout << "MultiInlet Hover Enter" << std::endl;
		if ( m_Animation->currentTime()==0)
		{
			expand();
		}
	}

	void UbMultiInletNode::hoverLeaveEvent( QGraphicsSceneHoverEvent * event )
	{
		//std::cout << "MultiInlet Hover Leave" << std::endl;
		close();
		//m_Animation->setCurrentTime(0);

		//UbNode::hoverLeaveEvent(event);
	}

	void UbMultiInletNode::hoverMoveEvent( QGraphicsSceneHoverEvent * event )
	{
		//std::cout << "MultiInlet Hover Move" << std::endl;
		//UbNode::hoverMoveEvent(event);
	}

	Uber::UbNodeRef UbMultiInletNode::getNodeUnderMouse()
	{
		return m_Container->getNodeUnderMouse();
	}

	QRectF UbMultiInletNode::boundingRect() const
	{
		QRectF rect = UbNode::boundingRect();
		if ( m_Handle.getSize()>0)
		{
			QRectF rectContainer = m_Container->boundingRect();
			////std::cout << "RectContainer" << rectContainer.x() << " " <<  rectContainer.y() << " " << rectContainer.width() << " " << rectContainer.height() << std::endl;
			rect.setTopLeft(rectContainer.topLeft());
			rect.setTopRight(rectContainer.topRight());
		}
		////std::cout << "RectA" << rect.x() << " " <<  rect.y() << " " << rect.width() << " " << rect.height() << std::endl;
		return rect;
	}

}
