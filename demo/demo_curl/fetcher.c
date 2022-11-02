#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

char *URL = "https://leetcode.com/api/problems/algorithms/";

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

static CURLcode http_get(CURL *handle, char const *url, response_t *resp)
{
    CURLcode res;

    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, resp);

    res = curl_easy_perform(handle);
    if (res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    return res;
}

static int get_title_slug(char const *json_string,
        int const target_id, char *result)
{
	cJSON *root = cJSON_Parse(json_string);

	cJSON *pairs = 0;
	cJSON *pair  = 0;

	pairs = cJSON_GetObjectItem(root, "stat_status_pairs");
    // FIXME: This is not thread safe try to use `cJSON ParseWithOpts`
    // with `return_parse_end` instead.
    if (!pairs) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr)
            fprintf(stderr, "cJSON_Parse() failed: %s\n", error_ptr);
        cJSON_Delete(root);
        return 0;
    }

    cJSON_ArrayForEach (pair, pairs) {
	    cJSON *stat = cJSON_GetObjectItem(pair, "stat");
        int question_id = cJSON_GetObjectItem(stat, "question_id")->valueint;

        if (question_id == target_id) {
            char *title_slug_ = cJSON_GetObjectItem(stat, "question__title_slug")->valuestring;
            int len = strlen(title_slug_);
            char *ptr = realloc(result, len+1);
            result = ptr;
            memcpy(result, title_slug_, len+1);
            cJSON_Delete(root);
            return len;
        }
    }

    cJSON_Delete(root);
    return 0;
}


int main(int argc, char* argv[])
{
    CURL *curl_handle;
    CURLcode res;
    response_t resp = { .data = malloc(0), .size = 0 };

    curl_handle = curl_easy_init();
    if (!curl_handle) {}

    res = http_get(curl_handle, (char const *)URL, &resp);
    if (res != CURLE_OK) goto cleanup;

    char *title_slug = malloc(0);
    get_title_slug((char const*)resp.data, 20, title_slug);
    printf("%s\n", title_slug);

    /* curl_easy_reset(curl_handle); */
    /* http_post(curl_handle) */

cleanup:
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();

    return 0;
}
