#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;
void find_minmax(const vector<double> numbers, double& min, double& max);
vector<double> input_numbers(size_t count);
vector<size_t> make_histogram(const vector<double>& numbers,const size_t& bin_count,const double& min,const double& max);
void show_histogram_text(const vector<size_t>& bins);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke , string fill );
void show_histogram_svg(const vector<size_t>& bins, string info);
string make_info_text();

