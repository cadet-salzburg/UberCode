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
#include <exception>
#include "UbBundleBlock.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
#include "UbMultiInletNode.h"
#include "app/_2RealEngine.h"
#include "DataflowEngineManager.h"
#include <QToolTip>

using namespace _2Real;
using namespace _2Real::app;
using namespace std;

namespace Uber {

	UbBundleBlock::UbBundleBlock(QGraphicsItem *parent,  _2Real::app::BundleHandle handle, QString blockName) :
		UbAbstractBlock( parent )
	{
		try
		{
			m_BlockHandle = handle.createBlockInstance( blockName.toStdString() );
			m_BlockHandle.setUpdateRate( 30 );
			m_BlockHandle.setup();
			m_BlockHandle.start();
			m_BlockId = QString::fromUtf8( m_BlockHandle.getIdAsString().c_str() );
		}
		catch ( Exception &e )
		{
			cout << e.message() << " " << e.what() << endl;
		}
		arrangeNodes();
		setAcceptHoverEvents( true ); 
		//setToolTip( QString::fromUtf8( m_BlockHandle.getBlockInfo().name.c_str() ) );
	}

	UbBundleBlock::UbBundleBlock( QGraphicsItem *parent,  QString blockInstanceId )
		:UbAbstractBlock(parent)
	{
		Engine::BlockHandles blockHandles = Engine::instance().getCurrentBlocks();
		Engine::BlockHandleIterator iter = blockHandles.begin();
		for ( ; iter!= blockHandles.end(); ++iter )
		{
			if ( iter->getIdAsString() == blockInstanceId.toUtf8().constData() )
			{
				//std::cout << "found " << std::endl;
				break;
			}
		}

		if ( iter != blockHandles.end() )
		{
			m_BlockHandle	= *iter;
			m_BlockId = QString::fromUtf8( m_BlockHandle.getIdAsString().c_str() );
			setName(m_BlockId);
		} else
		{
			throw std::exception("Cannot find any block instance with the specified Id.");
		}
		//arrangeNodes();
		setAcceptHoverEvents( true ); 
	}

	UbBundleBlock::~UbBundleBlock()
	{
		std::cout << "goodbye" << std::endl;
		//m_BlockHandle.kill();
	}

	void UbBundleBlock::arrangeNodes()
	{
		qreal nodeSpacing = 5;

		try
		{
			int inletIdx   = 0;
			int outletIdx  = 0;

			//Create Inlets
			BlockInfo::InletInfos inlets = m_BlockHandle.getBlockInfo().inlets;
			for(auto it = inlets.begin(); it != inlets.end(); it++)
			{
				_2Real::app::InletHandle handle = m_BlockHandle.getInletHandle(it->name);
				if ( handle.isMultiInlet() )
				{
					UbMultiInletNodeRef node(new UbMultiInletNode(this,handle));
					QPointF pos = QPointF(-m_Width/2.f, -m_Height/2.f) + QPointF( node->getWidth()/2,node->getHeight()/2 ) + QPointF(m_CornerRadius, m_CornerRadius);
					node->setPos( pos + inletIdx*(node->getWidth()+nodeSpacing)*QPointF(1.f, 0.f));
					m_Inlets.push_back(node);
				} else
				{
					UbInletNodeRef node(new UbInletNode(this, handle));
					QPointF pos = QPointF(-m_Width/2.f, -m_Height/2.f) + QPointF( node->getWidth()/2,node->getHeight()/2 ) + QPointF(m_CornerRadius, m_CornerRadius);
					node->setPos( pos + inletIdx*(node->getWidth()+nodeSpacing)*QPointF(1.f, 0.f));
					m_Inlets.push_back(node);
				}
				//m_Inputs.append( node );

				inletIdx++;
			}

			//Create Outlets
			BlockInfo::OutletInfos outlets = m_BlockHandle.getBlockInfo().outlets;
			for(auto it = outlets.begin(); it != outlets.end(); it++)
			{
				UbOutletNodeRef node( new UbOutletNode(this, m_BlockHandle.getOutletHandle(it->name)));
				//m_Outputs.append( node );
				QPointF pos = -QPointF(-m_Width/2.f, -m_Height/2.f) - QPointF( node->getWidth()/2,node->getHeight()/2 ) - QPointF(m_CornerRadius, m_CornerRadius);
				node->setPos( pos - outletIdx*(node->getWidth()+nodeSpacing)*QPointF(1.f, 0.f));
				m_Outlets.push_back(node);
				outletIdx++;
			}
		}
		catch(Exception& e)
		{
			cout << e.message() << e.what() << std::endl;
		}
	}

	QVector<UbNodeRef> const& UbBundleBlock::getInlets() const
	{
		return m_Inlets;
	}

	QVector<UbNodeRef> const& UbBundleBlock::getOutlets() const
	{
		return m_Outlets;
	}
	void UbBundleBlock::hoverMoveEvent ( QGraphicsSceneHoverEvent * event )
	{
		QPointF pos = event->lastScreenPos();
		QToolTip::showText( QPoint(pos.x(),pos.y()), QString::fromUtf8(m_BlockHandle.getBlockInfo().name.c_str()) );
	}
}