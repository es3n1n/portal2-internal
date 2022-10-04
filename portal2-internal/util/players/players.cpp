#include "players.hpp"
#include "sdk/portal.hpp"

namespace util::players {
    void c_local_player::get() {
        m_idx = portal::engine_client->get_local_player();
        m_ent = portal::entitylist->get_client_entity(m_idx);
        m_pl = reinterpret_cast<c_base_player*>(m_ent);
    }

    c_base_player* get(int idx) {
        return reinterpret_cast<c_base_player*>(portal::entitylist->get_client_entity(idx));
    }
} // namespace util::players
