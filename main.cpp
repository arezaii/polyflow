#include <iostream>
#include "polyflow.hpp"
#include <cstdio>
#include <getopt.h>

int main(int argc, char ** argv) {

    double m_X = 0.0;
    double m_Y = 0.0;
    double m_Z = 0.0;

    int m_nx = 0;
    int m_ny = 0;
    int m_nz = 0;

    double m_dX = 1.0;
    double m_dY = 1.0;
    double m_dZ = 1.0;

    int m_numSubgrids{};
    int m_p = 1;
    int m_q = 1;
    int m_r = 1;

    //Tracks if we own m_data, and need to free it.
    bool m_dataOwner = false;
    std::FILE* m_fp;
    int errcheck;
    double* m_data = nullptr;
    int j,k,i;
    int nsg;
    int x,y,z,nx,ny,nz,rx,ry,rz;
    int qq;
    int index;
    int read_count;
    uint64_t tmp;
    uint64_t* buf;


    std::string m_filename = "None";
    int c;
    int err=0;
    while( ( c = getopt (argc, argv, "i:") ) != -1 )
    {
        switch(c)
        {
            case 'i':
                if(optarg) m_filename = optarg;
                break;
            case '?':
                err =1;
                break;
        }
    }


    {
        S0();
        for (int c1 = 0; c1 < m_numSubgrids; c1 += 1) {
            S1(c1);
            if (c1 + 1 == m_numSubgrids)
            S2(m_numSubgrids - 1);
            S3(c1);
            for (int c3 = 0; c3 < nz; c3 += 1)
                for (int c5 = 0; c5 < ny; c5 += 1) {
                    S4(c1, c3, c5);
                    S5(c1, c3, c5);
                    S6(c1, c3, c5);
                    for (int c7 = 0; c7 <= nx; c7 += 1) {
                        S7(c1, c3, c5, c7);
                        S8(c1, c3, c5, c7);
                        S9(c1, c3, c5, c7);
                    }
                }
        }
    }
    S10();
    return 0;
}
