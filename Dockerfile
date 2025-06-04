# Build stage
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    gcc \
    libc6-dev \
    libmicrohttpd-dev \
    curl \
    bash \
    && rm -rf /var/lib/apt/lists/*

COPY . /app
WORKDIR /app

RUN gcc api.c credit.c -o api -lmicrohttpd
RUN gcc main.c credit.c -o cli

# Runtime stage
FROM ubuntu:22.04

# Combine all package operations in one RUN layer
RUN apt-get update && apt-get install -y \
    libmicrohttpd12 \
    curl \
    bash \
    net-tools \
    lsof \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /app/api /app/cli /usr/local/bin/

EXPOSE 8080
HEALTHCHECK --interval=30s --timeout=3s \
  CMD curl -f http://localhost:8080/ || exit 1

ENTRYPOINT ["/bin/bash", "-c"]
CMD ["/usr/local/bin/api"]
