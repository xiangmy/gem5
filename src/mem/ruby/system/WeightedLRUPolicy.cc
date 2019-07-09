/*
 * Copyright (c) 2013-2015 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * For use for simulation and test purposes only
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Derek Hower
 */

#include "mem/ruby/system/WeightedLRUPolicy.hh"

#include <cassert>
#include <memory>

WeightedLRUPolicy::WeightedLRUPolicy(const Params* p)
    : BaseReplacementPolicy(p), m_cache(p->cache)
{
}

WeightedLRUPolicy *
WeightedLRUReplacementPolicyParams::create()
{
    return new WeightedLRUPolicy(this);
}

//void
//WeightedLRUPolicy::touch(int64_t set, int64_t index, Tick time)
//{
//    assert(index >= 0 && index < m_assoc);
//    assert(set >= 0 && set < m_num_sets);
//
//    m_last_ref_ptr[set][index] = time;
//}
void
WeightedLRUPolicy::touch(const std::shared_ptr<ReplacementData>&
                                        replacement_data, Tick time) const
{
    std::static_pointer_cast<WeightedLRUReplData>(replacement_data)->
                                                      lastTouchTick = time;
}

void
WeightedLRUPolicy::touch(const std::shared_ptr<ReplacementData>&
                                                  replacement_data) const
{
    std::static_pointer_cast<WeightedLRUReplData>(replacement_data)->
                                                 lastTouchTick = curTick();
}

/*
void
WeightedLRUPolicy::touch(int64_t set, int64_t index, Tick time, int occupancy)
{
    assert(index >= 0 && index < m_assoc);
    assert(set >= 0 && set < m_num_sets);

    m_last_ref_ptr[set][index] = time;
    m_last_occ_ptr[set][index] = occupancy;
}
*/
void
WeightedLRUPolicy::touch(const std::shared_ptr<ReplacementData>&
                        replacement_data, Tick time, int occupancy) const
{
    std::static_pointer_cast<WeightedLRUReplData>(replacement_data)->
                                                      lastTouchTick = time;
    std::static_pointer_cast<WeightedLRUReplData>(replacement_data)->
                                                  last_occ_ptr = occupancy;
}

//int64_t
//WeightedLRUPolicy::getVictim(int64_t set) const
//{
//    Tick time, smallest_time;
//    int64_t smallest_index;
//
//    smallest_index = 0;
//    smallest_time = m_last_ref_ptr[set][0];
//    int smallest_weight = m_last_occ_ptr[set][0];
//
//    for (unsigned i = 1; i < m_assoc; i++) {
//
//        int weight = m_last_occ_ptr[set][i];
//        if (weight < smallest_weight) {
//            smallest_weight = weight;
//            smallest_index = i;
//            smallest_time = m_last_ref_ptr[set][i];
//        } else if (weight == smallest_weight) {
//            time = m_last_ref_ptr[set][i];
//            if (time < smallest_time) {
//                smallest_index = i;
//                smallest_time = time;
//            }
//        }
//    }
//    return smallest_index;
//}
ReplaceableEntry*
WeightedLRUPolicy::getVictim(const ReplacementCandidates& candidates) const
{
    assert(candidates.size() > 0);

    ReplaceableEntry* victim = candidates[0];
    for (const auto& candidate : candidates) {
        if (std::static_pointer_cast<WeightedLRUReplData>(
                    candidate->replacementData)->last_occ_ptr <
                std::static_pointer_cast<WeightedLRUReplData>(
                    victim->replacementData)->last_occ_ptr) {
            victim = candidate;
        } else if (std::static_pointer_cast<WeightedLRUReplData>(
                    candidate->replacementData)->last_occ_ptr ==
                std::static_pointer_cast<WeightedLRUReplData>(
                    victim->replacementData)->last_occ_ptr) {
            if (std::static_pointer_cast<WeightedLRUReplData>(
                        candidate->replacementData)->lastTouchTick <
                    std::static_pointer_cast<WeightedLRUReplData>(
                        victim->replacementData)->lastTouchTick) {
                victim = candidate;
            }
        }
    }
    return victim;
}

std::shared_ptr<ReplacementData>
WeightedLRUPolicy::instantiateEntry()
{
    return std::shared_ptr<ReplacementData>(new WeightedLRUReplData);
}

void
WeightedLRUPolicy::reset(const std::shared_ptr<ReplacementData>&
                                                    replacement_data) const
{
    // Set last touch timestamp
    std::static_pointer_cast<ReplacementData>(
        replacement_data)->lastTouchTick = curTick();
}

void
WeightedLRUPolicy::invalidate(const std::shared_ptr<ReplacementData>&
                                                    replacement_data) const
{
    // Reset last touch timestamp
    std::static_pointer_cast<ReplacementData>(
        replacement_data)->lastTouchTick = Tick(0);
}
