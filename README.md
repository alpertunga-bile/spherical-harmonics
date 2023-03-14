# spherical-harmonics

Based on [Stupid Spherical Harmonics (SH) Tricks][def]

[def]: https://www.ppsloan.org/publications/StupidSH36.pdf

- [x] Using [PXDMath](https://github.com/alpertunga-bile/PixelDancerMath) library
- [x] Skybox textures are taken from LearnOpenGL repository
- [x] Using stb-image library for getting pixels

## Results

- 3 bands are used.

```
------------------------------------------------------------------------------------------
-- Gentle Introduction 2500 Samples
Red   Channel : 176.24  -87.31  30.56   38.85   -19.09  -195.23 -16.78  18.46   -79.45
Green Channel : 180.62  -90.11  31.15   38.25   -20.07  -201.06 -15.86  19.18   -83.21
Blue  Channel : 180.97  -89.77  30.19   39.73   -21.19  -201.68 -17.55  19.95   -84.28
------------------------------------------------------------------------------------------
-- Stupid SH Tricks
Red   Channel : 175.04  -17.14  44.01   4.37    6.79    -9.50   -3.80   1.30    -0.47
Green Channel : 175.37  -16.95  45.36   4.43    6.63    -10.24  -3.46   1.36    -0.43
Blue  Channel : 175.31  -16.58  45.54   4.40    6.63    -8.71   -2.39   1.72    -0.44
```