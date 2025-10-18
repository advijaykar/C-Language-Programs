#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <curl/curl.h>

struct DownloadData {
    const char *url;
    const char *filename;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

void *download(void *arg) {
    struct DownloadData *data = (struct DownloadData *)arg;
    CURL *curl = curl_easy_init();
    if(curl) {
        FILE *fp = fopen(data->filename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, data->url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
        printf("Downloaded: %s\n", data->filename);
    }
    return NULL;
}

int main() {
    pthread_t threads[2];
    struct DownloadData files[2] = {
        {"https://example.com/file1.jpg", "file1.jpg"},
        {"https://example.com/file2.jpg", "file2.jpg"}
    };

    for(int i = 0; i < 2; i++)
        pthread_create(&threads[i], NULL, download, &files[i]);
    
    for(int i = 0; i < 2; i++)
        pthread_join(threads[i], NULL);

    printf("All downloads completed.\n");
    return 0;
}
