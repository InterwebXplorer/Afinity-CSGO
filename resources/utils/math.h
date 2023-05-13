#pragma once
#include <directxmath.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "../sdk/datatypes/vector.h"
#include "../sdk/datatypes/qangle.h"
#include "../sdk/datatypes/matrix.h"

#pragma region math_definitions
#define M_HPI			DirectX::XM_PIDIV2	
#define M_QPI			DirectX::XM_PIDIV4	
#define M_PI			DirectX::XM_PI		
#define M_2PI			DirectX::XM_2PI		
#define M_GPI			1.6180339887498f	
#define M_RADPI			57.295779513082f	

#define M_METRE2INCH( x )	( ( x ) / 0.0254f )
#define M_INCH2METRE( x )	( ( x ) * 0.0254f )
#define M_METRE2FOOT( x )	( ( x ) * 3.28f )
#define M_FOOT2METRE( x )	( ( x ) / 3.28f )
#define M_RAD2DEG( x )		DirectX::XMConvertToDegrees( x )
#define M_DEG2RAD( x )		DirectX::XMConvertToRadians( x )
#pragma endregion

extern "C" using RandomSeedFn = int(__cdecl*)(int Seed);
extern "C" using RandomFloatFn = float(__cdecl*)(float MinVal, float MaxVal);
extern "C" using RandomFloatExpFn = float(__cdecl*)(float MinVal, float MaxVal, float Exponent);
extern "C" using RandomIntFn = int(__cdecl*)(int MinVal, int MaxVal);
extern "C" using RandomGaussianFloatFn = float(__cdecl*)(float Mean, float StdDev);


namespace Math {
	bool	Setup();

	void	VectorAngles(const Vector& Forward, QAngle& View);

	void	AngleVectors(const QAngle& View, Vector* Forward, Vector* Right = nullptr, Vector* Up = nullptr);

	void	AngleMatrix(const QAngle& View, matrix3x4_t& Output, const Vector& Origin = Vector(0.0f, 0.0f, 0.0f));
	
	Vector2D AnglePixels(const float Sensitivity, const float Pitch, const float Yaw, const QAngle& Begin, const QAngle& End);

	QAngle	PixelsAngle(const float Sensitivity, const float Pitch, const float Yaw, const Vector2D& Pixels);

	QAngle	CalcAngle(const Vector& Start, const Vector& End);

	Vector	VectorTransform(const Vector& Transform, const matrix3x4_t& matrix);

	Vector	ExtrapolateTick(const Vector& a0, const Vector& b0);

	void	RotatePoint(const ImVec2& In, const float Angle, ImVec2* OutPoint);

	void	RotateCenter(const ImVec2& Center, const float Angle, ImVec2* OutPoint);

	
	inline RandomSeedFn				RandomSeed;
	inline RandomFloatFn			RandomFloat;
	inline RandomFloatExpFn			RandomFloatExp;
	inline RandomIntFn				RandomInt;
	inline RandomGaussianFloatFn	RandomGaussianFloat;

	/*--------------------Extra Math Shit--------------------*/
	
	template <typename T, typename... Ts>
	T RandomIntSet(T First, Ts... Rest);
	void RandomIntRange(int Min, int Max);
	void IntAddSubtractRange(int AddStart, int AddEnd, int SubtractStart, int SubtractEnd, int Amount);
	void IntAddRange(int AddStart, int AddEnd, int Amount);
	void IntSubtractRange(int SubtractStart, int SubtractEnd, int Amount);
	float Calculate3DDistance(const Vector& Point1, const Vector& Point2);
}