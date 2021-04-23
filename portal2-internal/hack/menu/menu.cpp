#include "menu.h"
#include <Windows.h>
#include "../../util/util.h"


namespace hack::menu {
	void render( ) {
		if ( !opened )
			return;

		ImGui::SetNextWindowPos( ImGui::GetIO( ).DisplaySize * 0.5f, ImGuiCond_Once, ImVec2( 0.5f, 0.5f ) );
		ImGui::SetNextWindowSize( ImVec2( 500, 450 ), ImGuiCond_Once );

		if ( ImGui::Begin( "portal2-internal by es3n1n", &opened, ImGuiWindowFlags_NoCollapse ) ) {

		}
		ImGui::End( );
	}

	void toggle( ) {
		if ( !util::input::get( VK_INSERT ).pressed( ) )
			return;
		opened ^= true;
	}

	void setup( ) {
		auto& io = ImGui::GetIO( );
		io.IniFilename = nullptr;

		auto& style = ImGui::GetStyle( );
		ImGui::StyleColorsDark( );
	}
}
