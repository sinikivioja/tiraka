// Datastructures.hh
// This project was build to a code base
// the main was given by the course

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <deque>
#include <set>
#include <map>

// Types for IDs
using PlaceID = long long int;
using AreaID = long long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;


// This is the class I implemented

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();
    
    int place_count();
    void clear_all();
    std::vector<PlaceID> all_places();
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);
    Coord get_place_coord(PlaceID id);
    std::vector<PlaceID> places_alphabetically();


    std::vector<PlaceID> places_coord_order();
    std::vector<PlaceID> find_places_name(Name const& name);
    std::vector<PlaceID> find_places_type(PlaceType type);
    bool change_place_name(PlaceID id, Name const& newname);
    bool change_place_coord(PlaceID id, Coord newcoord);

    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);
    Name get_area_name(AreaID id);
    std::vector<Coord> get_area_coords(AreaID id);
    std::vector<AreaID> all_areas();

    bool add_subarea_to_area(AreaID id, AreaID parentid);
    std::vector<AreaID> subarea_in_areas(AreaID id);
    
    // Phase 2 operations

    std::vector<WayID> all_ways();
    bool add_way(WayID id, std::vector<Coord> coords);
    std::vector<std::pair<WayID, Coord>> ways_from(Coord xy);
    std::vector<Coord> get_way_coords(WayID id);

    void clear_ways();

    std::vector<std::tuple<Coord, WayID, Distance>> breadth_search_first(Coord fromxy, Coord toxy);
    std::vector<std::tuple<Coord, WayID, Distance>> route_any(Coord fromxy, Coord toxy);
    bool remove_way(WayID id);

private:
    // PHASE 1
    struct Place
    {
        Name place_name;
        PlaceType place_type;
        Coord place_coordinates;
    };

    struct Area
    {
        Name area_name;
        std::vector<Coord> area_coordinates;
        std::vector<Area*> children;
        Area* parent;
        AreaID id;
    };

    std::unordered_map <PlaceID, Place> Placemap;
    std::unordered_map <AreaID, Area> Areamap;

    // PHASE 2

    struct Way {
       WayID way_id = NO_WAY;
       std::vector<Coord> coords_ = {};
       int lenght = 0;
    };

    struct Crossroad {
        Coord crossroad_coord = NO_COORD;
        std::vector<Way*> ways_crossroad = {};
    };

    std::unordered_map <Coord, Crossroad, CoordHash> Crossroadmap;
    std::unordered_map <WayID, Way> Waymap;

    std::set<Coord> visited;
    std::deque<Coord> path;
    std::map<Coord, std::pair<Coord, Way*>> trace;
};

#endif // DATASTRUCTURES_HH
