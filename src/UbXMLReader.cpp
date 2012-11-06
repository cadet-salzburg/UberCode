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
		}
		QMap<QString, QPoint> UbXMLReader::getData()
		{
			return m_BlockData;
		}
	} // namespace xml
} // namespace Ubercode