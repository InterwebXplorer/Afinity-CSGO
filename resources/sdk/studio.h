#pragma once
#include "datatypes/matrix.h"

using RadianEuler = float[3];
using Quaternion = float[4];

#pragma region studio_definitions
#define MAXSTUDIOBONECTRLS 4
#define MAXSTUDIOPOSEPARAM 24
#define MAXSTUDIOSKINS 32
#define MAXSTUDIOFLEXCTRL 96
#define MAXSTUDIOBONES 128
#define MAXSTUDIOANIMBLOCKS 256
#define MAXSTUDIOFLEXDESC 1024

#define BONE_CALCULATE_MASK 0x1F
#define BONE_PHYSICALLY_SIMULATED 0x01
#define BONE_PHYSICS_PROCEDURAL 0x02
#define BONE_ALWAYS_PROCEDURAL 0x04
#define BONE_SCREEN_ALIGN_SPHERE 0x08
#define BONE_SCREEN_ALIGN_CYLINDER 0x10

#define BONE_USED_MASK 0x0007FF00
#define BONE_USED_BY_ANYTHING 0x0007FF00
#define BONE_USED_BY_HITBOX 0x00000100
#define BONE_USED_BY_ATTACHMENT 0x00000200
#define BONE_USED_BY_VERTEX_MASK 0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0 0x00000400
#define BONE_USED_BY_VERTEX_LOD1 0x00000800
#define BONE_USED_BY_VERTEX_LOD2 0x00001000
#define BONE_USED_BY_VERTEX_LOD3 0x00002000
#define BONE_USED_BY_VERTEX_LOD4 0x00004000
#define BONE_USED_BY_VERTEX_LOD5 0x00008000
#define BONE_USED_BY_VERTEX_LOD6 0x00010000
#define BONE_USED_BY_VERTEX_LOD7 0x00020000
#define BONE_USED_BY_BONE_MERGE 0x00040000
#define BONE_ALWAYS_SETUP 0x00080000

#define BONE_USED_BY_VERTEX_AT_LOD(iLOD) (BONE_USED_BY_VERTEX_LOD0 << (iLOD))
#define BONE_USED_BY_ANYTHING_AT_LOD(iLOD) ((BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK) | BONE_USED_BY_VERTEX_AT_LOD(iLOD))

#define MAX_NUM_LODS 8

#define BONE_TYPE_MASK 0x00F00000
#define BONE_FIXED_ALIGNMENT 0x00100000
#define BONE_HAS_SAVEFRAME_POS 0x00200000
#define BONE_HAS_SAVEFRAME_ROT64 0x00400000
#define BONE_HAS_SAVEFRAME_ROT32 0x00800000
#pragma endregion

struct vcollide_t;
struct virtualmodel_t;
struct vertexfileheader_t;

struct studiohdr_t;
class CStudioHdr {
public:
	studiohdr_t *pStudioHdr;
	virtualmodel_t *pVirtualModel;
	void *pSoftbody;
	mutable CUtlVector<const studiohdr_t *> pStudioHdrCache;
	mutable int mnFrameUnlockCounter;
	int *pFrameUnlockCounter;
	std::byte pad0[0x8];
	CUtlVector<int> vecBoneFlags;
	CUtlVector<int> vecBoneParent;
	void *pActivityToSequence;
};

struct mstudiobone_t {
	int nNameIndex;
	int iParent;
	int iBoneController[6];

	Vector vecPosition;
	Quaternion qWorld;
	RadianEuler radRotation;

	Vector vecPositionScale;
	Vector vecEulerScale;

	matrix3x4_t matPoseToBone;
	Quaternion qAlignment;
	int iFlags;
	int iProcedureType;
	int nProcedureIndex;
	mutable int miPhysicsBone;
	int nSurfacePropIndex;
	int iContents;
	int iSurfaceProp;
	std::byte pad0[0x1C];

