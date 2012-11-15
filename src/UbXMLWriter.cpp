#include <QFile>
#include <QTextStream>
#include <iostream>
#include "UbXMLWriter.h"


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
				std::cout << "The xml file is in read-only mode" << std::endl;
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
				std::cout << "There was no root element found that is named \"config\" " <<std::endl;
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