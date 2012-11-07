#include "UbImageBlock.h"

namespace Uber {
	UbImageBlock::UbImageBlock( QGraphicsItem *parent )
		:m_Node(0),
		m_Image( new UbImage() )
	{

	}
	UbImageBlock::~UbImageBlock(void)
	{

	}
	void UbImageBlock::setNode( UbOutletNode *node )
	{
		m_Node = node;
	}
	void UbIOBlock::updateData(_2Real::app::AppData data) 
	{
		m_Data = data;
		if ( m_Node && m_Node->type() == Uber::OutputNodeType )
		{
			UbOutletNode *m_OutletNode = 0;
			m_OutletNode =  dynamic_cast<UbOutletNode*>(m_Node);


			try
			{
				if( m_OutletNode->getHandle().getTypename() == "number image" )
				{
					Image const& img = m_Data.getData< Image >();
					QImage q( img.getData(), img.getWidth(), img.getHeight(), 3*img.getWidth(), QImage::Format_RGB888 );
					//QImage q2 = q.copy();
					dynamic_cast<UbImage*>(m_ValueWidget)->setImage(q);
					m_ProxyWidget->update();
				}
				update();
			}
			catch(Exception& e)
			{
				cout << e.message() << e.what() << std::endl;
			}
		}
	}
}