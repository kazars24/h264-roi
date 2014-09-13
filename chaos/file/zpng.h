#ifndef ZPNG_H
#define ZPNG_H

#include "ztypes.h"
#include "zimage.h"
//#include "zbitmap.h"
#include "zstring.h"
#include "zpath.h"
#include "zerror.h"

#define PNG_DEBUG 3
#include <png.h>

namespace LibChaos {

class ZPNG {
public:
    struct PNGError {
        enum pngerrors {
            none = 0,
            badfile = 1,
            sigreadfail = 2,
            sigcheckfail = 3,
            readstructfail = 4,
            infostructfail = 5,
            libpngerror = 6,
            imageallocfail = 7,
            rowallocfail = 8,
            badpointer = 9,
            unsupportedchannelcount = 10,
            emptyimage = 11,
            writestructfail = 12,
            badwritefile = 13,
            invaliddimensions = 14,
        };
    };
    struct PNGWrite {
        enum pngoptions {
            none = 0,
            interlace = 1
        };
    };

public:
    ZPNG(){

    }
    ZPNG(const ZImage &img) : image(img){

    }

    bool read(ZPath path);
    bool write(ZPath path, PNGWrite::pngoptions options = PNGWrite::none);

    static ZString libpngVersionInfo();

    ZString &pngText(ZString key){
        return text[key];
    }

    ZImage &getImage(){
        return image;
    }

private:
    struct PngReadData {
        png_struct *png_ptr = NULL;
        png_info *info_ptr = NULL;

        FILE *infile = NULL;

        png_uint_32 width, height;
        unsigned char channels;
        int bit_depth, color_type;
        unsigned char bg_red, bg_green, bg_blue;
        double gamma;

        unsigned char *image_data = nullptr;

        ZString err_str;
    };

    struct PngWriteData {
        png_struct *png_ptr = NULL;
        png_info *info_ptr = NULL;

        FILE *outfile = NULL;

        png_uint_32 width, height;
        int bit_depth, color_type;

        unsigned char *image_data = NULL;
        unsigned char **row_pointers = NULL;

        double gamma;

        bool interlaced;

        bool have_bg;
        unsigned char bg_red, bg_green, bg_blue;

        bool have_time;
        time_t modtime;

        ZString err_str;
    };

private:
    static int readpng_init(PngReadData *data);
    static int readpng_get_bgcolor(PngReadData *data);
    static int readpng_get_image(PngReadData *data, double display_exponent);
    static void readpng_cleanup(PngReadData *data);
    static void readpng_warning_handler(png_struct *png_ptr, png_const_charp msg);
    static void readpng_error_handler(png_struct *png_ptr, png_const_charp msg);

    static int writepng_init(PngWriteData *mainprog_ptr, const AsArZ &text);
    static int writepng_encode_image(PngWriteData *mainprog_ptr);
    static int writepng_encode_row(PngWriteData *mainprog_ptr, unsigned char *row);
    static int writepng_encode_finish(PngWriteData *mainprog_ptr);
    static void writepng_cleanup(PngWriteData *mainprog_ptr);
    static void writepng_warning_handler(png_struct *png_ptr, png_const_charp msg);
    static void writepng_error_handler(png_struct *png_ptr, png_const_charp msg);

private:
    ZImage image;
    AsArZ text;
    ZError error;
};

}

#endif // ZPNG_H
