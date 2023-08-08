#include "base.h"

int stringBinaryToDecimal(char* binary)
{
	int dec, pwr, i;
	dec = 0;
	pwr = 1;
	for(i = 9; i >= 0; --i)
	{
		if(binary[i] == '1')
			dec += pwr;
		pwr = pwr * 2;
	}
	return dec;
}


char* stringBinaryToNewBase(char* binary, char res[3])
{
	int dec;
	dec = stringBinaryToDecimal(binary);
	DecToNewBase(dec, res);
	return res;
}

char* DecToNewBase(int num, char res[3])
{
	int i;
	char base32[32] = {'!','@','#', '$', '%', '^', '&', '*', '<', '>', 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
	res[1] = base32[0];
	res[0] = base32[0];
	res[2] = '\0';
	i = 1; 
    while (num > 0)
    {
      	res[i--] = base32[num % 32];
      	num /= 32;
   	}
	return res;
}

