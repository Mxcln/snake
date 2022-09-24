#ifndef SETTINGSCREEN_SCREEN_H
#define SETTINGSCREEN_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"

namespace sfSnake
{
    enum Switch {ON,OFF};
    enum Speed {SLOW,MODEST,FAST};

    struct Setting
    {
        static sf::Color background_color;
        static Switch grid_switch;
        static sf::Color grid_color;
        static bool game_pause;
        static Speed game_speed;

    };

    class SettingScreen : public Screen
    {
    public:
        struct attribute
        {
            sf::Color color_;
            Switch switch_;
            Speed speed_;

            sf::Text text;
        };

    public:
        SettingScreen();

        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

        static const int color_num;
        static const int settings_num;
        static const int button_size;
        static const int line_size;

        static Setting setting;

    private:
        sf::Font font_;
        sf::Text text_;
        sf::Font font_chosen;

        std::vector<sf::Sprite> sprites_;
        std::vector<sf::Texture> textures_;



        // WHITE BLACK BROWN
        //  OFF    ON
        // WHITE BLACK BROWN
        // MODEST SLOW FAST
        std::vector<std::vector<attribute>> setting_form;

        //point to current setting
        attribute *background_color;
        attribute *grid_switch;
        attribute *grid_color;
        attribute *game_speed;
    };
}

#endif