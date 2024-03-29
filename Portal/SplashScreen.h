#pragma once
#include"State.h"
#include"System.h"
class SplashScreen : public State
{
private:
	Data* _data;
	sf::Sprite _logo;
	sf::RectangleShape _loginbox;
	sf::Text _loginbutton;
	sf::RectangleShape _registerbox;
	sf::Text _registerbutton;
	bool _loginfocus;
	bool _registerfocus;
	bool _loginselected;
	bool _registerselected;
public:
	SplashScreen(Data* data);
	~SplashScreen();
	void Init() ;
	void ProcessInput() ;
	void Update() ;
	void Draw() ;
};

