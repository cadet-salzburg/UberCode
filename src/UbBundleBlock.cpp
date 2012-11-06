#include <exception>
#include "UbBundleBlock.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
#include "app/_2RealEngine.h"

using namespace _2Real;
using namespace _2Real::app;
using namespace std;

namespace Uber {

	UbBundleBlock::UbBundleBlock(QGraphicsItem *parent,  _2Real::app::BundleHandle handle, QString blockName)
		:UbAbstractBlock(parent)
	{
		try
		{
			m_BlockHandle = handle.createBlockInstance( blockName.toStdString() );
			m_fDefaultFps = 30.0;
			m_BlockHandle.setUpdateRate( m_fDefaultFps );
			m_BlockHandle.setup();
			m_BlockHandle.start();
			m_BlockId = QString::fromUtf8( m_BlockHandle.getIdAsString().c_str() );
		}
		catch ( Exception &e )
		{
			cout << e.message() << " " << e.what() << endl;
		}
		constructPath();
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
				std::cout << "found " << std::endl;
				break;
			}
		}

		if ( iter != blockHandles.end() )
		{
			m_BlockHandle	= *iter;
			m_BlockId = QString::fromUtf8( m_BlockHandle.getIdAsString().c_str() );
		} else
		{
			throw std::exception("Cannot find any block instance with the specified Id.");
		}
		constructPath();
	}

	UbBundleBlock::~UbBundleBlock(void)
	{

	}

	void UbBundleBlock::addNodes()
	{
		qreal nodeSpacing = 4;

		try
		{
			int inletIdx   = 0;
			int outletIdx  = 0;

			//Create Inlets
			BlockInfo::InletInfos inlets = m_BlockHandle.getBlockInfo().inlets;
			for(auto it = inlets.begin(); it != inlets.end(); it++)
			{
				UbInletNode *node = new UbInletNode(this, m_BlockHandle.getInletHandle(it->name));
				//m_Inputs.append( node );
				QPointF pos = QPointF(-m_Width/2.f, -m_Height/2.f) + node->getRadius()*QPointF(1.f,1.f) + QPointF(m_CornerRadius, m_CornerRadius);
				node->setPos( pos + inletIdx*(2*node->getRadius()+nodeSpacing)*QPointF(1.f, 0.f));
				inletIdx++;
			}

			//Create Outlets
			BlockInfo::OutletInfos outlets = m_BlockHandle.getBlockInfo().outlets;
			for(auto it = outlets.begin(); it != outlets.end(); it++)
			{
				UbOutletNode *node = new UbOutletNode(this, m_BlockHandle.getOutletHandle(it->name));
				//m_Outputs.append( node );
				QPointF pos = -QPointF(-m_Width/2.f, -m_Height/2.f) - node->getRadius()*QPointF(1.f,1.f) - QPointF(m_CornerRadius, m_CornerRadius);
				node->setPos( pos - outletIdx*(2*node->getRadius()+nodeSpacing)*QPointF(1.f, 0.f));
				outletIdx++;
			}
		}
		catch(Exception& e)
		{
			cout << e.message() << e.what() << std::endl;
		}
	}
}