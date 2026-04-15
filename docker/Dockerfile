FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    ca-certificates \
    python3 \
    xz-utils \
    && rm -rf /var/lib/apt/lists/*

# ARM GCC 12 (más cercano a CubeIDE)
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu/12.2.mpacbti-rel1/binrel/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz \
    && tar -xf arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz -C /opt \
    && mv /opt/arm-gnu-toolchain-* /opt/arm-toolchain \
    && rm arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz

ENV PATH="/opt/arm-toolchain/bin:${PATH}"

WORKDIR /workspace