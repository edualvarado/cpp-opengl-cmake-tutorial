#pragma once


#include "vcl/containers/containers.hpp"

#include <string>
#include <sstream>
#include <fstream>

namespace vcl
{
	/** Ensure that a file already exists and is accessible
	 * Display an error message with some reminder on path setting in case the file cannot be accessed */
	void assert_file_exist(const std::string& filename);

	/** Return true if the file can be accessed, false otherwise */
	bool check_file_exist(const std::string filename);


	template <typename T> void read_from_file(std::string const& filename, T& data);
	template <typename T> void read_from_file(std::string const& filename, buffer<buffer<T>>& data);

	template <typename T> std::istream& read_from_stream(std::istream& stream, T& data);
	template <typename T, size_t N> std::istream& read_from_stream(std::istream& stream, buffer_stack<T,N>& data);
	template <typename T> std::istream& read_line_from_stream(std::istream& stream, T& data);
	template <typename T> std::istream& read_from_stream(std::istream& stream, buffer<T>& data);
	template <typename T> std::istream& read_from_stream_per_line(std::istream& stream, buffer<T>& data);
}


namespace vcl
{
	template <typename T>
	std::istream& read_from_stream(std::istream& stream, T& data)
	{
		stream >> data;
		return stream;
	}

	template <typename T, size_t N>
	std::istream& read_from_stream(std::istream& stream, buffer_stack<T,N>& data)
	{
		for(size_t k=0; k<N && stream.good(); ++k)
			read_from_stream(stream,data[k]);
		return stream;
	}

	template <typename T>
	std::istream& read_line_from_stream(std::istream& stream, T& data)
	{
		if(stream.good()) {
			std::string line;
			std::getline(stream, line);
			if(stream.good())
			{
				std::istringstream stream_line(line);
				read_from_stream(stream_line, data);
			}
		}

		return stream;
	}

	template <typename T>
	std::istream& read_from_stream(std::istream& stream, buffer<T>& data)
	{
		while(stream.good()) {
			T temp;
			read_from_stream(stream, temp);
			if(stream)
				data.push_back(temp);
		}
		
		return stream;
	}

	template <typename T>
	std::istream& read_from_stream_per_line(std::istream& stream, buffer<T>& data)
	{
		while(stream.good()) {
			T temp;
			read_line_from_stream(stream, temp);
			if(stream.good())
				data.push_back(temp);
		}

		return stream;
	}

	template <typename T>
	void read_from_file(std::string const& filename, T& data)
	{
		assert_file_exist(filename);

		// Open file with pointer at last position
		std::ifstream stream(filename);
		assert_vcl_no_msg(stream.is_open());

		read_from_stream(stream, data);

		stream.close();
		assert_vcl_no_msg(!stream.is_open());
	}

	template <typename T>
	void read_from_file(std::string const& filename, buffer<buffer<T>>& data)
	{
		assert_file_exist(filename);

		// Open file with pointer at last position
		std::ifstream stream(filename);
		assert_vcl_no_msg(stream.is_open());

		read_from_stream_per_line(stream, data);

		stream.close();
		assert_vcl_no_msg(!stream.is_open());
	}


}