#include <iostream>
#include <string>
#include "histogram.h"
#include <vector>

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max)
{

    if (numbers.size() == 0)
    {
        return;
    }
    min = numbers[0];
    max = numbers[0];

    for (double number : numbers)
    {
        if (number < min)
        {
            min = number;
        }
        else if (number > max)
        {
            max = number;
        }
    }
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout << "<rect x = '" << x << "' y = '" << y << "' width = '" << width << "' height = '" << height << "' stroke ='" << stroke << "' fill ='" << fill << "'/>";
}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto COLOUR_RED = "#c51d34";
    const string COLOUR_BLUE = "#171dbf";
    const string COLOUR_GREEN = "#3ab53e";

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 0;
    double MAX_WIDTH = (IMAGE_WIDTH - TEXT_WIDTH) / BLOCK_WIDTH;

    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }

    for (size_t bin : bins)
    {
        double bin_width;
        if (max_bin > MAX_WIDTH)
        {
            bin_width = MAX_WIDTH * (static_cast<double>(bin) / max_bin);
        }
        else
        {
            bin_width = BLOCK_WIDTH * bin;
        }
        //const double bin_width = BLOCK_WIDTH * bin;

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, COLOUR_RED, COLOUR_BLUE);
        top += BIN_HEIGHT;
    }
    svg_end();
}