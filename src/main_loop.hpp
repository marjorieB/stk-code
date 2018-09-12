//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004-2015 Ingo Ruhnke <grumbel@gmx.de>
//  Copyright (C) 2006-2015 SuperTuxKart-Team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_MAIN_LOOP_HPP
#define HEADER_MAIN_LOOP_HPP

#include "utils/synchronised.hpp"
#include "utils/types.hpp"
#include <atomic>

/** Management class for the whole gameflow, this is where the
    main-loop is */
class MainLoop
{
private:
    /** True if the main loop should exit. */
    std::atomic_bool m_abort;

    /** True if the frame rate should be throttled. */
    bool m_throttle_fps;

    bool m_frame_before_loading_world;

    Synchronised<int> m_ticks_adjustment;

    uint64_t m_curr_time;
    uint64_t m_prev_time;
    unsigned m_parent_pid;
    float    getLimitedDt();
    void     updateRace(int ticks);
public:
         MainLoop(unsigned parent_pid);
        ~MainLoop();
    void run();
    void abort();
    void setThrottleFPS(bool throttle) { m_throttle_fps = throttle; }
    // ------------------------------------------------------------------------
    /** Returns true if STK is to be stoppe. */
    bool isAborted() const { return m_abort; }
    // ------------------------------------------------------------------------
    void setFrameBeforeLoadingWorld()  { m_frame_before_loading_world = true; }
    // ------------------------------------------------------------------------
    void setTicksAdjustment(int ticks)
    {
        m_ticks_adjustment.lock();
        m_ticks_adjustment.getData() += ticks;
        m_ticks_adjustment.unlock();
    }
};   // MainLoop

extern MainLoop* main_loop;

#endif

/* EOF */
