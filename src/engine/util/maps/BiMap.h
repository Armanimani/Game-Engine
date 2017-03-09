#pragma once
#include <vector>
#include <algorithm>

template <class T, class S>
class BiMap
{
public:
	void registerElement(const T& t, const S& s);
	const T& getCorrespondingElement(const S& s);
	const S& getCorrespondingElement(const T& t);
protected:
	std::vector<T> vecT;
	std::vector<S> vecS;
};

template<class T, class S>
inline void BiMap<T, S>::registerElement(const T & t, const S & s)
{
	vecT.push_back(t);
	vecS.push_back(s);
}

template<class T, class S>
inline const T & BiMap<T, S>::getCorrespondingElement(const S & s)
{
	std::size_t pos = std::find(vecS.cbegin(), vecS.cend(), s) - vecS.cbegin();
	if (pos >= vecS.size())
	{
		Debug::print("Item is not registered!");
	}
	return vecT[pos];
}

template<class T, class S>
inline const S & BiMap<T, S>::getCorrespondingElement(const T & t)
{
	std::size_t pos = std::find(vecT.cbegin(), vecT.cend(), t) - vecT.cbegin();
	if (pos >= vecT.size())
	{
		Debug::print("Item is not registered!");
	}
	return vecS[pos];
}
