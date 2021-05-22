#include <iostream>
#include <vector>
#include "histogram.h"
using namespace std;

int main() {
    // Ввод данных
    const auto input = read_input(cin);
    // Обработка данных
    double min, max;
    find_minmax(input.numbers, min, max);
    const auto bins = make_histogram(input.numbers, input.bin_count, min, max);
    // Вывод данных
    show_histogram_svg(bins);
    return 0;
}
