#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>
#include <algorithm>


std::vector<unsigned int> ZFunction(const std::string & str);
std::vector<unsigned int> PrefixFunction(const std::string & str);
std::vector<unsigned int> KMP(const std::string & pattern, const std::string & text);
std::vector<std::string> StringToVectorStrings(std::string const& stringNumbers, char separator);


#endif /* SEARCH_H */

