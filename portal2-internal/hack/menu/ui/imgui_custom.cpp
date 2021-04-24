#include "imgui_custom.h"
#include <Windows.h>
#include <algorithm>
#include <string>


namespace detail {
	std::string get_key_name( const int key ) {
		auto code = MapVirtualKeyA( key, MAPVK_VK_TO_VSC );

		switch ( key ) {
		case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
		case VK_RCONTROL: case VK_RMENU:
		case VK_LWIN: case VK_RWIN: case VK_APPS:
		case VK_PRIOR: case VK_NEXT:
		case VK_END: case VK_HOME:
		case VK_INSERT: case VK_DELETE:
		case VK_DIVIDE:
		case VK_NUMLOCK:
			code |= KF_EXTENDED;
			break;
		default:
			break;
		}

		char ret_buff[ 128 ];
		strcpy_s( ret_buff, "-" );
		int result = GetKeyNameTextA( code << 16, ret_buff, 128 );

		if ( !result ) {
			switch ( key ) {
			case VK_XBUTTON1:
				strcpy_s( ret_buff, "M4" );
				break;
			case VK_XBUTTON2:
				strcpy_s( ret_buff, "M5" );
				break;
			case VK_LBUTTON:
				strcpy_s( ret_buff, "M1" );
				break;
			case VK_MBUTTON:
				strcpy_s( ret_buff, "M3" );
				break;
			case VK_RBUTTON:
				strcpy_s( ret_buff, "M2" );
				break;
			}
		}

		auto transformer = std::string( ret_buff );
		std::transform( transformer.begin( ), transformer.end( ), transformer.begin( ), ::tolower );
		return "[" + transformer + "]"; // yes, i am retarded
	}
}


bool ImGui::Hotkey( const char* label, int* k, const ImVec2& size_arg ) {
	ImGuiWindow* window = GetCurrentWindow( );
	if ( window->SkipItems )
		return false;

	SameLine( window->Size.x - 20 );

	ImGuiContext& g = *GImGui;

	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID( label );
	ImGuiIO* io = &GetIO( );

	char buf_display[ 64 ] = "[-]";

	if ( *k != 0 && g.ActiveId != id )
		strcpy_s( buf_display, detail::get_key_name( *k ).c_str( ) );

	ImVec2 label_size = CalcTextSize( buf_display );
	ImRect frame_bb( window->DC.CursorPos, window->DC.CursorPos + label_size );
	ImRect total_bb( window->DC.CursorPos, window->DC.CursorPos + ImVec2( window->Pos.x + window->Size.x - window->DC.CursorPos.x, label_size.y ) );
	ItemSize( total_bb, style.FramePadding.y );

	total_bb.Min.x -= label_size.x;
	frame_bb.Min.x -= label_size.x;

	if ( !ItemAdd( total_bb, id, &frame_bb ) )
		return false;

	const bool hovered = IsItemHovered( );
	const bool edit_requested = hovered && io->MouseClicked[ 0 ];
	const bool style_requested = hovered && io->MouseClicked[ 1 ];

	if ( edit_requested ) {
		if ( g.ActiveId != id ) {
			memset( io->MouseDown, 0, sizeof( io->MouseDown ) );
			memset( io->KeysDown, 0, sizeof( io->KeysDown ) );
			*k = 0;
		}

		SetActiveID( id, window );
		FocusWindow( window );
	}
	else if ( !hovered && io->MouseClicked[ 0 ] && g.ActiveId == id )
		ClearActiveID( );

	bool value_changed = false;

	if ( g.ActiveId == id ) {
		for ( auto i = 0; i < 5; i++ ) {
			if ( io->MouseDown[ i ] ) {
				switch ( i ) {
				case 0:
					*k = VK_LBUTTON;
					break;
				case 1:
					*k = VK_RBUTTON;
					break;
				case 2:
					*k = VK_MBUTTON;
					break;
				case 3:
					*k = VK_XBUTTON1;
					break;
				case 4:
					*k = VK_XBUTTON2;
				}
				value_changed = true;
				ClearActiveID( );
			}
		}

		if ( !value_changed ) {
			for ( auto i = VK_BACK; i <= VK_RMENU; i++ ) {
				if ( io->KeysDown[ i ] ) {
					*k = i;
					value_changed = true;
					ClearActiveID( );
				}
			}
		}

		if ( ImGui::IsKeyPressedMap( ImGuiKey_Escape ) ) {
			*k = 0;
			ClearActiveID( );
		}
	}

	window->DrawList->AddText( frame_bb.Min, g.ActiveId == id ? ImColor( 255 / 255.f, 16 / 255.f, 16 / 255.f, g.Style.Alpha ) : ImColor( 90 / 255.f, 90 / 255.f, 90 / 255.f, g.Style.Alpha ), buf_display );

	return value_changed;
}