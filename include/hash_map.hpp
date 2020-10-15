#pragma once

#include <vector>
#include <functional>

namespace crs {
	namespace {
		template <typename K, typename T>
		class hopscotch_bucket {
		private:
			std::vector<K> _keys;
			std::vector<T> _data;

		public:
			hopscotch_bucket() = default;
			hopscotch_bucket(const hopscotch_bucket&) = default;

			hopscotch_bucket(std::size_t size)
			{
				_bucket.reserve(size);
			}

			~hopscotch_bucket() = default;

			inline std::size size() const
			{
				return _keys.size();
			}

			inline void reserve()
			{
				_buckets.reserve();
			}

			inline void clear()
			{
				_keys.clear();
				_data.clear();
			}

			void emplace(const K& k, const T& t)
			{
			}

			void erase(const K& k)
			{
				
			}
		};
	}

	template <typename K, typename T>
	class hash_map {
	private:
	
		std::hash<K> _hash;
		std::vector<hopscotch_bucket<K, T>> _buckets;

	public:
		hash_map() = default;
		hash_map(const hash_map&) = default;

		hash_map(std::size_t size)
		{
			_bucket.reserve(size);
		}

		~hash_map() = default;

		inline std::size_t size() const
		{
			return _bucket.size();
		}

		inline void reserve()
		{
			_bucket.reserve();
		}

		inline void clear()
		{
			_bucket.clear();
		}

		template <typename... Args>
		T& emplace(const K& k, Args&&... args)
		{
			std::size_t i = _hash(k) & 
		}

		T& find(const K& k)
		{
			std::size_t index = _hash(key) & 
		}
	};
}
