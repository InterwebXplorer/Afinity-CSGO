#pragma once
#include <vector>
#include <windows.h>
#include "../imgui/freetype/imgui_freetype.h"

#pragma region memory_modules_definitions
#define ENGINE_DLL				XorStr("engine.dll")
#define CLIENT_DLL				XorStr("client.dll")
#define LOCALIZE_DLL			XorStr("localize.dll")
#define MATERIALSYSTEM_DLL		XorStr("materialsystem.dll")
#define VGUI_DLL				XorStr("vguimatsurface.dll")
#define VGUI2_DLL				XorStr("vgui2.dll")
#define SHADERPIDX9_DLL			XorStr("shaderapidx9.dll")
#define GAMEOVERLAYRENDERER_DLL XorStr("gameoverlayrenderer.dll")
#define PHYSICS_DLL				XorStr("vphysics.dll")
#define VSTDLIB_DLL				XorStr("vstdlib.dll")
#define TIER0_DLL				XorStr("tier0.dll")
#define INPUTSYSTEM_DLL			XorStr("inputsystem.dll")
#define STUDIORENDER_DLL		XorStr("studiorender.dll")
#define DATACACHE_DLL			XorStr("datacache.dll")
#define STEAM_API_DLL			XorStr("steam_api.dll")
#define MATCHMAKING_DLL			XorStr("matchmaking.dll")
#define SERVER_DLL				XorStr("server.dll")
#define SERVERBROWSER_DLL		XorStr("serverbrowser.dll")
#pragma endregion


template <typename T>
class CSingleton
{
protected:
	CSingleton() { }
	~CSingleton() { }

	CSingleton(const CSingleton&) = delete;
	CSingleton& operator=(const CSingleton&) = delete;

	CSingleton(CSingleton&&) = delete;
	CSingleton& operator=(CSingleton&&) = delete;
public:
	static T& Get()
	{
		static T pInstance{ };
		return pInstance;
	}
};


class CWrappedProtect
{
public:
	CWrappedProtect(void* pBaseAddress, const std::size_t uLength, const DWORD dwFlags) :
		pBaseAddress(pBaseAddress), uLength(uLength)
	{
		if (!VirtualProtect(pBaseAddress, uLength, dwFlags, &dwOldFlags))
			throw std::system_error(GetLastError(), std::system_category(), XorStr("failed to protect region"));
	}

	~CWrappedProtect()
	{
		VirtualProtect(pBaseAddress, uLength, dwOldFlags, &dwOldFlags);
	}
private:
	void*			pBaseAddress;
	std::size_t		uLength;
	DWORD			dwOldFlags;
};


namespace MEM
{

	
	
	
	std::uintptr_t FindPattern(const std::string_view szModuleName, const std::string_view szPattern);
	
	
	std::uintptr_t FindPattern(const std::uint8_t* uRegionStart, const std::uintptr_t uRegionSize, const std::string_view szPattern);
	
	
	void* GetModuleBaseHandle(const std::string_view szModuleName);
	
	
	void* GetExportAddress(const void* pModuleBase, const std::string_view szProcedureName);
	
	std::vector<std::uintptr_t> GetCrossReferences(const std::uintptr_t uAddress, std::uintptr_t uRegionStart, const std::size_t uRegionSize);
	
	
	
	
	bool GetSectionInfo(const std::uintptr_t uBaseAddress, const std::string_view szSectionName, std::uintptr_t* puSectionStart, std::uintptr_t* puSectionSize);
	
	std::uintptr_t GetVTableTypeDescriptor(const std::string_view szModuleName, const std::string_view szTableName);
	
	std::uintptr_t* GetVTablePointer(const std::string_view szModuleName, const std::string_view szTableName);
	
	
	template <typename T, std::size_t S>
	std::vector<T> GetFilledVector(const T& fill)
	{
		std::vector<T> vecTemp(S);
		std::fill(vecTemp.begin(), vecTemp.begin() + S, fill);
		return vecTemp;
	}
	
	template <typename T = void*>
	constexpr T GetVFunc(void* thisptr, std::size_t nIndex)
	{
		return (*static_cast<T**>(thisptr))[nIndex];
	}
	
	
	template <typename T, typename ... Args_t>
	constexpr T CallVFunc(void* thisptr, std::size_t nIndex, Args_t... argList)
	{
		using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
		return (*static_cast<VirtualFn**>(thisptr))[nIndex](thisptr, argList...);
	}


	std::vector<std::optional<std::uint8_t>> PatternToBytes(const std::string_view szPattern);
	std::string BytesToPattern(const std::uint8_t* arrBytes, const std::size_t uSize);


	
	bool IsValidCodePtr(const void* pPointer);
}
