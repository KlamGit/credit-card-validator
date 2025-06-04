#include <microhttpd.h> // lightweight HTTP server library
#include "credit.h" // credit card processing library 
#include <stdlib.h> // for atoll (ASCII to long long conversion)
#include <stdio.h> // standard I/O library, for snprintf and printf
#include <netinet/in.h> // For sockaddr_in
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int handle_request(void *cls, struct MHD_Connection *connection, 
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls)
 {
    // 1. Extract credit card number from URL (e.g., ?card = 378282246310005)
    const char *card_number = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "card");

    if (!card_number) {
    const char *msg = "{\"error\": \"Missing 'card' parameter\"}";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(msg), (void *)msg, MHD_RESPMEM_MUST_COPY);
    MHD_add_response_header(response, "Content-Type", "application/json");
    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    MHD_destroy_response(response);
    return ret;
    }

    // 2. Validate the credit card number using the credit library
    bool valid = check_luhn_maths(atoll(card_number));
    const char *type = credit_card_type(atoll(card_number));

    // 3. Format JSON response
    char response[100];
    snprintf(response, sizeof(response), "{\"valid\": %s, \"type\": \"%s\"}",
             valid ? "true" : "false", valid ? type : "INVALID");

    // 4. Send HTTP response
    struct MHD_Response *http_response = MHD_create_response_from_buffer (strlen(response), (void *)response, 
                                                                           MHD_RESPMEM_MUST_COPY);
    MHD_add_response_header(http_response, "Content-Type", "application/json");
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, http_response);
    MHD_destroy_response(http_response);
    printf("Received request for card: %s\n", card_number);
    return ret;
    }

    int main() {
                struct sockaddr_in addr;
                memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_port = htons(PORT);
                addr.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to all interfaces

                struct MHD_Daemon *daemon = MHD_start_daemon(
                    MHD_USE_SELECT_INTERNALLY,
                    PORT,
                    NULL,
                    NULL,
                    &handle_request,
                    NULL,
                    MHD_OPTION_SOCK_ADDR, (struct sockaddr *)&addr, // Add this line
                    MHD_OPTION_END
                );
    if (!daemon) return 1;

    printf("API server is running on port http://0.0.0.0:%d\n", PORT);

    pause(); // keep running indefinitely

    MHD_stop_daemon(daemon); // will never be reached
    return 0;
}