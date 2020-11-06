
#include <getopt.h>
#include "simpleOpenReadCloseGen.hpp"
#include "simpleWriteFileGen.hpp"
#include "addToGridGen.hpp"

int calcOffset(int extent, int block_count, int block_idx);
int calcExtent(int extent, int block_count, int block_idx);
int main(int argc, char ** argv) {
    int cws_val;
m_filename = "None";
outfilename = "None";
cws_val = 0;

    int c;
    int err=0;
    while( ( c = getopt (argc, argv, "i:o:s:") ) != -1 )
    {
        switch(c)
        {
            case 'i':
                if(optarg) m_filename = optarg;
                break;
            case 'o':
                if(optarg) outfilename = optarg;
            case 's':
                if(optarg) cws_val = atoi(optarg);
            case '?':
                err =1;
                break;
        }
    }

    #include "simpleOpenReadCloseGen.cpp"

    #include "addToGridGen.cpp"

    for (int m =0;m<2*m_nx;m++){ \
                std::cout<<"Cell "<<m<<": " <<m_data[m]<<std::endl; \
            }                               \
            std::cout<<"End Reading PFB File "<<m_filename<<"."<<std::endl;

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