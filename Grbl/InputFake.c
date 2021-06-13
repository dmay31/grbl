#include "grbl.h"

static uint8_t pos = 0;
static uint8_t strIndex = 0;

static const char * code[] = {"G0 Y500\n", "G0 X500\n", "G0 Y100\n"};

char serial_read_test(void)
{
	if( strIndex < 3 )
	{
		if( pos < strlen(code[strIndex]) )
		{
			return code[strIndex][pos++];
		}
		else
		{
			strIndex++;
			pos = 0;
			return SERIAL_NO_DATA;
		}
	}
	else
	{
		return SERIAL_NO_DATA;
	}
	
}