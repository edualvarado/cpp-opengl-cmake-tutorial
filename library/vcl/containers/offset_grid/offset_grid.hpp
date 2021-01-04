#pragma once

#include <tuple>

namespace vcl
{

	// Compute the 1D offset corresponding to the index (k1,k2) in a 2D grid with static size
	template <size_t N1> size_t offset_grid_stack(size_t k1, size_t k2)
	{
		return k1 + N1 * k2;
	}

	template <size_t N1> std::pair<size_t,size_t> index_grid_from_offset_stack(size_t offset)
	{
		size_t const k1 = static_cast<size_t>(offset / N1);
		size_t const k2 = offset - k1 * N1;
		return { k1,k2 };
	}

	size_t offset_grid(size_t k1, size_t k2, size_t N1);
	std::pair<size_t,size_t> index_grid_from_offset(size_t offset, size_t N1);
	size_t offset_grid(size_t k0, size_t k1, size_t k2, size_t N1, size_t N2);

}