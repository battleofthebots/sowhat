FROM ghcr.io/battleofthebots/botb-base-image:latest
ARG NAME=sowhat
LABEL org.opencontainers.image.title=$NAME org.opencontainers.image.description=$NAME org.opencontainers.image.url=https://github.com/battleofthebots/$NAME org.opencontainers.image.source=https://github.com/battleofthebots/$NAME org.opencontainers.image.version=main
WORKDIR /opt/
COPY . .
RUN make release
ENTRYPOINT ["/opt/bin/sowhat"]
