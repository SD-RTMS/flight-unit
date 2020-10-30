#!/bin/bash

cd proto
protoc --plugin=protoc-gen-nanopb=../lib/nanopb/generator/protoc-gen-nanopb --nanopb_out=. *.proto
mv *.pb.h ../include
mv *.pb.c ../src
