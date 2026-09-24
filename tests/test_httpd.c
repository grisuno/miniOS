/** Docstring: Host test for headers/httpd.h (make test-httpd).
 *
 * Drives the GET parser, the suffix content-type map and the response
 * head builder. Verifies the happy path, query stripping, every
 * fail-closed refusal (method, path, traversal, version, truncation),
 * the head byte layout and the cap bound, so a mutant that accepts a
 * traversal or misreports Content-Length dies on the host with no
 * QEMU boot.
 */

#include <stdio.h>
#include <string.h>

#include "httpd.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    char path[HTTPD_MAX_PATH];
    char head[HTTPD_HEAD_MAX];
    int n;

    CHECK(httpd_parse_get("GET /a.txt HTTP/1.0\r\n", 21u, path, sizeof(path)) == 0, "get ok");
    CHECK(strcmp(path, "a.txt") == 0, "get path");
    CHECK(httpd_parse_get("GET /d/f.c HTTP/1.1\r\n\r\n", 20u, path, sizeof(path)) == 0, "get nested");
    CHECK(strcmp(path, "d/f.c") == 0, "nested path");
    CHECK(httpd_parse_get("GET /q?a=b HTTP/1.0\r\n", 20u, path, sizeof(path)) == 0, "query ok");
    CHECK(strcmp(path, "q") == 0, "query stripped");
    CHECK(httpd_parse_get("POST /a HTTP/1.0\r\n", 18u, path, sizeof(path)) == HTTPD_ERR_METHOD, "post refused");
    CHECK(httpd_parse_get("GET", 3u, path, sizeof(path)) == HTTPD_ERR_METHOD, "short refused");
    CHECK(httpd_parse_get("GET / HTTP/1.0\r\n", 17u, path, sizeof(path)) == HTTPD_ERR_PATH, "root empty");
    CHECK(httpd_parse_get("GET /../s HTTP/1.0\r\n", 20u, path, sizeof(path)) == HTTPD_ERR_PATH, "traversal refused");
    CHECK(httpd_parse_get("GET /a\x7f HTTP/1.0\r\n", 18u, path, sizeof(path)) == HTTPD_ERR_PATH, "nonprint refused");
    CHECK(httpd_parse_get("GET /a.txt\r\n", 12u, path, sizeof(path)) == HTTPD_ERR_VERSION, "no version");
    CHECK(httpd_parse_get("GET /a.txt FOO/1\r\n", 17u, path, sizeof(path)) == HTTPD_ERR_VERSION, "bad version");
    CHECK(httpd_parse_get(0, 10u, path, sizeof(path)) == HTTPD_ERR_BOUND, "null req");
    CHECK(httpd_parse_get("GET /a HTTP/1.0\r\n", 18u, 0, sizeof(path)) == HTTPD_ERR_BOUND, "null out");
    {
        char tiny[4];
        CHECK(httpd_parse_get("GET /abcdef HTTP/1.0\r\n", 22u, tiny, sizeof(tiny)) == HTTPD_ERR_PATH, "overlong refused");
    }

    CHECK(strcmp(httpd_ctype("a.html"), "text/html") == 0, "html");
    CHECK(strcmp(httpd_ctype("a.txt"), "text/plain") == 0, "txt");
    CHECK(strcmp(httpd_ctype("a.c"), "text/plain") == 0, "c");
    CHECK(strcmp(httpd_ctype("a.png"), "image/png") == 0, "png");
    CHECK(strcmp(httpd_ctype("a.wad"), "application/octet-stream") == 0, "wad");
    CHECK(strcmp(httpd_ctype("a"), "application/octet-stream") == 0, "no suffix");
    CHECK(strcmp(httpd_ctype(0), "application/octet-stream") == 0, "null path");

    n = httpd_header(200, "OK", "text/plain", 12u, head, sizeof(head));
    CHECK(n > 0, "head ok");
    CHECK(strncmp(head, "HTTP/1.0 200 OK\r\n", 15) == 0, "head status");
    CHECK(strstr(head, "Content-Type: text/plain\r\n") != 0, "head ctype");
    CHECK(strstr(head, "Content-Length: 12\r\n") != 0, "head length");
    CHECK(strstr(head, "Connection: close\r\n\r\n") != 0, "head close");
    n = httpd_header(404, "Not Found", "text/plain", 0u, head, sizeof(head));
    CHECK(n > 0 && strncmp(head, "HTTP/1.0 404 Not Found\r\n", 22) == 0, "head 404");
    CHECK(httpd_header(99, "X", "text/plain", 0u, head, sizeof(head)) == HTTPD_ERR_BOUND, "bad code");
    CHECK(httpd_header(200, 0, "text/plain", 0u, head, sizeof(head)) == HTTPD_ERR_BOUND, "null reason");
    {
        char tiny[16];
        CHECK(httpd_header(200, "OK", "text/plain", 0u, tiny, sizeof(tiny)) == HTTPD_ERR_BOUND, "head cap");
    }

    if (failures == 0)
        printf("httpd: ok\n");
    return failures != 0;
}
