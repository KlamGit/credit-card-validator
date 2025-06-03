# Build stage
FROM alpine:latest AS builder
RUN apk add --no-cache gcc musl-dev libmicrohttpd-dev
COPY . /app
WORKDIR /app
RUN gcc api.c credit.c -o api -lmicrohttpd  # Build API version
RUN gcc main.c credit.c -o cli              # Build CLI version

# Runtime stage
FROM alpine:latest
RUN apk add --no-cache libmicrohttpd
COPY --from=builder /app/api /app/cli /usr/local/bin/
EXPOSE 8080
CMD ["/usr/local/bin/api"]  # Default: Run the API