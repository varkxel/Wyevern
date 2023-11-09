#ifndef WYEMATHS_VECTORARRAY_INCLUDED
#define WYEMATHS_VECTORARRAY_INCLUDED

#include "Vector.hpp"
#include <vector>
#include <array>

namespace Wyevern::Mathematics
{
	template<typename type, uint dimensions>
	class VectorArrayBase
	{
	protected:
		std::array<std::vector<type>, dimensions> components;

	public:
		constexpr std::vector<type>& GetComponent(const std::size_t dimension)
		{
			static_assert(dimension < dimensions, "Dimension provided to VectorArray::GetComponent is out of bounds.");
			return components[dimension];
		}
		
		void Add(Vector<type, dimensions> vector)
		{
			for(uint i = 0; i < dimensions; ++i)
			{
				components[i].push_back(vector[i]);
			}
		}

		void Remove(const std::size_t index)
		{
			for(uint i = 0; i < dimensions; ++i)
			{
				components[i].erase(components[i].begin() + index);
			}
		}

		constexpr Vector<type, dimensions> operator[](const std::size_t index) const
		{
			Vector<type, dimensions> result;
			for(uint i = 0; i < dimensions; ++i)
			{
				result[i] = components[i][index];
			}
			return result;
		}
	};

	template<typename type, uint dimensions>
	struct VectorArray : public VectorArrayBase<type, dimensions>
	{
	};

	template<typename type>
	struct VectorArray<type, 1> : public VectorArrayBase<type, 1>
	{
		std::vector<type>& x = this->components[0];
	};

	template<typename type>
	struct VectorArray<type, 2> : public VectorArrayBase<type, 2>
	{
		std::vector<type>& x = this->components[0];
		std::vector<type>& y = this->components[1];
	};

	template<typename type>
	struct VectorArray<type, 3> : public VectorArrayBase<type, 3>
	{
		std::vector<type>& x = this->components[0];
		std::vector<type>& y = this->components[1];
		std::vector<type>& z = this->components[2];
	};

	template<typename type>
	struct VectorArray<type, 4> : public VectorArrayBase<type, 4>
	{
		std::vector<type>& x = this->components[0];
		std::vector<type>& y = this->components[1];
		std::vector<type>& z = this->components[2];
		std::vector<type>& w = this->components[3];
	};
}

#endif