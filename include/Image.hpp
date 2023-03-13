#pragma once

#include "../stb-image/stb_image.h"
#include <iostream>
#include <vector>

struct ImageData
{
	int width;
	int height;
	int channel;
	int size;
	std::vector<unsigned char> pixels;

	int GetValue(int index)
	{
		return index >= size ? 0 : static_cast<int>(pixels[index]);
	}
};

class Image
{
public:
	void Setup()
	{
		images.resize(6);

		std::vector<const char*> faces =
		{
			"skybox/right.jpg",
			"skybox/left.jpg",
			"skybox/top.jpg",
			"skybox/bottom.jpg",
			"skybox/front.jpg",
			"skybox/back.jpg"
		};

		for (int i = 0; i < 6; i++)
		{
			LoadTexture(i, faces[i]);
		}
	}

	ImageData operator[](int index)
	{
		return images[index];
	}

private:
	void LoadTexture(int index, const char* texName)
	{
		stbi_set_flip_vertically_on_load(true);
		int width = 0, height = 0, channel = 0;
		unsigned char* texture = stbi_load(texName, &width, &height, &channel, 0);
		images[index].width = width;
		images[index].height = height;
		images[index].channel = channel;
		LoadToVector(index, width * height * channel, texture);
		images[index].size = images[index].pixels.size();
		stbi_image_free(texture);
	}

	void LoadToVector(int index, size_t size, unsigned char* tex)
	{
		images[index].pixels.insert(images[index].pixels.end(), &tex[0], &tex[size - 1]);
	}

private:
	std::vector<ImageData> images;
};
