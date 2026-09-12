#include <stdio.h>
#include <libgen.h>
#include <curl/curl.h>

char *PROGNAME;

int main(int argc, char **argv)
{
	PROGNAME = basename(argv[0]);

	curl_global_init(CURL_GLOBAL_ALL);
	CURL *handle = curl_easy_init();

	if (!handle) {
		fprintf(stderr, "%s: CURL handle couldn't be acquired\n",
			PROGNAME);
	}
	CURLcode res;
	curl_easy_setopt(handle, CURLOPT_URL, "https://example.com");
	res = curl_easy_perform(handle);

	curl_easy_cleanup(handle);

	curl_global_cleanup();
	return 0;
}
