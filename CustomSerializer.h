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

#ifndef CUSTOMSERIALIZER_H
#define CUSTOMSERIALIZER_H


#include <QDomNode>
#include <QString>
#include <QVariant>


#include "Factory/Factory.h"


class QObject;


namespace QObjectSerialization {
	/**
	  @biref Interface for user defuned serializers.
	*/
	class CustomSerializer: public Factory::IProducible {
	public:
		static std::shared_ptr< CustomSerializer > createObject();

		static QString typeId ();

		/**
		  @brief Performs seralization of given value.

		  @details The value is expected to be stored in QVariant. The reason for that is that
		  this class is supposed to be used to serialize objects properties, values of which are
		  retreived as QVariant is requested with property() function.

		  @param [in] i_value Property value to serialize.

		  @returns QDomNode with serialized value.
		*/
		virtual QDomNode serialize (QVariant i_value) = 0;
	};

	template class Factory::Factory< CustomSerializer >;
}

#endif // CUSTOMSERIALIZER_H
