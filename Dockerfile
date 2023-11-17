FROM ubuntu:latest

RUN  \
  apt-get install -y \
    make \
    libgtest-dev
