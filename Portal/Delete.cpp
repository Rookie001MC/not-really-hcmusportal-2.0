#include "Delete.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include "CourseMan.h"
#include "CourseView.h"

DeleteCourse::DeleteCourse(Data *data)
    : _data(data),
      _boxfocus(0),
      _blink(1),
      _exitfocus(0),
      _submitfocus(0),
      _exitselected(0),
      _submitselected(0),
      l(0)
{}
DeleteCourse::~DeleteCourse() {}
void DeleteCourse::Init()
{
    time = sf::Time::Zero;

    std::ifstream f("buffer.txt");
    getline(f, tmp);
    f.close();

    std::ifstream file("Cmanage\\" + tmp + ".txt");
    std::string get;
    while (!file.eof())
    {
        getline(file, get);
        if (get.empty())
        {
            continue;
        }
        _get[l] = get;
        _id[l]  = get.substr(get.find("(") + 1, get.find(")") - get.find("(") - 1);
        l++;
    }
    file.close();
    _box.setSize(sf::Vector2f(300, 40));
    _box.setFillColor(sf::Color::White);
    _box.setOrigin(
        sf::Vector2f(_box.getGlobalBounds().width / 2, _box.getGlobalBounds().height / 2));
    _box.setPosition(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2 - 100);
    _box.setOutlineThickness(1);
    _box.setOutlineColor(sf::Color(40, 116, 166, 240));

    _text.setFont(_data->_assets->GetFont(CHIVOMONO_LIGHT));
    _text.setString("Course ID: ");
    _text.setCharacterSize(25);
    _text.setPosition(_data->_window->getSize().x / 2 - 150, _data->_window->getSize().y / 2 - 160);
    _text.setFillColor(sf::Color::Black);

    _submitbutton.setSize(sf::Vector2f(150, 40));
    _submitbutton.setFillColor(sf::Color(40, 116, 166, 240));
    _submitbutton.setOrigin(sf::Vector2f(_submitbutton.getGlobalBounds().width / 2,
                                         _submitbutton.getGlobalBounds().height / 2));
    _submitbutton.setPosition(_data->_window->getSize().x / 2,
                              _data->_window->getSize().y / 2 + 100);

    _exitbutton.setSize(sf::Vector2f(150, 40));
    _exitbutton.setFillColor(sf::Color(214, 219, 223, 240));
    _exitbutton.setOrigin(sf::Vector2f(_exitbutton.getGlobalBounds().width / 2,
                                       _exitbutton.getGlobalBounds().height / 2));
    _exitbutton.setPosition(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2 + 150);

    _submit.setFont(_data->_assets->GetFont(KANIT));
    _submit.setString("SUBMIT");
    _submit.setCharacterSize(24);
    _submit.setOrigin(
        sf::Vector2f(_submit.getGlobalBounds().width / 2, _submit.getGlobalBounds().height / 2));
    _submit.setPosition(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2 + 95);
    _submit.setFillColor(sf::Color::White);

    _exit.setFont(_data->_assets->GetFont(KANIT));
    _exit.setString("BACK");
    _exit.setCharacterSize(24);
    _exit.setOrigin(
        sf::Vector2f(_exit.getGlobalBounds().width / 2, _exit.getGlobalBounds().height / 2));
    _exit.setPosition(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2 + 145);
    _exit.setFillColor(sf::Color::Black);

    _showbox.setFont(_data->_assets->GetFont(LIGHT));
    _showbox.setCharacterSize(24);
    _showbox.setFillColor(sf::Color::Black);
    _showbox.setPosition(_data->_window->getSize().x / 2 - 150,
                         _data->_window->getSize().y / 2 - 115);
    _showbox.setString("");

    _status.setCharacterSize(20);
    _status.setFont(_data->_assets->GetFont(CHIVOMONO_LIGHT));
    _status.setStyle(sf::Text::Italic);
    _status.setFillColor(sf::Color::Red);
}
void DeleteCourse::ProcessInput()
{
    sf::Event event;
    while (_data->_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _data->_window->close();
        }
        if (event.type == sf::Event::MouseMoved)
        {
            _exitfocus   = (_exitbutton.getGlobalBounds().contains(
                              sf::Vector2f(sf::Mouse::getPosition(*_data->_window).x,
                                             sf::Mouse::getPosition(*_data->_window).y))
                                ? 1
                                : 0);
            _submitfocus = (_submitbutton.getGlobalBounds().contains(
                                sf::Vector2f(sf::Mouse::getPosition(*_data->_window).x,
                                             sf::Mouse::getPosition(*_data->_window).y))
                                ? 1
                                : 0);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _boxfocus       = (_box.getGlobalBounds().contains(
                             sf::Vector2f(sf::Mouse::getPosition(*_data->_window).x,
                                                sf::Mouse::getPosition(*_data->_window).y))
                                   ? 1
                                   : 0);
            _exitselected   = (_exitfocus ? 1 : 0);
            _submitselected = (_submitfocus ? 1 : 0);
            _blink          = 1;
        }

        if (event.type == sf::Event::TextEntered &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            if (event.text.unicode < 128)
            {
                if (_boxfocus)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                    {
                        if (!_getbox.empty())
                        {
                            _getbox.pop_back();
                        }
                    }
                    else
                    {
                        _getbox += static_cast<char>(event.text.unicode);
                    }
                }
                _blink = 1;
            }
        }
    }
}
void DeleteCourse::Update()
{
    time = clock.getElapsedTime();
    if (time.asSeconds() >= 0.5)
    {
        _blink = !_blink;
        clock.restart();
    }
    _showbox.setString(_getbox + ((_blink && _boxfocus) ? "|" : ""));
    (_exitfocus ? _exitbutton.setFillColor(sf::Color(214, 219, 223, 100))
                : _exitbutton.setFillColor(sf::Color(214, 219, 223, 240)));
    (_submitfocus ? _submitbutton.setFillColor(sf::Color(40, 116, 166, 100))
                  : _submitbutton.setFillColor(sf::Color(40, 116, 166, 240)));
    if (_exitselected)
    {
        _data->_states->RemoveState();
        _exitselected = 0;
    }
    if (!_getbox.empty() && (_submitselected || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
    {
        std::ofstream f("Cmanage\\" + tmp + ".txt");
        bool ok = 1;
        for (int i = 0; i < l; i++)
        {
            if (_id[i] == _getbox)
            {
                std::ofstream f1("Cmanage\\(" + _id[i] + ")" + tmp.substr(0, 1) + ".txt");
                std::ofstream f2("Cmanage\\(" + _id[i] + ")" + tmp.substr(0, 1) + ".csv");
                f1.clear();
                f2.clear();
                f1.close();
                f2.close();
                ok = 0;
            }
            else
            {
                f << _get[i] << std::endl;
            }
        }
        if (ok)
        {
            _status.setString("Not found!");
            _status.setOrigin(sf::Vector2f(_status.getGlobalBounds().width / 2,
                                           _status.getGlobalBounds().height / 2));
            _status.setPosition(_data->_window->getSize().x / 2,
                                _data->_window->getSize().y / 2 + 50);
        }
        else
        {
            Sleep(1000);
            _data->_states->RemoveState();
            _data->_states->AddState(new CourseMan(_data), 1);
        }
        _submitselected = 0;
    }
}
void DeleteCourse::Draw()
{
    _data->_window->clear(sf::Color::White);
    _data->_window->draw(_box);
    _data->_window->draw(_text);
    _data->_window->draw(_submitbutton);
    _data->_window->draw(_exitbutton);
    _data->_window->draw(_submit);
    _data->_window->draw(_exit);
    _data->_window->draw(_showbox);
    _data->_window->draw(_status);
    _data->_window->display();
}

DeleteStudent::DeleteStudent(Data *data)
    : _data(data),
      _boxfocus(0),
      _blink(1),
      _exitfocus(0),
      _submitfocus(0),
      _exitselected(0),
      _submitselected(0),
      l(0)
{}
DeleteStudent::~DeleteStudent() {}
void DeleteStudent::Init()
{
    time = sf::Time::Zero;

    std::ifstream f("buffer.txt");
    getline(f, tmp);
    f.close();

    std::ifstream file("Cmanage\\" + tmp + ".csv");
    std::string get;
    while (!file.eof())
    {
        getline(file, get);
        if (get.empty())
        {
            continue;
        }
        _get[l] = get;
        l++;
    }
    file.close();
    _box.setSize(sf::Vector2f(300, 40));
    _box.setFillColor(sf::Color::White);
    _box.setOrigin(
        sf::Vector2f(_box.getGlobalBounds().width / 2, _box.getGlobalBounds().height / 2));
    _box.setPosition(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2 - 100);
    _box.setOutlineThickness(1);
    _box.setOutlineColor(sf::Color(40, 116, 166, 240));

    _text.setFont(_data->_assets->GetFont(CHIVOMONO_LIGHT));
    _text.setString("Student ID: ");
    _text.setCharacterSize(25);
    _text.setPosition(_data->_window->getSize().x / 2 - 150, _data->_window->getSize().y / 2 - 160);
    _text.setFillColor(sf::Color::Black);

    _submitbutton.setSize(sf::Vector2f(150, 40));
    _submitbutton.setFillColor(sf::Color(40, 116, 166, 240));
    _submitbutton.setOrigin(sf::Vector2f(_submitbutton.getGlobalBounds().width / 2,
                                         _submitbutton.getGlobalBounds().height / 2));
    _submitbutton.setPosition(_data->_window->getSize().x / 2,
                              _data->_window->getSize().y / 2 + 100);

    _exitbutton.setSize(sf::Vector2f(150, 40));
    _exitbutton.setFillColor(sf::Color(214, 219, 223, 240));
    _exitbutton.setOrigin(sf::Vector2f(_exitbutton.getGlobalBounds().width / 2,
                                       _exitbutton.getGlobalBounds().height / 2));
    _exitbutton.setPosition(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2 + 150);

    _submit.setFont(_data->_assets->GetFont(KANIT));
    _submit.setString("SUBMIT");
    _submit.setCharacterSize(24);
    _submit.setOrigin(
        sf::Vector2f(_submit.getGlobalBounds().width / 2, _submit.getGlobalBounds().height / 2));
    _submit.setPosition(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2 + 95);
    _submit.setFillColor(sf::Color::White);

    _exit.setFont(_data->_assets->GetFont(KANIT));
    _exit.setString("BACK");
    _exit.setCharacterSize(24);
    _exit.setOrigin(
        sf::Vector2f(_exit.getGlobalBounds().width / 2, _exit.getGlobalBounds().height / 2));
    _exit.setPosition(_data->_window->getSize().x / 2, _data->_window->getSize().y / 2 + 145);
    _exit.setFillColor(sf::Color::Black);

    _showbox.setFont(_data->_assets->GetFont(LIGHT));
    _showbox.setCharacterSize(24);
    _showbox.setFillColor(sf::Color::Black);
    _showbox.setPosition(_data->_window->getSize().x / 2 - 150,
                         _data->_window->getSize().y / 2 - 115);
    _showbox.setString("");

    _status.setCharacterSize(20);
    _status.setFont(_data->_assets->GetFont(LIGHT));
    _status.setPosition(_data->_window->getSize().x / 2 - 150,
                        _data->_window->getSize().y / 2 + 245);
    _status.setFillColor(sf::Color::Red);
}
void DeleteStudent::ProcessInput()
{
    sf::Event event;
    while (_data->_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _data->_window->close();
        }
        if (event.type == sf::Event::MouseMoved)
        {
            _exitfocus   = (_exitbutton.getGlobalBounds().contains(
                              sf::Vector2f(sf::Mouse::getPosition(*_data->_window).x,
                                             sf::Mouse::getPosition(*_data->_window).y))
                                ? 1
                                : 0);
            _submitfocus = (_submitbutton.getGlobalBounds().contains(
                                sf::Vector2f(sf::Mouse::getPosition(*_data->_window).x,
                                             sf::Mouse::getPosition(*_data->_window).y))
                                ? 1
                                : 0);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _boxfocus       = (_box.getGlobalBounds().contains(
                             sf::Vector2f(sf::Mouse::getPosition(*_data->_window).x,
                                                sf::Mouse::getPosition(*_data->_window).y))
                                   ? 1
                                   : 0);
            _exitselected   = (_exitfocus ? 1 : 0);
            _submitselected = (_submitfocus ? 1 : 0);
            _blink          = 1;
        }

        if (event.type == sf::Event::TextEntered &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            if (event.text.unicode < 128)
            {
                if (_boxfocus)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                    {
                        if (!_getbox.empty())
                        {
                            _getbox.pop_back();
                        }
                    }
                    else
                    {
                        _getbox += static_cast<char>(event.text.unicode);
                    }
                }
                _blink = 1;
            }
        }
    }
}
void DeleteStudent::Update()
{
    time = clock.getElapsedTime();
    if (time.asSeconds() >= 0.5)
    {
        _blink = !_blink;
        clock.restart();
    }
    _showbox.setString(_getbox + ((_blink && _boxfocus) ? "|" : ""));
    (_exitfocus ? _exitbutton.setFillColor(sf::Color(214, 219, 223, 100))
                : _exitbutton.setFillColor(sf::Color(214, 219, 223, 240)));
    (_submitfocus ? _submitbutton.setFillColor(sf::Color(40, 116, 166, 100))
                  : _submitbutton.setFillColor(sf::Color(40, 116, 166, 240)));
    if (_exitselected)
    {
        _data->_states->RemoveState();
        _exitselected = 0;
    }
    if (!_getbox.empty() && (_submitselected || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
    {
        std::ofstream f("Cmanage\\" + tmp + ".csv");
        bool ok = 1;
        for (int i = 0; i < l; i++)
        {
            if (_get[i] == _getbox)
            {
                std::string gett;
                std::ifstream f1("Student\\" + _getbox + ".txt");
                std::ifstream ff("StudentScore\\" + _getbox + ".txt");
                std::string t[100], tt[100];
                int sz = 0;
                while (!f1.eof())
                {
                    getline(f1, gett);
                    if (gett.empty())
                    {
                        continue;
                    }
                    t[sz] = gett;
                    sz++;
                }
                f1.close();
                int sz1 = 0;
                while (!ff.eof())
                {
                    getline(ff, gett);
                    if (gett.empty())
                    {
                        continue;
                    }
                    tt[sz1] = gett;
                    sz1++;
                }
                ff.close();
                std::ofstream f2("Student\\" + _getbox + ".txt");
                for (int j = 0; j < sz; j++)
                {
                    if (t[j] != tmp)
                    {
                        f2 << t[j] << std::endl;
                    }
                }
                f2.close();
                std::ofstream fff("StudentScore\\" + _getbox + ".txt");
                for (int j = 0; j < sz1; j++)
                {
                    if (tt[j].substr(0, tt[j].find(",")) != tmp)
                    {
                        fff << tt[j] << std::endl;
                    }
                }
                fff.close();
                ok = 0;
            }
            else
            {
                f << _get[i] << std::endl;
            }
        }
        if (ok)
        {
            _status.setString("Not found!");
        }
        else
        {
            Sleep(1000);
            _data->_states->RemoveState();
            _data->_states->AddState(new CourseView(_data), 1);
        }
        _submitselected = 0;
    }
}
void DeleteStudent::Draw()
{
    _data->_window->clear(sf::Color::White);
    _data->_window->draw(_box);
    _data->_window->draw(_text);
    _data->_window->draw(_submitbutton);
    _data->_window->draw(_exitbutton);
    _data->_window->draw(_submit);
    _data->_window->draw(_exit);
    _data->_window->draw(_showbox);
    _data->_window->draw(_status);
    _data->_window->display();
}