FROM ubuntu:22.04

COPY . /usr/src/

WORKDIR /usr/src/

# from https://github.com/pickling-21/s21_matrixplus/blob/main/src/Valgrind/Dockerfile
RUN apt-get -y update; apt-get -y install valgrind; apt-get -y install check; \
apt-get -y install gcc; apt-get -y install make; mkdir -p /usr/src/; \
apt-get -y install g++; apt-get install -y g++ libgtest-dev;
#

USER root

CMD make leaks
