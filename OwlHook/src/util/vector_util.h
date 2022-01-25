#pragma once

#include <vector>
#include <iostream>

/* vector utils, would define generic methods in vector_util.cpp but it won't let me */

namespace vector
{
	template <typename T>
	int index_in_vector(std::vector<T>* vector, T* element)
	{
		auto it = std::find(vector->begin(), vector->end(), *element);
		return std::distance(vector.begin(), it);
	}

	template <typename T>
	void remove_element(std::vector<T>* vector, T* element)      
	{
		int i = index_in_vector(*vector, element);
		vector->erase(vector->begin(), vector->begin() + 1);
	}

	template <typename T>
	void remove_first(std::vector<T>* vector)
	  {
		vector->erase(vector->begin());
	}
}