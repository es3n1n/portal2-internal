#pragma once

class c_base_player;
class c_base_entity;

namespace util::players {
    c_base_player* get(int idx);

    inline class c_local_player {
    private:
        c_base_entity* m_ent;
        c_base_player* m_pl;
        int m_idx;
    public:
        c_base_player* operator->() {
            return m_pl;
        }
        c_base_entity* ent() {
            return m_ent;
        }
        int idx() {
            return m_idx;
        }
        bool valid() {
            return static_cast<bool>(m_pl);
        }
        void get();
    } local;
} // namespace util::entities
