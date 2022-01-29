FROM alpine:3.14
RUN apk add --no-cache clang make musl-dev

COPY . /app/calculator
WORKDIR /app/calculator

RUN make
