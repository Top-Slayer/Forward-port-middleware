#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "util.h"

char *serve_js(char *content, char *type)
{
    size_t body_len = strlen(content);
    char *body = (char *)malloc(body_len + 1);
    if (!body)
    {
        LOG_ERR("malloc failed");
        return NULL;
    }

    strcpy(body, content);

    char *type_content = (type == NULL) ? "text/plain" : type;
    const char *header_template =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: %s\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Content-Length: %zu\r\n"
        "Content-Disposition: inline; filename=\"public/output.js\"\r\n"
        "Connection: close\r\n"
        "\r\n";

    size_t header_len = strlen(header_template) + strlen(type_content) + 20;
    size_t response_len = header_len + body_len + 1;

    char *response = (char *)malloc(response_len);
    if (!response)
    {
        LOG_ERR("malloc failed");
        free(body);
        return NULL;
    }

    sprintf(response, header_template, type_content, body_len);
    strcat(response, body);

    free(body);

    return response;
}

char *forward_url(char *url)
{
    size_t body_len = strlen(url);
    char *body = (char *)malloc(body_len + 1);
    if (!body)
    {
        LOG_ERR("malloc failed");
        return NULL;
    }

    strcpy(body, url);

    const char *header_template =
        "HTTP/1.1 302 Found\r\n"
        "Location: %s\r\n"
        "Content-Length: 0\r\n"
        "Connection: close\r\n"
        "\r\n";

    size_t header_len = strlen(header_template) + 20;
    size_t response_len = header_len + body_len + 1;

    char *response = (char *)malloc(response_len);
    if (!response)
    {
        LOG_ERR("malloc failed");
        free(body);
        return NULL;
    }

    sprintf(response, header_template, url);
    strcat(response, body);

    free(body);

    return response;
}