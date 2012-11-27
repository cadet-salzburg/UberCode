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
		typedef QPair< QString, QPair<QString, QString> > UiLinkData;
		class UbXMLReader
		{
		public:
			UbXMLReader(QString const& filePath);
			~UbXMLReader(void);
			QMap<QString, QPoint>			getBlockData();
			QMap<QString, QPoint>			getInterfaceData();
			QList<LinkData>					getLinkData();
			QList<UiLinkData>				getInterfaceLinkData();
		private:
			void							initialize();
			QString							m_FilePath;
			QDomDocument					m_DomDocument;
			QDomElement						m_Root;
			QMap<QString, QPoint>			m_BlockData;
			QList<LinkData>					m_LinkData;
			QMap<QString, QPoint>			m_InterfaceData;
			QList<UiLinkData>				m_UiLinkData;
		};
	}
}