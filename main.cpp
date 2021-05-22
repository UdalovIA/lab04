#include <iostream>
#include <vector>
#include "histogram.h"
#include <curl/curl.h>
using namespace std;

int main() {
    curl_global_init(CURL_GLOBAL_ALL);
    // Ввод данных
    const auto input = read_input(cin, true);
    // Обработка данных
    const auto bins = make_histogram(input);
    // Вывод данных
    show_histogram_svg(bins);
    return 0;
}
