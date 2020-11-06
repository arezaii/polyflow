
#include <getopt.h>
#include "simpleOpenReadCloseGen.hpp"
#include "simpleWriteFileGen.hpp"

int calcOffset(int extent, int block_count, int block_idx);
int calcExtent(int extent, int block_count, int block_idx);
int main(int argc, char ** argv) {

m_filename = "None";
outfilename = "None";
    int c;
    int err=0;
    while( ( c = getopt (argc, argv, "i:o:") ) != -1 )
    {
        switch(c)
        {
            case 'i':
                if(optarg) m_filename = optarg;
                break;
            case 'o':
                if(optarg) outfilename = optarg;
            case '?':
                err =1;
                break;
        }
    }

    #include "simpleOpenReadCloseGen.cpp"

    #include "simpleWriteFileGen.cpp"

    if(m_fp){std::fclose(m_fp);}
    free(m_data);
    return 0;

}


int calcOffset(int extent, int block_count, int block_idx) {
    int lx = extent % block_count;
    int bx = extent / block_count;
    int offset =  block_idx * bx;
    if (block_idx < lx) {
        offset += block_idx;
    }else{
        offset += lx;
    }
    return offset;
}

int calcExtent(int extent, int block_count, int block_idx) {
    int lx = extent % block_count;
    int bx = extent / block_count;
    int block_extent = bx;
    if (block_idx < lx) {
        block_extent++;
    }
    return block_extent;
}