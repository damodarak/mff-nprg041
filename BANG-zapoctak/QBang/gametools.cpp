#include "game.h"

#include <algorithm>

using namespace std;

void GameTools::load_characters(Game* g, std::vector<Hrac>& characters)
{
    //nacteni vsech moznych hracu
    Hrac pl = make_unique<Bart>(g);
    characters.push_back(move(pl));
    pl = make_unique<Blackj>(g);
    characters.push_back(move(pl));
    pl = make_unique<Calamity>(g);
    characters.push_back(move(pl));
    pl = make_unique<Carlson>(g);
    characters.push_back(move(pl));
    pl = make_unique<Cringo>(g);
    characters.push_back(move(pl));
    pl = make_unique<Jesse>(g);
    characters.push_back(move(pl));
    pl = make_unique<Jourd>(g);
    characters.push_back(move(pl));
    pl = make_unique<Ketchum>(g);
    characters.push_back(move(pl));
    pl = make_unique<Lucky>(g);
    characters.push_back(move(pl));
    pl = make_unique<Paul>(g);
    characters.push_back(move(pl));
    pl = make_unique<Pedro>(g);
    characters.push_back(move(pl));
    pl = make_unique<Rose>(g);
    characters.push_back(move(pl));
    pl = make_unique<Slab>(g);
    characters.push_back(move(pl));
    pl = make_unique<Suzy>(g);
    characters.push_back(move(pl));
    pl = make_unique<Vulture>(g);
    characters.push_back(move(pl));
    pl = make_unique<Willy>(g);
    characters.push_back(move(pl));

    auto rd = random_device{};
    auto rng = default_random_engine{ rd() };
    for (size_t i = 0; i < 20; i++)
    {
        shuffle(begin(characters), end(characters), rng);//pro nahodny vyber postav
    }
}

void GameTools::load_card(Game *g, std::vector<std::string> &v)
{
    Card card(stoi(v[4]), v[0], v[3][0], v[1], stoi(v[2]), v[5], stoi(v[6]));

    g->deck.push_back(card);

    //po kazde nove karte premichame balicek
    auto rd = random_device{};
    auto rng = default_random_engine{ rd() };
    shuffle(begin(g->deck), end(g->deck), rng);//pro nahodny vyber karet
}

void GameTools::rm_enemy(Game *g, int id)
{
    //kdykoli nekdo umre, tak nema smysl uchovavat tohoto hrace v seznamu nepratel

    for(size_t i = 0; i <g->game_order.size(); i++)
    {
        if(g->game_order[i]->enemies_id.find(id) != g->game_order[i]->enemies_id.end())
        {
            g->game_order[i]->enemies_id.erase(id);
        }
    }
}

void GameTools::rotate_serif(Game *g)
{
    while (g->game_order[0]->role != 'S')
    {
        rotate(g->game_order.begin(), g->game_order.begin() + 1, g->game_order.end());
    }

    g->active_player = 0;
}

void GameTools::saloon(Game *g)
{
    //vsem +1 zivot, pokud jiz nemaji max. pocet
    for(size_t i = 0; i < g->game_order.size(); i++)
    {
        if(g->game_order[i]->max_health > g->game_order[i]->health)
        {
            g->game_order[i]->health++;
        }
    }
}

void GameTools::set_notai(Game *g)
{
    for(size_t i = 0; i < g->game_order.size(); i++)
    {
        if(!g->game_order[i]->isai)
        {
            g->notai = i;
            return;
        }
    }
    g->notai = 0;
}

void GameTools::load_emporio(Game *g)
{
    //byla zahrana karta Hokynarstvi
    for(size_t i = 0; i < g->game_order.size(); i++)
    {
        g->emporio.push_back(g->draw_from_deck());
    }
}