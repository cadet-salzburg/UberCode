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
#include <QString>
#include "UbBundleBlock.h"
#include "UbInterfaceBlock.h"

namespace Uber {
	namespace xml {
		class UbXMLWriter
		{
		public:
			UbXMLWriter( QString const& filePath );
			~UbXMLWriter( void );
			void addUbBlock(  UbBundleBlock &UbBlock );
			void addInterfaceBlock( const UbInterfaceBlock &block );
		private:
			void initialize();
			void writeFile() const;
			QDomDocument m_DomDocument;
			QDomElement m_Root;
			QString m_FilePath;
		};
	}
}