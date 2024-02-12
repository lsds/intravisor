FROM alpine:edge

RUN apk add --no-cache musl-dev libstdc++ libgcc
RUN apk add --no-cache --virtual=.build-deps \
        g++ \
        make \
        m4 \
	git \
	cmake \
	wget \
	patch \
	bash


COPY arch.patch /
RUN git clone https://github.com/ggerganov/ggml.git && cd /ggml/ && git checkout 8ca2c19a3bb8622954d858fbf6383522684eaf34 && patch -p 1 < /arch.patch
RUN cd /ggml && mkdir build && cd build && cmake .. 
RUN cd /ggml/build && make -j$(nproc) gpt-2
RUN cd /ggml/build && ../examples/gpt-2/download-ggml-model.sh 117M

RUN apk del .build-deps

#RUN cd /ggml/build && ./bin/gpt-2 -m models/gpt-2-117M/ggml-model.bin -p "Once upon a time" -t 4 -n 100
