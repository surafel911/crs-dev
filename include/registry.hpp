#pragma once

#include <atomic>
#include <ctime>
#include <vector>
#include <functional>
#include <unordered_map>

#include <component.hpp>

namespace crs {
	template <typename T>
	class registry {
	private:
		std::vector<T> _data;
		std::function<void(T&)> _update;
		std::unordered_map<std::size_t, std::size_t> _map;

		registry(const registry<T>&) = delete;

	public:
		registry()
		{
			static_assert(std::is_base_of<component, T>::value,
				"Invalid registry type, check type inherits from component interface.");
		}

		registry(std::size_t size) : _update(nullptr)
		{
			static_assert(std::is_base_of<component, T>::value,
				"Invalid registry type, check type inherits from component interface.");

			_map.reserve(size);
			_data.reserve(size);
		}

		registry(std::function<void(T&)> update) : _update(update)
		{
			static_assert(std::is_base_of<component, T>::value,
				"Invalid registry type, check type inherits from component interface.");
		}
	
		registry(std::size_t size, std::function<void(T&)> update) : _update(update)
		{
			static_assert(std::is_base_of<component, T>::value,
				"Invalid registry type, check type inherits from component interface.");
		
			_map.reserve(size);
			_data.reserve(size);
		}

		~registry() = default;

		inline T& get(const std::size_t h) const
		{
			return _data[_map.find(h)->second];
		}

		inline const std::vector<T>& data() const
		{
			return _data;
		}

		inline std::size_t size() const
		{
			return _data.size();
		}

		void update()
		{
			for (T& t : _data) {
				_update(t);
			}	
		}

		void clear()
		{
			_data.clear();
			_map.clear();
		}

		void reserve()
		{
			_data.reserve();
			_map.reserve();
		}

		template <typename ... Args>
		std::pair<std::size_t, std::reference_wrapper<T>> emplace(Args&&... args)
		{
			T& c = _data.emplace_back(args...);
			c._handle = static_cast<std::size_t>(clock());
			
			_map.emplace(c._handle, _data.size() - 1);

			return std::make_pair(c._handle, std::reference_wrapper(c));
		}

		void erase(const std::size_t h)
		{
			auto eraseIt = _map.find(h);

			if (eraseIt == _map.end()) {
				return;
			}

			_data[eraseIt->second] = std::move(_data.back());
			_data.pop_back();

			if (_data.size() == 0) {
				_map.erase(eraseIt);
			} else {
				auto movedIt = _map.find(_data[eraseIt->second]._handle);
				movedIt->second = eraseIt->second;
			}
		}
	};
}
