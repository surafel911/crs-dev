#pragma once

#include <cstddef>

namespace crs {
	class component {
	template <typename T>
	friend class registry;

	private:
		std::size_t _handle;
	public:
		inline const std::size_t get_handle() const { return _handle; }
	};
}
