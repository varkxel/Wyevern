#ifndef WYEVERN_ARCHITECTURE_INCLUDED
#define WYEVERN_ARCHITECTURE_INCLUDED

#include <cstdint>

#ifdef __cpp_lib_hardware_interference_size
#include <new>
#endif

namespace Wyevern::Architecture {
	// False sharing mitigation values
	#ifdef __cpp_lib_hardware_interference_size
		constexpr std::size_t FalseSharingMitigation = std::hardware_destructive_interference_size;
	#else
		constexpr std::size_t FalseSharingMitigation = 64;
	#endif

	constexpr std::size_t PadToCache(const std::size_t structSize) {
		std::size_t size = FalseSharingMitigation;
		while(size < structSize) {
			size += FalseSharingMitigation;
		}
		return size - structSize;
	}
}

#endif
