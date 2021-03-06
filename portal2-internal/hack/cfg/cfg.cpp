#include "cfg.h"
#include "detail/json.hpp"
#include <fstream>
#include <filesystem>


namespace hack::cfg {
	void push( bool* ptr, std::string name ) { _bools.push_back( { ptr, name } ); }

	void init( ) {
		push( &opts::bhop, "misc_bhop" );

		read( "config" );
	}

	std::string& get_path( std::string& path ) {
		std::filesystem::create_directory( _dir );
		path = _dir + "\\" + path + ".json";
		return path;
	}

	void read( std::string path ) {
		path = get_path( path );
		if ( !std::filesystem::exists( path ) ) return;

		std::ifstream reader( path );
		nlohmann::json data;
		reader >> data;
		reader.close( );

		auto sanityChecks = [ ] ( nlohmann::json& d, std::string& c ) -> bool { return d.find( c ) != d.end( ); };

		for ( auto& b : _bools )
			if ( sanityChecks( data, b.m_name ) )
				*b.m_ptr = data[ b.m_name ].get<bool>( );
	}

	void save( std::string path ) {
		path = get_path( path );

		nlohmann::json data;

		for ( auto& b : _bools )
			data[ b.m_name ] = *b.m_ptr;
		
		std::ofstream reader( path );
		reader.clear( );
		reader << std::setw( 4 ) << data << std::endl;
		reader.close( );
	}
}
