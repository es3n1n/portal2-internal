#include "../../cfg/cfg.h"
#include "misc.h"

namespace hack::features::misc {
    void bhop(c_usercmd* cmd) {
        if (!cfg::opts::bhop)
            return;

        if (!(cmd->m_buttons & e_cmd_buttons::in_jump) || // space button isn't pressed
            util::entities::local->m_fFlags() & e_ent_flags::fl_onground // we're on ground
        )
            return; // so we'll keep a space button to jump

        cmd->m_buttons &= ~e_cmd_buttons::in_jump; // remove jump button ( space button is pressed & we're in air )
    }
} // namespace hack::features::misc
