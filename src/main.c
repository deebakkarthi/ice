#include <curl/curl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UVARC_GEN_AI_ENDPOINT                                                  \
  "https://open-webui.rc.virginia.edu/api/chat/completions"

char *PROGNAME;
char *UVARC_GenAI_API;

int main(int argc, char **argv) {
  CURL *curl = curl_easy_init();
  struct curl_slist *headers = NULL;
  CURLcode res;

  PROGNAME = basename(argv[0]);

  UVARC_GenAI_API = getenv("UVARC_GenAI_API");
  if (!UVARC_GenAI_API) {
    fprintf(stderr,
            "%s: UVARC_GenAI_API environment variable is"
            " not set\n",
            PROGNAME);
    return 1;
  }

  curl_global_init(CURL_GLOBAL_ALL);

  if (!curl) {
    fprintf(stderr, "%s: CURL handle couldn't be acquired\n", PROGNAME);
    return 1;
  }

  curl_easy_setopt(curl, CURLOPT_URL, UVARC_GEN_AI_ENDPOINT);

  curl_easy_setopt(curl, CURLOPT_POST, 1L);

  {
    /*'Authorization: Bearer ' is 22 bytes
     * The length of the API key has to be figured during runtime
     * +1 for null terminator*/

    char *auth_string = (char *)malloc(22 + strlen(UVARC_GenAI_API) + 1);

    sprintf(auth_string, "Authorization: Bearer %s", UVARC_GenAI_API);
    headers = curl_slist_append(headers, auth_string);

    free(auth_string);
  }

  headers = curl_slist_append(headers, "Content-Type: application/json");

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
                   "{\"model\": \"Kimi K2.5\", \"messages\": [{\"role\": "
                   "\"user\", \"content\": \"Hello\"}], \"stream_options\": "
                   "{\"include_usage\": true}}");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);

  /*curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);*/

  res = curl_easy_perform(curl);

  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);

  curl_global_cleanup();

  return 0;
}
