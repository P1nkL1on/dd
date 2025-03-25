#include <iostream>
#include <string>
#include <functional>
#include <unordered_set>
#include <unordered_map>

// enum item_tag
// {
//     physical_item,
// };


struct item_view
{

};


struct container;


struct item_get_view_context
{
    virtual ~item_get_view_context() = default;
    virtual item_view *create_icon(const std::string &icon_path) = 0;
};


struct item
{
    // virtual std::unordered_set<item_tag> tags() const { return {}; }
    virtual item_view *view(item_get_view_context &) const { return nullptr; }
    container *_parent = nullptr;
    int _date_created = -1;
    int _date_will_be_destroyed = -1;
};


enum container_type
{
    provider = 0x1,
    consumer = 0x2,
    forced = 0x4,

    provider_consumer = provider | consumer,
    forced_provider = forced | provider,
    forced_consumer = forced | consumer,
};

enum container_event
{
    before_destroy,
    become_empty,
    become_full,
};


using container_trigger = std::function<void(container_trigger_context &ctx)>;


struct container : item
{
    virtual ~container() = default;
    virtual container_type type() const { return provider_consumer; }
    virtual bool can_item_be_placed_inside(const item &) const { return true; }
    virtual container_trigger register_triggers(container_event) const { return nullptr; }
};


// implementation


struct time_for_action : item
{
    item_view *view(item_get_view_context &ctx) const override
    {
        return ctx.create_icon("time_for_action.png");
    }
    static bool eq(const item &i) 
    {
        return dynamic_cast<const time_for_action *>(&i) != nullptr; 
    }
};


struct brawl : container
{
    item_view *view(item_get_view_context &ctx) const override
    {
        return ctx.create_icon("brawl.png");
    }
    container_type type() const override
    {
        return consumer; 
    }
    bool can_item_be_placed_inside(const item &i) const override
    {
        return time_for_action::eq(i);
    }
    container_trigger register_triggers(container_event e) const override
    {
        if (e == become_full) {
            return [](container_trigger_context &ctx) {
                
            };
        }
        return nullptr;
    }
};


int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}