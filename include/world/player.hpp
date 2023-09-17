#ifndef GODOT_GAME_01_WORLD_PLAYER
#define GODOT_GAME_01_WORLD_PLAYER

// Main Header
#include <world/world.hpp>
#include <gen/area2d.hpp>

// External Dependencies
#include <core/vector2.hpp>
#include <core/godot.hpp>
#include <gen/animated_sprite.hpp>
#include <gen/collision_shape2d.hpp>
#include <gen/input.hpp>
#include <gen/node2d.hpp>

// Internal Dependencies

WORLD_BEGIN

class player final : 
	public gd::area2d 
{
	GODOT_CLASS(world::player, gd::area2d);

public:		// Types
	/**
	@brief Child nodes of this node
	*/
	struct child_nodes_list {
		// Player animated sprite
		gd::animated_sprite* animated_sprite = nullptr;
		// Player hit box
		gd::collision_shape2d* hit_box = nullptr;
	};

public:		// Static Methods
	/**
	@brief Register class members
	*/
	static
	void
	_register_methods();

private:	// Static Attributes
	// Default player movement speed
	static constexpr
	float default_speed = 400.0f;

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
	@brief Called every frame
	@param [delta] Refers to the frame length - the amount of the time that the
		previous frame took to complete
	*/
	void
	_process(
		const double delta
	);

	/**
	@brief Called when the player collides with other node
	@param [other] The node that collided with the player
	*/
	void
	_on_body_entered(
		const gd::node2d* other
	);

	/**
	@brief Called when the game starts
	@param [start_pos] Start position of the player
	*/
	void
	start(
		const gd::vector2& start_pos
	);

private:	// Attributes
	// Player input
	gd::input* input = nullptr;
	// Size of the game window
	gd::vector2 screen_size = gd::vector2(0.0f, 0.0f);

public:		// Attributes
	// Child nodes of this node
	player::child_nodes_list child_nodes;
	// Player movement speed
	float speed = player::default_speed;
};

WORLD_END

// Inline File
#include <world/player.ipp>

#endif // GODOT_GAME_01_WORLD_PLAYER