//
// Created by arezaii on 10/30/20.
//

#ifndef POLYFLOW_SIMPLEOPENREADCLOSEGEN_HPP
#define POLYFLOW_SIMPLEOPENREADCLOSEGEN_HPP

#include <iostream>
#include <cstdint>
#include <cstdio>
#include "pfutil.hpp"

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


std::FILE* m_fp;
int errcheck;
double* m_data = nullptr;
int x,y,z,nx,ny,nz,rx,ry,rz;
int qq;
int index;
int read_count;
uint64_t tmp;
uint64_t* buf;
std::string m_filename;

#define S0() {m_fp = fopen( m_filename.c_str(), "rb"); \
              std::cout << "Begin Reading PFB " << m_filename<<std::endl;\
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
             READINT(rz,m_fp,errcheck);\
             qq = z*m_nx*m_ny + y*m_nx + x;}
#define S2(nsg){m_p = m_nx/nx;\
             m_q = m_ny/ny;\
             m_r = m_nz/nz;}



#define S3(nsg,k,i){index = qq+k*m_nx*m_ny+i*m_nx;\
                    buf= (uint64_t*)&(m_data[index]);\
                    read_count = fread(buf,8,nx,m_fp);}



#define S4(nsg,k,i,j){tmp = buf[j];\
                      tmp = bswap64(tmp);\
                      m_data[index+j] = *(double*)(&tmp);}


#define S5(){ \
            for (int m =0;m<2*m_nx;m++){ \
                std::cout<<"Cell "<<m<<": " <<m_data[m]<<std::endl; \
            }                               \
            std::cout<<"End Reading PFB File "<<m_filename<<"."<<std::endl;}
#endif //POLYFLOW_SIMPLEOPENREADCLOSEGEN_HPP
