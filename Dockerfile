FROM conanio/clang11 as builder
USER root
WORKDIR /project
COPY src ./src
COPY test ./test
COPY CMakeLists.txt ./CMakeLists.txt
RUN cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B ./bin
RUN cmake --build ./bin --target all
RUN ./bin/test

FROM debian as backend
COPY --from=builder /project/bin/app /app
ENTRYPOINT ["/app"]
