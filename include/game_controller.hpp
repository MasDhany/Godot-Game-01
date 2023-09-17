#ifndef GODOT_GAME_01_GAME_CONTROLLER
#define GODOT_GAME_01_GAME_CONTROLLER

// Main Header
#include <gen/node.hpp>

// External Dependencies
#include <core/ref.hpp>
#include <core/godot.hpp>
#include <gen/random_number_generator.hpp>
#include <gen/node2d.hpp>
#include <gen/path_follow2d.hpp>
#include <gen/timer.hpp>
#include <gen/audio_stream_player.hpp>
#include <gen/packed_scene.hpp>
#include <gen/position2d.hpp>

// Internal Dependencies
#include <ui/hud.hpp>
#include <world/player.hpp>

class game_controller final :
	public gd::node
{
	GODOT_CLASS(game_controller, gd::node);

public:		// Types
	/**
	@brief Child nodes of this node
	*/
	struct child_nodes_list {
		// Mob timer
		gd::timer* mob_timer = nullptr;
		// Score timer
		gd::timer* score_timer = nullptr;
		// Start timer
		gd::timer* start_timer = nullptr;
		// Music
		gd::audio_stream_player* music = nullptr;
		// Death sound
		gd::audio_stream_player* death_sound = nullptr;
	};

public:     // Static Methods
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

public:     // Methods
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
	@brief Called when the mob timer is timed out
	*/
	void
	_on_mob_timer_timeout();

	/**
	@brief Called when the score timer is timed out
	*/
	void
	_on_score_timer_timeout();

	/**
	@brief Called when the start timer is timed out
	*/
	void
	_on_start_timer_timeout();

	/**
	@brief
	*/
	void
	new_game();

	/**
	@brief
	*/
	void
	game_over();

private:    // Attributes
	// Player score
	int score = 0;
	// Game HUD
	ui::hud* hud = nullptr;
	// Pointer to world node
	gd::node2d* world = nullptr;
	// Pointer to player
	world::player* player = nullptr;
	// Player start position
	gd::position2d* player_start_position = nullptr;
	// Mob spawn location
	gd::path_follow2d* mob_spawn_location = nullptr;
	// Random number generator
	gd::ref<gd::random_number_generator> random_generator = nullptr;

public:     // Attributes
	// Child nodes of this node
	game_controller::child_nodes_list child_nodes;
	// Mob scene
	gd::ref<gd::packed_scene> mob_scene;
};

// Inline File
#include <game_controller.ipp>

#endif // GODOT_GAME_01_GAME_CONTROLLER