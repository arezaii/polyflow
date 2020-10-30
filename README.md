# PolyFlow

Experimental code demonstrating use of polyhedral model on reading ParFlow binary files (.pfb)


## Requirements

* C++ compiler
* CMake >= 3.14

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
bin/polyflow -i <parflow_binary_file.pfb>
```

## Output

Only prints when opening the file and after closing it.

```
Begin Reading PFB /home/arezaii/pf_subsetter_testing/forcings/NLDAS 1.Temp.000013_to_000024.pfb
End Reading PFB File /home/arezaii/pf_subsetter_testing/forcings/NLDAS 1.Temp.000013_to_000024.pfb.

```


