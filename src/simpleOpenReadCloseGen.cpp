//
// Created by arezaii on 10/30/20.
//

#include "simpleOpenReadCloseGen.hpp"


void run_generated_code() {
    S0();
    for (int c1 = 0; c1 < m_numSubgrids; c1 += 1) {
        S1(c1);
        if (c1 + 1 == m_numSubgrids)
        S2(m_numSubgrids - 1);
        for (int c3 = 0; c3 < nz; c3 += 1)
            for (int c4 = 0; c4 < ny; c4 += 1) {
                S3(c1, c3, c4);
                for (int c5 = 0; c5 <= nx; c5 += 1)
                S4(c1, c3, c4, c5);
            }
    }
    S5();
}

/*
 * # define S0() {m_fp = fopen( m_filename.c_str(), "rb"); \
              # std::cout << "Begin Reading PFB " << m_filename<<std::endl;\
              # READDOUBLE(m_X,m_fp,errcheck); \
              # READDOUBLE(m_Y,m_fp,errcheck);\
              # READDOUBLE(m_Z,m_fp,errcheck);\
              # READINT(m_nx,m_fp,errcheck);\
              # READINT(m_ny,m_fp,errcheck); \
              # READINT(m_nz,m_fp,errcheck); \
              # READDOUBLE(m_dX,m_fp,errcheck);\
              # READDOUBLE(m_dY,m_fp,errcheck);\
              # READDOUBLE(m_dZ,m_fp,errcheck);\
              # READINT(m_numSubgrids,m_fp,errcheck);\
              # m_data = (double*)std::malloc(sizeof(double)*m_nx*m_ny*m_nz);}
# define S1(nsg){READINT(x,m_fp,errcheck);\
             # READINT(y,m_fp,errcheck);\
             # READINT(z,m_fp,errcheck);\
             # READINT(nx,m_fp,errcheck);\
             # READINT(ny,m_fp,errcheck);\
             # READINT(nz,m_fp,errcheck);\
             # READINT(rx,m_fp,errcheck);\
             # READINT(ry,m_fp,errcheck);\
             # READINT(rz,m_fp,errcheck);\
             # qq = z*m_nx*m_ny + y*m_nx + x;}
# define S2(nsg){m_p = m_nx/nx;\
             # m_q = m_ny/ny;\
             # m_r = m_nz/nz;}

# define S3(nsg,k,i){index = qq+k*m_nx*m_ny+i*m_nx;\
                    # buf= (uint64_t*)&(m_data[index]);\
                    # read_count = fread(buf,8,nx,m_fp);}

# define S4(nsg,k,i,j){tmp = buf[j];\
                      # tmp = bswap64(tmp);\
                      # m_data[index+j] = *(double*)(&tmp);}

# define S5(){if(m_fp){std::fclose(m_fp);} \
            # for (int m =0;m<2*m_nx;m++){ \
                # std::cout<<"Cell "<<m<<": " <<m_data[m]<<std::endl; \
            # }                               \
            # free(m_data);\
            # std::cout<<"End Reading PFB File "<<m_filename<<"."<<std::endl;}

Domain := [m_numSubgrids, nz, ny, nx] -> {
    S0[];
    S1[nsg] : 0 <= nsg < m_numSubgrids;
    S2[nsg] : 0 <= nsg < m_numSubgrids and nsg = (m_numSubgrids - 1);
    S3[nsg,k,i] : 0 <= nsg < m_numSubgrids and 0 <= k < nz and 0 <= i < ny;
    S4[nsg,k,i,j] : 0 <= nsg < m_numSubgrids and 0 <= k < nz and 0 <= i < ny and 0 <= j <= nx;
    S5[];
};

Read := [m_numSubgrids] -> {
    S1[] -> m_nx[0];
    S1[] -> m_ny[0];
    S1[] -> m_nz[0];
    S2[nsg] -> m_nx[0];
    S2[nsg] -> m_ny[0];
    S2[nsg] -> m_nz[0];
    S2[nsg] -> nx[0];
    S2[nsg] -> ny[0];
    S2[nsg] -> nz[0];
    S3[nsg,k,i] -> m_nx[0];
    S3[nsg,k,i] -> m_ny[0];
    S3[nsg,k,i] -> qq[0];
    S3[nsg,k,i] -> x[0];
    S3[nsg,k,i] -> y[0];
    S3[nsg,k,i] -> nx[0];
    S4[nsg,k,i,j] -> buf[j];
    S4[nsg,k,i,j] -> index[0];
} * Domain;

Write := [m_numSubgrids, index] -> {
    S0[] -> m_fp[0];
    S0[] -> m_data[0];
    S0[] -> m_numSubgrids[0];
    S0[] -> m_nx[0];
    S0[] -> m_ny[0];
    S0[] -> m_nz[0];
    S1[nsg] -> x[0];
    S1[nsg] -> y[0];
    S1[nsg] -> z[0];
    S1[nsg] -> nx[0];
    S1[nsg] -> ny[0];
    S1[nsg] -> nz[0];
    S1[nsg] -> rx[0];
    S1[nsg] -> ry[0];
    S1[nsg] -> rz[0];
    S1[nsg] -> qq[0];
    S2[nsg] -> m_p[0];
    S2[nsg] -> m_q[0];
    S2[nsg] -> m_r[0];
    S3[nsg,k,i] -> index[0];
    S3[nsg,k,i] -> buf[0];
    S3[nsg,k,i] -> read_count[0];
    S4[nsg,k,i,j] -> tmp[0];
    S4[nsg,k,i,j] -> m_data[index + j];
} * Domain;

Schedule := [m_numSubgrids] -> {
   S0[] ->        [0,0,0,0,0,0];
   S1[nsg] ->     [1,nsg,0,0,0,0];
   S2[nsg] ->     [1,nsg,1,0,0,0];
   S3[nsg,k,i] -> [1,nsg,2,k,i,0];
   S4[nsg,k,i,j]->[1,nsg,2,k,i,j];
   S5[] ->        [2,0,0,0,0,0];

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