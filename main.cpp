#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <CImg.h>
using namespace cimg_library;

int main(int argc, char **argv)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int AVAIL_ROWS = w.ws_row;
    int AVAIL_COLUMNS = w.ws_col;

    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <input_image_path> [output_file_path (optional)] [channel to use for grayscale]" << std::endl;
        return 1;
    }

    const char *fileName = argv[1];
    CImg<unsigned char> image;
    try
    {
        image.load(fileName);
    }
    catch (const CImgException &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (argc >= 4)
    {
        image = image.channel(std::stoi(argv[3]));
    }
    else
    {
        image = image.channel(1);
    }

    std::cout << "Succesfully opened file " << fileName << std::endl;

    image.resize(AVAIL_COLUMNS, AVAIL_ROWS);

    const char *charMap = " .,->|[0";

    int width = image.width();
    int height = image.height();
    int pixelCount = width * height;
    int *pixels = new int[pixelCount];
    std::cout << width << "x" << height << std::endl;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            pixels[r * width + c] = (int)image(c, r, 0, 0);
            std::cout << (int)image(c, r, 0, 0) << std::endl;
        }
    }

    if (argc >= 3)
    {
        try
        {
            image.save(argv[2]);
            std::cout << "Image resized and saved as " << argv[2] << " successfully!" << std::endl;
        }
        catch (const CImgException &e)
        {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }

    delete[] pixels;

    return 0;
}