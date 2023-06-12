#pragma once
#include "recv.hpp"

class i_client_networkable;

class c_clientclass {
    using create_class_fn = i_client_networkable*(int ent_num, int serial_num);
    using create_event_fn = i_client_networkable*();

public:
    create_class_fn m_create;
    create_event_fn m_create_event;
    char* m_network_name;
    c_recv_table* m_recv_table;
    c_clientclass* m_next;
    int m_classid;
};
