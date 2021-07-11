// Datastructures.cc
// This project was build to a code base
// the main was given by the course

#include "datastructures.hh"

#include <random>
#include <deque>
#include <cmath>
#include <list>
#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>


std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{

}

int Datastructures::place_count()
{
    return Placemap.size();
}

// removes everything
void Datastructures::clear_all()
{
    Areamap.clear();
    Placemap.clear();
}

std::vector<PlaceID> Datastructures::all_places()
{
    std::vector<PlaceID> places_all;
    for (auto key_val_pair : Placemap) {
        places_all.push_back(key_val_pair.first);
    }

    return places_all;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    // esim: add_place 10 'Laavu' shelter (3,3)
    if (Placemap.count(id) == 1) {
        return false;
    }
    else {
        Place temp;
        temp.place_name = name;
        temp.place_type = type;
        temp.place_coordinates = xy;

        Placemap.insert({id, temp});
        return true;
    }
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    if (Placemap.count(id) == 0) {
        return {NO_NAME, PlaceType::NO_TYPE};
    }
    else {
        return {Placemap.at(id).place_name, Placemap.at(id).place_type};
    }
}

Coord Datastructures::get_place_coord(PlaceID id)
{
    if (Placemap.count(id) == 0) {
        return NO_COORD;
    }
    else {
        return Placemap.at(id).place_coordinates;
    }
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{
    if (Areamap.count(id) == 1) {
        return false;
    }
    else {
        Area temp = {};

        std::vector<struct Area*> children_vec;
        temp.children = children_vec;
        temp.area_name = name;
        temp.area_coordinates = coords;
        temp.id = id;

        Areamap.insert({id, temp} );
        return true;
    }
}

Name Datastructures::get_area_name(AreaID id)
{
    if (Areamap.count(id) == 0) {
        return NO_NAME;
    }
    else {
        return Areamap.at(id).area_name;
    }
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    if (Areamap.count(id) == 0) {
        return {NO_COORD};
    } else {
        return Areamap.at(id).area_coordinates;
    }
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}

// places in alphabethical order
std::vector<PlaceID> Datastructures::places_alphabetically()
{
    std::vector<std::pair<Name, PlaceID>> places_unordered = {};
    std::pair<Name, PlaceID> pair_;

    for (const auto & pair : Placemap) {
        pair_ = std::make_pair(pair.second.place_name, pair.first);
        places_unordered.push_back(pair_);
    }

    std::sort(places_unordered.begin(), places_unordered.end());
    std::vector<PlaceID> places_ascii;
    for (const auto & pair : places_unordered) {
        places_ascii.push_back(pair.second);
    }

    return places_ascii;
}

// places in coordinate order
std::vector<PlaceID> Datastructures::places_coord_order()
{
    std::vector<std::pair<Coord, PlaceID>> place_vec;

    for (auto const& pair : Placemap) {
        place_vec.push_back( {pair.second.place_coordinates, pair.first} );
    }
    std::sort(place_vec.begin(), place_vec.end());

    std::vector<PlaceID> vec_coord_order;
    for (auto const& pair : place_vec) {
        vec_coord_order.push_back(pair.second);
    }
    return vec_coord_order;
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{
    std::vector<PlaceID> place_vec;

    for(std::unordered_map<PlaceID, Place>::iterator it = Placemap.begin(); it != Placemap.end(); ++it) {

        if (it->second.place_name != name) {
            continue;
        } else {
            place_vec.push_back(it->first);
        }
    }
    return place_vec;
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    std::vector<PlaceID> place_vec;

    for(std::unordered_map<PlaceID, Place>::iterator it = Placemap.begin(); it != Placemap.end(); ++it) {
        if (it->second.place_type != type) {
            continue;
        } else {
            place_vec.push_back(it->first);
        }
    }
    return place_vec;
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    if (Placemap.count(id) == 0) {
        return false;
    }
    else {
        Placemap.at(id).place_name = newname;
        return true;
    }
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    if (Placemap.count(id) == 0) {
        return false;
    } else {
        Placemap.at(id).place_coordinates = newcoord;
        return true;
    }
}

std::vector<AreaID> Datastructures::all_areas()
{
    std::vector<PlaceID> areas_all;

    for (auto key_val_pair : Areamap) {
        areas_all.push_back(key_val_pair.first);
    }
    return areas_all;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    if (Areamap.at(id).parent == &Areamap.at(parentid)) {
        return false;
    }
    //jos id tai parentid ei olemassa
    if (Areamap.find(id) == Areamap.end() or
            Areamap.find(parentid) == Areamap.end()) {
        return false;
    }
    else {
        // children->parent
        Areamap.at(id).parent = &Areamap.at(parentid);
        // parent->children
        Areamap.at(parentid).children.push_back(&Areamap.at(id));

        return true;
    }
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    std::vector<AreaID> area_vec = {};

    // if id has no area
    if (Areamap.find(id) == Areamap.end()) {
        return {NO_AREA};
    }
    if (Areamap.at(id).parent == nullptr) {
        return {NO_AREA};
    }
    Area* parent = &Areamap.at(id);
    while (parent->parent != nullptr) {
        parent = parent->parent;
        area_vec.push_back(parent->id);
    }
    return area_vec;
}

bool Datastructures::remove_place(PlaceID id)
{
    if (Placemap.count(id) == 0) {
        return false;
    } else {
        Placemap.erase(id);
        return true;
    }
}

std::vector<WayID> Datastructures::all_ways()
{
    std::vector<WayID> ways_all;
    for (auto pair : Waymap) {
        ways_all.push_back(pair.first);
    }
    return ways_all;
}

bool Datastructures::add_way(WayID id, std::vector<Coord> coords)
{   
    if (Waymap.count(id) == 1) {
        return false;
    }
    else {
        Way temp;
        temp.way_id = id;
        temp.coords_ = coords;

        // lasketaan etaisyys
        int x1, y1, x2, y2, lenght_temp, lenght = 0;

        for (unsigned int i = 0; i<coords.size()-1; i++) {
            x1 = coords.at(i).x;
            y1 = coords.at(i).y;

            x2 = coords.at(i+1).x;
            y2 = coords.at(i+1).y;

            lenght_temp = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
            lenght_temp = ceil(lenght_temp);
            lenght = lenght_temp + lenght;
        }

        temp.lenght = lenght;
        Waymap.insert({id, temp});

        // lisataan crossroadit
        Crossroad temp_;
        temp_.crossroad_coord = coords.front();
        temp_.ways_crossroad.push_back(&Waymap.at(id));
        Crossroadmap.insert({coords.front(), temp_});
        temp_.crossroad_coord = coords.back();
        temp_.ways_crossroad.push_back(&Waymap.at(id));
        Crossroadmap.insert({coords.back(), temp_});

        return true;
    }
}

std::vector<std::pair<WayID, Coord>> Datastructures::ways_from(Coord xy)
{
    std::vector<std::pair<WayID, Coord>> ways_coords;
    std::pair<WayID, Coord> pair_way;

    for (auto & pair : Waymap) {
        if (pair.second.coords_.front() == xy) {
            pair_way = std::make_pair(pair.second.way_id, pair.second.coords_.back());
            ways_coords.push_back(pair_way);
        }
        if (pair.second.coords_.back() == xy) {
            pair_way = std::make_pair(pair.second.way_id, pair.second.coords_.front());
            ways_coords.push_back(pair_way);
        }
    }
    if (ways_coords.size() == 0) {
        return {{NO_WAY, NO_COORD}};
    } else {
        return ways_coords;
    }
}

std::vector<Coord> Datastructures::get_way_coords(WayID id)
{
    if (Waymap.count(id) == 0) {
        return {NO_COORD};
    }
    else {
        return Waymap.at(id).coords_;
    }
}

void Datastructures::clear_ways()
{
    Waymap.clear();
}

std::vector<std::tuple<Coord, WayID, Distance>> Datastructures::breadth_search_first(Coord fromxy, Coord toxy) {

    // checking if there is a route
    if ((Crossroadmap.find(fromxy) == Crossroadmap.end()) ||
            (Crossroadmap.find(toxy) == Crossroadmap.end())) {
        return {{NO_COORD, NO_WAY, NO_DISTANCE}};
    }

    // using inline bool operator
    if (operator==(fromxy, toxy)) {
        return {{fromxy, NO_WAY, 0}};
    }

    // clearing the data structures
    visited.clear();
    path.clear();
    trace.clear();

    // adding the end coord
    Coord temp;
    temp = toxy;
    visited.insert(temp);
    path.push_back(temp);

    while (!path.empty()) {
        temp = path.front();
        path.pop_front();

        // checking for the neighbours
        for (Way *i : Crossroadmap.at(temp).ways_crossroad) {
            Coord j;
            if (operator==(temp, i->coords_[0])) {
                j = i->coords_.back();
            } else {
                j = i->coords_[0];
            }

            if (visited.find(j) == visited.end()) {
                visited.insert(j);
                path.push_back(j);
                trace.insert({j, {temp, i}});
            }
        }
    }

    int lenght_full = 0;
    std::vector<std::tuple<Coord, WayID, Distance>> route_vec;
    route_vec.push_back((std::tuple(fromxy, NO_WAY, lenght_full)));

    while (operator!=(std::get<0>(route_vec.back()), toxy)) {
        if (trace.find(std::get<0>(route_vec.back())) != trace.end()) {
            std::pair<Coord, Way*> next_coord;
            next_coord = trace.at(std::get<0>(route_vec.back()));
            std::get<1>(route_vec.back()) = next_coord.second->way_id;
            lenght_full = lenght_full + next_coord.second->lenght;
            route_vec.push_back(std::tuple(next_coord.first, NO_WAY, lenght_full));
        }
        else {
            route_vec.push_back(std::tuple(fromxy, NO_WAY, lenght_full));
        }
    }
    return {route_vec};
}

std::vector<std::tuple<Coord, WayID, Distance>> Datastructures::route_any(Coord fromxy, Coord toxy)
{
    // returns a eay
    return breadth_search_first (fromxy, toxy);
}

bool Datastructures::remove_way(WayID id)
{
    if (Waymap.count(id) == 0) {
        return false;
    } else {
        Waymap.erase(id);
    }
    return true;
}
