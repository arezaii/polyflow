
#include <getopt.h>
#include "simpleOpenReadCloseGen.cpp"

int main(int argc, char ** argv) {

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

    run_generated_code();

    return 0;
}
