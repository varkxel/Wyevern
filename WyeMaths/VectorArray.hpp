#ifndef WYEMATHS_VECTORARRAY_INCLUDED
#define WYEMATHS_VECTORARRAY_INCLUDED

#include "Vector.hpp"
#include <vector>
#include <array>

namespace Wyevern::Mathematics {
	template<typename type, uint dimensions>
	class VectorArrayBase {
	protected:
		std::array<std::vector<type>, dimensions> components;

	public:
		constexpr std::vector<type>& GetComponent(const std::size_t dimension) {
			static_assert(dimension < dimensions, "Dimension provided to VectorArray::GetComponent is out of bounds.");
			return components[dimension];
		}
		
		void Add(Vector<type, dimensions> vector) {
			for(uint i = 0; i < dimensions; ++i) {
				components[i].push_back(vector[i]);
			}
		}

		void Remove(const std::size_t index) {
			for(uint i = 0; i < dimensions; ++i) {
				components[i].erase(components[i].begin() + index);
			}
		}

		constexpr Vector<type, dimensions> operator[](const std::size_t index) const {
			Vector<type, dimensions> result;
			for(uint i = 0; i < dimensions; ++i) {
				result[i] = components[i][index];
			}
			return result;
		}

		explicit operator std::vector<Vector<type, dimensions>>() const {
			const std::size_t size = components[0].size();

			std::vector<Vector<type, dimensions>> results;
			results.reserve(size);
			for(std::size_t i = 0; i < size; ++i) {
				Vector<type, dimensions> vec;
				for(uint dim = 0; dim < dimensions; ++dim) {
					vec[dim] = components[dim][i];
				}
				results.push_back(vec);
			}
			return results;
		}
	};

	template<typename type, uint dimensions>
	struct VectorArray : VectorArrayBase<type, dimensions> {
		// Template specialization is fun, isn't it?
	};

	template<typename type>
	struct VectorArray<type, 1> : VectorArrayBase<type, 1> {
		std::vector<type>& x = this->components[0];
	};

	template<typename type>
	struct VectorArray<type, 2> : VectorArrayBase<type, 2> {
		std::vector<type>& x = this->components[0];
		std::vector<type>& y = this->components[1];
	};

	template<typename type>
	struct VectorArray<type, 3> : VectorArrayBase<type, 3>
	{
		std::vector<type>& x = this->components[0];
		std::vector<type>& y = this->components[1];
		std::vector<type>& z = this->components[2];
	};

	template<typename type>
	struct VectorArray<type, 4> : VectorArrayBase<type, 4>
	{
		std::vector<type>& x = this->components[0];
		std::vector<type>& y = this->components[1];
		std::vector<type>& z = this->components[2];
		std::vector<type>& w = this->components[3];
	};
}

#endif