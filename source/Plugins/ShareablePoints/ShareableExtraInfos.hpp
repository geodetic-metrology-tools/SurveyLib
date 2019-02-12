/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEEXTRAINFOS_HPP
#define SHAREABLEEXTRAINFOS_HPP

#include <string>
#include <unordered_map>

/**
 * Container class that can keep additional information about points or parameters.
 *
 * ShareableExtraInfos is part of the @ref shpoints module.
 * @ingroup shpoints
 *
 * It is a map with string as keys and string as values. Thus, it can easily contains the content of a config file.
 * 
 * This class is meant to hold extra information that are not part of the basic parameters of the class ShareableParams.
 * It is also usde in ShareablePoint to store specific application information about a point (like its deviation).
 *
 * @see shpoints, ShareableParams, ShareablePoint
*/
class ShareableExtraInfos
{
private:
	/** Config : map of key -> value of the config. */
	std::unordered_map<std::string, std::string> _extraInfos;

public:
	/** Default constructor. */
	ShareableExtraInfos() {}
	/**
	 * Initializer list constructor.
	 * Works like std::map constructor.
	 */
	ShareableExtraInfos(std::initializer_list<decltype(ShareableExtraInfos::_extraInfos)::value_type> l) : _extraInfos(l) {}

	/** Comparison operator. */
	bool operator==(const ShareableExtraInfos& a) const { return _extraInfos == a._extraInfos; }
	/** Comparison operator. */
	bool operator!=(const ShareableExtraInfos& a) const { return !(*this == a); }

	/**
	 * Insert or change a value.
	 *
	 * Insert the new value associated to the given key. If key already exists, its value is changed to the new provided value.
	 * It has a behavior similar to operator[]().
	 *
	 * @param key the key of the config
	 * @param value the value of the config
	 * @see operator[]()
	 */
	void addExtraInfo(const std::string& key, const std::string& value) { const auto& p = _extraInfos.emplace(key, value); if (!p.second) p.first->second = value; }
	/** @return true if the key exists */
	bool has(const std::string& key) const { return _extraInfos.find(key) != std::end(_extraInfos); }
	/**
	 * If key exists, returns its value.
	 *
	 * @throw std::out_of_range if key is unknown
	 * @param key the key we want its value
	 * @return the value associated with the key
	 * @see operator[]()
	 */
	const std::string& at(const std::string& key) const { return _extraInfos.at(key); }
	/** @see at() */
	std::string& at(const std::string& key) { return _extraInfos.at(key); }
	/**
	 * Return the value of the given key.
	 *
	 * If the key doesn't exist, it insert a new entry with the given key and an empty string value.
	 *
	 * @param key the key we wants its value
	 * @return the value associated with the key
	 */
	std::string& operator[] (const std::string& key) { return _extraInfos[key]; }
	/** Remove all values. */
	void clear() noexcept { _extraInfos.clear(); }
	/** Return the size of the container (the number of added keys). */
	size_t size() const noexcept { return _extraInfos.size(); }
	/** Tells if the container is empty (size == 0). */
	bool empty() const noexcept { return _extraInfos.empty(); }
	const std::unordered_map<std::string, std::string>& getMap() const noexcept { return _extraInfos; }
};

#endif // SHAREABLEEXTRAINFOS_HPP
