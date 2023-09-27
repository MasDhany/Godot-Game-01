// Main Header
#include <ui/movement_button.hpp>

// External Dependencies
#include <gen/node.hpp>
#include <gen/button.hpp>
#include <gen/input.hpp>

// Internal Dependencies

/******************************
	Public Static Methods - Begin
******************************/

void
ui::movement_button::_register_methods()
{
	gd::register_method("_ready", &movement_button::_ready);

#if defined(ANDROID)
	gd::register_method("_on_up_button_down", &movement_button::_on_up_button_down);
	gd::register_method("_on_up_button_up", &movement_button::_on_up_button_up);
	gd::register_method("_on_down_button_down", &movement_button::_on_down_button_down);
	gd::register_method("_on_down_button_up", &movement_button::_on_down_button_up);
	gd::register_method("_on_right_button_down", &movement_button::_on_right_button_down);
	gd::register_method("_on_right_button_up", &movement_button::_on_right_button_up);
	gd::register_method("_on_left_button_down", &movement_button::_on_left_button_down);
	gd::register_method("_on_left_button_up", &movement_button::_on_left_button_up);
#endif // ANDROID

	gd::register_method("new_game", &movement_button::new_game);
	gd::register_method("game_over", &movement_button::game_over);
}

/******************************
	Public Static Methods - End
******************************/

/******************************
	Private Methods - Begin
******************************/

void
ui::movement_button::initialize_child_nodes()
{
	this->child_nodes.up = this->gd::node::get_node<gd::button>("up");
	this->child_nodes.down = this->gd::node::get_node<gd::button>("down");
	this->child_nodes.right = this->gd::node::get_node<gd::button>("right");
	this->child_nodes.left = this->gd::node::get_node<gd::button>("left");
}

/******************************
	Private Methods - End
******************************/

/******************************
	Public Methods - Begin
******************************/

void
ui::movement_button::_ready()
{
	this->gd::canvas_item::hide();

#if defined(ANDROID)
	this->initialize_child_nodes();

	this->input = gd::input::get_singleton();
#endif // ANDROID
}

void
ui::movement_button::_on_up_button_down()
{
	this->input->action_press("move_up");
}

void
ui::movement_button::_on_up_button_up()
{
	this->input->action_release("move_up");
}

void
ui::movement_button::_on_down_button_down()
{
	this->input->action_press("move_down");
}

void
ui::movement_button::_on_down_button_up()
{
	this->input->action_release("move_down");
}

void
ui::movement_button::_on_right_button_down()
{
	this->input->action_press("move_right");
}

void
ui::movement_button::_on_right_button_up()
{
	this->input->action_release("move_right");
}

void
ui::movement_button::_on_left_button_down()
{
	this->input->action_press("move_left");
}

void
ui::movement_button::_on_left_button_up()
{
	this->input->action_release("move_left");
}

void
ui::movement_button::new_game()
{
#if defined(ANDROID)
	this->gd::canvas_item::show();
#endif // ANDROID
}

void
ui::movement_button::game_over()
{
#if defined(ANDROID)
	this->gd::canvas_item::hide();
#endif // ANDROID
}

/******************************
	Public Methods - End
******************************/