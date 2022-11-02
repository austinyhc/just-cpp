#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

char* URL = "https://leetcode.com/api/problems/algorithms/";

typedef struct response {
    char *data;
    size_t size;
} response_t;

static size_t write_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    response_t *response = (response_t*) userp;
    char *ptr = realloc(response->data, response->size + realsize + 1);
    if (!ptr) {
        printf("Not enough memory\n");
        return 0;
    }

    response->data = ptr;
    memcpy(&(response->data[response->size]), buffer, realsize);
    response->size += realsize;
    response->data[response->size] = 0;
    return realsize;
}

int main(void)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {
        response_t resp = { .data = malloc(0), .size = 0 };

        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        printf("%ld\n", resp.size);

        curl_easy_cleanup(curl);
    }
    return 0;
}
