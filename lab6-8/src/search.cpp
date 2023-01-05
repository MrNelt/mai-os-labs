#include "search.h"



std::vector<unsigned int> ZFunction(const std::string & s) {
	unsigned int n = s.size();
	std::vector<unsigned int> z(n);
	unsigned int l = 0;
	unsigned int r = 0;
	for (unsigned int i = 1; i < n; ++i) {
		if (i <= r) {
			z[i] = std::min(z[i - l], r - i);
		}
		while (i + z[i] < n and s[i + z[i]] == s[z[i]]) {
			++z[i];
		}
		if (i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
	return z;
}

std::vector<unsigned int> PrefixFunction(const std::string & s) {
	std::vector<unsigned int> z = ZFunction(s);
	unsigned int n = s.size();
	std::vector<unsigned int> sp(n);
	for (unsigned int i = n - 1; i > 0; --i) {
		sp[i + z[i] - 1] = z[i];
	}
	return sp;
}

std::vector<unsigned int> KMP(const std::string & pattern, const std::string & text) {
	std::vector<unsigned int> p = PrefixFunction(pattern);
	unsigned int m = pattern.size();
	unsigned int n = text.size();
	unsigned int i = 0;
	std::vector<unsigned int> ans;
	if (m > n) {
		return ans;
	}
	while (i < n - m + 1) {
		unsigned int j = 0;
		while (j < m and pattern[j] == text[i + j]) {
			++j;
		}
		if (j == m) {
			ans.push_back(i);
		} else {
			if (j > 0 and j > p[j - 1]) {
				i = i + j - p[j - 1] - 1;
			}
		}
		++i;
	}
	return ans;
}

std::vector<std::string> StringToVectorStrings(std::string const& stringNumbers, char separator=' ') {
    std::vector<std::string> results;
    auto start = stringNumbers.begin();
    auto end = stringNumbers.end();
    auto next = std::find(start, end, separator);
    while (next != end) {
        results.emplace_back(start, next);
        start = next + 1;
        next = std::find(start, end, separator);
    }
    results.emplace_back(start, next);
    return results;
}