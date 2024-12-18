# Use the official Ubuntu 22.04 image as the base image
FROM ubuntu:22.04 as base

# Set shell for running commands
SHELL ["/bin/bash", "-c"]

# Install essential packages
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    curl \
    git \
    g++ \
    libgtest-dev \
    libx11-6 \
    libx11-dev \
    mesa-utils \
    # required by ompl
    libboost-serialization-dev \
    libboost-filesystem-dev \
    libboost-system-dev \
    libboost-program-options-dev \
    libboost-test-dev \
    libeigen3-dev \
    libode-dev \
    libyaml-cpp-dev \
    # required by BTCPP
    libzmq3-dev \
    libsqlite3-dev \
    pkg-config \
    python3-dev python3-venv python3-pip python3-setuptools \
    wget && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# add custom library paths to the dynamic linker configuration
RUN echo "/usr/local/lib" >> /etc/ld.so.conf.d/99local.conf && ldconfig

ENV LANG en_GB.UTF-8
ENV LANGUAGE en_GB.UTF-8

RUN python3 -m pip install --upgrade pip

ENV CXX=g++
ENV MAKEFLAGS="-j8"

# install BehaviorTree.CPP (v4.6.2) from source
RUN wget https://github.com/BehaviorTree/BehaviorTree.CPP/archive/refs/tags/4.6.2.tar.gz -O /opt/BehaviorTree.CPP-4.6.2.tar.gz && \
    tar -xzf /opt/BehaviorTree.CPP-4.6.2.tar.gz -C /opt && \
    rm /opt/BehaviorTree.CPP-4.6.2.tar.gz && \
    cd /opt/BehaviorTree.CPP-4.6.2 && \
    mkdir build && cd build && \
    cmake -DBTCPP_UNIT_TESTS=OFF -DBTCPP_EXAMPLES=OFF .. && \
    make && make install

# install ompl (v1.6.0) from source
RUN wget https://github.com/ompl/ompl/archive/refs/tags/1.6.0.tar.gz -O /opt/ompl-1.6.0.tar.gz && \
    tar -xzf /opt/ompl-1.6.0.tar.gz -C /opt && \
    rm /opt/ompl-1.6.0.tar.gz && \
    cd /opt/ompl-1.6.0 && \
    mkdir -p build/Release && \
    cd build/Release && \
    cmake ../.. -DOMPL_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DPYTHON_EXEC=/usr/bin/python3 && \
    make && make install

# Create a symlink for 'python' to 'python3'
RUN ln -sf /usr/bin/python3 /usr/bin/python

# Create a workspace
WORKDIR /workspace

# Install Python dependencies
COPY requirements.txt /workspace/
RUN pip3 install --upgrade pip && \
    pip3 install --no-cache-dir -r /workspace/requirements.txt

FROM base AS dev

ENV PYTHONUNBUFFERED=1

# Set entrypoint script
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

WORKDIR /workspace
ENTRYPOINT ["/entrypoint.sh"]