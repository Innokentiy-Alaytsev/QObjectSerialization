/*
  The MIT License (MIT)

  Copyright (c) 2016 Innokentij Alajcev (Иннокентий Алайцев)

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

#ifndef QOBJECTSERIALIZATION_H
#define QOBJECTSERIALIZATION_H


#include <QDomNode>
#include <QString>
#include <QStringList>


class QObject;


namespace QObjectSerialization {
	/**
	  @brief Possible sources for tag name of XML DOM node used for object serialization.
	*/
	typedef enum {
		/**
		  @brief Use object type name as tag name.
		*/
		TAG_TYPE_NAME,
		/**
		  @brief Use object name as tag name.
		*/
		TAG_OBJECT_NAME,
		/**
		  @brief Use user provided tag name.
		*/
		TAG_USER_DEFINED
	} TagNameSource_t;

	/*!
	  @brief Perform serialization of object properties to XML DOM.

	  @details Properties are saved in 2 different ways:
	  - those properties that have type that can be converted in QString are stored as attributes;
	  - those properties that have type that can not be converted in QString are stored in child
	  nodes with respective name if serializer for type is provided.

	  @param [in] i_object Object to serialize its properties.

	  @param [in] i_tagNameSource Tag name source to use to form XML DOM node tag name.

	  @param [in] i_tagName Tag name for XML DOM node which will store serialized object properties.
	  Required id i_tagNameSource = TAG_USER_DEFINED.

	  @param [in] i_propertiesNames A list of properties to serialize. If the list is empty, then
	  all properties are serialized.

	  @returns XML DOM node with serialized object properties. Node will be null on failure.
	*/
	QDomNode serialize (
		QObject* i_object,
		TagNameSource_t i_tagNameSource,
		QString i_tagName = QString (),
		QStringList i_propertiesNames = QStringList ());

	/*!
	  @brief Perform deserialization of object properties from XML DOM.

	  @details The object must be created before call to this function. If any of properties is not
	  stored in XML DOM it will not be changed.

	  The structure of XML DOM should be the same as created by serialize() function.

	  Properties, stored in "property" nodes will be deserialized only if there is registered
	  deserializer for respective type.

	  @param [out] o_object Object to set its properties according to contents of XML DOM node.

	  @param [in] i_serialized XML DOM node with serialized properties of an object.
	*/
	void deserialize (
		QObject* o_object,
		QDomNode i_serialized);

	/**
	  @brief Searches for XML DOM node which contains serialized properties of an object.

	  @details Search is performed recursively beginning from the given node itself.

	  The first node that matches search criteria is returned.

	  @param [in] i_serialisedObjects XML DOM node with serialized object somewhere inside it.

	  @param [in] i_object Serialized properties of this object are being searched.

	  @param [in] tagNameSource_t Tag name source to use to form XML DOM node tag name to find.

	  @param [in] i_tagName Tag name to find. Required is i_tagNameSource = TAG_USER_DEFINED.
	*/
	QDomNode getSerializedObjectNode (
		QDomNode i_serialisedObjects,
		QObject* i_object,
		TagNameSource_t i_tagNameSource,
		QString i_tagName = QString ());
}

#endif // QOBJECTSERIALIZATION_H
