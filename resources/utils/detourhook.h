#pragma once
#include <format>
#include "../minhook/minhook.h"

class DetourHook
{
public:
	DetourHook() = default;

	explicit DetourHook(void *pFunction, void *pDetour)
		: pBaseFn(pFunction), pReplaceFn(pDetour) {}

	bool Create(void *pFunction, void *pDetour)
	{
		pBaseFn = pFunction;

		if (pBaseFn == nullptr)
			return false;

		pReplaceFn = pDetour;

		if (pReplaceFn == nullptr)
			return false;

		const MH_STATUS status = MH_CreateHook(pBaseFn, pReplaceFn, &pOriginalFn);

		if (status != MH_OK)
			throw std::runtime_error(std::format(XorStr("failed to create hook function, status: {}\nbase function -> {:#08X}"), MH_StatusToString(status), reinterpret_cast<std::uintptr_t>(pBaseFn)));

		if (!this->Replace())
			return false;

		return true;
	}

	bool Replace()
	{
		if (pBaseFn == nullptr)
			return false;

		if (bIsHooked)
			return false;

		const MH_STATUS status = MH_EnableHook(pBaseFn);

		if (status != MH_OK)
			throw std::runtime_error(std::format(XorStr("failed to enable hook function, status: {}\nbase function -> {:#08X} address"), MH_StatusToString(status), reinterpret_cast<std::uintptr_t>(pBaseFn)));

		bIsHooked = true;
		return true;
	}

	bool Remove()
	{
		if (!this->Restore())
			return false;

		const MH_STATUS status = MH_RemoveHook(pBaseFn);

		if (status != MH_OK)
			throw std::runtime_error(std::format(XorStr("failed to remove hook, status: {}\n base function -> {:#08X} address"), MH_StatusToString(status), reinterpret_cast<std::uintptr_t>(pBaseFn)));

		return true;
	}

	bool Restore()
	{
		if (!bIsHooked)
			return false;

		const MH_STATUS status = MH_DisableHook(pBaseFn);

		if (status != MH_OK)
			throw std::runtime_error(std::format(XorStr("failed to restore hook, status: {}\n base function -> {:#08X} address"), MH_StatusToString(status), reinterpret_cast<std::uintptr_t>(pBaseFn)));

		bIsHooked = false;
		return true;
	}

	template <typename Fn>
	Fn GetOriginal()
	{
		return static_cast<Fn>(pOriginalFn);
	}

	inline bool IsHooked() const
	{
		return bIsHooked;
	}

private:
	bool bIsHooked = false;
	void *pBaseFn = nullptr;
	void *pReplaceFn = nullptr;
	void *pOriginalFn = nullptr;
};
