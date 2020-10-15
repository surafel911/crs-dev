#include <vector>
#include <chrono>
#include <iomanip>
#include <iostream>

#include <registry.hpp>
#include <component.hpp>

constexpr int TEST_COUNT = 100000;

struct transform : public crs::component {
	float x, y, z;
};


inline double test_insertion(crs::registry<transform>& r)
{
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < TEST_COUNT; i++) {
		r.emplace();
	}

	std::chrono::duration<double> diff = (std::chrono::high_resolution_clock::now() - start);
	std::cout << diff.count() << std::endl;

	return diff.count();
}

inline void test_deletion(crs::registry<transform>& r)
{
	std::vector<std::size_t> hs(TEST_COUNT);

	for (const transform& t : r.data()) {
		hs.emplace_back(t.get_handle());
	}

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < TEST_COUNT; i++) {
		r.erase(hs[i]);
	}

	std::chrono::duration<double> diff = (std::chrono::high_resolution_clock::now() - start);
	std::cout << diff.count() << std::endl << r.size() << std::endl;
}

int main()
{
	crs::registry<transform> r([](transform& t) { std::cout << "x: " << t.x << std::endl; });
	
	std::cout << std::fixed << std::setprecision(9) << std::left;

	auto r1 = test_insertion(r);
	r.clear();
	auto r2 = test_insertion(r);

	std::cout << "% improv: " << (r1 - r2) / r1 << std::endl;
}
