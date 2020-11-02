
#include <getopt.h>
#include "simpleOpenReadCloseGen.hpp"

int main(int argc, char ** argv) {

//m_filename = "/home/arezaii/pfdir/parflow/test/washita/NLDAS/NLDAS.Temp.000001_to_000024.pfb.00000";

m_filename = "None";
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

    #include "simpleOpenReadCloseGen.cpp"


    return 0;


}
