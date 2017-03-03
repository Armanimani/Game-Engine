#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "../../debug/Debug.h"

template <class T>
class UMap
{
public:
	inline const std::unordered_map<std::string, std::shared_ptr<T>>& getMap() { return map; }
	inline void addItem(const std::shared_ptr<T> item);
	inline const std::shared_ptr<T> getItem(const std::string& name);
	inline void clearMap();

protected:
	std::unordered_map<std::string, std::shared_ptr<T>> map;
};

template<class T>
inline void UMap<T>::addItem(const std::shared_ptr<T> item)
{
	auto it = map.find(item->getName());
	if (it == map.cend())
	{
		map.insert(std::make_pair(item->getName(), item));
	}
}

template<class T>
inline const std::shared_ptr<T> UMap<T>::getItem(const std::string& name)
{
	auto it = map.find(name);

	if (it == map.cend())
	{
		Debug::print(name);
		Debug::print("item not found!");
		Debug::print(" ");
		return nullptr;
	}
	return it->second;
}

template<class T>
inline void UMap<T>::clearMap()
{
	map.clear();
}
