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


#include "QVector3DDeserializer.h"


using namespace QObjectSerialization;


FACTORY_ADD_PRODUCTION (CustomDeserializer, QVector3DDeserializer)

FACTORY_PRODUCTION_CREATE_OBJECT (CustomDeserializer, QVector3DDeserializer)

FACTORY_PRODUCTION_TYPEID_QT_METATYPE (QVector3DDeserializer, QVector3D)


QVariant QVector3DDeserializer::deserialize (QDomNode i_serializedValue) {
	QVariant deserializedValue;

	QDomElement serializedElement (i_serializedValue.toElement ());

	if (!serializedElement.isNull () &&
		(typeId () == serializedElement.tagName ())) {
		deserializedValue = QVector3D (
			serializedElement.attribute ("x").toFloat (),
			serializedElement.attribute ("y").toFloat (),
			serializedElement.attribute ("z").toFloat ());
	}

	return deserializedValue;
}
