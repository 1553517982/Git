static unsigned char					 g_sKeybuf[16] = 
{ 35,27,120,59,
  200,68,81,1,
  36,187,0,9,
  79,122,215,31 };
extern "C"
{
	char* encryptBuffer(char* buffer, unsigned int size)
	{
		int i;
		for (i = 0; i < size; i++)
			buffer[i] ^= g_sKeybuf[i&15];
		return (char*) buffer;
	}
};