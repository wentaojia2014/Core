#include <cstring>
#include <vector>

#include "PNGLoader.h"

namespace Core {

    std::shared_ptr<StandardImage> PNGLoader::loadPNG(const std::string& path) {

        int width, height;
        png_byte color_type;
        png_byte bit_depth;
        png_bytep *row_pointers = nullptr;

        FILE *fp = fopen(path.c_str(), "rb");

        png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if(!png) abort();

        png_infop info = png_create_info_struct(png);
        if(!info) {
            throw PNGLoaderException("PNGLoader::loadPNG() -> Could not allocate PNG info object.");
        }

        if(setjmp(png_jmpbuf(png))) abort();

        png_init_io(png, fp);

        png_read_info(png, info);

        width      = png_get_image_width(png, info);
        height     = png_get_image_height(png, info);
        color_type = png_get_color_type(png, info);
        bit_depth  = png_get_bit_depth(png, info);

        // Read any color_type into 8bit depth, RGBA format.
        // See http://www.libpng.org/pub/png/libpng-manual.txt

        if(bit_depth == 16)
            png_set_strip_16(png);

        if(color_type == PNG_COLOR_TYPE_PALETTE)
            png_set_palette_to_rgb(png);

        // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
        if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
            png_set_expand_gray_1_2_4_to_8(png);

        if(png_get_valid(png, info, PNG_INFO_tRNS))
            png_set_tRNS_to_alpha(png);

        // These color_type don't have an alpha channel then fill it with 0xff.
        if(color_type == PNG_COLOR_TYPE_RGB ||
            color_type == PNG_COLOR_TYPE_GRAY ||
            color_type == PNG_COLOR_TYPE_PALETTE) {
                png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
            }

        if(color_type == PNG_COLOR_TYPE_GRAY ||
            color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
            png_set_gray_to_rgb(png);

        png_read_update_info(png, info);

        std::vector<int> rowSizes;
        row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
        for(int y = 0; y < height; y++) {
            size_t rowSize = png_get_rowbytes(png,info);
            row_pointers[y] = (png_byte*)malloc(rowSize);
            rowSizes.push_back(rowSize);
        }

        png_read_image(png, row_pointers);

        fclose(fp);

        StandardImage * rawPNG = new(std::nothrow) StandardImage(width, height);
        if (rawPNG == nullptr) {
            throw PNGLoaderException("PNGLoader::loadPNG() -> Could not allocate StandardImage object.");
        }
        rawPNG->init();
        std::shared_ptr<StandardImage> pngPtr = std::shared_ptr<StandardImage>(rawPNG);

        Byte * rawData = rawPNG->getImageData();

        UInt32 index = 0;
        for(int y = 0; y < height; y++) {
            UInt32 targetIndex = height - y - 1;
            size_t rowSize = rowSizes[targetIndex];
            memcpy(rawData + index, row_pointers[targetIndex], rowSize);
            index += rowSize;
        }

        for(int y = 0; y < height; y++) {
            free(row_pointers[y]);
        }
        free(row_pointers);      

        return pngPtr;
    }

}