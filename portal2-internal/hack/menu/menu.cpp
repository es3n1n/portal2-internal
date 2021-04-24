#include "menu.h"
#include <Windows.h>
#include "../../util/util.h"
#include "../cfg/cfg.h"


namespace hack::menu {
	void render( ) {
		if ( !opened )
			return;

		ImGui::SetNextWindowPos( ImGui::GetIO( ).DisplaySize * 0.5f, ImGuiCond_Once, ImVec2( 0.5f, 0.5f ) );
		ImGui::SetNextWindowSize( ImVec2( 500, 450 ), ImGuiCond_Once );

		if ( !ImGui::Begin( "portal2-internal by es3n1n", &opened, ImGuiWindowFlags_NoCollapse ) )
			return ImGui::End( );

		ImGui::Checkbox( "bhop", &cfg::opts::bhop );
		ImGui::Spacing( );
		if ( ImGui::Button( "save" ) )
			cfg::save( "config" );
		ImGui::SameLine( );
		if ( ImGui::Button( "load" ) )
			cfg::read( "config" );

		ImGui::End( );
	}

	void toggle( ) {
		if ( !util::input::get( VK_INSERT ).pressed( ) )
			return;
		opened ^= true;
	}

	void setup( ) {
		auto& io = ImGui::GetIO( );
		io.LogFilename = NULL;
		io.IniFilename = NULL;
	}
}
