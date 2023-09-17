// Main Header
#include <world/player.hpp>

// External Dependencies
#include <core/dictionary.hpp>
#include <core/math.hpp>
#include <gen/animated_sprite.hpp>
#include <gen/collision_shape2d.hpp>
#include <gen/input.hpp>
#include <gen/canvas_item.hpp>
#include <gen/node.hpp>
#include <gen/node2d.hpp>
#include <gen/object.hpp>

// Internal Dependencies

/******************************
	Public Static Methods - Begin
******************************/

void
world::player::_register_methods()
{
	gd::register_method("_ready", &player::_ready);
	gd::register_method("_process", &player::_process);
	gd::register_method("_on_body_entered", &player::_on_body_entered);

	gd::register_method("start", &player::start);

	gd::register_property("speed", &player::speed, player::default_speed);

	gd::register_signal<world::player>("hit", gd::dictionary());
}

/******************************
	Public Static Methods - End
******************************/

/******************************
	Private Methods - Begin
******************************/

void
world::player::initialize_child_nodes()
{
	this->child_nodes.animated_sprite = this->gd::node::get_node<gd::animated_sprite>("animated_sprite");
	this->child_nodes.hit_box = this->gd::node::get_node<gd::collision_shape2d>("hit_box");
}

/******************************
	Private Methods - End
******************************/

/******************************
	Public Methods - End
******************************/

void
world::player::_ready()
{
	this->initialize_child_nodes();

	this->input = gd::input::get_singleton();
	this->screen_size = this->gd::canvas_item::get_viewport_rect().size;

	this->gd::canvas_item::hide();
}

void
world::player::_process(
	const double delta
)
{
	// Player movement velocity
	gd::vector2 velocity(0.0f, 0.0f);

	velocity.x = (this->input->get_action_strength("move_right") - this->input->get_action_strength("move_left"));
	velocity.y = (this->input->get_action_strength("move_down") - this->input->get_action_strength("move_up"));

	if (velocity.length() > 0) {
		velocity = velocity.normalized() * this->speed;

		this->child_nodes.animated_sprite->play();
	}
	else {
		this->child_nodes.animated_sprite->stop();
	}

	if (velocity.x != 0.0f) {
		this->child_nodes.animated_sprite->set_animation("walk");
		this->child_nodes.animated_sprite->set_flip_v(false);
	}
	else if (velocity.y != 0.0f) {
		this->child_nodes.animated_sprite->set_animation("up");
		this->child_nodes.animated_sprite->set_flip_v(velocity.y > 0);
	}

	// The next player position
	gd::vector2 position = this->gd::node2d::get_position();

	position += (velocity * static_cast<float>(delta));
	position.x = gd::math::clamp(position.x, 0.0f, this->screen_size.x);
	position.y = gd::math::clamp(position.y, 0.0f, this->screen_size.y);
	
	this->gd::node2d::set_position(position);
}

void
world::player::_on_body_entered(
	const gd::node2d*
)
{
	this->gd::canvas_item::hide();
	this->gd::object::emit_signal("hit");
	this->child_nodes.hit_box->set_deferred("disabled", true);
}

void
world::player::start(
	const gd::vector2& start_pos
)
{
	this->gd::node2d::set_position(start_pos);
	this->gd::canvas_item::show();
	this->child_nodes.hit_box->set_disabled(false);
}

/******************************
	Public Methods - End
******************************/