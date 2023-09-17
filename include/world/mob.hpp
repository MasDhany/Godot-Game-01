#ifndef GODOT_GAME_01_WORLD_MOB
#define GODOT_GAME_01_WORLD_MOB

// Main Header
#include <world/world.hpp>
#include <gen/rigid_body2d.hpp>

// External Dependencies
#include <core/godot.hpp>
#include <gen/animated_sprite.hpp>
#include <gen/collision_shape2d.hpp>
#include <gen/visibility_notifier2d.hpp>

// Internal Dependencies

WORLD_BEGIN

class mob final :
	public gd::rigid_body2d
{
	GODOT_CLASS(world::mob, gd::rigid_body2d);

public:		// Types
	/**
	@brief Child nodes of this nod
	*/
	struct child_nodes_list {
		// Mob animated sprite
		gd::animated_sprite* animated_sprite = nullptr;
		// Mob hit box
		gd::collision_shape2d* hit_box = nullptr;
		// Mob visibility notifier2d
		gd::visibility_notifier2d* visibility_notifier2d = nullptr;
	};

public:		// Static Methods
	/**
	@brief Register class members
	*/
	static
	void
	_register_methods();

private:	// Methods
	/**
	@brief Initialize child nodes of this node
	*/
	void
	initialize_child_nodes();

public:		// Methods
	/**
	@brief Class initialization
	*/
	inline
	void 
	_init() const noexcept;

	/**
	@brief Called when the object is ready to use
	*/
	void
	_ready();

	/**
	@brief Called when the mob exits the screen
	*/
	void
	_on_visibility_notifier2d_screen_exited();

public:		// Attributes
	// Child nodes of this nod
	mob::child_nodes_list child_nodes;
};

WORLD_END

// Inline Files
#include <world/mob.ipp>

#endif // GODOT_GAME_01_WORLD_MOB