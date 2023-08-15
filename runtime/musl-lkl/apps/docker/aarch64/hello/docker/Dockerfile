FROM alpine:latest

RUN apk add --no-cache bash musl-dev
RUN apk add --no-cache --virtual=.build-deps \
        g++ \
        make \
        m4

COPY hello_world.c /
RUN gcc hello_world.c && /a.out
RUN apk del .build-deps