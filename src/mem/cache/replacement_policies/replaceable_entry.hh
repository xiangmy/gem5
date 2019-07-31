/**
 * Copyright (c) 2018 Inria
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Daniel Carvalho
 */

#ifndef __MEM_CACHE_REPLACEMENT_POLICIES_REPLACEABLE_ENTRY_HH__
#define __MEM_CACHE_REPLACEMENT_POLICIES_REPLACEABLE_ENTRY_HH__

#include <cstdint>
#include <memory>

#include "params/BaseReplacementPolicy.hh"

/**
 * The replacement data needed by replacement policies. Each replacement policy
 * should have its own implementation of replacement data.
 */
struct ReplacementData
{
        /**
         * Tick on which the entry was last touched.
         *
         * This field is needed to return the correct value for getLastAccess()
         * function in AbstractReplacementPolicy in Ruby system. By adding
         * necessary functions from AbstractReplacementPolicy, we can use
         * BaseReplacementPolicy in Ruby system so that Ruby system can support
         * different replacement policies from Classic system. For replacement
         * policies that don't use lastTouchTick, we set it to 0.
         */
        Tick lastTouchTick;

        /**
         * Default constructor. Invalidata data.
         */
         ReplacementData() : lastTouchTick(0) {}
};

/**
 * A replaceable entry is a basic entry in a 2d table-like structure that needs
 * to have replacement functionality. This entry is located in a specific row
 * and column of the table (set and way in cache nomenclature), which are
 * stored within the entry itself.
 *
 * It contains the replacement data pointer, which must be instantiated by the
 * replacement policy before being used.
 * @sa Replacement Policies
 */
class ReplaceableEntry
{
  protected:
    /**
     * Set to which this entry belongs.
     */
    uint32_t _set;

    /**
     * Way (relative position within the set) to which this entry belongs.
     */
    uint32_t _way;

   public:
     /**
      * Replacement data associated to this entry.
      * It must be instantiated by the replacement policy before being used.
      */
     std::shared_ptr<ReplacementData> replacementData;

    /**
     * Set both the set and way. Should be called only once.
     *
     * @param set The set of this entry.
     * @param way The way of this entry.
     */
    void setPosition(const uint32_t set, const uint32_t way) {
        _set = set;
        _way = way;
    }

    /**
     * Get set number.
     *
     * @return The set to which this entry belongs.
     */
    uint32_t getSet() const { return _set; }

    /**
     * Get way number.
     *
     * @return The way to which this entry belongs.
     */
    uint32_t getWay() const { return _way; }
};

#endif // __MEM_CACHE_REPLACEMENT_POLICIES_REPLACEABLE_ENTRY_HH_
