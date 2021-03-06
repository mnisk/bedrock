#pragma once
#ifndef BEDROCK_ARRAY_HPP
#define BEDROCK_ARRAY_HPP

// A wrapper around C-style arrays which doesn't decay to a pointer.

#include "type.hpp"
#include "trait.hpp"
#include "algorithm.hpp"

namespace br {
	// Iterator.
	template <typename T>
	struct ArrayIterator: BiDirectionalIterator<ArrayIterator<T>> {
		T* ptr = nullptr;


		constexpr T& operator*() const {
			return *ptr;
		}

		void next() { ++ptr; }
		void prev() { --ptr; }

		constexpr ArrayIterator<T>& operator++() noexcept {
			++ptr;
			return *this;
		}

		constexpr ArrayIterator<T> operator++(int) noexcept {
			auto tmp = *this;
			++ptr;
			return tmp;
		}

		constexpr ArrayIterator<T>& operator--() noexcept {
			--ptr;
			return *this;
		}

		constexpr ArrayIterator<T> operator--(int) noexcept {
			auto tmp = *this;
			--ptr;
			return tmp;
		}
	};


	template <typename T> constexpr bool operator==(const ArrayIterator<T>& lhs, const ArrayIterator<T>& rhs) {
		return lhs.ptr == rhs.ptr;
	}

	template <typename T> constexpr bool operator!=(const ArrayIterator<T>& lhs, const ArrayIterator<T>& rhs) {
		return lhs.ptr != rhs.ptr;
	}





	// Array.
	template <typename T, br::size_t N>
	struct Array: Container<Array<T, N>> {
		T buffer[N]{0};

		// Obtain iterators.
		constexpr auto begin() noexcept {
			ArrayIterator<T> it;
			it.ptr = buffer;
			return it;
		}

		constexpr auto end() noexcept {
			ArrayIterator<T> it;
			it.ptr = buffer + N;
			return it;
		}

		constexpr T& operator[](br::index_t i) noexcept {
			return buffer[i];
		}
	};


	template <typename T, typename... Ts>
	constexpr auto arr_create(const T& first, const Ts&... elements) {
		ensure_variadic_parity<T, Ts...>();

		T tmp[] = { first, elements... };
		Array<T, sizeof...(Ts) + 1> arr;

		for (br::index_t i = 0; i < sizeof...(Ts) + 1; i++)
			arr.buffer[i] = tmp[i];

		return arr;
	}

	template <typename T, br::size_t N>
	constexpr auto arr_create() {
		return br::Array<T, N>{};
	}



	template <typename T, br::size_t N>
	constexpr auto& at(const Array<T, N>& arr, br::index_t i) {
		return arr.buffer[i];
	}

	template <typename T, br::size_t N>
	constexpr br::size_t size(const Array<T, N>&) {
		return N;
	}

	template <typename T, br::size_t N>
	constexpr bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
		bool same = true;

		for (br::index_t i = 0; i < N; ++i)
			same = lhs[i] == rhs[i];

		return same;
	}

	template <typename T, br::size_t N>
	constexpr bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
		return not(lhs == rhs);
	}





	// other:
	// iterators  : come up with a decent interface for iterators
	// allocators : come up with a decent interface for allocators
}

#endif

