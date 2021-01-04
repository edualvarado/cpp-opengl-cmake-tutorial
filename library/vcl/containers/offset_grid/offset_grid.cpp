#include "vcl/base/base.hpp"
#include "offset_grid.hpp"


namespace vcl
{

	size_t offset_grid(size_t k1, size_t k2, size_t N1)
	{
		return k1 + N1*k2;
	}
	std::pair<size_t,size_t> index_grid_from_offset(size_t offset, size_t N1)
	{
		size_t const k1 = static_cast<size_t>(offset / N1);
		size_t const k2 = offset - k1 * N1;
		return { k1,k2 };
	}

	size_t offset_grid(size_t k0, size_t k1, size_t k2, size_t N1, size_t N2)
	{
		return k0 + N1 * (k1 + N2 * k2);
	}
}