#include "gui/guidebug.h"
#include <string>
#include <sstream>

guiDebug::guiDebug()
{
    //ctor
}

void guiDebug::initialize(sfg::Desktop *desktop){

	// Create the label.
	m_labelPlayerPosition = sfg::Label::Create( "X: Y: Z:" );
    m_labelPlayerTarget = sfg::Label::Create( "X: Y: Z:" );
    m_labelBlocksLoaded = sfg::Label::Create( "Blocks loaded: " );
    m_labelFps = sfg::Label::Create( "Fps: 0" );
    m_labelCursor = sfg::Label::Create("Cursor");
	// Create a simple button and connect the click signal.
	//button = sfg::Button::Ptr( sfg::Button::Create( "Greet SFGUI!" ) );
//	button->GetSignal( sfg::Widget::OnLeftClick ).Connect( &HelloWorld::OnButtonClick, this );

	// Create a vertical box layouter with 5 pixels spacing and add the label
	// and button to it.
	box = sfg::Box::Ptr( sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f ) );
	box->Pack(m_labelPlayerPosition);
	box->Pack(m_labelPlayerTarget);
	box->Pack(m_labelBlocksLoaded);
	box->Pack(m_labelFps);
	box->Pack(m_labelCursor);
	//box->Pack( button, false );

	// Create a window and add the box layouter to it. Also set the window's title.
	window_gui = sfg::Window::Ptr( sfg::Window::Create() );
	window_gui->SetTitle( "Debug:" );
	window_gui->Add( box );

	// Create a desktop and add the window to it.
	desktop->Add( window_gui );


}

void guiDebug::setPlayerPosition(glm::vec3 pos){

    std::stringstream ss;
    ss.setf( std::ios::fixed, std::ios::floatfield );
    ss.precision(3);

    ss << "Position: " << pos.x << " " << pos.y << " " << pos.z;

    m_labelPlayerPosition->SetText(ss.str());

}

void guiDebug::setPlayerTarget(glm::vec3 pos, uint8_t type, uint8_t hp){

    std::stringstream ss;
    ss.setf( std::ios::fixed, std::ios::floatfield );
    ss.precision(0);

    ss << "Target: " << pos.x << " " << pos.y << " " << pos.z << ", t: " << (int)type << ", hp: " << (int)hp;

    m_labelPlayerTarget->SetText(ss.str());

}

 void guiDebug::setRenderData(int rendered, int loaded){
    std::stringstream ss;
    ss.setf( std::ios::fixed, std::ios::floatfield );
    ss.precision(0);

    ss << "Rendered: " << rendered << " loaded: " << loaded ;

    m_labelBlocksLoaded->SetText(ss.str());


}

 void guiDebug::setFps(int fps){
    std::stringstream ss;
    ss.setf( std::ios::fixed, std::ios::floatfield );
    ss.precision(0);

    ss << "Fps: " << fps;

    m_labelFps->SetText(ss.str());


}

void guiDebug::setCursor(int x, int y) {

    std::stringstream ss;
    ss.setf( std::ios::fixed, std::ios::floatfield );
    ss.precision(0);

    ss << "Cursor: " << x << " " << y ;

    m_labelCursor->SetText(ss.str());



}
