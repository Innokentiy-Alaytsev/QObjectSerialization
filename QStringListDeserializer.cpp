#include "QStringListDeserializer.h"


#include <QStringList>


Factory::AddProduction<
	QObjectSerialization::CustomDeserializer,
	QObjectSerialization::QStringListDeserializer > addQStringListDeserializer;


std::shared_ptr< QObjectSerialization::CustomDeserializer >
QObjectSerialization::QStringListDeserializer::createObject () {
	return std::shared_ptr< CustomDeserializer > (new QStringListDeserializer);
}


QString QObjectSerialization::QStringListDeserializer::typeId () {
	static QString s_typeId (
		QMetaType::typeName (
			QMetaType::QStringList));

	return s_typeId;
}

QVariant QObjectSerialization::QStringListDeserializer::deserialize (QDomNode i_serializedValue) {
	QVariant deserializedValue;

	QDomElement serializedElement (i_serializedValue.toElement ());

	if (!serializedElement.isNull () &&
		(typeId () == serializedElement.tagName ())) {
		QStringList stringList;

		for (QDomElement stringElement = serializedElement.firstChildElement("string");
			!stringElement.isNull ();
			stringElement = stringElement.nextSiblingElement ("string")) {
			stringList.append (stringElement.attribute ("text"));
		}

		deserializedValue = stringList;
	}

	return deserializedValue;
}
