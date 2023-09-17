// Main Header
#include <ui/hud.hpp>

// External Dependencies
#include <core/godot.hpp>
#include <core/dictionary.hpp>
#include <core/variant.hpp>
#include <gen/label.hpp>
#include <gen/button.hpp>
#include <gen/timer.hpp>

// Internal Dependencies

/******************************
	Public Static Methods - Begin
******************************/

void
ui::hud::_register_methods()
{
	gd::register_method("_ready", &hud::_ready);
	gd::register_method("_on_start_button_pressed", &hud::_on_start_button_pressed);
	gd::register_method("_on_start_message_timer_timeout", &hud::_on_start_message_timer_timeout);
	gd::register_method("_on_start_button_timer_timeout", &hud::_on_start_button_timer_timeout);
	gd::register_method("_on_get_ready_message_timer_timeout", &hud::_on_get_ready_message_timer_timeout);
	gd::register_method("update_score", &hud::update_score);
	gd::register_method("show_get_ready", &hud::show_get_ready);
	gd::register_method("show_game_over", &hud::show_game_over);

	gd::register_signal<ui::hud>("start_button_pressed", gd::dictionary());
}

/******************************
	Public Static Methods - End
******************************/

/******************************
	Private Methods - Begin
******************************/

void
ui::hud::initialize_child_nodes()
{
	this->child_nodes.score = this->gd::node::get_node<gd::label>("score");
	this->child_nodes.message = this->gd::node::get_node<gd::label>("message");
	this->child_nodes.start_button = this->gd::node::get_node<gd::button>("start_button");
	this->child_nodes.start_message_timer = this->gd::node::get_node<gd::timer>("start_message_timer");
	this->child_nodes.get_ready_message_timer = this->gd::node::get_node<gd::timer>("get_ready_message_timer");
	this->child_nodes.start_button_timer = this->gd::node::get_node<gd::timer>("start_button_timer");
}

/******************************
	Private Methods - End
******************************/

/******************************
	Public Methods - Begin
******************************/

void
ui::hud::_ready()
{
	this->initialize_child_nodes();
}

void
ui::hud::_on_start_button_pressed()
{
	this->child_nodes.start_button->hide();

	this->gd::object::emit_signal("start_button_pressed");
}

void
ui::hud::_on_start_message_timer_timeout()
{
	this->child_nodes.message->set_text("Dodge the\nCreeps");
	this->child_nodes.message->show();
	this->child_nodes.start_button_timer->start();
}

void
ui::hud::_on_start_button_timer_timeout()
{
	this->child_nodes.start_button->show();
}

void
ui::hud::_on_get_ready_message_timer_timeout()
{
	this->child_nodes.message->hide();
}

void
ui::hud::update_score(
	const int score
)
{
	this->child_nodes.score->set_text(gd::variant(score));
}

void
ui::hud::show_get_ready()
{
	this->child_nodes.message->set_text("Get Ready");
	this->child_nodes.message->show();
	this->child_nodes.get_ready_message_timer->start();
}

void
ui::hud::show_game_over()
{
	this->child_nodes.message->set_text("Game Over");
	this->child_nodes.message->show();
	this->child_nodes.start_message_timer->start();
}

/******************************
	Public Methods - End
******************************/