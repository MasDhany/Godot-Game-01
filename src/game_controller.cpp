// Main Header
#include <game_controller.hpp>

// External Dependencies
#include <core/defs.hpp>
#include <core/ref.hpp>
#include <core/vector2.hpp>
#include <gen/packed_scene.hpp>
#include <gen/node.hpp>
#include <gen/timer.hpp>
#include <gen/audio_stream_player.hpp>
#include <gen/position2d.hpp>
#include <gen/object.hpp>
#include <gen/path_follow2d.hpp>
#include <gen/random_number_generator.hpp>
#include <gen/scene_tree.hpp>

// Internal Dependencies
#include <world/mob.hpp>
#include <world/player.hpp>

/******************************
	Public Static Methods - Begin
******************************/

void
game_controller::_register_methods()
{
	gd::register_method("_ready", &game_controller::_ready);
	gd::register_method("_on_mob_timer_timeout", &game_controller::_on_mob_timer_timeout);
	gd::register_method("_on_score_timer_timeout", &game_controller::_on_score_timer_timeout);
	gd::register_method("_on_start_timer_timeout", &game_controller::_on_start_timer_timeout);
	gd::register_method("new_game", &game_controller::new_game);
	gd::register_method("game_over", &game_controller::game_over);

	gd::register_property("mob_scene", &game_controller::mob_scene, (gd::ref<gd::packed_scene>)nullptr);
}

/******************************
	Public Static Methods - End
******************************/

/******************************
	Private Methods - Begin
******************************/

void
game_controller::initialize_child_nodes()
{
	this->child_nodes.mob_timer = this->gd::node::get_node<gd::timer>("mob_timer");
	this->child_nodes.score_timer = this->gd::node::get_node<gd::timer>("score_timer");
	this->child_nodes.start_timer = this->gd::node::get_node<gd::timer>("start_timer");
	this->child_nodes.music = this->gd::node::get_node<gd::audio_stream_player>("music");
	this->child_nodes.death_sound = this->gd::node::get_node<gd::audio_stream_player>("death_sound");
}

/******************************
	Private Methods - End
******************************/

/******************************
	Public Methods - Begin
******************************/

void
game_controller::_ready()
{
	this->initialize_child_nodes();

	this->hud = this->gd::node::get_node<ui::hud>("/root/main/ui/hud");
	this->player = this->gd::node::get_node<world::player>("/root/main/world/player");
	this->world = this->gd::node::get_node<gd::node2d>("/root/main/world");
	this->player_start_position = this->gd::node::get_node<gd::position2d>("/root/main/world/player_start_position");
	this->mob_spawn_location = this->gd::node::get_node<gd::path_follow2d>("/root/main/world/mob_path/mob_spawn_location");
	this->random_generator = (gd::ref<gd::random_number_generator>)gd::random_number_generator::_new();
	this->random_generator->randomize();
}

void
game_controller::_on_mob_timer_timeout()
{
	// Create a new instance of the Mob scene.
	world::mob* mob = gd::object::cast_to<world::mob>(this->mob_scene->instance());

	// Choose a random location on Path2D.
	this->mob_spawn_location->set_offset((float)this->random_generator->randi());

	// Set the mob's direction perpendicular to the path direction.
	float direction = this->mob_spawn_location->get_rotation() + (float)Math_PI / 2;

	// Set the mob's position to a random location.
	mob->set_position(this->mob_spawn_location->get_position());

	// Add some randomness to the direction.
	direction += this->random_generator->randf_range((float)-Math_PI / 4, (float)Math_PI / 4);
	mob->set_rotation(direction);
	
	// Choose the velocity for the mob.
	const gd::vector2 velocity = gd::vector2(this->random_generator->randf_range(150.0, 250.0), 0.0);

	mob->set_linear_velocity(velocity.rotated(direction));
	
	// Spawn the mob by adding it to the Main scene.
	this->world->add_child(mob);
}

void
game_controller::_on_score_timer_timeout()
{
	this->score++;

	this->hud->update_score(this->score);
}

void
game_controller::_on_start_timer_timeout()
{
	this->child_nodes.mob_timer->start();
	this->child_nodes.score_timer->start();
}

void
game_controller::new_game()
{
	this->get_tree()->call_group("mobs", "queue_free");

	this->child_nodes.music->play();

	this->score = 0;
	this->player->start(this->player_start_position->get_position());
	this->child_nodes.start_timer->start();

	this->hud->update_score(this->score);
	this->hud->show_get_ready();
}

void
game_controller::game_over()
{
	this->child_nodes.music->stop();
	this->child_nodes.death_sound->play();

	this->child_nodes.score_timer->stop();
	this->child_nodes.mob_timer->stop();

	this->hud->show_game_over();
}

/******************************
	Public Methods - End
******************************/