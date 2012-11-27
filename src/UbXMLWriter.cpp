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
#include "UbXMLWriter.h"
#include "UbLinkController.h"
#include "UbPathBlock.h"

namespace Uber {
	namespace xml {

		UbXMLWriter::UbXMLWriter( QString const& filePath )
			:m_FilePath(filePath)
		{
			initialize();
		}
		UbXMLWriter::~UbXMLWriter()
		{
			writeFile();
		}
		void UbXMLWriter::initialize()
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

			file.close();
			m_Root = m_DomDocument.documentElement();
			if ( m_Root.tagName() != "config") {
				//std::cout << "There was no root element found that is named \"config\" " <<std::endl;
				return;
			}
		}

		void UbXMLWriter::addUbBlock(  UbBundleBlock &UbBlock )
		{
			QDomNode ubercodeData;
			QDomNode blockInstances;
			ubercodeData	= m_Root.namedItem("ubercode_data"); 
			if ( ubercodeData.isNull() )
			{
				ubercodeData	 = m_Root.appendChild(m_DomDocument.createElement("ubercode_data"));
			}
			blockInstances	= ubercodeData.namedItem("block_instances"); 
			if ( blockInstances.isNull() )
			{
				blockInstances  = ubercodeData.appendChild(m_DomDocument.createElement("block_instances"));
			}

			QDomNode blockInstance   = blockInstances.appendChild(m_DomDocument.createElement("block_instance"));
			QDomNode blockInstanceId = blockInstance.appendChild(m_DomDocument.createElement("block_instance_id"));
			QDomText blockInstanceIdName = m_DomDocument.createTextNode( QString::fromUtf8( UbBlock.getHandle().getIdAsString().c_str()));
			blockInstanceId.appendChild(blockInstanceIdName);
			QDomNode position = blockInstance.appendChild(m_DomDocument.createElement("position"));
			QDomNode positionX = position.appendChild(m_DomDocument.createElement("x"));
			QDomNode positionY = position.appendChild(m_DomDocument.createElement("y"));
			QDomText positionXvalue = m_DomDocument.createTextNode(QString::number(UbBlock.x()));
			QDomText positionYvalue = m_DomDocument.createTextNode(QString::number(UbBlock.y()));
			positionX.appendChild(positionXvalue);
			positionY.appendChild(positionYvalue);
		}

		void UbXMLWriter::addInterfaceBlock( const UbInterfaceBlock &block )
		{
			QDomNode ubercodeData;
			QDomNode uiInstances;
			ubercodeData	= m_Root.namedItem("ubercode_data"); 
			if ( ubercodeData.isNull() )
			{
				ubercodeData	 = m_Root.appendChild(m_DomDocument.createElement("ubercode_data"));
			}
			uiInstances	= ubercodeData.namedItem("ui_instances"); 
			if ( uiInstances.isNull() )
			{
				uiInstances  = ubercodeData.appendChild(m_DomDocument.createElement("ui_instances"));
			}
			QDomNode uiInstance   = uiInstances.appendChild(m_DomDocument.createElement("ui_instance"));
			QDomNode uiInstanceNameTag = uiInstance.appendChild(m_DomDocument.createElement("ui_instance_name"));
			QDomText uiInstanceName = m_DomDocument.createTextNode( block.getName() );
			uiInstanceNameTag.appendChild(uiInstanceName);
			QDomNode position = uiInstance.appendChild(m_DomDocument.createElement("position"));
			QDomNode positionX = position.appendChild(m_DomDocument.createElement("x"));
			QDomNode positionY = position.appendChild(m_DomDocument.createElement("y"));
			QDomText positionXvalue = m_DomDocument.createTextNode(QString::number(block.x()));
			QDomText positionYvalue = m_DomDocument.createTextNode(QString::number(block.y()));
			positionX.appendChild(positionXvalue);
			positionY.appendChild(positionYvalue);
			 if ( block.type() == PathBlockType )
			 {
				 const UbPathBlock &pathBlock = static_cast<const  UbPathBlock&>(block);
				 QDomNode value = uiInstance.appendChild(m_DomDocument.createElement("value"));
				 QString val = pathBlock.getValue();
				 QDomText valueString = m_DomDocument.createTextNode(val);
				 value.appendChild(valueString);
			 }
			//Get link ( if any )
			UbNodeRef nd = block.getNode();
			QVector<UbLinkRef> links = UbLinkController::getInstance()->getLinksWithEndNode(nd);

			QVector<UbLinkRef>::iterator iter = links.begin();
			for ( ;iter!=links.end(); ++iter )
			{
				UbLinkRef link = *iter;
				UbNodeRef startNode = link->getStartNode();
				QString startNodeId = startNode->getName();
				QString blockStrId("");

				UbObject* parent = startNode->getParentBlock();
				if ( parent )
				{
					UbBundleBlock *b = static_cast<UbBundleBlock*>(parent);
					blockStrId = b->getBlockId();
				};
				//Write the details to XML
				QDomNode uiLinks	= ubercodeData.namedItem("ui_links"); 
				if ( uiLinks.isNull() )
				{
					uiLinks  = ubercodeData.appendChild(m_DomDocument.createElement("ui_links"));
				}
				QDomNode uiLink   = uiLinks.appendChild(m_DomDocument.createElement("ui_link"));
				QDomNode interfaceNode  = uiLink.appendChild(m_DomDocument.createElement("ui_node"));
				QDomNode uiId  = interfaceNode.appendChild(m_DomDocument.createElement("ui_name"));
				QDomText uiIdText = m_DomDocument.createTextNode( block.getName() );
				uiId.appendChild(uiIdText);
				//
				QDomNode blockNode  = uiLink.appendChild(m_DomDocument.createElement("block_node"));
				//
				QDomNode blockId  = blockNode.appendChild(m_DomDocument.createElement("block_name"));
				QDomText blockIdText = m_DomDocument.createTextNode( blockStrId );
				blockId.appendChild(blockIdText);
				//
				QDomNode nodeId = blockNode.appendChild(m_DomDocument.createElement("node_name"));
				QDomText nodeIdText = m_DomDocument.createTextNode(startNodeId);
				nodeId.appendChild(nodeIdText);
				//
			}
		}
		void UbXMLWriter::writeFile() const
		{
			QFile file( m_FilePath );
			if ( file.open( QIODevice::WriteOnly ) ) 
			{
				QTextStream textStream(&file);
				textStream << m_DomDocument.toString() ;
				file.close();
			}
		}
	} // end namespace xml
} //end namespace ubercode