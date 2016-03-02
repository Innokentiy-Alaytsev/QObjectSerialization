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

#include "QObjectSerialization.h"


#include <QObject>
#include <QVariant>

#include <QSet>
#include <QString>
#include <QMetaObject>
#include <QMetaProperty>


#include "CustomSerializer.h"
#include "CustomDeserializer.h"


using namespace QObjectSerialization;


/*
   Namespace defiden in order to prevent colisions.
*/
namespace QObjectSerializationPrivate {
	/**
	  @brief A helper function to get object's properties names set.

	  @param [in] i_object Object to get its properties set.

	  @returns Set of object's properties names.
	*/
	QSet< QString > objectPropertiesSet (QObject* i_object) {
		QSet< QString > objectPropertiesSet;

		const QMetaObject* metaObject (i_object->metaObject ());

		for (int propertyIndex (0), propertiesCount (metaObject->propertyCount());
			 propertyIndex < propertiesCount;
			 ++propertyIndex) {
			QMetaProperty metaProperty (metaObject->property (propertyIndex));

			objectPropertiesSet.insert (metaProperty.name ());
		}

		return objectPropertiesSet;
	}

	/**
	  @biref A helper function to get XML DOM node tag name for object.

	  @param [in] i_object Object to get XML DOM node name for.

	  @param [in] i_tagNameSource Source to get XML DOM node tag name.

	  @param [in] i_tagName Tag name to use is i_tagNameSource == TAG_USER_DEFINED.
	*/
	QString getTagNameForObject (
		QObject* i_object,
		TagNameSource_t i_tagNameSource,
		QString i_tagName) {
		QString tagName;

		switch (i_tagNameSource) {
			case TAG_TYPE_NAME: {
				tagName = i_object->metaObject ()->className ();

				break;
			}

			case TAG_OBJECT_NAME: {
				tagName = i_object->objectName ();

				break;
			}

			case TAG_USER_DEFINED: {
				tagName = i_tagName;

				break;
			}

			default: {
				/// @todo Implement error processing with exception.

				break;
			}
		}

		return tagName;
	}
}


using namespace QObjectSerializationPrivate;


QDomNode QObjectSerialization::serialize (
	QObject* i_object,
	TagNameSource_t i_tagNameSource,
	QString i_tagName,
	QStringList i_propertiesNames) {
	QDomDocument serializedDocument;

	QDomElement serializedElement (
		serializedDocument
			.createElement (
				getTagNameForObject (
					i_object,
					i_tagNameSource,
					i_tagName)));

	serializedDocument.appendChild (serializedElement);

	QStringList objectPropertiesNames (
		i_propertiesNames.isEmpty ()
		? objectPropertiesSet (i_object).values ()
		: i_propertiesNames);

	foreach (QString propertyName, objectPropertiesNames) {
		QVariant propertyValue (
			i_object->property (
				propertyName
					.toLatin1 ()));

		if (propertyValue.canConvert (QVariant::String)) {
			serializedElement.setAttribute (
				propertyName,
				propertyValue.toString ());
		}
		else {
			auto serializer = Factory::Factory< CustomSerializer >::createObject (
				propertyValue.typeName());

			if (serializer) {
				QDomElement propertyElement (
					serializedDocument
						.createElement ("property"));

				propertyElement.setAttribute (
					"name",
					propertyName);

				propertyElement.appendChild (
					serializer->serialize (propertyValue));

				serializedElement.appendChild (propertyElement);
			}
		}
	}

	return QDomNode (serializedDocument.documentElement ());
}


void QObjectSerialization::deserialize (
	QObject* o_object,
	QDomNode i_serialized) {
	QDomElement serializedElement (
		i_serialized.toElement ());

	if (!serializedElement.isNull ()) {
		QDomNamedNodeMap serializedAtributes (
			serializedElement
				.attributes());

		for (
			int attributeIndex = 0;
			attributeIndex < serializedAtributes.count ();
			++attributeIndex) {
			QDomAttr attribute (
				serializedAtributes
					.item(
						attributeIndex)
						.toAttr ());

			o_object->setProperty (
				attribute.name ().toLatin1 (),
				attribute.value ());
		}

		for (QDomElement propertyElement = serializedElement.firstChildElement("property");
			!propertyElement.isNull ();
			propertyElement = propertyElement.nextSiblingElement ("property")) {
			QString propertyName = propertyElement.attribute ("name");

			if (!propertyName.isEmpty ()) {
				QDomElement valueElement (
					propertyElement.firstChild ().toElement ());

				if (!valueElement.isNull ()) {
					auto deserializer = Factory::Factory< CustomDeserializer >::createObject (
						valueElement.tagName());

					if (deserializer) {
						QVariant propertyValue = deserializer->deserialize (valueElement);

						if (propertyValue.isValid ()) {
							o_object->setProperty (
								propertyName.toLatin1 (),
								propertyValue);
						}
					}
				}
			}
		}
	}
}


QDomNode QObjectSerialization::getSerializedObjectNode (
	QDomNode i_serialisedObjects,
	QObject* i_object,
	TagNameSource_t i_tagNameSource,
	QString i_tagName) {
	QDomNode serializedObjectNode;

	if ((nullptr != i_object) &&
		!i_serialisedObjects.isNull ()) {
		QString serializedObjectTag (
			getTagNameForObject (
				i_object,
				i_tagNameSource,
				i_tagName));

		if (serializedObjectTag == i_serialisedObjects.toElement ().tagName ()) {
			serializedObjectNode = i_serialisedObjects;
		}
		else {
			serializedObjectNode = i_serialisedObjects.firstChildElement (serializedObjectTag);

			if (serializedObjectNode.isNull ()) {
				for (auto childNode = i_serialisedObjects.firstChild ();
					 !childNode.isNull () && serializedObjectNode.isNull ();
					 childNode = childNode.nextSibling ()) {
					serializedObjectNode = getSerializedObjectNode (
						childNode,
						i_object,
						i_tagNameSource,
						i_tagName);
				}
			}
		}
	}

	return serializedObjectNode;
}