	inline const char *GetName() {
		if (!nNameIndex)
			return nullptr;
		return (char *)this + nNameIndex;
	}

	inline void *GetProcedure() const {
		if (!nProcedureIndex)
			return nullptr;
		return (std::uint8_t *)this + nProcedureIndex;
	}

	inline const char *GetSurfacePropName() const {
		if (!nSurfacePropIndex)
			return nullptr;
		return (char *)this + nSurfacePropIndex;
	}
};

struct mstudiobonecontroller_t {
	int iBone;
	int nType;
	float flStart;
	float flEnd;
	int iRest;
	int iInputField;
	std::byte pad0[0x40];
};

struct mstudiobbox_t {
	int iBone;
	int iGroup;
	Vector vecBBMin;
	Vector vecBBMax;
	int nHitboxNameIndex;
	QAngle angOffsetOrientation;
	float flRadius;
	std::byte pad0[0x10];

	inline const char *GetHitboxName() const {
		if (!nHitboxNameIndex)
			return nullptr;
		return (const char *)this + nHitboxNameIndex;
	}
};

struct mstudiohitboxset_t {
	int nNameIndex;
	int nHitboxes;
	int nHitboxIndex;

	inline const char *GetName() const {
		if (!nNameIndex)
			return nullptr;
		return (char *)this + nNameIndex;
	}

	inline mstudiobbox_t *GetHitbox(int iHitBox) const {
		if (iHitBox < 0 || iHitBox >= nHitboxes)
			return nullptr;
		return (mstudiobbox_t *)((std::uint8_t *)this + nHitboxIndex) + iHitBox;
	}
};

class virtualgroup_t {
public:
	void *pCache;
	CUtlVector<int> vecBoneMap;
	CUtlVector<int> vecMasterBone;
	CUtlVector<int> vecMasterSequence;
	CUtlVector<int> vecMasterAnim;
	CUtlVector<int> vecMasterAttachment;
	CUtlVector<int> vecMasterPose;
	CUtlVector<int> vecMasterNode;
};

struct virtualsequence_t {
	int nFlags;
	int iActivity;
	int iGroup;
	int nIndex;
};

struct virtualgeneric_t {
	int iGroup;
	int nIndex;
};

struct virtualmodel_t {
	inline virtualgroup_t *GetAnimGroup(const int iAnimation)
	{

		return &vecGroup[vecAnim[iAnimation].iGroup];
	}

	inline virtualgroup_t *GetSequenceGroup(const int iSequence)
	{

		return &vecGroup[vecSequence[iSequence].iGroup];
	}

	std::byte pad0[0x8];
	CUtlVector<virtualsequence_t> vecSequence;
	CUtlVector<virtualgeneric_t> vecAnim;
	CUtlVector<virtualgeneric_t> vecAttachment;
	CUtlVector<virtualgeneric_t> vecPose;
	CUtlVector<virtualgroup_t> vecGroup;
	CUtlVector<virtualgeneric_t> vecNode;
	CUtlVector<virtualgeneric_t> vecIKLock;
	CUtlVector<unsigned short> vecAutoplaySequences;
};

struct studiohdr_t;
struct mstudioseqdesc_t {
	int nBaseStudio;
	inline studiohdr_t *GetStudioHdr() const {
		return (studiohdr_t *)((std::uint8_t *)this + nBaseStudio);
	}

	int nLabelIndex;
	inline const char *GetLabel() const {
		return (char *)this + nLabelIndex;
	}

	int nActivityNameIndex;
	inline const char *GetActivityName() const {
		return (char *)this + nActivityNameIndex;
	}

	int iFlags;

	int iActivity;
	int iActivityWeight;

	int nEvents;
	int nEventIndex;
	inline void *GetEvent(int iEvent) const {
		if (iEvent < 0 || iEvent >= nEvents)
			return nullptr;
		return ((std::uint8_t *)this + nEventIndex) + iEvent;
	}

