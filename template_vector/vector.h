#include <iostream>
#include <algorithms>

/** 
 * @brief A standard container that gives access to elements in O(1) time.
 */
namespace test
{
	template<typename T>
	class vector
	{
	private:
		T*          m_elements { nullprt };
		std::size_t m_size     { 0 };
		std::size_t m_capacity { 0 };

		/**
		 * @brief Check if the container is full or not
		 * @return True if the container is full
		 */
	       	[[nodiscard]] bool full() { return size() == capacity(); }

		/**
		 * @brief Grow the container twice its size.
		 */
		void grow() { reserve(capacity() ? capacity() * 2 : 16); }

	public:
		// Capacity related member functions
		/**
		 * @brief Returns the number of elements in the vector.
		 */
		[[nodiscard]] std::size_t size() const { return m_size; }

		/**
		 * @brief Returns the total number of elements a vector can hold
		 */
		[[nodiscard]] std::size_t capacity() const { return m_capacity; }
		
		/**
		 * @brief Checks if the vector is empty or not.
		 * @return Returns True if the vector is empty
		 */
		[[nodiscrard]] bool empty() const { return size() == 0; } 
	};
		
}

