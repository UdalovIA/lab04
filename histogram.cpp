#include "histogram.h"
#include <iostream>
void find_minmax(const vector<double> numbers,
                 double& min, double& max) {
    if (numbers.size() == 0)
        return;
    min = numbers[0];
    max = numbers[0];
    // (здесь код поиска минимума и максимума)
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }
}
vector<double> input_numbers(istream& in, size_t count) {
   vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}
Input
read_input(istream& in,bool prompt) {
    Input data;
    if(prompt)
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if(prompt)
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    if(prompt)
    cerr << "Enter column count: ";
    in >> data.bin_count;
    data.image_wigth = 400;
    //do {cerr << "Width: ";in >> data.image_wigth;if (data.image_wigth < 70)cerr << "The value is too small" << endl;else if (data.image_wigth > 800)cerr << "The value is too big" << endl;}while(data.image_wigth > 800 | data.image_wigth < 70);
    return data;
}
vector<size_t> make_histogram(Input input){
    double min, max;
    find_minmax(input.numbers, min, max);
    vector<size_t> result(input.bin_count);
    for (double number : input.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * input.bin_count);
        if (bin == input.bin_count) {
            bin--;
        }
        result[bin]++;
    }
    return result;
}
void show_histogram_text(const vector<size_t>& bins){
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }
}
void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_end() {
    cout << "</svg>\n";
}
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline
    << "'>" << text << "</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black"){
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}
void show_histogram_svg(const vector<size_t>& bins,Input input,string info ) {
    const auto IMAGE_WIDTH = input.image_wigth;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    double scaling_factor = 1;
    if ((max_count*BLOCK_WIDTH) > IMAGE_WIDTH) {
        scaling_factor = (IMAGE_WIDTH / (max_count*BLOCK_WIDTH));
    }
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
    const double bin_width = BLOCK_WIDTH * bin * scaling_factor;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
    top += BIN_HEIGHT;

    }
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, info);
    svg_end();
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size;
    data_size=item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}
Input
download(const string& address) {
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
            if(curl) {
                CURLcode res;
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
                curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
                res = curl_easy_perform(curl);
                double total;
                CURLcode result = curl_easy_perform(curl);
                    if(CURLE_OK == result) {
                        result = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total);
                    if(CURLE_OK == result) {
                    cerr << "Time: " << total;
                    }
                        }
                 if (res != 0)
                {
                cout << curl_easy_strerror(res) << endl;
                exit(1);
                }
                curl_easy_cleanup(curl);
            }
    return read_input(buffer, false);
    }



string make_info_text()
{
    stringstream buffer;
    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD build;
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & 0xff;
    DWORD version_minor = version >> 8;
    //printf("M_version10 = %lu\n",version_major);
    //printf("M_version16 = %08lx\n",version_major);
    //printf("m_version10 = %lu\n",version_minor);
    //printf("m_version16 = %08lx\n",version_minor);
    if ((info & 0x80000000) == 0)
    {
    build = platform;
    }
    else printf("minor_bit = %u",1);
    //printf("Windows v%lu.%lu (build %lu)\n",version_major,version_minor,build);
    char system_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD Size = sizeof(system_name);
    GetComputerNameA(system_name, &Size);
    //printf("System name: %s\n", system_name);
    buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ")" << " " << "Computer name: " << system_name;
    return buffer.str();
}

