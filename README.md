# System Info Script

This Bash script collects and displays system information, such as CPU details, memory usage, disk usage, network information, and system status. It then broadcasts the collected data to all logged-in users using the `wall` command.

## Features

- Displays system architecture
- Shows physical and virtual CPU cores
- Reports RAM usage (total, used, and percentage)
- Calculates disk usage (total, used, and percentage)
- Displays CPU load percentage
- Shows the last system boot time
- Checks if LVM is in use
- Counts active TCP connections
- Lists the number of logged-in users
- Displays network information (IP and MAC address)
- Counts executed sudo commands

## Usage

Run the script with:

```bash
./script.sh

