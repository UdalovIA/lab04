#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <curl/curl.h>
using namespace std;
struct Input {
    vector<double> numbers;
    size_t bin_count;
};
Input
read_input(istream& in, bool prompt);
void find_minmax(const vector<double> numbers, double& min, double& max);
vector<double> input_numbers(istream& in, size_t count);
vector<size_t> make_histogram(Input input);
void show_histogram_text(const vector<size_t>& bins);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke , string fill );
void show_histogram_svg(const vector<size_t>& bins);
Input
download(const string& address);

