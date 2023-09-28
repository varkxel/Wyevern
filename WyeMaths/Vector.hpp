#ifndef WYEMATHS_VECTOR_INCLUDED
#define WYEMATHS_VECTOR_INCLUDED

#include <array>
#include <functional>
#include <type_traits>

#include "BasicTypes.hpp"

//#include "Generated/Vector2.gen.hpp"
//#include "Generated/Vector3.gen.hpp"
//#include "Generated/Vector4.gen.hpp"

namespace Wyevern::Mathematics
{
	template<
		typename type, uint vectorDimensions,
		uint swizzleDimensions, std::array<type, swizzleDimensions> order
	>
	class Swizzle;

	/// \summary n-Dimensional Vector type.
	template<typename type, uint dimensions>
	union Vector
	{
		// Checks
		static_assert(dimensions > 0, "Vector cannot have dimensions less or equal to 0. What the hell are you trying to do?!");
		static_assert(std::is_arithmetic_v<type>, "Vector must be created with a numeric type.");
		
		std::array<type, dimensions> array;
		
		constexpr explicit Vector(const type setAll)
		{
			for(uint i = 0; i < dimensions; ++i)
			{
				array[i] = setAll;
			}
		}
		
		constexpr explicit Vector(std::array<type, dimensions> values)
		{
			for(uint i = 0; i < dimensions; ++i)
			{
				array[i] = values[i];
			}
		}
	};

	template<
		typename type, uint vectorDimensions,
		uint swizzleDimensions, std::array<type, swizzleDimensions> order
	>
	class Swizzle final
	{
	private:
		std::array<type, vectorDimensions> array;

	public:
		constexpr operator Vector<type, swizzleDimensions>() const
		{
			Vector<type, swizzleDimensions> result;
			for(uint i = 0; i < swizzleDimensions; ++i)
			{
				result[i] = array[order[i]];
			}
			return result;
		}

		constexpr Swizzle& operator =(const Vector<type, swizzleDimensions>& vec) const
		{
			for(uint i = 0; i < swizzleDimensions; ++i)
			{
				array[order[i]] = vec[i];
			}
			return *this;
		}
	};

	typedef Vector<int32, 2> int2_32;
	typedef Vector<int32, 3> int3_32;
	typedef Vector<int32, 4> int4_32;
	
	typedef Vector<uint32, 2> uint2_32;
	typedef Vector<uint32, 3> uint3_32;
	typedef Vector<uint32, 4> uint4_32;
	
	typedef Vector<int64, 2> int2_64;
	typedef Vector<int64, 3> int3_64;
	typedef Vector<int64, 4> int4_64;
	
	typedef Vector<uint64, 2> uint2_64;
	typedef Vector<uint64, 3> uint3_64;
	typedef Vector<uint64, 4> uint4_64;
	
	typedef Vector<float32, 2> float2;
	typedef Vector<float32, 3> float3;
	typedef Vector<float32, 4> float4;
	
	typedef Vector<float64, 2> double2;
	typedef Vector<float64, 3> double3;
	typedef Vector<float64, 4> double4;
	
	typedef int2_32 int2;
	typedef int3_32 int3;
	typedef int4_32 int4;
	
	typedef uint2_32 uint2;
	typedef uint3_32 uint3;
	typedef uint4_32 uint4;
	
	typedef int2_64 long2;
	typedef int3_64 long3;
	typedef int4_64 long4;
	
	typedef uint2_64 ulong2;
	typedef uint3_64 ulong3;
	typedef uint4_64 ulong4;
}

#endif