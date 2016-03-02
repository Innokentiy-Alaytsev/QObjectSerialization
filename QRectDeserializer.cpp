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

#include "QRectDeserializer.h"


#include <QRect>
#include <QRectF>


Factory::AddProduction<
	QObjectSerialization::CustomDeserializer,
	QObjectSerialization::QRectFDeserializer > addQRectFDeserializer;
Factory::AddProduction<
	QObjectSerialization::CustomDeserializer,
	QObjectSerialization::QRectDeserializer > addQRectDeserializer;


std::shared_ptr< QObjectSerialization::CustomDeserializer >
QObjectSerialization::QRectFDeserializer::createObject () {
	return std::shared_ptr< CustomDeserializer > (new QRectFDeserializer);
}


QString QObjectSerialization::QRectFDeserializer::typeId () {
	static QString s_typeId (
		QMetaType::typeName (
			QMetaType::QRectF));

	return s_typeId;
}


QVariant QObjectSerialization::QRectFDeserializer::deserialize (QDomNode i_serializedValue) {
	QVariant deserializedValue;

	QDomElement serializedElement (i_serializedValue.toElement ());

	if (!serializedElement.isNull () &&
		(typeId () == serializedElement.tagName ())) {
		deserializedValue = QRectF (
			serializedElement.attribute ("x").toFloat (),
			serializedElement.attribute ("y").toFloat (),
			serializedElement.attribute ("width").toFloat (),
			serializedElement.attribute ("height").toFloat ());
	}

	return deserializedValue;
}


std::shared_ptr< QObjectSerialization::CustomDeserializer >
QObjectSerialization::QRectDeserializer::createObject () {
	return std::shared_ptr< CustomDeserializer > (new QRectDeserializer);
}


QString QObjectSerialization::QRectDeserializer::typeId () {
	static QString s_typeId (
		QMetaType::typeName (
			QMetaType::QRect));

	return s_typeId;
}


QVariant QObjectSerialization::QRectDeserializer::deserialize (QDomNode i_serializedValue) {
	QDomElement serializedElement (i_serializedValue.toElement ());

	serializedElement.setTagName (QRectFDeserializer::typeId ());

	return QRectFDeserializer ().deserialize (serializedElement);
}
