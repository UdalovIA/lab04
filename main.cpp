#include <iostream>
#include <vector>
#include "histogram.h"
using namespace std;

int main() {
    // Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    // Обработка данных
    double min, max;
    find_minmax(numbers, min, max);
    const auto bins = make_histogram(numbers, bin_count, min, max);
    // Вывод данных
    show_histogram_svg(bins);
    return 0;
}
