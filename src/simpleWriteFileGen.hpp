//
// Created by arezaii on 11/5/20.
//

#ifndef POLYFLOW_SIMPLEWRITEFILEGEN_HPP
#define POLYFLOW_SIMPLEWRITEFILEGEN_HPP

#include <vector>
#include "pfutil.hpp"


std::string outfilename;
std::FILE* fp;
int max_x_extent;
int nsg;
int sg_count;
std::vector<double> writeBuf;
std::vector<long> _offsets;
int w_x;
int w_y;
int w_z;
int offset_z;
int offset_z_1;
int offset_y;
int offset_y_1;
int x_extent;
uint64_t* w_buf;
uint64_t w_tmp;
int written;


#define S10() {_offsets.reserve((m_p*m_q*m_r) + 1);\
            fp = std::fopen(outfilename.c_str(), "wb");\
            m_numSubgrids = m_p * m_q * m_r; \
            WRITEDOUBLE(m_X,fp);\
            WRITEDOUBLE(m_Y,fp);\
            WRITEDOUBLE(m_Z,fp);\
            WRITEINT(m_nx,fp);\
            WRITEINT(m_ny,fp);\
            WRITEINT(m_nz,fp);\
            WRITEDOUBLE(m_dX,fp);\
            WRITEDOUBLE(m_dY,fp);\
            WRITEDOUBLE(m_dZ,fp);\
            WRITEINT(m_numSubgrids,fp);\
            max_x_extent =calcExtent(m_nx,m_p,0); \
            writeBuf.reserve(max_x_extent);  \
            nsg=0;\
            _offsets[0] = 0;\
            sg_count = 1;}

#define S11(nsg_z,nsg_y,nsg_x)  {w_x = m_X + calcOffset(m_nx,m_p,nsg_x);\
                w_y = m_Y + calcOffset(m_ny,m_q,nsg_y);\
                w_z = m_Z + calcOffset(m_nz,m_r,nsg_z);\
                WRITEINT(w_x, fp);                        \
                WRITEINT(w_y, fp);\
                WRITEINT(w_z, fp);\
                x_extent =calcExtent(m_nx,m_p,nsg_x);\
                WRITEINT(x_extent, fp);\
                WRITEINT(calcExtent(m_ny,m_q,nsg_y), fp);\
                WRITEINT(calcExtent(m_nz,m_r,nsg_z), fp);\
                WRITEINT(1, fp);\
                WRITEINT(1, fp);\
                WRITEINT(1, fp);                         \
                                           \
                offset_z = calcOffset(m_nz,m_r,nsg_z);\
                offset_z_1 = calcOffset(m_nz,m_r,nsg_z+1); \
                offset_y = calcOffset(m_ny,m_q,nsg_y);\
                offset_y_1 = calcOffset(m_ny,m_q,nsg_y+1); \
                }
#define S12(nsg_z,nsg_y,nsg_x,iz,iy){  w_buf = (uint64_t*)&(m_data[iz*m_nx*m_ny+iy*m_nx+calcOffset(m_nx,m_p, \
nsg_x)]);}

#define S13(nsg_z,nsg_y,nsg_x,iz,iy,j) { w_tmp = w_buf[j];\
               w_tmp = bswap64(w_tmp);\
               writeBuf[j] = *(double*)(&w_tmp);\
         }
#define S14(nsg_z,nsg_y,nsg_x,iz,iy)  {written = fwrite(writeBuf.data(),sizeof(double),x_extent,fp);\
}

#define S15(nsg_z,nsg_y,nsg_x) { _offsets[sg_count] = std::ftell(fp);\
                sg_count++;}

#define S16(nsg_z) { nsg++;}

#define S17() {fclose(fp);\
               fprintf(stdout,"finished writing file %s", outfilename.c_str());}



#endif //POLYFLOW_SIMPLEWRITEFILEGEN_HPP
