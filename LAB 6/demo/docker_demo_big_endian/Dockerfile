# docker run --rm --privileged multiarch/qemu-user-static --reset -p yes
# Use a big-endian image
FROM s390x/alpine:latest

RUN apk update && apk add --no-cache gcc musl-dev

WORKDIR /app
COPY demo_pointers_casting.c .

RUN gcc -o demo_pointers_casting demo_pointers_casting.c
CMD ["./demo_pointers_casting"]
