#!/bin/bash

# Check if the correct number of arguments is provided
# $# -> numbers of arguments
if [ $# -ne 1 ]; then
	echo "Usage: $0 <pid>"
	exit 1
fi

# Assign the provided PID to the 'pid' variable
pid="$1"

# If sig is 0, then no signal is sent, but error checking is still performed 
# this can be used to check for the existence of a process ID or process 
# group ID.
if ! kill -0 "$pid" 2>/dev/null; then
	echo "Invalid PID: $pid"
	exit 1
fi

# Send the SIGQUIT signal to the target process
kill -QUIT "$pid"