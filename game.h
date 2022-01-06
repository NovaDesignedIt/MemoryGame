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
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <forward_list>
#include <nana/audio/player.hpp>
#include <map>
#include <cassert>
#define ENABLE_NANA_AUDIO
#include    <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include "card.h"
#include <nana/threads/pool.hpp>
#include <random>

//keep this defined to print out all the console messages
#define NANA_CONSOL_OUTPUT_DEBUG
//this is to promtp right to replay (for testing)
//#define PROMPT_REPLAY_TEST

//this is for speeding testing. it just gives all the cards the same ID
//#define SPEED_TESTING

using namespace nana;
// workaround insufficiency in VS2013.
#if defined(_MSC_VER) && (_MSC_VER < 1900)      //VS2013
const std::string plus_minus(to_utf8(L"\u00b1");   // 0xB1    u8"\261"
#else
const std::string plus_minus(u8"\u00b1");
#endif


nana::paint::image* image_of_cards[10]{
	 new nana::paint::image("images/star.bmp"),
	 new nana::paint::image("images/circle.bmp"),
	 new nana::paint::image("images/pentagon.bmp"),
	 new nana::paint::image("images/triangle.bmp"),
	 new nana::paint::image("images/checkers.bmp"),
	 new nana::paint::image("images/hexagon.bmp"),
	 new nana::paint::image("images/flash.bmp"),
	 new nana::paint::image("images/question.bmp"),
	 new nana::paint::image("images/puppy.bmp"),
	 new nana::paint::image("images/dictator.bmp")
};
/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@class game inherits from form (game is a form)
	@method list
		- clicked(); -listens for click events
		- check_if_complete(); - checks is this->game variable is complete.
		- complete(); - notifes user of the finished game and returns the game to a regular state.
		- memory_cards_shuffle(); simple shuffling algorithm
		- reset(); - returns the game to a playable state if user wishes
		- records(); - handles the records of best users that played and handles IO to a record file.
		- ~game(); destructors that deallocates the game.
******************************************************************************************************/
class game : public form {
public:
	game::game();
	bool game::prompt_replay();
	bool game::check_if_complete();
	void game::complete();
	std::vector <card*>& game::memory_cards_shuffle(std::vector <card*>& array_of_cards);
	bool game::clicked(int a, card& card, nana::paint::image img);
	void game::reset();
	void game::records(bool read, std::string name);
	void game::delete_allocated_memory();
	~game();

	void game::print_records();
private:

	card* matching_data_structure[2] = { nullptr,nullptr };
	int success = 0;
	int turns = 0;
	std::vector <card*> array_of_cards;
	std::map<char, card*> cards_map;
	std::list <button> buttons_list;
	void game::test();
	std::vector<std::pair<int, std::string>> top_record;


};

/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program game constructor where I build the GUI and STATE the game and the 
******************************************************************************************************/
inline
game::game() : form(API::make_center(850, 550)) {

	nana::paint::image background, card_image;
	//one thread.
	nana::threads::pool pool(1);


	this->caption(("memory-game final project C++;"));
	static place place(*this);


	//layout 
	place.div("<abc grid=[5,4] gap=10 margin=[5,110,5,110] gap=25>");
	//getting image files
	background = nana::paint::image("images/cards.bmp");

	//need to implement a shuffle algorithm
			//shuffle the images assigne all of them to first 10 cards
				//shuffle the images then assigne them all to the next 10 cards
					//display the cards.


	//fill up coordinate positions
	int position_of_cards[20];
	for (int i = 0; i < 20; i++) {
		position_of_cards[i] = i;
	}

	int k = 0;
	//i is an integer
	for (auto i : position_of_cards) {


		this->buttons_list.emplace_front((*this).handle());
		//access first in the list
		auto& button_card = buttons_list.front();

		//for the 2 sets of cards assigne them an image an Image ID and a position.
		if (i > 9) {
			//second set.
			this->cards_map[i] = new card(image_of_cards[k], k, &button_card, i, false);
			k++;
		}
		else {
			//first set.
			this->cards_map[i] = new card(image_of_cards[i], i, &button_card, i, false);
		}
		//set this buttons back image the stars
		button_card.icon(background);

		//the Event listener, this event listener listens to all events going on in the game and when 
			//the game detects that it's finish the clicked() method returns true and prompts the user 
				//to enter their name and such.
		button_card.events().click(pool_push(pool, [&, i]() {
#ifdef PROMPT_REPLAY_TEST
			this->prompt_replay();
#endif
			if (clicked(i, *this->cards_map[i], background)) {
				this->complete();
			

				this->prompt_replay();
				this->reset();
			}
			}));

	}

	//now we have to return the buttons into our stack of cards. 
	for (auto buttons : this->cards_map) {
		this->array_of_cards.push_back(buttons.second);
	}

#ifdef NANA_CONSOL_OUTPUT_DEBUG
	std::cout << "array of cards" << std::endl;
	std::cout << "******************** [Construction cards] ********************" << std::endl;
	for (auto button : this->array_of_cards) {
		std::cout << *button << std::endl;
	}
	std::cout << "****************************************\n\n" << std::endl;
	std::cout << "******************** [Shuffling Order of cards] ********************" << std::endl;
#endif 


	//shuffle the cards;
	memory_cards_shuffle(this->array_of_cards);

	//now place the buttons in the layout
	int j = 0;
	for (auto& i : this->array_of_cards) {
		i->setPosition(j);
		place["abc"] << *i->getButton();
		j++;
	}

#ifdef NANA_CONSOL_OUTPUT_DEBUG
	std::cout << "array of cards - Shuffled" << std::endl;
	for (auto button : this->array_of_cards) {
		std::cout << *button << std::endl;
	}
#endif 
	place.collocate();

	drawing dw(*this);

	nana::paint::image img("images/black.bmp");
	dw.draw([&img](nana::paint::graphics& graph) {
		if (img.empty()) return;
		img.paste(graph, nana::point{});

		});
	dw.update();


#ifdef SPEED_TESTING //this sets all the shape Id's to be the same is for TESTING ONLY.
	for (auto& i : array_of_cards) {
		i->setShapeID(1);
	}
#endif
	//show it.
	show();
	exec(
#ifdef NANA_AUTOMATIC_GUI_TESTING
		1, 1, [&game]()
		{
			test();
		}
#endif
	);
}//END OF GAME CONSTRUCTOR


/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com

@mnethod :  bool game::clicked(int a, card& card, nana::paint::image img){}

@program click();
the click method is the logic handler of the entire game. it checks each click if the game is finished.
	algorithm( > x) ->  card clicked () -> put card in match structure;
				-> second card clicked() -> does second card match first? : YES? -> hide the buttons and increment success variables || NO? flip back play sounds
					-> is finished()?   YES? -> prompt_preplay(); NO? LOOP back(> x)
					
******************************************************************************************************/
inline
bool game::clicked(int a, card& card, nana::paint::image img) {
	if (card.is_faceup()) {
		return false;
	}
	card.getButton()->icon(*(card.getimage()));

	//if the first card isn't null?
	if (this->matching_data_structure[0] != nullptr) {

		if ((this->matching_data_structure[0]->return_card_position() == card.return_card_position())) {
			return false;
		}


		if (*matching_data_structure[0] == card) {
			//consol out data.
#ifdef NANA_CONSOL_OUTPUT_DEBUG
			std::cout << "[card 2]" << std::endl;
			std::cout << card << std::endl;
			std::cout << "******************** [ Match Found ] ********************" << std::endl;
#endif 
			nana::audio::player correct("sounds/correct.wav");
#ifndef SPEED_TESTING
			correct.play();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
#endif
			//the cards match so remove them and set them to flipped();
			this->matching_data_structure[0]->flip();
			this->matching_data_structure[0]->getButton()->hide();
			card.flip();
			card.getButton()->hide();
			++success;
			++turns;
			matching_data_structure[0] = nullptr;

			if (check_if_complete()) {
			
				return true;
			}
			else {
				turns++;
				return false;
			}
		}
		else {
#ifdef NANA_CONSOL_OUTPUT_DEBUG
			std::cout << "[card 2]" << std::endl;
			std::cout << card << std::endl;
			std::cout << "[ XXXX ] =/= [ NO MATCH ]" << std::endl;
#endif

			nana::audio::player wrong("sounds/wrong.wav");
#ifndef SPEED_TESTING
			wrong.play();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
#endif
			matching_data_structure[0]->getButton()->icon(img);
			card.getButton()->icon(img);
			matching_data_structure[0] = nullptr;
			++turns;
		}

		return false;
	}
	else {
		//the first card to be verified isn't there? put this card in.
#ifdef NANA_CONSOL_OUTPUT_DEBUG
		std::cout << " [card 1]" << std::endl;
		std::cout << card << std::endl;
#endif
		matching_data_structure[0] = &card;
		return false;
	}

}

/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com

@method: bool game::prompt_replay(){}

@program: Simple form the prompt user if they want to replay, the game. two buttons with event listeners
	>wants to replay? reset the game variables and reset the boards to show the cards and shuffle. 


******************************************************************************************************/


inline
bool game::prompt_replay() {
	this->records(true, "not applicable");
	std::string record_string = "records:";
	int j = 0;
	if (this->turns < this->top_record.at(0).first) {
		record_string += "\tnew record!";
	}
	while (j < 5) {
		record_string += "\n" + std::to_string(this->top_record.at(j).first) + "\t" + this->top_record.at(j).second;
		j++;
	}

	form fm;
	std::string name;
	//Define a label and display a text.
	label lab{ fm, "Memory test took you " + std::to_string(this->turns) + " turns to complete " };
	textbox name_input{ fm };
	name_input.tip_string("name:");
	name_input.multi_lines(false);

	lab.format(true);
	label records{ fm ,record_string };

	//Define a button and answer the click event.
	button btn{ fm, "Quit" };
	btn.events().click([&fm, this, &name_input, &name] {
		name_input.getline(0, name);
		this->records(false, name);
		
#ifdef NANA_CONSOL_OUTPUT_DEBUG
		std::cout << "***************name inputed: " << name << std::endl;
#endif
		fm.close();
		this->close();
		return true;
		});

	button btn2{ fm, "Play" };
	btn2.events().click([&fm, this, &name_input, &name] {
		name_input.getline(0, name);
		this->records(false, name);

#ifdef NANA_CONSOL_OUTPUT_DEBUG
		std::cout << "***************name inputed: " << name << std::endl;
#endif
		this->show();
		this->success = 0;
		this->turns = 0;
		fm.close();
		return true;
		});

	//Layout management
	fm.div("vert <weight=20% text><weight=10% <textbox>pad=10><weight=60% records><weight=20  <gap=5 button2><gap=5 button>");
	fm["text"] << lab;
	fm["textbox"] << name_input;
	fm["button2"] << btn2;
	fm["records"] << records;
	fm["button"] << btn;
	fm.collocate();

	//Show the form
	fm.collocate();
	fm.show();

	//Start to event loop process, it blocks until the form is closed.
	exec();
	return true;
}




/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@method: bool game::check_if_complete()
@program: returns true/false;
******************************************************************************************************/

inline
bool game::check_if_complete() {
	return (success == 10);
}

/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@method: void game::complete(){}
@program: notifies the user if won. 
******************************************************************************************************/
inline
void game::complete() {
#ifdef NANA_CONSOL_OUTPUT_DEBUG
	std::cout << "you're finished! congrats! number of turns it took you " << turns << std::endl;
#endif
	nana::audio::player ending("sounds/end.wav");
	ending.play();
}


/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@method:   std::vector <card*>& game::memory_cards_shuffle(std::vector <card*>& array_of_cards)
@program: shuffles the mad of cards.
******************************************************************************************************/
inline
std::vector <card*>& game::memory_cards_shuffle(std::vector <card*>& array_of_cards) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(array_of_cards.begin(), array_of_cards.end(), std::default_random_engine(seed));
	return array_of_cards;
}

