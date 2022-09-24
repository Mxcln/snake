#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "SettingScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

const int SettingScreen::color_num = 3;
const int SettingScreen::settings_num = 4;
const int SettingScreen::button_size = 50;
const int SettingScreen::line_size = 35;

sf::Color Setting::background_color = sf::Color::White;
Switch Setting::grid_switch = OFF;
sf::Color Setting::grid_color = sf::Color::White;
bool Setting::game_pause = false;
Speed Setting::game_speed = MODEST;

SettingScreen::SettingScreen()
{
    font_.loadFromFile("Fonts/fzby.ttf");
    text_.setFont(font_);
    text_.setString(
        "\n\n Background Color:"
        "\n\n Grid Switch:"
        "\n\n Grid Color:"
        "\n\n Speed:"
        "\n\n\n         Press [Space] to return");
    text_.setFillColor(sf::Color::Blue);
    font_chosen.loadFromFile("Fonts/game_over.ttf");

    setting_form.resize(settings_num);
    for (int i = 0; i < settings_num; i++)
    {
        attribute temp;
        temp.text.setFillColor(sf::Color::Green);
        temp.text.setFont(font_chosen);
        temp.text.setPosition(Game::Width * 5 / 8 + button_size / 6,
                              SettingScreen::line_size*(i*2+2.5)-line_size/2);

        temp.color_ = sf::Color::White;
        temp.switch_ = OFF;
        temp.speed_ = MODEST;
        temp.text.setString( i==1 ? "OFF" : ( i==3 ? "MODEST" : "WHITE"));
        setting_form[i].push_back(temp);
        
        temp.color_ = sf::Color::Black;
        temp.switch_ = ON;
        temp.speed_ = FAST;
        temp.text.setString( i==1 ? "ON" : ( i==3 ? "FAST" : "BLACK"));
        setting_form[i].push_back(temp);

        temp.color_ = sf::Color(90, 57, 18);
        temp.speed_ = SLOW;
        temp.text.setString(  i==3 ? "SLOW" : "BROWN");
        setting_form[i].push_back(temp);
    }

    //get current settings
    background_color = &setting_form[0][(Setting::background_color == sf::Color::White 
                                         ? 0 
                                         : (Setting::background_color == sf::Color::Black ? 1 : 2))];
    grid_switch = &setting_form[1][(Setting::grid_switch == ON ? 1 : 0)];
    grid_color = &setting_form[2][(Setting::grid_color == sf::Color::White 
                                   ? 0 
                                   : (Setting::grid_color == sf::Color::Black ? 1 : 2))];
    game_speed = &setting_form[3][(Setting::game_speed == MODEST 
                                   ? 0 
                                   : (Setting::game_speed == FAST ? 1 : 2))];

    //set sprites of buttons
    sprites_.resize(settings_num * 2);
    textures_.resize(settings_num * 2);
    for (int i = 0; i < settings_num * 2; i++)
    {
        textures_[i].loadFromFile(i % 2 ? "pic/right_button.png" : "pic/left_button.png");
        sprites_[i].setTexture(textures_[i]);
        sprites_[i].setOrigin(SettingScreen::line_size /2 ,SettingScreen::line_size /2);
        sprites_[i].setPosition(Game::Width * ( i%2 ? 8 : 5)/9,
                                SettingScreen::line_size*((i/2)*2+2.5));
    }
}

void SettingScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i curr_pos = sf::Mouse::getPosition(window);
        
        for (std::vector<sf::Sprite>::size_type i = 0; i < sprites_.size(); i++)
        {
            // check which button is pressed
            if (curr_pos.x > sprites_[i].getPosition().x &&
                curr_pos.x < sprites_[i].getPosition().x + button_size &&
                curr_pos.y > sprites_[i].getPosition().y &&
                curr_pos.y < sprites_[i].getPosition().y + button_size)
            {
                switch (i)
                {
                //move the pointers
                case 0:
                    if (background_color->color_ == sf::Color::White)
                        background_color += 2;
                    else
                        background_color--;
                    break;
                case 1:
                    if (background_color->color_ == sf::Color(90, 57, 18))
                        background_color -= 2;
                    else
                        background_color++;
                    break;
                case 2:
                case 3:
                    if (grid_switch->switch_ == OFF)
                        grid_switch++;
                    else
                        grid_switch--;
                    break;
                case 4:
                    if (grid_color->color_ == sf::Color::White)
                        grid_color += 2;
                    else
                        grid_color--;
                    break;
                case 5:
                    if (grid_color->color_ == sf::Color(90, 57, 18))
                        grid_color -= 2;
                    else
                        grid_color++;
                    break;
                case 6:
                    if (game_speed->speed_ == MODEST )
                        game_speed += 2;
                    else
                        game_speed--;
                    break;
                case 7:
                    if (game_speed->speed_ == SLOW)
                        game_speed -= 2;
                    else
                        game_speed++;
                    break;
                }
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Game::Screen = std::make_shared<MenuScreen>();
    }
}

void SettingScreen::update(sf::Time delta)
{
    Setting::background_color = background_color->color_;
    Setting::grid_switch = grid_switch->switch_;
    Setting::grid_color = grid_color->color_;
    Setting::game_speed = game_speed->speed_;
}

void SettingScreen::render(sf::RenderWindow &window)
{
    window.draw(text_);
    for (auto sprite : sprites_)
        window.draw(sprite);
    window.draw(background_color->text);
    window.draw(grid_switch->text);
    window.draw(grid_color->text);
    window.draw(game_speed->text);
}