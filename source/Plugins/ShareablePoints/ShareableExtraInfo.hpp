/*
© Copyright CERN 2000-2018. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef SHAREABLEEXTRAINFOS_HPP
#define SHAREABLEEXTRAINFOS_HPP

#include <string>
#include <unordered_map>

class ShareableExtraInfos
{
public:
	void addExtraInfo(const std::string& key, const std::string& value) { const auto& p = _extraInfos.emplace(key, value); if (!p.second) p.first->second = value; }
	bool has(const std::string& key) const { return _extraInfos.find(key) != std::end(_extraInfos); }
	const std::string& at(const std::string& key) const { return _extraInfos.at(key); }
	std::string& at(const std::string& key) { return _extraInfos.at(key); }
	std::string& operator[] (const std::string& key) { return _extraInfos[key]; }
	void clear() noexcept { _extraInfos.clear(); }
	size_t size() const noexcept { return _extraInfos.size(); }
	bool empty() const noexcept { return _extraInfos.empty(); }
	const std::unordered_map<std::string, std::string>& getMap() const noexcept { return _extraInfos; }

private:
	std::unordered_map<std::string, std::string> _extraInfos;
};

#endif // SHAREABLEEXTRAINFOS_HPP
