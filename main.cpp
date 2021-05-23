#include <iostream>
#include <vector>
#include "histogram.h"
#include <curl/curl.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1){
            CURL *curl = curl_easy_init();
            if(curl) {
                CURLcode res;
                curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
                res = curl_easy_perform(curl);
                 if (res != 0)
                {
                cout << curl_easy_strerror(res) << endl;
                exit(1);
                }
                curl_easy_cleanup(curl);
            }
        return 0;
        }
    curl_global_init(CURL_GLOBAL_ALL);
    // Ввод данных
    const auto input = read_input(cin, true);
    // Обработка данных
    const auto bins = make_histogram(input);
    // Вывод данных
    show_histogram_svg(bins);
    return 0;
}
