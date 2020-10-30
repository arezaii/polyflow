#ifndef PARFLOWIO_PFUTIL_HPP
#define PARFLOWIO_PFUTIL_HPP
#include <cstdint>

/** Tests if the machine is little endian.
 * \return          `true` if the machine is little endian.
 */
bool isLittleEndian();

/** Tests if the machine is big endian.
 * \return          `true` if the machine is big endian.
 */
bool isBigEndian();

/** Returns `data` with the byte order reversed on little endian platforms.
 * \param   data    The data to be reversed
 * \return          `data` with the byte order reversed if the platform is little endian.
 */
uint32_t bswap32(uint32_t data);

/** Returns `data` with the byte order reversed on little endian platforms.
 * \param   data    The data to be reversed
 * \return          `data` with the byte order reversed if the platform is little endian.
 */
uint64_t bswap64(uint64_t data);


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

#endif //PARFLOWIO_PFUTIL_HPP
