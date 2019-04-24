#include <stdio.h>
#include "ConvertEncoding.h"

#define READ_BUFFER_SIZE 4096
#define WRITE_BUFFER_UTF8_SIZE (3*READ_BUFFER_SIZE+1)

unsigned char readBuffer[READ_BUFFER_SIZE];
unsigned char writeBufferUtf8[WRITE_BUFFER_UTF8_SIZE];

const char* path = "sample.txt";

const char* win1251OutPath = "win1251.txt";
const char* utf8OutPath = "utf8.txt";

FILE* sample;
FILE* win1251Out;
FILE* utf8Out;

int OpenFiles();
void CloseFiles();

int main()
{
	if(!OpenFiles()) return 0;

	int readBufferSize = fread(readBuffer, 1, READ_BUFFER_SIZE, sample);

	while (readBufferSize != 0)
	{
		unsigned char* currentWriteBufferUtf8 = ConvertEncoding_OneByte_To_UTF8(readBuffer, writeBufferUtf8, readBufferSize, ISO8859_5_To_UTF8_Table);
		ConvertEncoding_OneByte_To_OneByte(readBuffer, readBuffer, readBufferSize, ISO8859_5_To_win1251_Table);

		fwrite(readBuffer, 1, readBufferSize, win1251Out);
		fwrite(writeBufferUtf8, 1, currentWriteBufferUtf8 - writeBufferUtf8, utf8Out);

		readBufferSize = fread(readBuffer, 1, READ_BUFFER_SIZE, sample);
	}

	CloseFiles();

	return 0;
}

int OpenFiles()
{
	sample = fopen(path, "rb");
	if (sample == NULL)
	{
		printf("%s open error", path);
		getchar();

		return 0;
	}

	win1251Out = fopen(win1251OutPath, "wb");
	if (win1251Out == NULL)
	{
		fclose(sample);

		printf("%s open error", win1251OutPath);
		getchar();

		return 0;
	}

	utf8Out = fopen(utf8OutPath, "wb");
	if (utf8Out == NULL)
	{
		fclose(sample);

		printf("%s open error", utf8OutPath);
		getchar();

		return 0;
	}

	return 1;
}

void CloseFiles()
{
	fclose(sample);

	fclose(win1251Out);
	fclose(utf8Out);
}
