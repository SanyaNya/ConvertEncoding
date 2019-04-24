#ifndef CONVERT_ENCODING_H
#define CONVERT_ENCODING_H

//Код в UTF8 обозначается как {size, byte0, byte1, byte2}, где size количество байт
//При переводе из OEM866 или ISO8859-5 максимальный размер 3

extern const unsigned char OEM866_To_UTF8_Table[256][4];
extern const unsigned char ISO8859_5_To_UTF8_Table[256][4];
extern const unsigned char OEM866_To_win1251_Table[256];
extern const unsigned char ISO8859_5_To_win1251_Table[256];

//Чтение readBuffer, перекодировка указанной однобайтной кодировки в UTF8, запись в writeBuffer.
//Возвращает текущую позицию writeBuffer.
//Размер writeBuffer должен быть в 4 раза больше readBuffer(Максимальный размер символа UTF8 - 4 байта).
unsigned char* ConvertEncoding_OneByte_To_UTF8(unsigned char* readBuffer, unsigned char* writeBuffer, int readBufferSize, const unsigned char* EncodingTable_OneByte_To_UTF8);

//Чтение readBuffer, перекодировка указанной однобайтной кодировки в другую указанную однобайтной кодировку, запись в writeBuffer.
void ConvertEncoding_OneByte_To_OneByte(unsigned char* readBuffer, unsigned char* writeBuffer, int readBufferSize, const unsigned char* EncodingTable_OneByte_To_OneByte);

#endif