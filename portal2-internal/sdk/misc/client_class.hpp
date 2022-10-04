#pragma once
#include "recv.hpp"

class i_client_networkable;

typedef i_client_networkable* (*create_client_class_fn)(int entnum, int serialNum);
typedef i_client_networkable* (*create_event_fn)();

class c_clientclass {
public:
    create_client_class_fn m_create;
    create_event_fn m_create_event;
    char* m_network_name;
    c_recv_table* m_recv_table;
    c_clientclass* m_next;
    int m_classid;
};
