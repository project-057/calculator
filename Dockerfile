FROM alpine:3.14
RUN apk add --no-cache clang clang-dev make musl-dev lld dpkg
RUN update-alternatives --install /usr/bin/ld ld /usr/bin/lld 10

COPY . /app/calculator
WORKDIR /app/calculator

RUN make
