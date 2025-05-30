#include <vector>
#include "UI.hpp"
#include "Benchmark.hpp"
using namespace std;

int main() {
    // BENCHMARK

    vector<size_t> test_sizes = {1000, 10000, 50000, 100000, 500000};
    Benchmark<ArrayDeque<int>>("ArrayDeque", test_sizes);
    Benchmark<NewDeque<int>>("NewDeque", test_sizes);

    /*
    DequeUI ui;
    ui.Run();
    */
    return 0;
}