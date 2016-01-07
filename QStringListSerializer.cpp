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