	Vector vecBBMin;
	Vector vecBBMax;

	int nBlends;
	int nBlendIndex;

	inline int GetAnimValue(int x, int y) const {
		if (x >= iGroupSize[0])
			x = iGroupSize[0] - 1;

		if (y >= iGroupSize[1])
			y = iGroupSize[1] - 1;

		int iOffset = y * iGroupSize[0] + x;
		short *arrBlends = (short *)((std::uint8_t *)this + nBlendIndex);
		return (int)arrBlends[iOffset];
	}

	int nMovementIndex;
	int iGroupSize[2];
	int nParamIndex[2];
	float flParamStart[2];
	float flParamEnd[2];
	int iParamParent;

	float flFadeInTime;
	float flFadeOutTime;

	int iEntryNode;
	int iExitNode;
	int iNodeFlags;

	float flEntryPhase;
	float flExitPhase;

	float flLastFrame;

	int iNextSequence;
	int iPose;

	int nIKRules;

	int nAutoLayers;
	int nAutoLayerIndex;
	inline void *GetAutoLayer(int iAutoLayer) const {
		if (iAutoLayer < 0 || iAutoLayer >= nAutoLayers)
			return nullptr;
		return ((std::uint8_t *)this + nAutoLayerIndex) + iAutoLayer;
	}

	int nWeightListIndex;
	inline float *GetBoneWeight(int iBone) const {
		return ((float *)((std::uint8_t *)this + nWeightListIndex) + iBone);
	}

	int nPoseKeyIndex;
	inline float *GetPoseKey(int iParameter, int iAnimation) const {
		return (float *)((std::uint8_t *)this + nPoseKeyIndex) + iParameter * iGroupSize[0] + iAnimation;
	}

	int nIKLocks;
	int nIKLockIndex;
	inline void *GetIKLock(int iIK) const {
		if (iIK < 0 || iIK >= nIKLocks)
			return nullptr;
		return ((std::uint8_t *)this + nIKLockIndex) + iIK;
	}

	int nKeyValueIndex;
	int iKeyValueSize;
	inline const char *KeyValueText() const {
		if (!iKeyValueSize)
			return nullptr;
		return (char *)this + nKeyValueIndex;
	}

	int nCyclePoseIndex;

	int nActivityModifierIndex;
	int nActivityModifiers;

	int nAnimTagIndex;
	int nAnimTags;

	int nRootDriverIndex;
	std::byte pad[0x8];
};

struct mstudioposeparamdesc_t {
	int nNameIndex;
	int nFlags;
	float flStart;
	float flEnd;
	float flLoop;

	inline const char *GetName() const {
		return (char *)this + nNameIndex;
	}
};

struct studiohwdata_t;
struct studiohdr_t {
	int nID;
	int iVersion;
	int iChecksum;
	char szName[64];
	int iLength;

	Vector vecEyePosition;
	Vector vecIllumPosition;
	Vector vecHullMin;
	Vector vecHullMax;
	Vector vecViewBBMin;
	Vector vecViewBBMax;

	int iFlags;

	int nBones;
	int nBoneIndex;
	inline mstudiobone_t *GetBone(int iBone) const {
		if (iBone < 0 || iBone >= nBones)
			return nullptr;
		return (mstudiobone_t *)((std::uint8_t *)this + nBoneIndex) + iBone;
	}

	int nBoneControllers;
	int nBoneControllerIndex;
	inline void *GetBoneController(int iBoneController) const {
		if (iBoneController < 0 || iBoneController >= nBoneControllers)
			return nullptr;
		return ((std::uint8_t *)this + nBoneControllerIndex) + iBoneController;
	}

	int nHitboxSets;
	int nHitboxSetIndex;
	inline mstudiohitboxset_t *GetHitboxSet(int iSet) const {
		if (iSet < 0 || iSet >= nHitboxSets)
			return nullptr;
		return (mstudiohitboxset_t *)((std::uint8_t *)this + nHitboxSetIndex) + iSet;
	}

