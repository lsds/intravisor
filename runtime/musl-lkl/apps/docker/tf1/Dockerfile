# Prepares an alpine based image with Python3 and TF installed
# TF is compiled for CPU and without AVX so should be able to run on older processors and virtual machines

FROM alpine:3.8

LABEL maintainer="mech <mech@themech.net>"

ENV TENSORFLOW_VERSION 1.10.1
ENV BAZEL_VERSION 0.17.2
# resources for bazel when building tensorflow: RAM, CPU, IO
ENV LOCAL_RESOURCES 6144,1.0,1.0
ENV JAVA_HOME /usr/lib/jvm/java-1.8-openjdk

RUN apk upgrade --update \
    && apk add --no-cache python3 py3-numpy py3-numpy-f2py libpng libjpeg-turbo libstdc++ \
    && rm -rf /usr/bin/python \
    && ln -s /usr/bin/python3 /usr/bin/python \
    && pip3 install -U --no-cache-dir pip setuptools wheel \
    && sed -i 's/#  define WITH_THREAD/#undef WITH_THREAD/g' /usr/include/python3.6m/pyport.h \
    && : install tools needed during the build process \
    && apk add --no-cache --virtual=.build-deps curl bash openjdk8 build-base gcc g++ linux-headers zip musl-dev patch python3-dev py-numpy-dev \
    && : download and build bazel

RUN cd /tmp \
    && curl -SLO https://github.com/bazelbuild/bazel/releases/download/${BAZEL_VERSION}/bazel-${BAZEL_VERSION}-dist.zip \
    && mkdir bazel-${BAZEL_VERSION} \
    && unzip -qd bazel-${BAZEL_VERSION} bazel-${BAZEL_VERSION}-dist.zip \
    && cd bazel-${BAZEL_VERSION} \
    && sed -i -e '/"-std=c++0x"/{h;s//"-fpermissive"/;x;G}' tools/cpp/cc_configure.bzl \
    && sed -i -e '/#endif  \/\/ COMPILER_MSVC/{h;s//#else/;G;s//#include <sys\/stat.h>/;G;}' third_party/ijar/common.h \
    && sed -i -e 's/-classpath/-J-Xmx8192m -J-Xms128m -classpath/g' scripts/bootstrap/compile.sh \
    && bash compile.sh \
    && cp -p output/bazel /usr/bin/ \
    && : download and build tensorflow pip package

RUN cd /tmp \
    && wget -q -O - https://github.com/tensorflow/tensorflow/archive/v${TENSORFLOW_VERSION}.tar.gz | tar -xzf - -C /tmp \
    && cd /tmp/tensorflow-${TENSORFLOW_VERSION} \
    && : need to patch the sources \
    && sed -i -e '/JEMALLOC_HAVE_SECURE_GETENV/d' third_party/jemalloc.BUILD \
    && sed -i -e '/define TF_GENERATE_BACKTRACE/d' tensorflow/core/platform/default/stacktrace.h \
    && sed -i -e '/define TF_GENERATE_STACKTRACE/d' tensorflow/core/platform/stacktrace_handler.cc \
    && : the types below are fixed in tensorflow 1.11 \
    && sed -i -e 's/uint /uint32_t /g' tensorflow/contrib/lite/kernels/internal/spectrogram.cc \
    && PYTHON_BIN_PATH=/usr/bin/python \
        PYTHON_LIB_PATH=/usr/lib/python3.6/site-packages \
        CC_OPT_FLAGS="-march=native" \
        TF_NEED_JEMALLOC=1 \
        TF_NEED_GCP=0 \
        TF_NEED_HDFS=0 \
        TF_NEED_S3=0 \
        TF_ENABLE_XLA=0 \
        TF_NEED_GDR=0 \
        TF_NEED_VERBS=0 \
        TF_NEED_OPENCL=0 \
        TF_NEED_CUDA=0 \
        TF_NEED_MPI=0 \
        TF_NEED_KAFKA=0 \
        TF_NEED_AWS=0 \
        TF_NEED_OPENCL_SYCL=0 \
        TF_DOWNLOAD_CLANG=0 \
        TF_SET_ANDROID_WORKSPACE=0 \
        bash configure

RUN   cd /tmp/tensorflow-${TENSORFLOW_VERSION} \
    && bazel build -c opt --local_resources ${LOCAL_RESOURCES} --jobs 1 //tensorflow/tools/pip_package:build_pip_package

RUN   cd /tmp/tensorflow-${TENSORFLOW_VERSION} \
    && ./bazel-bin/tensorflow/tools/pip_package/build_pip_package /tmp/tensorflow_pkg
RUN  cd \
    && pip3 install --no-cache-dir /tmp/tensorflow_pkg/tensorflow-${TENSORFLOW_VERSION}-cp36-cp36m-linux_aarch64.whl

RUN apk add --no-cache --virtual=.build-deps git

# Clone Tensorflow models and benchmarks repositories
RUN git clone --depth 1 https://github.com/tensorflow/models.git /tf-models
RUN git clone --depth 1 https://github.com/tensorflow/benchmarks.git -b cnn_tf_v1.10_compatible /tf-benchmarks

ADD app app

ADD app/data/mnist data

RUN apk del .build-deps \
    && rm -f /usr/bin/bazel \
    && rm -rf /tmp/* /root/.cache

