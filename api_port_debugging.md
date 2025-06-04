## Issue: Curl is not returning anything even after making sure API is running on port 8080

## Solution
# This is what worked for me:
My container is exiting immediately after starting, even though it prints API server is running....

That likely means my binary is not actually staying alive, likely because the while (1) {} loop is optimized out or misbehaving in Docker.

1. Replace while (1) {} with an actual blocking mechanism
    The empty while (1) {} loop might get optimized away or not block properly under Docker's default signals.

    Fix: Use pause() — it's safer and idiomatic for daemons:

    #include <unistd.h>  // add this at the top for pause()

// Replace:
while (1) {}

// With:
pause();
pause() waits for a signal and will keep the process alive.

2. Update api.c with null check for card_number (important!)
This is defensive programming — without it, atoll(NULL) is undefined:

if (!card_number) {
    const char *msg = "{\"error\": \"Missing 'card' parameter\"}";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(msg), (void *)msg, MHD_RESPMEM_MUST_COPY);
    MHD_add_response_header(response, "Content-Type", "application/json");
    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    MHD_destroy_response(response);
    return ret;
}
// Place the block above before calling check_luhn_maths(...)

3. Rebuild and rerun
    docker build -t credit-validator .
    docker run -p 8080:8080 --rm --name credit-api credit-validator 
    // Make sure there are no existing stopped container named credit-api, otherwise there will be an error. Reason is since we are using --rm, Docker expects no container with that name to already exist.

Following these steps, my API was finally now up and responding with the message:
    json
    { "error": "Missing 'card' parameter" }
    
// If there is an old container with the same name, remove it with -
    docker rm credit-api
    Then rerun container -
    docker run -p 8080:8080 --rm --name credit-api credit-validator

Tip: See all containers (including stopped ones) -
    docker ps -a

To inspect what's hanging around -
    docker container prune


Then test:
    curl "http://localhost:8080/?card=4111111111111111"

Bonus Debugging Tools
If it still exits, you can debug with:

bash
docker logs credit-api

Or run interactively:

bash
docker run -it -p 8080:8080 credit-validator /bin/bash

And then run:

bash
/usr/local/bin/api

✅ Summary
Step	Action
1.	Replace while (1) {} with pause();
2.	Null-check card_number in handle_request()
3.	Rebuild container and run with -p 8080:8080
4.	Test with curl to localhost:8080