	inline mstudiobbox_t *GetHitbox(int iHitBox, int iSet) const {
		const mstudiohitboxset_t *pHitboxSet = GetHitboxSet(iSet);

		if (pHitboxSet == nullptr)
			return nullptr;

		return pHitboxSet->GetHitbox(iHitBox);
	}

	inline int GetHitboxCount(int iSet) const {
		const mstudiohitboxset_t *pHitboxSet = GetHitboxSet(iSet);

		if (pHitboxSet == nullptr)
			return 0;

		return pHitboxSet->nHitboxes;
	}

	int nLocalAnimations;
	int nLocalAnimationIndex;
	inline void *GetAnimDescription(int iAnimation) const {
		if (iAnimation < 0 || iAnimation >= nLocalAnimations)
			iAnimation = 0;
		return ((std::uint8_t *)this + nLocalAnimationIndex) + iAnimation;
	}

	int nLocalSequences;
	int nLocalSequenceIndex;
	inline mstudioseqdesc_t *GetLocalSequenceDescription(int iSequence) const {
		if (iSequence < 0 || iSequence >= nLocalSequences)
			iSequence = 0;
		return (mstudioseqdesc_t *)((std::uint8_t *)this + nLocalSequenceIndex) + iSequence;
	}

	inline mstudioseqdesc_t &GetSequenceDescription(int iSequence, virtualmodel_t *pVirtualModel = nullptr, const studiohdr_t *pStudioHdr = nullptr) const {
		if (nIncludeModels == 0 || pVirtualModel == nullptr || pStudioHdr == nullptr)
			return *GetLocalSequenceDescription(iSequence);

		return *pStudioHdr->GetLocalSequenceDescription(pVirtualModel->vecSequence[iSequence].nIndex);
	}

	mutable int miActivityListVersion;
	mutable int miEventsIndexed;

	int nTextures;
	int nTextureIndex;
	inline void *GetTexture(int nIndex) const {
		if (nIndex < 0 || nIndex >= nTextures)
			return nullptr;
		return ((std::uint8_t *)this + nTextureIndex) + nIndex;
	}

	int nCdTextures;
	int nCdTextureIndex;
	inline char *GetCdTexture(int nIndex) const {
		if (nIndex < 0 || nIndex >= nCdTextures)
			return nullptr;
		return (((char *)this) + *((int *)((std::uint8_t *)this + nCdTextureIndex) + nIndex));
	}

	int nSkinRefs;
	int nSkinFamilies;
	int nSkinIndex;
	inline short *GetSkinRef(int nIndex) const {
		if (nIndex < 0 || nIndex >= nSkinRefs)
			return nullptr;
		return (short *)((std::uint8_t *)this + nSkinIndex) + nIndex;
	}

	int nBodyParts;
	int nBodyPartIndex;
	inline void *GetBodyPart(int nIndex) const {
		if (nIndex < 0 || nIndex >= nBodyParts)
			return nullptr;
		return ((std::uint8_t *)this + nBodyPartIndex) + nIndex;
	}

	int nAttachments;
	int nAttachmentIndex;
	inline void *GetAttachment(int nIndex) const {
		if (nIndex < 0 || nIndex >= nAttachments)
			return nullptr;
		return ((std::uint8_t *)this + nAttachmentIndex) + nIndex;
	}

	int nTransitions;
	int nTransitionIndex;
	int nTransitionNameIndex;
	inline std::uint8_t *GetTransition(int nIndex) const {
		if (nIndex < 0 || nIndex >= (nTransitions * nTransitions))
			return nullptr;
		return (std::uint8_t *)((std::uint8_t *)this + nTransitionIndex) + nIndex;
	}

