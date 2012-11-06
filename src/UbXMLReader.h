#pragma once
#include <QDomDocument>
#include <string>
#include <QMap>
#include <QPair>
#include <QString>
#include <QPoint>
#include "UbBundleBlock.h"

namespace Ubercode {
	namespace xml {
		typedef QPair< QPair<QString, QString>, QPair<QString, QString> > LinkData;
		class UbXMLReader
		{
		public:
			UbXMLReader(QString const& filePath);
			~UbXMLReader(void);
			QMap<QString, QPoint>	getBlockData();
			QList<LinkData>			getLinkData();
		private:
			void initialize();
			QString m_FilePath;
			QDomDocument m_DomDocument;
			QDomElement m_Root;
			QMap<QString, QPoint> m_BlockData;
			QList<LinkData>		  m_LinkData;
		};
	}
}