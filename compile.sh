#!/bin/bash
echo "Script Start"

g++ client.cpp -o client -O2;
g++ server.cpp -o server -O2;

echo "Script End"