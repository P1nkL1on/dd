#include <iostream>
#include <unordered_set>
#include <unordered_map>

enum item_tag
{
    physical_item,
};


struct item_view
{

};


struct container;


struct item
{
    std::unordered_set<item_tag> _tags;
    item_view *_view = nullptr;
    container *_parent = nullptr;
    int _date_created = -1;
    int _date_will_be_destroyed = -1;
};


struct container_filter
{
    virtual ~container_filter() = default;
    virtual bool is_ok(const item &item) const = 0;
};


enum container_event
{
    before_destroy,
};


struct container_trigger
{
    virtual ~container_trigger() = default;
};


struct container : item
{
    std::unordered_set<const container_filter *> _filters;
    std::unordered_map<container_event, container_trigger *> _triggers;
};


int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}