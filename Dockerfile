FROM alpine:3.14
RUN apk add --no-cache clang clang-dev make musl-dev lld

COPY . /app/calculator
WORKDIR /app/calculator

RUN make
