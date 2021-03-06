#ifndef DATABASE_H
#define DATABASE_H

#include <soci.h>
#include <string>
#include <vector>
#include <set>
#include <time.h>
#include <ctime>

class database
{
public:
    database(const std::string& dburl, int convention);
    ~database();

    static void register_dbs();

    struct object
    {
        int id;

        bool operator<(const object& rhs) const
        {
            return id < rhs.id;
        }

        bool operator==(const object& rhs) const
        {
            return id == rhs.id;
        }
    };

    struct timeslot : public object
    {
        std::tm start_dt;
        std::set<int> available_rooms;
    };

    struct room : public object
    {
        std::string name;
        std::set<int> available_timeslots;
        std::set<int> available_events;
    };

    struct person : public object
    {
        std::string name;
    };

    struct user : public object
    {
        std::string name;
    };

    struct event : public object
    {
        std::string name;
        std::set<int> user_presenters;
        std::set<int> person_presenters;
        std::set<int> suitable_rooms;
        std::set<int> rsvps;
    };

    std::vector<event> get_events();
    std::vector<timeslot> get_timeslots();
    std::vector<room> get_rooms();
    std::vector<person> get_people();
    std::vector<user> get_users();

    void clear_event_time(int id);
    void set_event_time(int id, const std::tm& start_dt);
    void set_event_room(int id, int room_id);

private:

    bool is_postgres;
    std::string path;
    int convention;
    soci::session db;
    

};

#endif // DATABASE_H
