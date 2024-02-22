# build container and tag it as sotn-build:latest
# docker build --tag sotn-build:latest .

# launch container and mount current directory under /sotn
# docker run --rm -it -v $(pwd):/sotn sotn-build /bin/bash

# cd /sotn
# make extract -j && make build -j
FROM ubuntu:22.04

RUN apt-get update

ADD tools/requirements-debian.txt tools/requirements-debian.txt
RUN apt-get install -y $(cat tools/requirements-debian.txt)

ADD tools/requirements-python.txt tools/requirements-python.txt
RUN pip3 install -r tools/requirements-python.txt

RUN git config --global --add safe.directory /sotn

WORKDIR /sotn