#!/bin/bash
echo "Script Start"

g++ client.cpp -o client -O2 -pthread;
g++ server.cpp -o server -O2 -pthread;

echo "Script End"