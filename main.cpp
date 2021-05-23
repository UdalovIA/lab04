#include <iostream>
#include <vector>
#include "histogram.h"

using namespace std;

<<<<<<< HEAD
int main(int argc, char* argv[]) {
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input);
=======
int main() {
    // Ввод данных
    string info = make_info_text();
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
    show_histogram_svg(bins, info);
>>>>>>> lab04-2
    return 0;
}
