#include <time.h>

static unsigned long state[16] =
{
	0x8C12D566, 0x00C2793E, 0x5016EECF, 0x234869FA,
	0x6E4C8852, 0x32574386, 0x3573DC34, 0x7E4C00F0,
	0xC830516B, 0x085437E9, 0x32478EAC, 0xDEFCDCD0,
	0xFE09BBC2, 0x34EA087D, 0x112F367C, 0x0324EFAA
};
// modify by jiehua on 2013.9.9 ,ola code is:
// static unsigned long index_i = 0;
// new code is:
static unsigned long index_i = 0;
//modify end

void winitseed(unsigned int seed)
{
	int i;
    
	if (!seed) seed = (unsigned int)time(NULL);
    
	for (i = 0; i < 16; ++i)
	{
		state[i] ^= seed;
	}
}


static unsigned long WELLRNG512()
{
	unsigned long a, b, c, d;
	a = state[index_i];
	c = state[(index_i + 13) & 15];
	b = a ^ c ^ (a << 16) ^ (c << 15);
	c = state[(index_i + 9) & 15];
	c ^= (c >> 11);
	a = state[index_i] = b ^ c;
	d = a ^ ((a << 5) & 0xDA442D20UL);
	index_i = (index_i + 15) & 15;
	a = state[index_i];
	state[index_i] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);
	return state[index_i];
}

unsigned long wrand(unsigned long max)
{
	return WELLRNG512() % max;
}

//返回一个随机数
unsigned long wrandvalue()
{
	return WELLRNG512();
}
