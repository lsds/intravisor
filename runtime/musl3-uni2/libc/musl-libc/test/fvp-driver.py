#!/usr/bin/env python3

import sys
import os

from telnetlib import Telnet

def fvp_init() -> int:
    script = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'fvp-run.sh')
    return os.system(f'/bin/bash {script}')

def _exec_command_fvp(telnet, cmd, expect: bytes, message, show: bool = False):
    if cmd:
        telnet.write(cmd)
    if message:
        print(message)
    res = telnet.read_until(expect)
    if show:
        print(res.decode('ascii'))

def fvp_boot_and_run_tests() -> int:

    host = 'localhost'
    with open('fvp.port', 'rt') as f:
        port = int(f.read().strip())

    print(f'connecting to {host}:{port}')

    with Telnet(host, port) as tn:
        _exec_command_fvp(tn, None, b'/ # ', 'waiting for fvp to boot...')
        _exec_command_fvp(tn, b'mkdir -p /mnt /tmp\n', b'/ # ', 'created /mnt /tmp', True)
        _exec_command_fvp(tn, b'mount -t 9p -o trans=virtio,version=9p2000.L FM /mnt\n', b'/ # ', 'mounted shared directory', True)
        _exec_command_fvp(tn, b'cd /mnt\n', b'/mnt # ', 'switched directory', True)
        _exec_command_fvp(tn, b'sh test-runner.sh > test-runner-output.txt 2>&1\n', b'/mnt # ', 'started tests...', True)

    return 0

def fvp_stop() -> int:
    return os.system("killall -v -g -9 FVP_Morello")

if __name__ == '__main__':
    command = sys.argv[1]
    if command == 'init':
        sys.exit(fvp_init())
    elif command == 'test':
        sys.exit(fvp_boot_and_run_tests())
    elif command == 'stop':
        sys.exit(fvp_stop())
    else:
        print(f'unknown command {command}')
        sys.exit(2)
