// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Serializer_json.hpp"

#include <deque>
#include <iostream>

#include <math.h>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

struct JSonObject
{
	JSonObject(const std::string name, rapidjson::Type type) : name(name), value(rapidjson::Value(type)) {}

	const std::string name;
	rapidjson::Value value;
};

class JSONObjectSerializer::_JSONObjectSerializer_pimpl
{
public:
	rapidjson::Value &getLastValue() { return stack.back().value; }
	JSonObject &getLastObject() { return stack.back(); }

public:
	std::deque<JSonObject> stack;
	rapidjson::Document doc;
};

template<typename T>
typename std::enable_if<!std::is_floating_point<T>::value>::type addToValue(rapidjson::Value &value, T newValue, rapidjson::Document::AllocatorType &allocator)
{
	if (value.IsArray())
		value.PushBack(newValue, allocator);
	else
		value = newValue;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value>::type addToValue(rapidjson::Value &value, T newValue, rapidjson::Document::AllocatorType &allocator)
{
	if (std::isnan(newValue))
	{
		if (value.IsArray())
			value.PushBack(rapidjson::Value(), allocator);
		else
			value = rapidjson::Value();
	}
	else
	{
		if (value.IsArray())
			value.PushBack(newValue, allocator);
		else
			value = newValue;
	}
}

JSONObjectSerializer::JSONObjectSerializer() : _pimpl(std::make_unique<_JSONObjectSerializer_pimpl>())
{
	_pimpl->doc.SetObject();
}

JSONObjectSerializer::~JSONObjectSerializer() = default;

/*
 * Converts the string to UTF-8 format and escapes quote and backslash characters.
 */
std::string latin_to_utf8(const std::string &str)
{
	std::string utf8;
	utf8.reserve(str.size() * 2);
	for (std::string::const_iterator it = str.cbegin(); it != str.cend(); ++it)
	{
		uint8_t ch = *it;
		// Escape backslash twice (once by StringBuffer::getString, and second time here)
		 if (ch == '\\')
			utf8.push_back('\\');

		// Change to utf-8
		if (ch < 0x80)
		{
			// Remove unacceptable for LGC Report quote sign and replace it with the `Right single quotation mark`
			if (ch == '\'')
				utf8 += u8"\u2019";
			else
				utf8.push_back(ch);
		}
		else
		{
			utf8.push_back(0xc0 | ch >> 6);
			utf8.push_back(0x80 | (ch & 0x3f));
		}
	}
	return utf8;
}

std::string JSONObjectSerializer::getStringRepresentation()
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer writer(buffer);
	_pimpl->doc.Accept(writer);

	return latin_to_utf8(buffer.GetString());
}

void JSONObjectSerializer::startObject(const std::string &name)
{
	_pimpl->stack.push_back(JSonObject(name, rapidjson::kObjectType));
}

void JSONObjectSerializer::startObject()
{
	startObject(std::string());
}

void JSONObjectSerializer::endObject()
{
	if (_pimpl->stack.empty())
		return;

	JSonObject &lastElement = _pimpl->getLastObject();
	auto &allocator = _pimpl->doc.GetAllocator();

	if (_pimpl->stack.size() == 1)
	{
		_pimpl->doc.AddMember(rapidjson::Value(lastElement.name, allocator), lastElement.value, allocator);
	}
	else
	{
		JSonObject &parentElement = *(_pimpl->stack.end() - 2);

		if (parentElement.value.IsArray() && lastElement.name.empty())
			parentElement.value.PushBack(lastElement.value, allocator);
		else if (parentElement.value.IsArray() && !lastElement.name.empty())
		{
			rapidjson::Value obj(rapidjson::kObjectType);
			obj.AddMember(rapidjson::Value(lastElement.name, allocator), lastElement.value, allocator);
			parentElement.value.PushBack(obj, allocator);
		}
		else
			parentElement.value.AddMember(rapidjson::Value(lastElement.name, allocator), lastElement.value, allocator);
	}

	_pimpl->stack.pop_back();
}

void JSONObjectSerializer::startArray(const std::string &name)
{
	_pimpl->stack.push_back(JSonObject(name, rapidjson::kArrayType));
}

void JSONObjectSerializer::startArray()
{
	_pimpl->stack.push_back(JSonObject("", rapidjson::kArrayType));
}

void JSONObjectSerializer::endArray()
{
	endObject();
}

void JSONObjectSerializer::startPrimitive(const std::string &name)
{
	startObject(name);
}

void JSONObjectSerializer::endPrimitive()
{
	endObject();
}

void JSONObjectSerializer::addValue(int value)
{
	addToValue(_pimpl->getLastValue(), value, _pimpl->doc.GetAllocator());
}

void JSONObjectSerializer::addValue(double value)
{
	addToValue(_pimpl->getLastValue(), value, _pimpl->doc.GetAllocator());
}

void JSONObjectSerializer::addValue(float value)
{
	addToValue(_pimpl->getLastValue(), value, _pimpl->doc.GetAllocator());
}

void JSONObjectSerializer::addValue(char value)
{
	addToValue(_pimpl->getLastValue(), value, _pimpl->doc.GetAllocator());
}

void JSONObjectSerializer::addValue(wchar_t value)
{
	addToValue(_pimpl->getLastValue(), value, _pimpl->doc.GetAllocator());
}

void JSONObjectSerializer::addValue(bool value)
{
	addToValue(_pimpl->getLastValue(), value, _pimpl->doc.GetAllocator());
}

void JSONObjectSerializer::addValue(const std::string &value)
{
	_pimpl->getLastValue().SetString(value, _pimpl->doc.GetAllocator());
}

void JSONObjectSerializer::addValue(char const *value)
{
	_pimpl->getLastValue().SetString(value, _pimpl->doc.GetAllocator());
}
