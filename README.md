# spherical-harmonics

Based on [Stupid Spherical Harmonics (SH) Tricks][def] and [A Gentle Introduction To Precomputed Radiance Transfer][def2]

[def]: https://www.ppsloan.org/publications/StupidSH36.pdf
[def2]: https://www.inf.ufrgs.br/~oliveira/pubs_files/Slomp_Oliveira_Patricio-Tutorial-PRT.pdf

- [x] Using [PXDMath](https://github.com/alpertunga-bile/PixelDancerMath) library
- [x] Skybox textures are taken from LearnOpenGL repository
- [x] Using stb-image library for getting pixels
- [x] Using AVX2(Advanced Vector Extension 2) 

## Results

- 3 bands are used.

```
Progress : %100 0.00 seconds
------------------------------------------------------------------------------------------
-- A Gentle Introduction To PRT 2500 Samples
Red   Channel : 146.17  -76.98  -7.71   2.87    1.68    -9.40   -34.86  3.66    -68.19
Green Channel : 147.48  -77.36  -7.56   3.23    1.67    -9.75   -35.88  3.68    -70.02
Blue  Channel : 146.13  -76.01  -9.06   3.11    1.20    -10.07  -32.76  3.54    -68.08
Texture 6 is in progress (6 | 6) DONE!!!
------------------------------------------------------------------------------------------
-- Stupid SH Tricks
Red   Channel : 175.04  -17.14  44.01   4.37    6.79    -9.50   -3.80   1.30    -0.47
Green Channel : 175.37  -16.95  45.36   4.43    6.63    -10.24  -3.46   1.36    -0.43
Blue  Channel : 175.31  -16.58  45.54   4.40    6.63    -8.71   -2.39   1.72    -0.44
```