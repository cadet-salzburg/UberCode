#pragma once
#include <QDomDocument>
#include <string>
#include <QMap>
#include <QString>
#include <QPoint>
#include "UbBundleBlock.h"

namespace Ubercode {
	namespace xml {
		class UbXMLReader
		{
		public:
			UbXMLReader(QString const& filePath);
			~UbXMLReader(void);
			QMap<QString, QPoint> getData();
		private:
			void initialize();
			QString m_FilePath;
			QDomDocument m_DomDocument;
			QDomElement m_Root;
			QMap<QString, QPoint> m_BlockData;
		};
	}
}