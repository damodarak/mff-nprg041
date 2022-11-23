#ifndef PREKLADY_H_
#define PREKLADY_H_

#include <set>
#include <iterator>
#include <string>
#include <array>
#include <map>

using Dvojka = std::pair<std::string, std::string>;
using Rozmezi = std::array<std::set<Dvojka>::iterator, 2>;

struct cmp {
	bool operator()(const Dvojka& left, const Dvojka& right) const;
};
struct cmp_second {
	bool operator()(const std::string& s1, const std::string& s2) const;
};
struct cmp_first {
	bool operator()(const std::string& s1, const std::string& s2) const;
};

class Preklady {
public:
	void add(const std::string& slovo, const std::string& preklad);
	void del(const std::string& slovo, const std::string& preklad);
	void del(const std::string& slovo);
	Rozmezi find(const std::string& slovo);
	Rozmezi prefix(const std::string& pre);
private:
	std::set<Dvojka, cmp> preklady;
	std::map<std::string, std::set<std::string, cmp_second>> slova;
	std::map<std::string, std::set<std::string, cmp_first>> prefixy;
};

void print(const Rozmezi& interval);
void print_pre(const Rozmezi& interval);

#endif