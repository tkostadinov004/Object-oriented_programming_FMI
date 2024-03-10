#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)
using namespace std;

namespace Constants
{
	constexpr size_t PLACEHOLDER_LENGTH = 100;
	constexpr size_t BUFFER_SIZE = 1024;
	constexpr size_t MAX_PLACEHOLDERS_COUNT = 20;
	const char* TEMP_PATH = "temp.txt";
}
struct Placeholder
{
	char title[Constants::PLACEHOLDER_LENGTH];
	char content[Constants::PLACEHOLDER_LENGTH];
};
struct Template
{
	Placeholder placeholders[Constants::MAX_PLACEHOLDERS_COUNT];
	size_t placeholdersCount = 0;
};
void deserializePlaceholder(std::ifstream& ifs, Placeholder& placeholder)
{
	char titleBuffer[Constants::PLACEHOLDER_LENGTH];
	char contentBuffer[Constants::PLACEHOLDER_LENGTH];
	ifs >> titleBuffer;
	ifs.ignore();

	ifs.getline(contentBuffer, Constants::PLACEHOLDER_LENGTH);

	strcpy(placeholder.title, titleBuffer);
	strcpy(placeholder.content, contentBuffer);
}
void deserializeTemplate(std::ifstream& ifs, Template& documentTemplate)
{
	while (!ifs.eof())
	{
		deserializePlaceholder(ifs, documentTemplate.placeholders[documentTemplate.placeholdersCount++]);
	}
}
void deserializeTemplate(const char* filename, Template& documentTemplate)
{
	if (!filename)
	{
		return;
	}

	std::ifstream ifs(filename);
	if (!ifs.is_open())
	{
		return;
	}

	deserializeTemplate(ifs, documentTemplate);
}
void getPlaceholderContentByName(const char* placeholderName, char* placeholderContent, const Template& documentTemplate)
{
	if (!placeholderName || !placeholderContent)
	{
		return;
	}

	for (size_t i = 0; i < documentTemplate.placeholdersCount; i++)
	{
		if (strcmp(placeholderName, documentTemplate.placeholders[i].title) == 0)
		{
			strcpy(placeholderContent, documentTemplate.placeholders[i].content);
			break;
		}
	}
}
void copyFile(std::ifstream& src, std::ofstream& dest)
{
	while (!src.eof())
	{
		char buffer[Constants::BUFFER_SIZE];
		src.getline(buffer, Constants::BUFFER_SIZE);

		dest << buffer << endl;
	}
}
void copyFile(const char* srcFilename, const char* destFilename)
{
	if (!srcFilename || !destFilename)
	{
		return;
	}

	std::ifstream src(srcFilename);
	if (!src.is_open())
	{
		return;
	}
	std::ofstream dest(destFilename);
	if (!dest.is_open())
	{
		return;
	}

	copyFile(src, dest);
}
void replaceInMessage(const char* messageFilename, const Template& documentTemplate)
{
	if (!messageFilename)
	{
		return;
	}

	std::ifstream ifs(messageFilename);
	std::ofstream tempFile(Constants::TEMP_PATH);

	if (!ifs.is_open() || !tempFile.is_open())
	{
		return;
	}

	while (!ifs.eof())
	{
		char buffer[Constants::BUFFER_SIZE];
		ifs.getline(buffer, Constants::BUFFER_SIZE, '{');
		tempFile << buffer;

		char placeholderName[Constants::PLACEHOLDER_LENGTH];
		ifs.getline(placeholderName, Constants::PLACEHOLDER_LENGTH, '}');
		
		if (ifs.eof())
		{
			break;
		}

		char placeholderContent[Constants::PLACEHOLDER_LENGTH];
		getPlaceholderContentByName(placeholderName, placeholderContent, documentTemplate);
		tempFile << placeholderContent;
	}
	ifs.close();
	tempFile.close();

	copyFile(Constants::TEMP_PATH, messageFilename);
}
int main()
{
	Template documentTemplate{};
	deserializeTemplate("template.txt", documentTemplate);

	replaceInMessage("message.txt", documentTemplate);
}