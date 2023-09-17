#ifndef GODOT_GAME_01_UI_HUD
#define GODOT_GAME_01_UI_HUD

// Main Header
#include <ui/ui.hpp>
#include <gen/canvas_layer.hpp>

// External Dependencies
#include <core/godot.hpp>
#include <gen/label.hpp>
#include <gen/button.hpp>
#include <gen/timer.hpp>

// Internal Dependencies

UI_BEGIN

class hud final :
	public gd::canvas_layer
{
	GODOT_CLASS(ui::hud, gd::canvas_layer);

public:		// Types
	/**
	@brief Child nodes of this node
	*/
	struct child_nodes_list {
		// Score text
		gd::label* score = nullptr;
		// Message
		gd::label* message = nullptr;
		// Start button
		gd::button* start_button = nullptr;
		// Start message timer
		gd::timer* start_message_timer = nullptr;
		// Get ready message timer
		gd::timer* get_ready_message_timer = nullptr;
		// Start button timer
		gd::timer* start_button_timer = nullptr;
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
	@brief Called when the start button is pressed
	*/
	void
	_on_start_button_pressed();

	/**
	@brief Called when the start message timer is timed out
	*/
	void
	_on_start_message_timer_timeout();

	/**
	@brief Called when the start button timer is timed out
	*/
	void
	_on_start_button_timer_timeout();

	/**
	#brief Called when the get ready message timer is timed out
	*/
	void
	_on_get_ready_message_timer_timeout();

	/**
	@brief Update score in the hud
	@param score New score to update
	*/
	void
	update_score(
		const int score
	);

	/**
	@brief Shows "Get Ready" message and set a timer to hide it
	*/
	void
	show_get_ready();

	/**
	@brief Shows "Game Over" message and set a timer to show start message
	*/
	void
	show_game_over();

public:		// Attributes
	// Child nodes of this node
	hud::child_nodes_list child_nodes;
};

UI_END

// Inline File
#include <ui/hud.ipp>

#endif // GODOT_GAME_01_UI_HUD