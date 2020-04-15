#include "ResourceData.h"

ResourceData::ResourceData()
{
	//dataFilePaths.emplace("Data//models//", DataTypes::MODELS);
	//dataFilePaths.emplace("Data//textures//", DataTypes::TEXTURES);
}

bool ResourceData::LoadImageData(std::string image)
{
	//ImageData img;
	images.emplace(image, ImageData());
	FILE* filePtr = nullptr;

	// Open the targa file for reading in binary.
	if (fopen_s(&filePtr, ("Data//textures//" + image + ".tga").c_str(), "rb") != 0)
		return false;

	// Read in the file header.
	if (static_cast<unsigned int>(fread(&images[image], sizeof(ImageData::ImageBufferData), 1, filePtr)) != 1)
		return false;

	// Check that it is 32 bit and not 24 bit.
	if (static_cast<int>(images[image].buffer.bpp) != 32)
		return false;

	// Get the important information from the header.
	auto height = static_cast<int>(images[image].buffer.height);
	auto width = static_cast<int>(images[image].buffer.width);

	// Calculate the size of the 32 bit image data.
	int imageSize = width * height * 4;

	// Allocate memory for the targa image data.
	unsigned char* targaImage = new unsigned char[imageSize];
	if (!targaImage)
		return false;

	// Read in the targa image data.
	if (static_cast<unsigned int>(fread(targaImage, 1, imageSize, filePtr)) != imageSize)
		return false;

	// Close the file.
	if (fclose(filePtr) != 0)
		return false;

    // Allocate memory for the targa destination data.
	images[image].data = new unsigned char[imageSize];
	if (!images[image].data)
		return false;

	// Initialize the index into the targa destination data array.
	int index = 0;

	// Initialize the index into the targa image data.
	int k = (width * height * 4) - (width * 4);

	// Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			images[image].data[index + 0] = targaImage[k + 2]; // Red.
			images[image].data[index + 1] = targaImage[k + 1]; // Green.
			images[image].data[index + 2] = targaImage[k + 0]; // Blue
			images[image].data[index + 3] = targaImage[k + 3]; // Alpha

			// Increment the indexes into the targa data.
			k += 4;
			index += 4;
		}

		// Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
		k -= (width * 8);
	}

	// Release the targa image data now that it was copied into the destination array.
	delete[] targaImage;
	targaImage = nullptr;

	delete filePtr;
	filePtr = nullptr;

	return true;
}
