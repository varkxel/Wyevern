#include "Vector.hpp"

using namespace Wyevern::Mathematics;

void dummy()
{
	float2 testVec(std::array{ 1.0f, 0.0f });
	float2 reverse = testVec.yx;

	float4 test = reverse.xyxy;
}
