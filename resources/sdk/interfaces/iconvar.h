#pragma once
#pragma region convar_enumerations

enum EConVarFlag : int
{

	FCVAR_NONE = 0,
	FCVAR_UNREGISTERED = (1 << 0),
	FCVAR_DEVELOPMENTONLY = (1 << 1),
	FCVAR_GAMEDLL = (1 << 2),
	FCVAR_CLIENTDLL = (1 << 3),
	FCVAR_HIDDEN = (1 << 4),

	FCVAR_PROTECTED = (1 << 5),
	FCVAR_SPONLY = (1 << 6),
	FCVAR_ARCHIVE = (1 << 7),
	FCVAR_NOTIFY = (1 << 8),
	FCVAR_USERINFO = (1 << 9),
	FCVAR_CHEAT = (1 << 14),
	FCVAR_PRINTABLEONLY = (1 << 10),
	FCVAR_UNLOGGED = (1 << 11),
	FCVAR_NEVER_AS_STRING = (1 << 12),

	FCVAR_SERVER = (1 << 13),
	FCVAR_DEMO = (1 << 16),
	FCVAR_DONTRECORD = (1 << 17),
	FCVAR_RELOAD_MATERIALS = (1 << 20),
	FCVAR_RELOAD_TEXTURES = (1 << 21),
	FCVAR_NOT_CONNECTED = (1 << 22),
	FCVAR_MATERIAL_SYSTEM_THREAD = (1 << 23),
	FCVAR_ARCHIVE_XBOX = (1 << 24),
	FCVAR_ACCESSIBLE_FROM_THREADS = (1 << 25),
	FCVAR_SERVER_CAN_EXECUTE = (1 << 28),
	FCVAR_SERVER_CANNOT_QUERY = (1 << 29),
	FCVAR_CLIENTCMD_CAN_EXECUTE = (1 << 30),
	FCVAR_MATERIAL_THREAD_MASK = (FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD)
};
#pragma endregion

using CVarDLLIdentifier_t = int;
class CConBase;
class CConVar;
class CConCmd;
class IConVar : public IAppSystem
{
public:
	virtual CVarDLLIdentifier_t AllocateDLLIdentifier() = 0;
	virtual void RegisterConCommand(CConVar *pCommandBase, int iDefaultValue = 1) = 0;
	virtual void UnregisterConCommand(CConVar *pCommandBase) = 0;
	virtual void UnregisterConCommands(CVarDLLIdentifier_t id) = 0;
	virtual const char *GetCommandLineValue(const char *szVariableName) = 0;
	virtual CConBase *FindCommandBase(const char *szName) = 0;
	virtual const CConBase *FindCommandBase(const char *szName) const = 0;
	virtual CConVar *FindVar(const char *szVariableName) = 0;
	virtual const CConVar *FindVar(const char *szVariableName) const = 0;
	virtual CConCmd *FindCommand(const char *szName) = 0;
	virtual const CConCmd *FindCommand(const char *szName) const = 0;
	virtual void InstallGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void RemoveGlobalChangeCallback(FnChangeCallback_t callback) = 0;
	virtual void CallGlobalChangeCallbacks(CConVar *pVar, const char *szOldString, float flOldValue) = 0;
	virtual void InstallConsoleDisplayFunc(void *pDisplayFunc) = 0;
	virtual void RemoveConsoleDisplayFunc(void *pDisplayFunc) = 0;
	virtual void ConsoleColorPrintf(const Color &color, const char *pFormat, ...) const = 0;
	virtual void ConsolePrintf(const char *pFormat, ...) const = 0;
	virtual void ConsoleDPrintf(const char *pFormat, ...) const = 0;
	virtual void RevertFlaggedConVars(int nFlag) = 0;
};
