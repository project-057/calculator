FROM alpine:3.15
RUN apk add --no-cache clang llvm compiler-rt compiler-rt-static lld make musl-dev clang-extra-tools

COPY . /app/calculator
WORKDIR /app/calculator

RUN make isformatted
RUN make
