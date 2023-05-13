#include "math.h"
#include "../sdk/interfaces.h"
#include "filelogging.h"
#include <random>

bool Math::Setup() {
	const void* VstdLib = Memory::GetModuleBaseHandle(VSTDLIB_DLL);

	if (VstdLib == nullptr)
		return false;

	RandomSeed = reinterpret_cast<RandomSeedFn>(Memory::GetExportAddress(VstdLib, "RandomSeed"));
	if (RandomSeed == nullptr)
		return false;

	RandomFloat = reinterpret_cast<RandomFloatFn>(Memory::GetExportAddress(VstdLib, "RandomFloat"));
	if (RandomFloat == nullptr)
		return false;

	RandomFloatExp = reinterpret_cast<RandomFloatExpFn>(Memory::GetExportAddress(VstdLib, "RandomFloatExp"));
	if (RandomFloatExp == nullptr)
		return false;

	RandomInt = reinterpret_cast<RandomIntFn>(Memory::GetExportAddress(VstdLib, "RandomInt"));
	if (RandomInt == nullptr)
		return false;

	RandomGaussianFloat = reinterpret_cast<RandomGaussianFloatFn>(Memory::GetExportAddress(VstdLib, "RandomGaussianFloat"));
	if (RandomGaussianFloat == nullptr)
		return false;

	return true;
}

void Math::VectorAngles(const Vector& Forward, QAngle& View) {
	float Pitch, Yaw;

	if (Forward.x == 0.f && Forward.y == 0.f) {
		Pitch = (Forward.z > 0.f) ? 270.f : 90.f;
		Yaw = 0.f;
	}
	else {
		Pitch = std::atan2f(-Forward.z, Forward.Length2D()) * 180.f / M_PI;

		if (Pitch < 0.f)
			Pitch += 360.f;

		Yaw = std::atan2f(Forward.y, Forward.x) * 180.f / M_PI;

		if (Yaw < 0.f)
			Yaw += 360.f;
	}

	View.x = Pitch;
	View.y = Yaw;
	View.z = 0.f;
}

void Math::AngleVectors(const QAngle& View, Vector* Forward, Vector* Right, Vector* Up) {
	float sp, sy, sr, cp, cy, cr;

	DirectX::XMScalarSinCos(&sp, &cp, M_DEG2RAD(View.x));
	DirectX::XMScalarSinCos(&sy, &cy, M_DEG2RAD(View.y));
	DirectX::XMScalarSinCos(&sr, &cr, M_DEG2RAD(View.z));

	if (Forward != nullptr) {
		Forward->x = cp * cy;
		Forward->y = cp * sy;
		Forward->z = -sp;
	}

	if (Right != nullptr) {
		Right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		Right->y = -1 * sr * sp * sy + -1 * cr * cy;
		Right->z = -1 * sr * cp;
	}

	if (Up != nullptr) {
		Up->x = cr * sp * cy + -sr * -sy;
		Up->y = cr * sp * sy + -sr * cy;
		Up->z = cr * cp;
	}
}

void Math::AngleMatrix(const QAngle& View, matrix3x4_t& Output, const Vector& Origin) {
	float sp, sy, sr, cp, cy, cr;

	DirectX::XMScalarSinCos(&sp, &cp, M_DEG2RAD(View.x));
	DirectX::XMScalarSinCos(&sy, &cy, M_DEG2RAD(View.y));
	DirectX::XMScalarSinCos(&sr, &cr, M_DEG2RAD(View.z));

	matOutput.SetForward(Vector(cp * cy, cp * sy, -sp));

	const float crcy = cr * cy;
	const float crsy = cr * sy;
	const float srcy = sr * cy;
	const float srsy = sr * sy;

	matOutput.SetLeft(Vector(sp * srcy - crsy, sp * srsy + crcy, sr * cp));
	matOutput.SetUp(Vector(sp * crcy + srsy, sp * crsy - srcy, cr * cp));
	matOutput.SetOrigin(Origin);
}

Vector2D Math::AnglePixels(const float Sensitivity, const float Pitch, const float Yaw, const QAngle& Begin, const QAngle& End) {
	QAngle Delta = Begin - End;
	Delta.Normalize();

	const float PixelMovePitch = (-Delta.x) / (Yaw * Sensitivity);
	const float PixelMoveYaw = (Delta.y) / (Pitch * Sensitivity);

	return Vector2D(PixelMoveYaw, PixelMovePitch);
}

