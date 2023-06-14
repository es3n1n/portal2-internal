#pragma once
#include "sdk/structs/c_usercmd.hpp"
#include "util/mem/mem.hpp"

#define MULTIPLAYER_BACKUP 150
#define READ_VERIFIED_COMMANDS(off) *reinterpret_cast<c_verified_usercmd**>(reinterpret_cast<uint32_t>(this) + (off))

class c_input {
private:
    [[maybe_unused]]std::uint8_t _pad[0xAD];
public:
    bool m_camera_in_third_person;
public:
    c_usercmd* get_command(int sequence_num) {
        // @xref: 55 8B EC 83 EC 60 0F 57 C0 33 C0 56  [client.dll]
        return util::mem::virtual_function<c_usercmd*(__thiscall*)(void* pthis, int slot, int sequence_number)>(this, 8)(this, 0, sequence_num);
    }

    c_verified_usercmd* get_verified_command(int sequence_number) {
        c_verified_usercmd* verified_commands = READ_VERIFIED_COMMANDS(0xF8); // portal2
        if (!verified_commands)
            verified_commands = READ_VERIFIED_COMMANDS(0xF0); // portal reloaded
        return &verified_commands[sequence_number % MULTIPLAYER_BACKUP];
    }
};

#undef READ_VERIFIED_COMMANDS
#undef MULTIPLAYER_BACKUP
