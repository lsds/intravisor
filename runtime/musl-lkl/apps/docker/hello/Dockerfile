FROM alpine:edge

RUN apk add --no-cache musl-dev
RUN apk add --no-cache --virtual=.build-deps \
        g++ \
        make \
        m4 \
	bash 

COPY hello_world.c /
RUN gcc hello_world.c && /a.out
RUN apk del .build-deps