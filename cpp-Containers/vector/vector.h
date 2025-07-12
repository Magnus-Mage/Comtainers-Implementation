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
		T*          m_elements { nullptr };
		std::size_t m_size     { 0 };
		std::size_t m_capacity { 0 };
		
		/**
		 * @brief Allocate memory to the vector on initialise 
		 * @param new_capacity The new capacity of the new container.
		 * @return Return pointer to the allocated memory
		 */
		T* allocate_aux(std::size_t new_capacity)
		{
			auto p = static_cast<T*>(::operator new(sizeof(T) * new_capacity));
			return p;
		}

		/**
		 * @brief Fills the raw memory block %[begin(), begin() + m_size) with %n copies
		 * %init
		 */
		template<typename U>
			requires std::is_convertible_v<U, T>
		void copy_aux(const U& init, std::size_t  size)
		{

		}

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
		
		// Constructor
		/**
		 * @brief creates a constructor with no elements
		 */
		vector() = default;

		/**
		 * @brief Initialise a vector with n copies of an element
		 * @param n Number of elements to initially create
		 * @param init a element to copy.
		 */
		vector(std::size_t n, const T& init)
			: m_elements {allocate_aux(n)}
			, m_size     { 0 }
			, m_capacity { n }
		{
			copy_aux(init, n);
			m_size     = n;	
		}	
	};
		
}

