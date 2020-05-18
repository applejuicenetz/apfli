FROM debian:8

RUN apt update && apt install -y \
    g++ \
    make \
    ncurses-dev \
    libxml2-dev \
    bzip2 \
    sharutils && \
    mkdir /work

VOLUME /work

WORKDIR /work

CMD ["tail", "-f", "/dev/null"]

# CMD ["make", "release"]
