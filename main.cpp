#include <iostream>
#include <vector>
#include "histogram.h"

using namespace std;


int main(int argc, char* argv[]) {
    string info = make_info_text();
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input, info);

    return 0;
}