QAngle Math::PixelsAngle(const float Sensitivity, const float Pitch, const float Yaw, const Vector2D& Pixels) {
	const float AngleMovePitch = (-Pixels.x) * (Yaw * Sensitivity);
	const float AngleMoveYaw = (Pixels.y) * (Pitch * Sensitivity);

	return QAngle(AngleMoveYaw, AngleMovePitch, 0.f);
}

QAngle Math::CalcAngle(const Vector& Start, const Vector& End) {
	QAngle View;
	const Vector Delta = End - Start;
	VectorAngles(Delta, View);
	angView.Normalize();

	return View;
}

Vector Math::VectorTransform(const Vector& Transform, const matrix3x4_t& Matrix) {
	return Vector(Transform.DotProduct(Matrix[0]) + Matrix[0][3], Transform.DotProduct(Matrix[1]) + Matrix[1][3], Transform.DotProduct(Matrix[2]) + Matrix[2][3]);
}

Vector Math::ExtrapolateTick(const Vector& a0, const Vector& b0) {
	return a0 + (b0 * I::Globals->flIntervalPerTick);
}

void Math::RotatePoint(const ImVec2& In, const float Angle, ImVec2* OutPoint) {
	if (&In == OutPoint) {
		const ImVec2 Point = In;
		RotatePoint(Point, Angle, OutPoint);
		return;
	}

	const float Sin = std::sinf(M_DEG2RAD(Angle));
	const float Cos = std::cosf(M_DEG2RAD(Angle));

	OutPoint->x = In.x * Cos - In.y * Sin;
	OutPoint->y = In.x * Sin + In.y * Cos;
}

void Math::RotateCenter(const ImVec2& Center, const float Angle, ImVec2* OutPoint) {
	const float Sin = std::sinf(M_DEG2RAD(Angle));
	const float Cos = std::cosf(M_DEG2RAD(Angle));

	OutPoint->x -= Center.x;
	OutPoint->y -= Center.y;

	const float x = OutPoint->x * Cos - OutPoint->y * Sin;
	const float y = OutPoint->x * Sin + OutPoint->y * Cos;

	OutPoint->x = x + Center.x;
	OutPoint->y = y + Center.y;
}

/*--------------------Extra Math Shit--------------------*/

template <typename T, typename... Ts>
T Math::RandomIntSet(T First, Ts... Rest) {
    std::vector<int> Numbers = {First, Rest...};
    std::random_device RandomDevice;
    std::mt19937 Gen(RandomDevice());
    std::uniform_int_distribution<int> Dis(0, Numbers.size() - 1);

    return Numbers[Dis(Gen)];
}

int Math::RandomIntRange(int Min, int Max) {
	return rand() % (Max - Min + 1) + Min;
}

int Math::IntAddSubtractRange(int AddStart, int AddEnd, int SubtractStart, int SubtractEnd, int Amount) {
	if (AddStart >= AddEnd || SubtractStart <= SubtractEnd || Amount <= 0) {
		WriteToLog("[Error] Unable to use set values");
		return 0;
	}

	int Result = AddStart;

	for (int i = AddStart; i <= AddEnd; i += Amount) {
		Result += i;
	}

	for (int i = SubtractStart; i >= SubtractEnd; i -= Amount) {
		Result -= i;
	}

	return Result;
}

int Math::IntAddRange(int AddStart, int AddEnd, int Amount) {
	if (AddStart >= AddEnd || Amount <= 0) {
		WriteToLog("[Error] Unable to use set values");
		return 0;
	}

	int Result = AddStart;

	for (int i = AddStart; i <= AddEnd; i += Amount) {
		Result += i;
	}

	return Result;
}

int Math::IntSubtractRange(int SubtractStart, int SubtractEnd, int Amount) {
	if (SubtractStart <= SubtractEnd || Amount <= 0) {
		WriteToLog("[Error] Unable to use set values");
		return 0;
	}

	int Result = SubtractStart;

	for (int i = SubtractStart; i >= SubtractEnd; i -= Amount) {
		Result -= i;
	}
	
	return Result;
}

float Math::Calculate3DDistance(const Vector& Point1, const Vector& Point2) {
	float DX = Point1.x - Point2.x;
	float DY = Point1.y - Point2.y;
	float DZ = Point1.z - Point2.z;

	return std::sqrt(DX * DX + DY * DY + DZ * DZ);
}