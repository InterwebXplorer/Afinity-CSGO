#pragma once
#include <format>
#include "../minhook/minhook.h"
#include "filelogging.h"

class DetourHook {
	public:
		DetourHook() = default;

		explicit DetourHook(void* Function, void* Detour) : BaseFn(Function), ReplaceFn(Detour) {}

		bool Create(void* Function, void* Detour) {
			BaseFn = Function;

			if (!BaseFn)
				return false;

			ReplaceFn = Detour;

			if (!ReplaceFn)
				return false;

			const MH_STATUS Status = MH_CreateHook(BaseFn, ReplaceFn, &OriginalFn);

			if (Status != MH_OK) {
				WriteToLog(std::format("[Error] Failed to create hook function <Status -> {}, Base function -> {:#08X}>", MH_StatusToString(Status), reinterpret_cast<std::uintptr_t>(BaseFn)));
				return false;
			}

			if (!this->Replace())
				return false;

			return true;
		}

		bool Replace() {
			if (!BaseFn)
				return false;

			if (IsHooked)
				return false;

			const MH_STATUS Status = MH_EnableHook(BaseFn);

			if (Status != MH_OK) {
				WriteToLog(std::format("[Error] Failed to enable hook function <Status -> {}, Base function -> {:#08X}>", MH_StatusToString(Status), reinterpret_cast<std::uintptr_t>(BaseFn)));
				return false;
			}

			IsHooked = true;
			return true;
		}

		bool Remove() {
			if (!this->Restore())
				return false;

			const MH_STATUS Status = MH_RemoveHook(BaseFn);

			if (Status != MH_OK) {
				WriteToLog(std::format("[Error] Failed to remove hook function <Status -> {}, Base function -> {:#08X}>", MH_StatusToString(Status), reinterpret_cast<std::uintptr_t>(BaseFn)));
				return false;
			}

			return true;
		}

		bool Restore() {
			if (!IsHooked)
				return false;

			const MH_STATUS Status = MH_DisableHook(BaseFn);

			if (Status != MH_OK) {
				WriteToLog(std::format("[Error] Failed to restore hook function <Status -> {}, Base function -> {:#08X}>", MH_StatusToString(Status), reinterpret_cast<std::uintptr_t>(BaseFn)));
				return false;
			}

			IsHooked = false;
			return true;
		}

		template <typename Function>
		Function GetOriginal() {
			return static_cast<Function>(OriginalFn);
		}

		inline bool IsHooked() const {
			return IsHooked;
		}

	private:
		bool IsHooked = false;	
		void* BaseFn = nullptr;
		void* ReplaceFn = nullptr;
		void* OriginalFn = nullptr;
};
