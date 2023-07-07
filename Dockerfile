FROM ghcr.io/battleofthebots/botb-base-image:ubuntu-20.04-defcon-2023
WORKDIR /opt/
COPY . .
RUN make
ENTRYPOINT ["/opt/sowhat"]
