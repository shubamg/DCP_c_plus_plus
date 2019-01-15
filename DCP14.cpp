using namespace std;

#include <chrono>
#include <random>
#include <iostream>
#include <utility>


struct Uniformly_random {

	default_random_engine d{};
	uniform_real_distribution<double> dis;

	Uniformly_random(double lower, double upper):
		d{chrono::system_clock::now().time_since_epoch().count()},
		dis{lower, upper} {}

	double get() { return dis(d); }
};

struct Random_point_generator {
	Uniformly_random urng1, urng2;
	Random_point_generator(double low, double high): urng1{low, high}, urng2{low, high} {}
	pair<double, double> get() { return make_pair(urng1.get(), urng2.get()); }
};

bool is_inside(pair<double, double> point) {
	return (point.first*point.first + point.second * point.second) <= 1;
}

int main() {
	int num_of_iterations = 1000000;
	Random_point_generator rpg{-1.0, 1.0};
	int inside_points = 0;
	for(int i=0; i<num_of_iterations; ++i)
		inside_points += is_inside(rpg.get());
	cout << (inside_points * 4.0 / num_of_iterations)<<endl;
	return 0;
}




