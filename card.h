#pragma once
#include <iostream>

/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@files >> card.h >> game.h final_project.cpp
@due - sunday april 18th 2021
******************************************************************************************************
* class instances variable 
*		image
*		shapeID
*		card_position	
*		*button 
*		flip position 
* 
card.h methods 
		card();
		card(nana::paint::image *img, int id, nana::button* button, int card_position,bool flipped);
		void setShapeID(int id);
		int getShapeID()const;
		std::string card::tostright();
		int card::return_card_position()const;
		void card::flip();
		bool card::is_faceup();
		nana::paint::image* card::getimage()const;
		friend std::ostream& operator<<(std::ostream& out, const card& c);
		bool card::operator==(const card& right_hand_side)const;
		nana::button* card::getButton();
		void card::setPosition(int pos);
		void card::show_();
		~card();

******************************************************************************************************/
class card {
private:

		nana::paint::image *img;
		int shapeID;
		int card_position;
		nana::button* button;
		bool flipped;

public:
	 
		card();
		card(nana::paint::image *img, int id, nana::button* button, int card_position,bool flipped);
		void setShapeID(int id);
		int getShapeID()const;
		std::string card::tostright();
		int card::return_card_position()const;
		void card::flip();
		bool card::is_faceup();
		nana::paint::image* card::getimage()const;
		friend std::ostream& operator<<(std::ostream& out, const card& c);
		bool card::operator==(const card& right_hand_side)const;
		nana::button* card::getButton();
		void card::setPosition(int pos);
		void card::show_();
		~card();

};


/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
card constructor takes it's image it's id, button,card_position, and it'sflipped 

******************************************************************************************************/

inline
card::card(nana::paint::image *img, int id, nana::button* button, int card_position,bool flipped) {
	this->img = img;
	this->shapeID = id;
	this->button = button;
	this->card_position = card_position;
	this->flipped = flipped;

}



/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
card constructor takes it's image it's id, button,card_position, and it'sflipped
******************************************************************************************************/
inline int card::return_card_position()const {
	return this->card_position;

}


/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@ destructor 
******************************************************************************************************/
inline 
	card::~card() {
	std::cout << "destroying card object" << std::endl;
}



/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@ get image
******************************************************************************************************/
nana::paint::image* card::getimage()const {
	return this->img;
}



/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@operator == comparator to compare the cards
******************************************************************************************************/
bool card::operator==(const card& right_hand_side)const {
	if (this->getShapeID() == right_hand_side.getShapeID()) {
		return true;
	}
	else return false;
}
/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@get return shapeID
******************************************************************************************************/
inline
 int card::getShapeID()const{
	return this->shapeID;
}
/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@get set the card position
******************************************************************************************************/
inline 
void card::setPosition(int pos) {
	this->card_position = pos;

}
 

/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@get set the shapeID
******************************************************************************************************/
inline
void card::setShapeID(int id) {
	this->shapeID =id;
	}


/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@get the methods too strings
******************************************************************************************************/
std::ostream& operator<<(std::ostream &out, const card& c){
	return out << "background image id:" << c.getShapeID() << "\n position: "<<c.return_card_position();
}


/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@get get the button pointer 
******************************************************************************************************/
inline nana::button* card::getButton() {
	return this->button;
}


/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@get flip the card face up or face down.
******************************************************************************************************/
inline void card::flip() {
	this->flipped = !flipped;
}



/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@show the button image
******************************************************************************************************/
inline 
void card::show_() {
	this->button->show();
}

/****************************************************************************************************
C++ Final Project CST 8219_300
prof. Kacy T.
@author Meech Lamirande Kabuasa  lami0039@algonquinlive.com
@program card.h
@get is the card faced up?
******************************************************************************************************/
inline
bool card::is_faceup() {
	return this->flipped;
}



