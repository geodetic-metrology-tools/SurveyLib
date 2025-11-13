// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef _SERIALIZER_JSON
#define _SERIALIZER_JSON

#include <memory>

#include "Serializer.hpp"

/**
 * The main quirk of this Serializer is that it is building the tree bottom-up (from the leaves) and when the last element
 * on the stack is meant to be finished (endObject()) then it is finally added to the document.
 * Adding is invalidating the previous rapidjson::Value but thanks to that there is no overhead (it is a move operation).
 */
class JSONObjectSerializer : public ObjectSerializer
{
public:
	JSONObjectSerializer();
	virtual ~JSONObjectSerializer();

	virtual std::string getStringRepresentation() override;

protected:
	virtual void startObject(const std::string &name) override;
	virtual void startObject() override;
	virtual void endObject() override;
	virtual void startArray(const std::string &name) override;
	virtual void startArray() override;
	virtual void endArray() override;
	virtual void startPrimitive(const std::string &name) override;
	virtual void endPrimitive() override;

	virtual void addValue(int value) override;
	virtual void addValue(double value) override;
	virtual void addValue(float value) override;
	virtual void addValue(char value) override;
	virtual void addValue(wchar_t value) override;
	virtual void addValue(bool value) override;
	virtual void addValue(const std::string &value) override;
	virtual void addValue(char const *value) override;

private:
	/** pimpl */
	class _JSONObjectSerializer_pimpl;
	std::unique_ptr<_JSONObjectSerializer_pimpl> _pimpl;
};

#endif
