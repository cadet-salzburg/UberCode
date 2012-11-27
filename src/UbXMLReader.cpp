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
				//std::cout << "The xml file is in read-only mode" << std::endl;
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
			//Get Interface Data
			QDomNode uiInstances = ubercodeData.namedItem("ui_instances");
			QDomNode currentUiInstance = uiInstances.firstChildElement("ui_instance");
			while ( !currentUiInstance.isNull() )
			{
				QString uiString;
				QPoint  uiPosition;
				QDomNode uiInstanceName = currentUiInstance.namedItem("ui_instance_name");
				if ( uiInstanceName.isElement() )
				{
					uiString = uiInstanceName.toElement().text();
				}

				QDomNode position = currentUiInstance.namedItem("position");
				QDomNode posX = position.namedItem("x");
				QDomNode posY = position.namedItem("y");
				if ( posX.isElement() )
				{
					uiPosition.setX( posX.toElement().text().toInt() );
				}
				if ( posY.isElement() )
				{
					uiPosition.setY( posY.toElement().text().toInt() );
				}
				m_InterfaceData.insert( uiString, uiPosition );

				currentUiInstance = currentUiInstance.nextSiblingElement("ui_instance");
			}
			//Get Interface-Link Data
			QDomNode uiLinks	= ubercodeData.namedItem("ui_links");
			QDomNode uiLink = uiLinks.firstChildElement("ui_link");
			while ( !uiLink.isNull() )
			{
				QDomNode uiNode = uiLink.namedItem("ui_node");
				QDomNode uiName = uiNode.namedItem("ui_name");
				QString uiString = uiName.toElement().text();

				QDomNode blockNode = uiLink.namedItem("block_node");

				QDomNode blockName = blockNode.namedItem("block_name");
				QString blockNameString = blockName.toElement().text();

				QDomNode nodeName = blockNode.namedItem("node_name");
				QString  nodeNameString = nodeName.toElement().text();

				QPair<QString, QString> blockData( blockNameString,nodeNameString );
				UiLinkData uilinkData(uiString,blockData);
				m_UiLinkData.push_back(uilinkData);
				uiLink = uiLink.nextSiblingElement("ui_link");
			}
			//
		}

		QMap<QString, QPoint> UbXMLReader::getBlockData()
		{
			return m_BlockData;
		}
		QList<LinkData> UbXMLReader::getLinkData()
		{
			return m_LinkData;
		}

		QMap<QString, QPoint> UbXMLReader::getInterfaceData()
		{
			return m_InterfaceData;
		}

		QList<UiLinkData> UbXMLReader::getInterfaceLinkData()
		{
			return m_UiLinkData;
		}

	} // namespace xml
} // namespace Ubercode