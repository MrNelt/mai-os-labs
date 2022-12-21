// #include "topology.h"
#include "topology.h"



bool TTopology::Erase(const int & elem) {
    for (auto it1 = container.begin(); it1 != container.end(); ++it1) {
        for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
            if (*it2 == elem) {
                if (it1->size() > 1) {
                    it1->erase(it2);
                } else {
                    container.erase(it1);
                }
                --containerSize;
                return true;
            }
        }
    }
    return false;
}

long long TTopology::Find(const int & elem) {
    long long ind = 0;
    for (auto & it1 : container) {
        for (int & it2 : it1) {
            if (it2 == elem) {
                return ind;
            }
        }
        ++ind;
    }
    return -1;
}

bool TTopology::Insert(const int & parent, const int & elem) {
    for (auto & it1 : container) {
        for (auto it2 = it1.begin(); it2 != it1.end(); ++it2) {
            if (*it2 == parent) {
                it1.insert(++it2, elem);
                ++containerSize;
                return true;
            }
        }
    }
    return false;
}

void TTopology::Insert(const int & elem) {
    std::list<int> newList;
    newList.push_back(elem);
    ++containerSize;
    container.push_back(newList);
}

size_t TTopology::Size() const{
    return containerSize;
}