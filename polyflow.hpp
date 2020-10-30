//
// Created by arezaii on 10/29/20.
//

#ifndef POLYFLOW_POLYFLOW_HPP
#define POLYFLOW_POLYFLOW_HPP
#include <cstdlib>
#include "pfutil.hpp"
#define WRITEINT(V,f) {uint32_t temp = bswap32(V); \
                         fwrite(&temp, 4, 1, f);}
#define READINT(V,f,err) {uint32_t buf; \
                         err = fread(&buf, 4, 1, f);\
                         uint32_t temp =  bswap32(buf);\
                         V = (int)temp;}
#define WRITEDOUBLE(V,f) {uint64_t t1 = *(uint64_t*)&V;\
                         t1 =  bswap64(t1); \
                         fwrite(&t1, 8, 1, f);}
#define READDOUBLE(V,f,err) {uint64_t buf; \
                         err = fread(&buf, 8, 1, f);\
                         uint64_t temp =  bswap64(buf);\
                         V = *(double*)&temp;}
#define S0() {m_fp = fopen( m_filename.c_str(), "rb"); \
              std::cout << "Begin Reading PFB" << m_filename<<std::endl;\
              READDOUBLE(m_X,m_fp,errcheck); \
              READDOUBLE(m_Y,m_fp,errcheck);\
              READDOUBLE(m_Z,m_fp,errcheck);\
              READINT(m_nx,m_fp,errcheck);\
              READINT(m_ny,m_fp,errcheck); \
              READINT(m_nz,m_fp,errcheck); \
              READDOUBLE(m_dX,m_fp,errcheck);\
              READDOUBLE(m_dY,m_fp,errcheck);\
              READDOUBLE(m_dZ,m_fp,errcheck);\
              READINT(m_numSubgrids,m_fp,errcheck);\
              m_data = (double*)std::malloc(sizeof(double)*m_nx*m_ny*m_nz);}
#define S1(nsg){READINT(x,m_fp,errcheck);\
             READINT(y,m_fp,errcheck);\
             READINT(z,m_fp,errcheck);\
             READINT(nx,m_fp,errcheck);\
             READINT(ny,m_fp,errcheck);\
             READINT(nz,m_fp,errcheck);\
             READINT(rx,m_fp,errcheck);\
             READINT(ry,m_fp,errcheck);\
             READINT(rz,m_fp,errcheck);}
#define S2(nsg){m_p = m_nx/nx;\
             m_q = m_ny/ny;\
             m_r = m_nz/nz;}

#define S3(nsg){ qq = z*m_nx*m_ny + y*m_nx + x;}

#define S4(nsg,k,i){index = qq+k*m_nx*m_ny+i*m_nx;}

#define S5(nsg,k,i){buf= (uint64_t*)&(m_data[index]);}

#define S6(nsg,k,i){read_count = fread(buf,8,nx,m_fp);}

#define S7(nsg,k,i,j){tmp = buf[j];}

#define S8(nsg,k,i,j){tmp = bswap64(tmp);}

#define S9(nsg,k,i,j){m_data[index+j] = *(double*)(&tmp);}

#define S10(){if(m_fp){std::fclose(m_fp);} \
            std::cout<<"End Reading PFB File"<<m_filename<<"."<<std::endl;}

#endif //POLYFLOW_POLYFLOW_HPP
