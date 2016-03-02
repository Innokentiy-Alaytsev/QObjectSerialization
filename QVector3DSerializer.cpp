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

#include <QVector3D>


#include "Factory/FactoryHelperMacros.h"


#include "QVector3DSerializer.h"


using namespace QObjectSerialization;


FACTORY_ADD_PRODUCTION (CustomSerializer, QVector3DSerializer)

FACTORY_PRODUCTION_CREATE_OBJECT (CustomSerializer, QVector3DSerializer)

FACTORY_PRODUCTION_TYPEID_QT_METATYPE (QVector3DSerializer, QVector3D)


QDomNode QVector3DSerializer::serialize (QVariant i_value) {
	QDomDocument serializedDocument;

	if (i_value.canConvert< QVector3D > ()) {
		QDomElement serializedElement (
			serializedDocument
			.createElement (typeId ()));

		serializedDocument.appendChild (serializedElement);

		QVector3D vactor3D (i_value.value< QVector3D > ());

		serializedElement.setAttribute (
			"x",
			QString::number (
				vactor3D.x ()));
		serializedElement.setAttribute (
			"y",
			QString::number (
				vactor3D.y ()));
		serializedElement.setAttribute (
			"z",
			QString::number (
				vactor3D.z ()));
	}

	return QDomNode (serializedDocument);
}
