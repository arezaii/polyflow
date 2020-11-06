# PolyFlow

Experimental code demonstrating use of polyhedral model on reading and writing ParFlow binary files (.pfb)


## Requirements

* C++ compiler
* CMake >= 3.14 
* [barvinok](http://barvinok.gforge.inria.fr/) 0.41.3
    * [gmp](https://gmplib.org/#DOWNLOAD) 6.0.0
    * [ntl](http://www.shoup.net/ntl/download.html) 9.3.0



## Building

Make a build directory in the repository root directory, *polyflow*
```shell script
mkdir build
cd build
cmake ..
make
```

## Usage

The previous build step should have created the binary in a subdirectory `bin`

```shell script
bin/polyflow -i <parflow_binary_file.pfb> -o <output_filename> -s <cellwise_sum_value>
```

where `cellwise_sum_value` is an integer value to add to every cell in `<parflow_binary_file.pfb>`

## Output

Only prints when opening the file and after writing it.

```
Begin Reading PFB /home/arezaii/pf_subsetter_testing/forcings/NLDAS 1.Temp.000013_to_000024.pfb
...<some pfb data>...
End Reading PFB File /home/arezaii/pfdir/parflow/test/washita/NLDAS/NLDAS.Temp.000001_to_000024.pfb.00000.
finished writing file test_out.pfb

```


## Installing Requirements

Installing the barvinok and ntl requirements can be a bit tricky. The following information is largely copied from 
the [blog of Dr. Michelle Strout](https://michellemillsstrout.blogspot.com/2015/09/getting-started-with-isccbarvinokisl.html)


This combination of packages worked on centOS 7

#### download, build, and install gmp
```
 1. download gmp-6.0.0a.tar.bz2 from https://gmplib.org/#DOWNLOAD 
 2. bunzip2 gmp-6.0.0a.tar.bz2
 3. cd gmp-6.0.0/
 4. ./configure —prefix=~/software
 5. make; make check; make install
```

#### download, build, and install ntl
```
 1. download ntl-9.3.0.tar.gz from http://www.shoup.net/ntl/download.html
 2. gunzip ntl-9.3.0.tar.gz; tar xvf ntl-9.3.0.tar
 3. cd ntl-9.3.0/src/
 4. ./configure DEF_PREFIX=~/software NTL_GMP_LIP=on CXXFLAGS='-DNTL_STD_CXX'
 5. make; make check; make install
```

#### download, build, and install barvinok
```
 1. download barvinok-0.41.3.tar.gz from http://barvinok.gforge.inria.fr 
 2. ./configure --prefix=~/software --with-gmp-prefix=~/software --with-ntl-prefix=~/software
 3. make; make check; make install
```