/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@destructor: 
@program: dealloc
******************************************************************************************************/
inline
game::~game() {
#ifdef NANA_CONSOL_OUTPUT_DEBUG
	std::cout << "destroying cards" << std::endl;
#endif
}

/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@method:  void game::reset()
@program: reset the deck of cards
******************************************************************************************************/
inline
void game::reset() {
	for (auto& i : this->array_of_cards) {
		i->flip();
		i->getButton()->icon(nana::paint::image("images/cards.bmp"));
		i->show_();
	}
}

/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@method:  void game::test() 
@program: game::test() tests the functionality method currently isn't implemented
******************************************************************************************************/


inline
void game::test() {
	while (check_if_complete()) {
		for (auto& i : this->array_of_cards) {
			i->getButton()->events().click;
			for (auto& j : this->array_of_cards) {
				if ((j->getShapeID() == i->getShapeID()) && (i->return_card_position() != j->return_card_position())) {
					j->getButton()->events().click;
				}
			}
		}
	}
}



/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@method: void game::records(bool read, std::string name)
@program: this handles the records of them game it takes the names from a file and keeps in the game memory
after the game has been completed, it displays the games record data. then inserts a name and rewrites into the file.

******************************************************************************************************/
inline
void game::records(bool read, std::string name) {
	if (read) {
		std::ifstream file("records.txt");
		std::string str;
		int turns_it_took;
		std::string name;

		if (!file) {
			std::cerr << "can't open file" << std::endl;
		}

		size_t pos = 0;
		std::string token;
		while (file >> name >> turns_it_took) {
			std::istringstream text_stream(str);
			this->top_record.push_back(std::make_pair(turns_it_took, name));
		}
		file.close();


	}
	else {
		if (name.empty()) {
			name = "noname";
		}
		else {
			remove_if(name.begin(), name.end(), isspace);
		}

		this->top_record.push_back(std::make_pair(this->turns, name));
		std::sort(this->top_record.begin(), this->top_record.end());
		std::ofstream out_file("records.txt", std::ios::trunc);
		for (auto& i : this->top_record) {
			out_file << i.second << " " << i.first << std::endl;
		}

	}


}


/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@method: void game::print_records()
@program: this prints the records for test purposes only; 

******************************************************************************************************/
#ifdef NANA_CONSOL_OUTPUT_DEBUG
inline
void game::print_records() {
	int j = 0;
	for (auto& i : this->top_record) {
		std::cout << j << " turns:" << i.first << "name" << i.second << std::endl;
		j++;
	}
}
#endif

/*****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@method: void game::delete_allocated_memory()
@program: dealloc memory

******************************************************************************************************/
void game::delete_allocated_memory() {
	for (auto& i : this->array_of_cards) {
		delete(i);
	}

}