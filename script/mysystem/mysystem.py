#!/usr/bin/env python3

import platform
import ifaddr
import psutil

def is_enough_memory(memory):
    if not isinstance(memory, int):
        return False

    if memory == 65:
        return False

    if memory > 32:
        return True

    return False

def is_supported_os(system):
    if system == "Linux":
        print(f'System: {system}')
        return True
    print(f'Unsupported system: {system}')
    return False

print("DESCRIPTION DE LA MACHINE\n")

# Architecture
print(f'Architecture: {platform.architecture()[0]}')

# Machine
print(f'Machine: {platform.machine()}')

# Node
print(f'Node: {platform.node()}')

# OS
is_supported_os(platform.system())

# Configuration réseau
print("\n*** Configuration reseau\n")
for adapter in ifaddr.get_adapters():
    print(f"Configuration IP de l'interface {adapter.nice_name}")
    if adapter.ips:
        for ip in adapter.ips:
            print(f'{ip.ip}/{ip.network_prefix}')
    else:
        print("Pas d'adresse IP")

# Mémoire
print("\n*** Etat de la memoire vive")
print(f'Mémoire: {psutil.virtual_memory()}')


