/*
  The MIT License (MIT)

  Copyright (c) 2016 Innokentij Alajcev (Иннокентий Алайцев) <alaitsev@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "QStringListSerializer.h"


#include <QStringList>


Factory::AddProduction<
	QObjectSerialization::CustomSerializer,
	QObjectSerialization::QStringListSerializer > addQStringListSerializer;


std::shared_ptr< QObjectSerialization::CustomSerializer >
QObjectSerialization::QStringListSerializer::createObject () {
	return std::shared_ptr< CustomSerializer > (new QStringListSerializer);
}


QString QObjectSerialization::QStringListSerializer::typeId () {
	static QString s_typeId (
		QMetaType::typeName (
			QMetaType::QStringList));

	return s_typeId;
}


QDomNode QObjectSerialization::QStringListSerializer::serialize (QVariant i_value) {
	QDomDocument serializedDocument;

	QDomElement serializedElement (
		serializedDocument
		.createElement (typeId ()));

	serializedDocument.appendChild (serializedElement);

	QStringList stringList (i_value.toStringList ());

	foreach (QString string, stringList) {
		QDomElement stringElement (
			serializedDocument.createElement ("string"));

		stringElement.setAttribute (
			"text",
			string);

		serializedElement.appendChild (stringElement);
	}

	return QDomNode (serializedDocument);
}
