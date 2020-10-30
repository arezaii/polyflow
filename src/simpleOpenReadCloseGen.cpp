//
// Created by arezaii on 10/30/20.
//

#include "simpleOpenReadCloseGen.hpp"


void run_generated_code() {
    S0();
    for (int c1 = 0; c1 < m_numSubgrids; c1 += 1) {
        S1(c1);
        if (c1 + 1 == m_numSubgrids) S2(m_numSubgrids - 1);
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
    S10();
}


/**
 * #define S0() {m_fp = fopen( m_filename.c_str(), "rb");\
#              READDOUBLE(m_X,m_fp,errcheck); \
#              READDOUBLE(m_Y,m_fp,errcheck);\
#              READDOUBLE(m_Z,m_fp,errcheck);\
#             READINT(m_nx,m_fp,errcheck);\
#              READINT(m_ny,m_fp,errcheck); \
#              READINT(m_nz,m_fp,errcheck); \
#              READDOUBLE(m_dX,m_fp,errcheck);\
#             READDOUBLE(m_dY,m_fp,errcheck);\
#              READDOUBLE(m_dZ,m_fp,errcheck);\
#              READINT(m_numSubgrids,m_fp,errcheck);\
#              m_data = (double*)std::malloc(sizeof(double)*m_nx*m_ny*m_nz);}
#define S1(nsg){READINT(x,m_fp,errcheck);\
#             READINT(y,m_fp,errcheck);\
#             READINT(z,m_fp,errcheck);\
#             READINT(nx,m_fp,errcheck);\
#             READINT(ny,m_fp,errcheck);\
#             READINT(nz,m_fp,errcheck);\
#             READINT(rx,m_fp,errcheck);\
#             READINT(ry,m_fp,errcheck);\
#             READINT(rz,m_fp,errcheck);}
#define S2(nsg){m_p = m_nx/nx;\
#             m_q = m_ny/ny;\
#             m_r = m_nz/nz;}

#define S3(nsg){ qq = z*m_nx*m_ny + y*m_nx + x;}

#define S4(nsg,k,i){index = qq+k*m_nx*m_ny+i*m_nx;}

#define S5(nsg,k,i){buf= (uint64_t*)&(m_data[index]);}

#define S6(nsg,k,i){read_count = fread(buf,8,nx,m_fp);}

#define  S7(nsg,k,i,j){tmp = buf[j];}

#define S8(nsg,k,i,j){tmp = bswap64(tmp);}

#define S9(nsg,k,i,j){m_data[index+j] = *(double*)(&tmp);}

#define S10(){if(m_fp){std::fclose(m_fp);}}

    # for (nsg = 0;nsg<m_numSubgrids; nsg++){
        # // read subgrid header
        #S1 READINT(x,m_fp,errcheck);
        #S1 READINT(y,m_fp,errcheck);
        #S1 READINT(z,m_fp,errcheck);
        #S1 READINT(nx,m_fp,errcheck);
        #S1 READINT(ny,m_fp,errcheck);
        #S1 READINT(nz,m_fp,errcheck);
        #S1 READINT(rx,m_fp,errcheck);
        #S1 READINT(ry,m_fp,errcheck);
        #S1 READINT(rz,m_fp,errcheck);
        # if(nsg == m_numSubgrids-1){
            #S2 m_p = m_nx/nx;
            #S2 m_q = m_ny/ny;
            #S2 m_r = m_nz/nz;
        # }

        # // read values for subgrid
        # // qq is the location of the subgrid
        # S3 int qq = z*m_nx*m_ny + y*m_nx + x;
        # int k,i,j;
        # //int index = qq;//+k*nx*ny+i*nx;
        # for (k=0; k<nz; k++){ // read nz
            # for(i=0;i<ny;i++){ //read ny
                # // read full "pencil"
                #S4 int index = qq+k*m_nx*m_ny+i*m_nx; //read qq, m_nx, m_ny
                #S5 uint64_t* buf = (uint64_t*)&(m_data[index]); //read m_data, index; write buf
                #S6 int read_count = fread(buf,8,nx,m_fp); //read buf, nx, m_fp?; write: read_count

                # for(j=0;j<nx;j++){ // read nx
                    #S7 uint64_t tmp = buf[j]; //read buf[j]; write tmp
                    #S8 tmp = bswap64(tmp); //read tmp; write tmp
                    #S9 m_data[index+j] = *(double*)(&tmp); // read index, tmp; write m_data[data+j]
                # }
            # }
        # }
    # }
# }

Domain := [m_numSubgrids, nz, ny, nx] -> {
    S0[];
    S1[nsg] : 0 <= nsg < m_numSubgrids;
    S2[nsg] : 0 <= nsg < m_numSubgrids and nsg = (m_numSubgrids - 1);
    S3[nsg] : 0 <= nsg < m_numSubgrids;
    #S4[nsg] : 0 <= nsg < m_numSubgrids;
    #S5[nsg,k] : 0 <= nsg < m_numSubgrids and 0 <= k < nz;
    S4[nsg,k,i] : 0 <= nsg < m_numSubgrids and 0 <= k < nz and 0 <= i < ny;
    S5[nsg,k,i] : 0 <= nsg < m_numSubgrids and 0 <= k < nz and 0 <= i < ny;
    S6[nsg,k,i] : 0 <= nsg < m_numSubgrids and 0 <= k < nz and 0 <= i < ny;
    #S9[nsg,k,i] : 0 <= nsg < m_numSubgrids and 0 <= k < nz and 0 <= i < ny;
    S7[nsg,k,i,j] : 0 <= nsg < m_numSubgrids and 0 <= k < nz and 0 <= i < ny and 0 <= j <= nx;
    S8[nsg,k,i,j] : 0 <= nsg < m_numSubgrids and 0 <= k < nz and 0 <= i < ny and 0 <= j <= nx;
    S9[nsg,k,i,j] : 0 <= nsg < m_numSubgrids and 0 <= k < nz and 0 <= i < ny and 0 <= j <= nx;
};

Read := [m_numSubgrids] -> {
    S2[nsg] -> nx[0];
    S2[nsg] -> m_nx[0];
    S2[nsg] -> ny[0];
    S2[nsg] -> m_ny[0];
    S2[nsg] -> nz[0];
    S2[nsg] -> m_nz[0];
    S3[nsg] -> z[0];
    S3[nsg] -> m_nx[0];
    S3[nsg] -> m_ny[0];
    S3[nsg] -> y[0];
    S3[nsg] -> m_nx[0];
    S3[nsg] -> x[0];
    #S4[nsg] -> nz[0];
    #S5[nsg,k] -> ny[0];
    S4[nsg,k,i] -> qq[0];
    S4[nsg,k,i] -> k[0];
    S4[nsg,k,i] -> m_nx[0];
    S4[nsg,k,i] -> m_ny[0];
    S5[nsg,k,i] -> index[0];
    S5[nsg,k,i] -> m_data[index];
    S6[nsg,k,i] -> buf[0];
    S6[nsg,k,i] -> nx[0];
    #S9[nsg,k,i] -> nx[0];
    S7[nsg,k,i,j] -> buf[j];
    S9[nsgk,k,i,j] -> tmp[0];
    S9[nsgk,k,i,j] -> tmp[0];
    S9[nsg,k,i,j] -> index[0];
} * Domain;

Write := [m_numSubgrids, index] -> {
    S0[] -> m_data[0];
    S1[nsg] -> x[0];
    S1[nsg] -> y[0];
    S1[nsg] -> z[0];
    S1[nsg] -> nx[0];
    S1[nsg] -> ny[0];
    S1[nsg] -> nz[0];
    S1[nsg] -> rx[0];
    S1[nsg] -> ry[0];
    S1[nsg] -> rz[0];
    S2[nsg] -> m_p[0];
    S2[nsg] -> m_q[0];
    S2[nsg] -> m_r[0];
    S3[nsg] -> qq[0];
    S4[nsg,k,i] -> index[0];
    S5[nsg,k,i] -> buf[0];
    S6[nsg,k,i] -> read_count[0];
    S7[nsg,k,i,j] -> tmp[0];
    S8[nsg,k,i,j] -> tmp[0];
    S9[nsg,k,i,j] -> m_data[index + j];
} * Domain;

Schedule := [m_numSubgrids] -> {
   S0[] ->        [0,0,0,0,0,0,0,0,0];
   S1[nsg] ->     [1,nsg,0,0,0,0,0,0,0];
   S2[nsg] ->     [1,nsg,1,0,0,0,0,0,0];
   S3[nsg] ->     [1,nsg,2,0,0,0,0,0,0];
   #S4[nsg] ->     [1,nsg,3,0,0,0,0,0,0];
   #S5[nsg,k] ->   [1,nsg,4,k,0,0,0,0,0];
   S4[nsg,k,i] -> [1,nsg,4,k,1,i,1,0,0];
   S5[nsg,k,i] -> [1,nsg,4,k,1,i,2,0,0];
   S6[nsg,k,i] -> [1,nsg,4,k,1,i,3,0,0];
   #S9[nsg,k,i] -> [1,nsg,4,k,1,i,4,0,0];
   S7[nsg,k,i,j] -> [1, nsg, 4, k,1 ,i, 4, j,0];
   S8[nsg,k,i,j] -> [1, nsg, 4, k,1 ,i, 4,j,1];
   S9[nsg,k,i,j] -> [1, nsg, 4, k,1 ,i, 4,j,2];
};

print "Schedule";
print Schedule;

### Happens-Before relation without syntactic sugar
# Lexico := { [i0,i1,i2] -> [o0,o1,o2] : i0 < o0 or i0 = o0 and i1 < o1 or i0 = o0 and i1 = o1 and i2 < o2 };
# Before := Schedule . Lexico . (Schedule^-1)
Before := Schedule << Schedule;

print "Before";
print Before;

RaW := (Write . (Read^-1)) * Before;
WaW := (Write . (Write^-1)) * Before;
WaR := (Read . (Write^-1)) * Before;

print "RaW deps";
print RaW;

print "WaW deps";
print WaW;

print "WaR deps";
print WaR;

IslSchedule := schedule Domain respecting (RaW+WaW+WaR) minimizing RaW;
IslSchedule := IslSchedule + {}; # flatten the schedule tree

print "IslSchedule";
print IslSchedule;

IslBefore := IslSchedule << IslSchedule;

print "IslBefore";
print IslBefore;

print "Does IslSchedule respects RaW deps?";
print RaW <= IslBefore;

print "Does IslSchedule respects WaW deps?";
print WaW <= IslBefore;

print "Does IslSchedule respects WaR deps?";
print WaR <= IslBefore;

print "Codegen";
codegen (IslSchedule * Domain);
codegen (Schedule * Domain);
 */

