#pragma once

#include "Memory.hpp"

namespace Coral {

	template<typename TValue>
	class Array
	{
	public:
		static Array New(int32_t InLength)
		{
			Array<TValue> result;
			result.m_Ptr = static_cast<TValue*>(Memory::AllocHGlobal(InLength * sizeof(TValue)));
			result.m_Length = InLength;
			return result;
		}

		static Array New(const std::vector<TValue>& InValues)
		{
			Array<TValue> result;
			result.m_Ptr = static_cast<TValue*>(Memory::AllocHGlobal(InValues.size() * sizeof(TValue)));
			result.m_Length = static_cast<int32_t>(InValues.size());
			memcpy(result.m_Ptr, InValues.data(), InValues.size() * sizeof(TValue));
			return result;
		}

		static Array New(std::initializer_list<TValue> InValues)
		{
			Array result;
			result.m_Ptr = static_cast<TValue*>(Memory::AllocHGlobal(InValues.size() * sizeof(TValue)));
			result.m_Length = static_cast<int32_t>(InValues.size());
			memcpy(result.m_Ptr, InValues.begin(), InValues.size() * sizeof(TValue));
			return result;
		}

		static void Free(Array InArray)
		{
			Memory::FreeHGlobal(InArray.m_Ptr);
			InArray.m_Ptr = nullptr;
			InArray.m_Length = 0;
		}

		bool IsEmpty() const { return m_Length == 0 || m_Ptr == nullptr; }

		TValue& operator[](size_t InIndex) { return m_Ptr[InIndex]; }
		const TValue& operator[](size_t InIndex) const { return m_Ptr[InIndex]; }

		size_t Length() const { return m_Length; }

		TValue* begin() { return m_Ptr; }
		TValue* end() { return m_Ptr + m_Length; }

		const TValue* begin() const { return m_Ptr; }
		const TValue* end() const { return m_Ptr + m_Length; }

		const TValue* cbegin() const { return m_Ptr; }
		const TValue* cend() const { return m_Ptr + m_Length; }

	private:
		TValue* m_Ptr = nullptr;
		int32_t m_Length = 0;
		Bool32 m_IsDisposed = false;
	};

}