	int nFlexDescs;
	int nFlexDescIndex;
	inline void *GetFlexDescription(int nIndex) const {
		if (nIndex < 0 || nIndex >= nFlexDescs)
			return nullptr;
		return ((std::uint8_t *)this + nFlexDescIndex) + nIndex;
	}

	int nFlexControllers;
	int nFlexControllerIndex;
	inline void *GetFlexController(int nIndex) const {
		if (nIndex < 0 || nIndex >= nFlexControllers)
			return nullptr;
		return ((std::uint8_t *)this + nFlexControllerIndex) + nIndex;
	}

	int nFlexRules;
	int nFlexRuleIndex;
	inline void *GetFlexRule(int nIndex) const {
		if (nIndex < 0 || nIndex >= nFlexRules)
			return nullptr;
		return ((std::uint8_t *)this + nFlexRuleIndex) + nIndex;
	}

	int nIkChains;
	int nIkChainIndex;
	inline void *GetIKChain(int nIndex) const {
		if (nIndex < 0 || nIndex >= nIkChains)
			return nullptr;
		return ((std::uint8_t *)this + nIkChainIndex) + nIndex;
	}

	int nMouths;
	int nMouthIndex;
	inline void *GetMouth(int nIndex) const {
		if (nIndex < 0 || nIndex >= nMouths)
			return nullptr;
		return ((std::uint8_t *)this + nMouthIndex) + nIndex;
	}

	int nPoseParameters;
	int nPoseParameterIndex;
	inline void *GetPoseParameter(int nIndex) const {
		if (nIndex < 0 || nIndex >= nPoseParameters)
			return nullptr;
		return ((std::uint8_t *)this + nPoseParameterIndex) + nIndex;
	}

	int nSurfacePropIndex;
	inline const char *GetSurfaceProp() const {
		if (!nSurfacePropIndex)
			return nullptr;
		return (char *)this + nSurfacePropIndex;
	}

	int nKeyValueIndex;
	int nKeyValueSize;
	inline const char *KeyValueText() const {
		if (!nKeyValueSize)
			return nullptr;
		return (char *)this + nKeyValueIndex;
	}

	int nIkAutoplayLocks;
	int nIkAutoplayLockIndex;
	inline void *GetIKAutoplayLock(int nIndex) const {
		if (nIndex < 0 || nIndex >= nIkAutoplayLocks)
			return nullptr;
		return ((std::uint8_t *)this + nIkAutoplayLockIndex) + nIndex;
	}

	float flMass;
	int iContents;

	int nIncludeModels;
	int nIncludeModelIndex;
	inline void *GetModelGroup(int nIndex) const {
		if (nIndex < 0 || nIndex >= nIncludeModels)
			return nullptr;
		return ((std::uint8_t *)this + nIncludeModelIndex) + nIndex;
	}

	int iVirtualModel;

	int nAnimBlockNameIndex;
	inline const char *GetAnimBlockName() const {
		return ((char *)this) + nAnimBlockNameIndex;
	}

	int nAnimBlocks;
	int nAnimBlockIndex;
	inline void *GetAnimBlock(int nIndex) const {
		if (nIndex < 0 || nIndex >= nAnimBlocks)
			return nullptr;
		return (((std::uint8_t *)this) + nAnimBlockIndex) + nIndex;
	}

	int iAnimBlockModel;

	int nBoneTableByNameIndex;
	inline const std::uint8_t *GetBoneTableSortedByName() const {
		return (std::uint8_t *)this + nBoneTableByNameIndex;
	}

	int iVertexBase;
	int nIndexBase;

	std::uint8_t uDirectionalLightDot;
	std::uint8_t uRootLOD;
	std::uint8_t nAllowedRootLODs;
	std::byte pad0[0x5];

	int nFlexControllerUI;
	int nFlexcontrollerUIIndex;

	float flVertAnimFixedPointScale;
	mutable int miSurfacePropLookup;
	int nStudioHdr2Index;

	std::byte pad1[0x4];
};
