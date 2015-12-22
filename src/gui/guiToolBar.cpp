#include "gui/guiToolBar.h"

guiToolBar::guiToolBar()
{
    //ctor
}

guiToolBar::~guiToolBar()
{
    //dtor
}


void guiToolBar::initialize(sfg::Desktop *desktop){


    imgGrass.loadFromFile("./res/images/grass.jpg");
    imgStone.loadFromFile("./res/images/stone.jpg");

    stone = sfg::Image::Create(imgStone);
    grass = sfg::Image::Create(imgGrass);

	// Create a vertical box layouter with 5 pixels spacing and add the label
	// and button to it.
	box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.0f );
	box->Pack(stone);
	box->Pack(grass);

	//box->Pack( button, false );

	// Create a window and add the box layouter to it. Also set the window's title.
	window_gui = sfg::Window::Create() ;
	window_gui->Add( box );
    //window_gui->SetStyle(sfg::Window::NO_STYLE);

	// Create a desktop and add the window to it.
	desktop->Add( window_gui );


}
