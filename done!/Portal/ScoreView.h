#pragma once
#include"State.h"
#include"System.h"
#include<fstream>

class ScoreView : public State
{
private:
	Data* _data;
	sf::Text _title;
	int cur;
	sf::Text _No[100], _id[100], _name[100], _mterm[100], _final[100], _other[100];
	sf::RectangleShape _exitbutton;
	sf::Text _exit;
	bool _exitfocus;
	bool _exitselected;
	std::string tmp;

public:
	ScoreView(Data* data);
	~ScoreView();
	void Init();
	void ProcessInput();
	void Update();
	void Draw();

};

class ScoreView1 : public State
{
private:
	Data* _data;
	sf::Text _title;
	int cur;
	sf::Text _id[100], _mterm[100], _final[100], _other[100], _finalmark[100];
	sf::Text _gpa;
	sf::RectangleShape _exitbutton;
	sf::Text _exit;
	bool _exitfocus;
	bool _exitselected;
	std::string tmp;

public:
	ScoreView1(Data* data);
	~ScoreView1();
	void Init();
	void ProcessInput();
	void Update();
	void Draw();

};
