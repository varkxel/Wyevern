#ifndef WYEVERN_APPLICATION_INCLUDED
#define WYEVERN_APPLICATION_INCLUDED

namespace Wyevern {
	class WyevernApplication {
		virtual ~WyevernApplication() = default;

		virtual void OnLoad() = 0;
	};
}

#endif
