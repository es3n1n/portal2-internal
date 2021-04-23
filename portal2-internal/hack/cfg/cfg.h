#pragma once
#include "opts.h"
#include <string>
#include <vector>


namespace hack::cfg {
	template <typename t>
	struct cfg_item_t {
	public:
		t* m_ptr;
		std::string m_name;
	};

	void push( bool* ptr, std::string name );
	void init( );

	void read( std::string path );
	void save( std::string path );
	std::string& get_path( std::string& path );

	//
	inline std::vector<cfg_item_t<bool>> _bools = {};

	//
	inline std::string _dir = "c:\\portal2-internal";
}
