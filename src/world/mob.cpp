// Main Header
#include <world/mob.hpp>

// External Dependencies
#include <core/ref.hpp>
#include <gen/random_number_generator.hpp>
#include <gen/sprite_frames.hpp>
#include <gen/node.hpp>
#include <gen/animated_sprite.hpp>

// Internal Dependencies

/******************************
	Public Static Methods - Begin
******************************/

void
world::mob::_register_methods()
{
	gd::register_method("_ready", &mob::_ready);
	gd::register_method("_on_visibility_notifier2d_screen_exited", &mob::_on_visibility_notifier2d_screen_exited);
}

/******************************
	Public Static Methods - End
******************************/

/******************************
	Private Methods - Begin
******************************/

void
world::mob::initialize_child_nodes()
{
	this->child_nodes.animated_sprite = this->gd::node::get_node<gd::animated_sprite>("animated_sprite");
	this->child_nodes.hit_box = this->gd::node::get_node<gd::collision_shape2d>("hit_box");
	this->child_nodes.visibility_notifier2d = this->gd::node::get_node<gd::visibility_notifier2d>("visibility_notifier2d");
}

/******************************
	Private Methods - End
******************************/

/******************************
	Public Methods - Begin
******************************/

void
world::mob::_ready()
{
	this->initialize_child_nodes();

	// Random number generator
	static gd::ref<gd::random_number_generator> random_generator = 
	[]() -> gd::random_number_generator*
	{
		// Random number generator
		gd::random_number_generator* init_random_generator = gd::random_number_generator::_new();

		// You must use randomize() if you want your sequence of "random" numbers to be different every time 
		// you run the scene.
		init_random_generator->randomize();
		return init_random_generator;
	}();
	
	this->child_nodes.animated_sprite->set_playing(true);

	// List of mob types. First, we get the list of animation names from the animated_sprite's frames property. 
	// This returns an Array containing all three animation names: ["walk", "swim", "fly"].
	static gd::pool_string_array mob_types = this->child_nodes.animated_sprite->get_sprite_frames()->get_animation_names();

	// We then need to pick a random number between 0 and 2 to select one of these names from the list 
	// (array indices start at 0). randi() % n selects a random integer between 0 and n-1.
	this->child_nodes.animated_sprite->set_animation(mob_types[random_generator->randi() % mob_types.size()]);
}

void
world::mob::_on_visibility_notifier2d_screen_exited()
{
	this->gd::node::queue_free();
}

/******************************
	Public Methods - Begin
******************************/