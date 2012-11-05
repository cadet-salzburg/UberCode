#pragma once
#include <QDomDocument>
#include <QString>
#include "UbBundleBlock.h"

namespace Ubercode {
	namespace xml {
		class UbXMLWriter
		{
		public:
			UbXMLWriter( QString const& filePath );
			~UbXMLWriter( void );
			void addUbBlock(  UbBundleBlock &UbBlock );
			void addUbElement();
		private:
			void initialize();
			void writeFile() const;
			QDomDocument m_DomDocument;
			QDomElement m_Root;
			QString m_FilePath;
		};
	}
}