#ifndef GODOT_GAME_01_UI_MOVEMENT_BUTTON
#define GODOT_GAME_01_UI_MOVEMENT_BUTTON

// Main Header
#include <ui/ui.hpp>
#include <gen/control.hpp>

// External Dependencies
#include <core/godot.hpp>
#include <gen/button.hpp>
#include <gen/input.hpp>

// Internal Dependencies

UI_BEGIN

class movement_button :
	public gd::control
{
	GODOT_CLASS(ui::movement_button, gd::control);

public:		// Types
	/**
	@brief Child nodes of this node
	*/
	struct child_nodes_list {
		// Up button
		gd::button* up = nullptr;
		// Down button
		gd::button* down = nullptr;
		// Right button
		gd::button* right = nullptr;
		// Left button
		gd::button* left = nullptr;
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
	@brief Called when up button is down
	*/
	void
	_on_up_button_down();

	/**
	@brief Called when up button is up
	*/
	void
	_on_up_button_up();

	/**
	@brief Called when down button is down
	*/
	void
	_on_down_button_down();

	/**
	@brief Called when down button is up
	*/
	void
	_on_down_button_up();

	/**
	@brief Called when right button is down
	*/
	void
	_on_right_button_down();

	/**
	@brief Called when right button is up
	*/
	void
	_on_right_button_up();

	/**
	@brief Called when left button is down
	*/
	void
	_on_left_button_down();

	/**
	@brief Called when left button is up
	*/
	void
	_on_left_button_up();

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

private:	// Attributes
	// Player input
	gd::input* input = nullptr;

public:		// Attributes
	// Child nodes of this node
	movement_button::child_nodes_list child_nodes;
};

UI_END

// Inline File
#include <ui/movement_button.ipp>

#endif // GODOT_GAME_01_UI_MOVEMENT_BUTTON