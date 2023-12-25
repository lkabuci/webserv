FROM gcc:9.5.0-bullseye

RUN apt-get update \
    && apt-get install --no-install-recommends -y \
        cmake=3.18.4-2+deb11u1 \
        vim=2:8.2.2434-3+deb11u1 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app/gtest
RUN git clone --depth=1 https://github.com/google/googletest.git ../googletest

RUN cmake ../googletest/ \
    && make \
    && make install \
    && rm -rf ../googletest

WORKDIR /app

CMD ["make", "-f", "Makefile-test"]
