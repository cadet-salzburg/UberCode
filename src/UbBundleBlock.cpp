#include "UbBundleBlock.h"
#include "UbInletNode.h"
#include "UbOutletNode.h"
using namespace _2Real;
using namespace _2Real::app;
using namespace std;


UbBundleBlock::UbBundleBlock(QGraphicsItem *parent,  _2Real::app::BundleHandle handle, QString blockName)
	:UbAbstractBlock(parent)
	,m_BundleHandle(handle)
	,m_BlockName(blockName)
{
	setup();
}
UbBundleBlock::~UbBundleBlock(void)
{

}

void UbBundleBlock::setup()
{
	try
	{
		m_BlockHandle = m_BundleHandle.createBlockInstance( m_BlockName.toStdString() );
		m_fDefaultFps = 30.0;
		m_BlockHandle.setUpdateRate( m_fDefaultFps );
		m_BlockHandle.setup();
		m_BlockHandle.start();
	}
	catch ( Exception &e )
	{
		cout << e.message() << " " << e.what() << endl;
	}
	constructPath();
}
//void UbBundleBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//
//}

void UbBundleBlock::addNodes()
{
	qreal nodeSpacing = 4;

	try
	{
		int inletIdx   = 0;
		int outletIdx  = 0;

		//Create Inlets
		BlockInfo::ParameterInfos inlets = m_BlockHandle.getBlockInfo().getInlets();
		for(auto it = inlets.begin(); it != inlets.end(); it++)
		{
			UbInletNode *node = new UbInletNode(this, m_BlockHandle.getInletHandle(it->getName()));
			//m_Inputs.append( node );
			QPointF pos = QPointF(-m_Width/2.f, -m_Height/2.f) + node->getRadius()*QPointF(1.f,1.f) + QPointF(m_CornerRadius, m_CornerRadius);
			node->setPos( pos + inletIdx*(2*node->getRadius()+nodeSpacing)*QPointF(1.f, 0.f));
			inletIdx++;
		}

		//Create Outlets
		BlockInfo::ParameterInfos outlets = m_BlockHandle.getBlockInfo().getOutlets();
		for(auto it = outlets.begin(); it != outlets.end(); it++)
		{
			UbOutletNode *node = new UbOutletNode(this, m_BlockHandle.getOutletHandle(it->getName()));
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