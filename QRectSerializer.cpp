#include "QRectSerializer.h"


#include <QRect>
#include <QRectF>


Factory::AddProduction<
	QObjectSerialization::CustomSerializer,
	QObjectSerialization::QRectFSerializer > addQRectFSerializer;
Factory::AddProduction<
	QObjectSerialization::CustomSerializer,
	QObjectSerialization::QRectSerializer > addQRectSerializer;


std::shared_ptr< QObjectSerialization::CustomSerializer >
QObjectSerialization::QRectFSerializer::createObject () {
	return std::shared_ptr< CustomSerializer > (new QRectFSerializer);
}


QString QObjectSerialization::QRectFSerializer::typeId () {
	static QString s_typeId (
		QMetaType::typeName (
			QMetaType::QRectF));

	return s_typeId;
}

QDomNode QObjectSerialization::QRectFSerializer::serialize (QVariant i_value) {
	QDomDocument serializedDocument;

	QDomElement serializedElement (
		serializedDocument
		.createElement (typeId ()));

	serializedDocument.appendChild (serializedElement);

	QRectF rect (i_value.toRectF());

	serializedElement.setAttribute (
		"height",
		QString::number (
			rect.height ()));
	serializedElement.setAttribute (
		"width",
		QString::number (
			rect.width ()));
	serializedElement.setAttribute (
		"x",
		QString::number (
			rect.x ()));
	serializedElement.setAttribute (
		"y",
		QString::number (
			rect.y ()));

	return QDomNode (serializedDocument);
}


std::shared_ptr< QObjectSerialization::CustomSerializer >
QObjectSerialization::QRectSerializer::createObject () {
	return std::shared_ptr< CustomSerializer > (new QRectSerializer);
}


QString QObjectSerialization::QRectSerializer::typeId () {
	static QString s_typeId (
		QMetaType::typeName (
			QMetaType::QRect));

	return s_typeId;
}


QDomNode QObjectSerialization::QRectSerializer::serialize (QVariant i_value) {
	QDomElement serializedElement (
		QRectFSerializer ()
			.serialize (i_value)
				.toDocument ()
					.documentElement());

	serializedElement.setTagName ("QRect");

	return QDomNode (serializedElement);
}
