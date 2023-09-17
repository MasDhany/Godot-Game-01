// Main Header

// External Dependencies
#include <core/godot.hpp>

// Internal Dependencies
#include <ui/hud.hpp>

#include <world/mob.hpp>
#include <world/player.hpp>

#include <game_controller.hpp>

extern "C" {
	void
	GDN_EXPORT 
	godot_nativescript_init(
		void* handle
	)
	{
		gd::godot::nativescript_init(handle);

		gd::register_class<ui::hud>();

		gd::register_class<world::mob>();
		gd::register_class<world::player>();
		
		gd::register_class<::game_controller>();
	}

	void 
	GDN_EXPORT 
	godot_gdnative_init(
		godot_gdnative_init_options* o
	)
	{
		gd::godot::gdnative_init(o);
	}

	void 
	GDN_EXPORT 
	godot_gdnative_terminate(
		godot_gdnative_terminate_options* o
	)
	{
		gd::godot::gdnative_terminate(o);
	}
}