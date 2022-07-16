#pragma once

#pragma region datamap_enumerations
enum EFieldTypes : int
{
	FIELD_VOID = 0,
	FIELD_FLOAT,
	FIELD_STRING,
	FIELD_VECTOR,
	FIELD_QUATERNION,
	FIELD_INTEGER,
	FIELD_BOOLEAN,
	FIELD_SHORT,
	FIELD_CHARACTER,
	FIELD_COLOR32,
	FIELD_EMBEDDED,
	FIELD_CUSTOM,
	FIELD_CLASSPTR,
	FIELD_EHANDLE,
	FIELD_EDICT,
	FIELD_POSITION_VECTOR,
	FIELD_TIME,
	FIELD_TICK,
	FIELD_MODELNAME,
	FIELD_SOUNDNAME,
	FIELD_INPUT,
	FIELD_FUNCTION,
	FIELD_VMATRIX,
	FIELD_VMATRIX_WORLDSPACE,
	FIELD_MATRIX3X4_WORLDSPACE,
	FIELD_INTERVAL,
	FIELD_MODELINDEX,
	FIELD_MATERIALINDEX,
	FIELD_VECTOR2D,
	FIELD_INTEGER64,
	FIELD_VECTOR4D,
	FIELD_TYPECOUNT
};

enum
{
	TD_OFFSET_NORMAL = 0,
	TD_OFFSET_PACKED = 1,
	TD_OFFSET_COUNT
};
#pragma endregion

struct DataMap_t;
struct TypeDescription_t
{
public:
	EFieldTypes iFieldType;
	const char *szFieldName;
	int iFieldOffset[TD_OFFSET_COUNT];
	unsigned short uFieldSize;
	short fFlags;
	std::byte pad0[0xC];
	DataMap_t *pTypeDescription;
	std::byte pad1[0x18];
};

struct DataMap_t
{
	TypeDescription_t *pDataDesc;
	int nDataFields;
	const char *szDataClassName;
	DataMap_t *pBaseMap;
	bool bChainsValidated;
	bool bPackedOffsetsComputed;
	int iPackedSize;
};
