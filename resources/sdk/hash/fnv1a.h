#pragma once
using FNV1A_t = std::uint32_t;

namespace FNV1A
{
	constexpr std::uint32_t ullBasis = 0x811C9DC5;
	constexpr std::uint32_t ullPrime = 0x1000193;

	consteval FNV1A_t HashConst(const char *szString, const FNV1A_t uValue = ullBasis) noexcept
	{
		return (szString[0] == '\0') ? uValue : HashConst(&szString[1], (uValue ^ static_cast<FNV1A_t>(szString[0])) * ullPrime);
	}

	inline FNV1A_t Hash(const char *szString, FNV1A_t uValue = ullBasis)
	{
		for (std::size_t i = 0U; i < strlen(szString); ++i)
		{
			uValue ^= szString[i];
			uValue *= ullPrime;
		}

		return uValue;
	}
}
