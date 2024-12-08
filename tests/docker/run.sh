#!/bin/bash

cd ./../../

docker build . -t leak_test:1 -f tests/docker/Dockerfile
docker run --rm -it leak_test:1
docker rmi -f leak_test:1

# docker builder prune
