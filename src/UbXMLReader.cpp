#include <QFile>
#include <QTextStream>
#include <iostream>
#include "UbXMLReader.h"

namespace Ubercode {
	namespace xml {

		UbXMLReader::UbXMLReader(QString const& filePath)
			:m_FilePath(filePath)
		{
			initialize();
		}
		UbXMLReader::~UbXMLReader(void)
		{

		}
		void UbXMLReader::initialize()
		{
			QFile file( m_FilePath );
			if ( !file.open(QIODevice::ReadWrite ) )
			{
				std::cout << "The xml file is in read-only mode" << std::endl;
				return;
			}
			if ( !m_DomDocument.setContent(&file) )
			{
				file.close();
				return;
			}
			m_Root = m_DomDocument.documentElement();
			//Get Block Data
			QDomNode ubercodeData	= m_Root.namedItem("ubercode_data");
			QDomNode blockInstances = ubercodeData.namedItem("block_instances");

			QDomNode currentBlockInstance = blockInstances.firstChildElement("block_instance");
			while ( !currentBlockInstance.isNull() )
			{
				QDomNode blockInstanceId = currentBlockInstance.namedItem("block_instance_id");

				QString blockInstIdString;
				QPoint  blockInstPos;
				if ( blockInstanceId.isElement() )
				{
					blockInstIdString = blockInstanceId.toElement().text();
				}
				QDomNode position = currentBlockInstance.namedItem("position");
				QDomNode posX = position.namedItem("x");
				QDomNode posY = position.namedItem("y");
				if ( posX.isElement() )
				{
					blockInstPos.setX( posX.toElement().text().toInt() );
				}
				if ( posY.isElement() )
				{
					blockInstPos.setY( posY.toElement().text().toInt() );
				}
				m_BlockData.insert( blockInstIdString, blockInstPos );
				currentBlockInstance = currentBlockInstance.nextSiblingElement("block_instance");
			}
			//Get Link Data
			QDomNode links	= m_Root.namedItem("links");
			QDomNode currentLink = links.firstChildElement("link");
			while ( !currentLink.isNull() )
			{
				QDomNode inlet = currentLink.namedItem("inlet");
				QDomNode outlet = currentLink.namedItem("outlet");
				QDomNode inletId = inlet.namedItem("inlet_id");
				QDomNode inletBlockId = inlet.namedItem("block_instance_id");
				QDomNode outletId = outlet.namedItem("outlet_id");
				QDomNode outletBlockId = outlet.namedItem("block_instance_id");
				QPair<QString, QString> inletData(inletBlockId.toElement().text(),inletId.toElement().text());
				QPair<QString, QString> outletData(outletBlockId.toElement().text(),outletId.toElement().text());
				LinkData linkData(outletData,inletData);
				m_LinkData.push_back(linkData);
				currentLink = currentLink.nextSiblingElement("link");
			}
		}

		QMap<QString, QPoint> UbXMLReader::getBlockData()
		{
			return m_BlockData;
		}
		QList<LinkData> UbXMLReader::getLinkData()
		{
			return m_LinkData;
		}
	} // namespace xml
} // namespace Ubercode