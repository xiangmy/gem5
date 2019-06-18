# Copyright (c) 2012 ARM Limited
# All rights reserved.
#
# The license below extends only to copyright in the software and shall
# not be construed as granting a license to any other intellectual
# property including but not limited to intellectual property relating
# to a hardware implementation of the functionality of the software
# licensed hereunder.  You may use the software subject to the license
# terms below provided that you ensure that this notice is replicated
# unmodified and in its entirety in all distributions of the software,
# modified or unmodified, in source code or in binary form.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met: redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer;
# redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution;
# neither the name of the copyright holders nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Authors: Andreas Hansson

import m5
from m5.objects import *

# Add the common scripts to our path
m5.util.addToPath('../learning_gem5/part1/')
m5.util.addToPath('../')

from caches import *

# import the SimpleOpts module
from common import SimpleOpts

# Set the usage message to display
SimpleOpts.set_usage("usage: %prog [options] <binary to execute>")

# Finalize the arguments and grab the opts so we can pass it on to our objects
(opts, args) = SimpleOpts.parse_args()

# Check if there was a binary passed in via the command line and error if
# there are too many arguments
#if len(args) == 1:
#    binary = args[0]
#elif len(args) > 1:
#    SimpleOpts.print_help()
#    m5.fatal("Expected a binary to execute as positional argument")

# both traffic generator and communication monitor are only available
# if we have protobuf support, so potentially skip this test
# require_sim_object("TrafficGen")
# require_sim_object("CommMonitor")
# This needs to be fixed in the new infrastructure

# even if this is only a traffic generator, call it cpu to make sure
# the scripts are happy
# cpu = TrafficGen(
#    config_file=os.path.join(os.path.dirname(os.path.abspath(__file__)),
#                             "tgen-simple-cache.cfg"))
cfg_file = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                                            "test1.cfg")
cpu = TrafficGen(config_file = cfg_file)

#class MyMem(SimpleMemory):
#    if args.bandwidth:
#        bandwidth = args.bandwidth
#    if args.latency:
#        latency = args.latency
#    if args.latency_var:
#        latency_var = args.latency_var

# system simulated
#system = System(cpu = cpu, physmem = MyMem(),
#                membus = IOXBar(width = 16),
#                clk_domain = SrcClockDomain(clock = '1GHz',
#                                            voltage_domain =
#                                            VoltageDomain()))

# create the system we are going to simulate
system = System()

# Set the clock fequency of the system (and all of its children)
system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()

system.mem_ranges = [AddrRange('4096MB')] # Create an address range

# Set up the system
#system.mem_mode = 'timing'               # Use timing accesses
#system.mem_ranges = [AddrRange('512MB')] # Create an address range

# Create a simple CPU
system.cpu = cpu

# Create an L1 instruction and data cache
#system.cpu.icache = L1ICache(opts)
#system.cpu.dcache = L1DCache(opts)

# Connect the instruction and data caches to the CPU
#system.cpu.icache.connectCPU(system.cpu)
#system.cpu.dcache.connectCPU(system.cpu)

# Create a memory bus, a coherent crossbar, in this case
system.l2bus = L2XBar()

# Hook the CPU ports up to the l2bus
#system.cpu.icache.connectBus(system.l2bus)
#system.cpu.dcache.connectBus(system.l2bus)

# Create an L2 cache and connect it to the l2bus
system.l2cache = L2Cache(opts)
#system.l2cache.connectCPUSideBus(system.l2bus)

# Create a memory bus
system.membus = SystemXBar()

# Connect the L2 cache to the membus
system.l2cache.connectMemSideBus(system.membus)

# add a communication monitor, and also trace all the packets and
# calculate and verify stack distance
#system.monitor = CommMonitor()
#system.monitor.trace = MemTraceProbe(trace_file = "monitor.ptrc.gz")
#system.monitor.stackdist = StackDistProbe(verify = True)

# connect the traffic generator to the bus via a communication monitor
system.cpu.port = system.l2bus.slave
system.l2cache.connectCPUSideBus(system.l2bus)

# connect the system port even if it is not used in this example
system.system_port = system.membus.slave

# Create a DDR3 memory controller
system.mem_ctrl = DDR3_1600_8x8()
system.mem_ctrl.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.master

# connect memory to the membus
#system.physmem.port = system.membus.master

# -----------------------
# run simulation
# -----------------------

root = Root(full_system = False, system = system)
root.system.mem_mode = 'timing'

m5.instantiate()
exit_event = m5.simulate(100000000000)

print(exit_event.getCause())
