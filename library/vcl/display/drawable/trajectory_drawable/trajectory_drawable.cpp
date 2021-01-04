#include "vcl/base/base.hpp"
#include "trajectory_drawable.hpp"

namespace vcl
{
	trajectory_drawable::trajectory_drawable(size_t N_max_sample_arg)
		:position_record(), time_record(), visual(), N_max_sample(N_max_sample_arg), current_size(0)
	{}

	void trajectory_drawable::clear()
	{
		position_record.clear();
		time_record.clear();
		visual.clear();
		current_size = 0;
	}
	void trajectory_drawable::add(vec3 const& position, float time)
	{
		assert_vcl_no_msg(position_record.size()==time_record.size());

		// Initialize if needed
		if (position_record.size()==0) {
			assert_vcl_no_msg(current_size==0);
			assert_vcl_no_msg(visual.vbo_position==0);

			position_record.resize(N_max_sample);
			time_record.resize(N_max_sample);
			visual = curve_drawable(position_record);
		}
		assert_vcl_no_msg(position_record.size()==N_max_sample);

		for(size_t k=N_max_sample-1; k>0; --k) { 
			position_record[k] = position_record[k-1];
			time_record[k] = time_record[k-1];
		}
		position_record[0] = position;
		time_record[0] = time;

		if(current_size<N_max_sample)
			current_size++;

		visual.update(position_record);

	}


}
