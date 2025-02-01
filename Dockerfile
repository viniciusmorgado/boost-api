FROM ubuntu AS build

RUN apt update && apt full-upgrade -y; \
    apt install libboost-all-dev clang clang-format musl-tools -y;

COPY . . 

RUN ./scripts/linux/formatter.sh; \
    mkdir -p build && \
    cd build && \
    cmake .. -DCMAKE_ENABLE_EXPORTS=on -DCMAKE_C_COMPILER=musl-gcc -DCMAKE_CXX_COMPILER=clang++ && \
    make;

FROM ubuntu

RUN apt update && apt full-upgrade -y;

# COPY --from=build  /config.json /app/config.json
COPY --from=build /build/boost_api /app/boost_api

EXPOSE 8080
CMD ["./app/boost_api"]

# ENTRYPOINT ["tail", "-f", "/dev/null"]