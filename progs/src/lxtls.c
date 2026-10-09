/** lxtls.c - libcurl/OpenSSL fetch probe (FreeDom readiness step 6,
 * docs/spec/network.md "Linux socket ABI").
 *
 * The full FreeDom GUI fetches through the static libcurl and OpenSSL that
 * tools/build_freedom_deps.sh pins; when a page fails it only reports a
 * status class. This probe runs the same libraries, the same CA bundle
 * path and the same resolver configuration on their own and prints what
 * failed: libcurl's verbose transcript (resolve, connect, TLS handshake,
 * HTTP), the CURLcode, its error buffer and the response code, plus
 * OpenSSL's own view: whether its random generator is seeded and, on a
 * failure, its error queue.
 *
 * Diagnostic mode: lxtls --rand
 * Walks OpenSSL's random generator stack on its own: fetches the
 * SEED-SRC and CTR-DRBG implementations, draws RAND_bytes and prints
 * "lxtls: rand <step> ok|FAIL" per step with the error queue.
 *
 * Usage: lxtls <url>
 * Prints "lxtls: <libcurl version line>", the verbose transcript as
 * "lxtls| ..." lines, then "lxtls: ok <http-code> <bytes> bytes" with exit
 * 0, or "lxtls: FAIL <curl-code> <error>" with exit 1. Exit 2 on a usage
 * error or when libcurl cannot initialize.
 */
#include <curl/curl.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>

#define LXTLS_TIMEOUT_S        30L
#define LXTLS_CONNECT_S        15L
#define LXTLS_MAX_REDIRECTS    5L
#define LXTLS_CA_BUNDLE        "/etc/ssl/certs/ca-certificates.crt"
#define LXTLS_RAND_BYTES       32

/* Count the body without storing it: the probe proves transport, not
 * content. */
static size_t lxtls_sink(char *data, size_t size, size_t nmemb, void *user) {
    (void)data;
    *(size_t *)user += size * nmemb;
    return size * nmemb;
}

/* Echo libcurl's informational and header lines, one prefixed line each. */
static int lxtls_debug(CURL *h, curl_infotype type, char *data, size_t size, void *user) {
    size_t i, start = 0;
    (void)h;
    (void)user;
    if (type != CURLINFO_TEXT && type != CURLINFO_HEADER_IN && type != CURLINFO_HEADER_OUT)
        return 0;
    for (i = 0; i <= size; i++) {
        if (i == size || data[i] == '\n') {
            size_t len = i - start;
            if (len > 0 && data[start + len - 1] == '\r') len--;
            if (len > 0) printf("lxtls| %.*s\n", (int)len, data + start);
            start = i + 1;
        }
    }
    fflush(stdout);
    return 0;
}

/* Report one RAND step and, on failure, OpenSSL's error queue. */
static int lxtls_step(const char *name, int ok) {
    printf("lxtls: rand %s %s\n", name, ok ? "ok" : "FAIL");
    if (!ok) ERR_print_errors_fp(stdout);
    fflush(stdout);
    return ok;
}

/* lxtls --rand: every layer RAND_status depends on, bottom up. */
static int lxtls_rand(void) {
    unsigned char buf[LXTLS_RAND_BYTES];
    EVP_RAND *seed = EVP_RAND_fetch(NULL, "SEED-SRC", NULL);
    EVP_RAND *drbg = EVP_RAND_fetch(NULL, "CTR-DRBG", NULL);
    int ok = lxtls_step("fetch-seed-src", seed != NULL);
    ok &= lxtls_step("fetch-ctr-drbg", drbg != NULL);
    EVP_RAND_free(seed);
    EVP_RAND_free(drbg);
    ok &= lxtls_step("primary", RAND_get0_primary(NULL) != NULL);
    ok &= lxtls_step("bytes", RAND_bytes(buf, sizeof buf) == 1);
    ok &= lxtls_step("status", RAND_status() == 1);
    return ok ? 0 : 1;
}

int main(int argc, char **argv) {
    char err[CURL_ERROR_SIZE];
    size_t bytes = 0;
    long code = 0;
    CURLcode rc;
    CURL *h;
    if (argc == 2 && strcmp(argv[1], "--rand") == 0) return lxtls_rand();
    if (argc != 2) {
        fprintf(stderr, "usage: lxtls <url> | lxtls --rand\n");
        return 2;
    }
    if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) return 2;
    h = curl_easy_init();
    if (!h) return 2;
    printf("lxtls: %s\n", curl_version());
    printf("lxtls: rand status %d\n", RAND_status());
    ERR_print_errors_fp(stdout);
    err[0] = 0;
    curl_easy_setopt(h, CURLOPT_URL, argv[1]);
    curl_easy_setopt(h, CURLOPT_ERRORBUFFER, err);
    curl_easy_setopt(h, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(h, CURLOPT_DEBUGFUNCTION, lxtls_debug);
    curl_easy_setopt(h, CURLOPT_WRITEFUNCTION, lxtls_sink);
    curl_easy_setopt(h, CURLOPT_WRITEDATA, &bytes);
    curl_easy_setopt(h, CURLOPT_CAINFO, LXTLS_CA_BUNDLE);
    curl_easy_setopt(h, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(h, CURLOPT_MAXREDIRS, LXTLS_MAX_REDIRECTS);
    curl_easy_setopt(h, CURLOPT_TIMEOUT, LXTLS_TIMEOUT_S);
    curl_easy_setopt(h, CURLOPT_CONNECTTIMEOUT, LXTLS_CONNECT_S);
    curl_easy_setopt(h, CURLOPT_SSLVERSION, (long)CURL_SSLVERSION_TLSv1_3);
    rc = curl_easy_perform(h);
    curl_easy_getinfo(h, CURLINFO_RESPONSE_CODE, &code);
    curl_easy_cleanup(h);
    curl_global_cleanup();
    if (rc != CURLE_OK) {
        printf("lxtls: FAIL %d %s\n", (int)rc, err[0] ? err : curl_easy_strerror(rc));
        ERR_print_errors_fp(stdout);
        return 1;
    }
    printf("lxtls: ok %ld %zu bytes\n", code, bytes);
    return 0;
}
