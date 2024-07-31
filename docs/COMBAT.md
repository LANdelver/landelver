# Table Side Combat Design

## Combat Manager

In order to avoid having to use a full blown entity component system (ECS) we will instead use an event system. This is inspired by how events work on the web, which will also help with having the table and website have similar logical paradigms. The combat manager is a global singleton that stores an array of function pointers to all the ways a combat event can be handled. We may find that we want to handle out of combat controls in a similar fashion but for now all event related stuff goes directly to the global combat manager.

An event is composed of two fields. The first is its type, this ensures that the correct handler gets called on a particular event. The second field is a generic data which can be of any type such that events can have custom data and can even be composed of other events. So like for example a spell attack event could have a dex save event inside its data to trigger that as part of its own handling for sequential events.

Heres the C code for an event.

```C
typedef enum {
    EVENT_TYPE_A,
    EVENT_TYPE_B,
    // etc...
    EVENT_TYPE_COUNT
} event_type_t;

typedef struct {
    event_type_t type;
    void *data;
} event_t;

```

Events can be handled in different ways so we want to make a generic function pointer for them.

```C
typedef void (*event_handler_t)(event_t *event);
```

to store the different types of handlers we will have an array for each corresponding function pointer.

```C
typedef struct {
    event_handler_t handlers[EVENT_TYPE_COUNT];
} event_system_t;

// we make a singleton global instance of this
event_system_t g_combat_manager;
```

next we need to add a way for the combat system to subscribe to events

```C
void add_event_listener(event_type_t type, event_handler_t handler) {
    g_combat_manager.handlers[type] = handler;
}
```

then we need a way to actually dispatch those events

```C
void dispatch_event(event_t *event) {
    g_combat_manager.handlers[event->type](event);
}
```

heres a sample of how it would be used in practice the combat manager file may have a function to handle the casting of fireball

```C
void on_cast_fireball(Event *event) {
    /* Use event data to trigger saves
    and deal corresponding damage*/
}

// then the combat manager will listen for this event like this
add_event_listener(EVENT_TYPE_CAST_FIREBALL, on_cast_fireball);

// in the player code somewhere you would have this
event_t cast_fireball;
cast_fireball.type = EVENT_TYPE_CAST_FIREBALL;
cast_fireball.data = ;// some struct with fireball data

dispatch_event(&cast_fireball);
```