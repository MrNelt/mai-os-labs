#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <list>
#include <algorithm>
#include <cmath>
#include <ostream>


class TTopology {
private:
	using TListType = std::list< std::list<int> >;
	using TIterator = typename std::list<int>::iterator;
	using TListIterator = typename TListType::iterator;

	// TListType container;
	// size_t containerSize{};
public:
	TListType container;
	size_t containerSize{};
	bool Erase(const int & elem);

	int Find(const int & elem);

	bool Insert(const int & parent, const int & elem);

	void Insert(const int & elem);

	size_t Size();

};
#endif /* TOPOLOGY_H */
