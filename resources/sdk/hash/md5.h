#pragma once
#include <cstring>
#include <assert.h>

#define MD5_DIGEST_LENGTH 16
#define MD5_BIT_LENGTH (MD5_DIGEST_LENGTH * sizeof(unsigned char))

typedef struct
{
	unsigned int buf[4];
	unsigned int bits[2];
	unsigned char in[64];
} MD5Context_t;

struct MD5Value_t;

namespace MD5
{

	void Init(MD5Context_t *context);

	void Update(MD5Context_t *context, unsigned char const *buf, unsigned int len);

	void Final(unsigned char digest[MD5_DIGEST_LENGTH], MD5Context_t *context);

	unsigned int PseudoRandom(unsigned int nSeed);

	void ProcessSingleBuffer(const void *p, int len, MD5Value_t &md5Result);

	bool Compare(const MD5Value_t &data, const MD5Value_t &compare);
}

struct MD5Value_t
{
	void Zero()
	{
		memset(bits, 0, sizeof(bits));
	};

	bool IsZero() const
	{
		for (int i = 0; i < (sizeof(bits) / sizeof(bits[0])); ++i)
		{
			if (bits[i] != 0)
				return false;
		}

		return true;
	};

	inline bool operator==(const MD5Value_t &src) const
	{
		return MD5::Compare(*this, src);
	};

	inline bool operator!=(const MD5Value_t &src) const
	{
		return !MD5::Compare(*this, src);
	};

	unsigned char bits[MD5_DIGEST_LENGTH];
};
