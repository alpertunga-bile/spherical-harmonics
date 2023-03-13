#define STB_IMAGE_IMPLEMENTATION
#include "include/Image.hpp"
#include "SphericalHarmonics.h"
#include "ConstantValues.h"
#include <iostream>

void PrintVector(std::vector<double>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        printf("%.2f\t", vec[i]);
    }

    printf("\n");
}

int main()
{
    Image image;
    image.Setup();

    SphericalHarmonics sh;
    int nBands = 3;

    double fWtSum = 0.0;

    const int totalBands = nBands * nBands;
    std::vector<double> Rresult(totalBands);
    std::vector<double> Gresult(totalBands);
    std::vector<double> Bresult(totalBands);

    for (int i = 0; i < totalBands; i++)
    {
        Rresult[i] = 0.0f;
        Gresult[i] = 0.0f;
        Bresult[i] = 0.0f;
    }

    // https://www.ppsloan.org/publications/StupidSH36.pdf
    for (int i = 0; i < 6; i++)
    {
        ImageData imageData = image[i];
        printf("At Texture %d\n", i + 1);
        for (int y = 0; y < imageData.height; y++)
        {
            for (int x = 0; x < imageData.width; x += imageData.channel)
            {
                float u = static_cast<float>(x) / static_cast<float>(imageData.width);
                float v = static_cast<float>(y) / static_cast<float>(imageData.height);
                double fTemp = 1.0 + static_cast<double>(u * u) + static_cast<double>(v * v);
                double fWt = 4.0 / (std::sqrt(fTemp) * fTemp);
                std::vector<float> coeff = sh.GetCoefficients(u, v, nBands);
                int pixelIndex = y * imageData.height + x;
                for (int j = 0; j < totalBands; j++)
                {
                    Rresult[j] += static_cast<double>(coeff[j]) * fWt * static_cast<double>(imageData.GetValue(pixelIndex + 0));
                    Gresult[j] += static_cast<double>(coeff[j]) * fWt * static_cast<double>(imageData.GetValue(pixelIndex + 1));
                    Bresult[j] += static_cast<double>(coeff[j]) * fWt * static_cast<double>(imageData.GetValue(pixelIndex + 2));
                }
                fWtSum += fWt;
            }
        }
    }

    for (int i = 0; i < totalBands; i++)
    {
        Rresult[i] *= 4.0 * PI / fWtSum;
        Gresult[i] *= 4.0 * PI / fWtSum;
        Bresult[i] *= 4.0 * PI / fWtSum;
    }

    PrintVector(Rresult);
    PrintVector(Gresult);
    PrintVector(Bresult);

    return 0;
}
