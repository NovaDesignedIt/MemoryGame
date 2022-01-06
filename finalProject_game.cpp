/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program Simple Memory game using Nana library framework
@files >> card.h >> game.h final_project.cpp
@due -  sunday april 18th 2021
******************************************************************************************************/
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <forward_list>
#include <nana/audio/player.hpp>
#include <map>
#include <cassert>

#define ENABLE_NANA_AUDIO
#include <iostream>
#include <chrono>
#include <thread>
#include "card.h"
#include "game.h"
#include <nana/threads/pool.hpp>
#include <random>

/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program main();
calls a game object which is a subclass of form
******************************************************************************************************/

//#define NANA_AUTOMATIC_GUI_TESTING
int main()
{
    using namespace nana;
	game play;
	play.delete_allocated_memory();
	return 0;
}
