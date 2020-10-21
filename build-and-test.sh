#!/bin/bash

cd software

# Configuration steps
sh gen_proto.sh

# Build steps
platformio run
