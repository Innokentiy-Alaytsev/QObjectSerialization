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
