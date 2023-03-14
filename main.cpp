#define STB_IMAGE_IMPLEMENTATION
#include "include/Image.hpp"
#include "include/Cubemap.hpp"
#include "SphericalHarmonics.h"
#include "ConstantValues.h"
#include <iostream>
#include <chrono>

void PrintVector(std::vector<double>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        printf("%.2f\t", vec[i]);
    }

    printf("\n");
}

void PrintResults(const char* resultName, std::vector<double>& Rresult, std::vector<double>& Gresult, std::vector<double>Bresult)
{
    printf("------------------------------------------------------------------------------------------\n");
    printf("-- %s\n", resultName);
    printf("Red   Channel : "); PrintVector(Rresult);
    printf("Green Channel : "); PrintVector(Gresult);
    printf("Blue  Channel : "); PrintVector(Bresult);
}

void StupidSH(Image& image, int nBands, std::vector<double>& Rresult, std::vector<double>& Gresult, std::vector<double>& Bresult)
{
    SphericalHarmonics sh;
    int totalBands = nBands * nBands;
    double fWtSum = 0.0;

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
            for (int x = 0; x < imageData.width * imageData.channel; x += imageData.channel)
            {
                float u = static_cast<float>(x) / (static_cast<float>(imageData.width) * static_cast<float>(imageData.channel));
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
}

void GentleIntroduction(Image& image, SphericalHarmonics& sh, int totalBands, int totalSample, std::vector<double>& Rresult, std::vector<double>& Gresult, std::vector<double>& Bresult)
{
    for (int i = 0; i < totalBands; i++)
    {
        Rresult[i] = 0.0f;
        Gresult[i] = 0.0f;
        Bresult[i] = 0.0f;
    }

    for (int i = 0; i < totalSample; i++)
    {
        auto progress = (int)((double)((double)(i) / (totalSample - 1)) * 100);
        std::cout << "\rProgress : %" << progress << " ";
        auto start = std::chrono::system_clock::now();

        // choose face and get image data
        SHSample sample = sh[i];
        auto [uv, face] = GetCubemapUVFace(sample.vec);
        ImageData imageData = image[face];

        // access pixel values
        int pixelIndex = (uv.x * imageData.width + uv.y * imageData.height) * imageData.channel;
        int rValue = imageData.GetValue(pixelIndex + 0);
        int gValue = imageData.GetValue(pixelIndex + 1);
        int bValue = imageData.GetValue(pixelIndex + 2);

        for (int b = 0; b < totalBands; b++)
        {
            double coeff = sample.coefficient[b];
            if (std::isnan(coeff))
            {
                std::cout << "Found it";
                exit(0);
            }
            Rresult[b] += rValue * coeff;
            Gresult[b] += gValue * coeff;
            Bresult[b] += bValue * coeff;
        }

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedSeconds = end - start;

        std::cout << std::fixed;
        std::cout << std::setprecision(2);
        std::cout << ((double)(100 - progress)) * elapsedSeconds.count() << " seconds" << std::flush;
    }

    std::cout << "\n";

    double weight = 4.0 * PI;
    double scale = weight / totalSample;

    for (int i = 0; i < totalBands; i++)
    {
        Rresult[i] *= scale;
        Gresult[i] *= scale;
        Bresult[i] *= scale;
    }
}

int main()
{
    Image image;
    image.Setup();

    int nBands = 3;
    int sampleCount = 50;
    SphericalHarmonics sh(sampleCount, nBands);

    const int totalBands = nBands * nBands;
    std::vector<double> Rresult(totalBands);
    std::vector<double> Gresult(totalBands);
    std::vector<double> Bresult(totalBands);

    GentleIntroduction(image, sh, totalBands, sh.GetSampleCount(), Rresult, Gresult, Bresult);

    PrintResults("Gentle Introduction 2500 Samples", Rresult, Gresult, Bresult);

    StupidSH(image, nBands, Rresult, Gresult, Bresult);

    PrintResults("Stupid SH Tricks", Rresult, Gresult, Bresult);

    return 0;
}
