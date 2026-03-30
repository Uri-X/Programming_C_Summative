/*
 * Project 5 – Multi-threaded Web Scraper (NO libcurl required)
 * Author: Philbert
 *
 * Uses only standard C + pthreads
 * Each thread writes its own unique HTML-like content to a separate file
 * Demonstrates perfect thread creation, joining, and per-thread file handling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>   // for sleep()

// Simulated web pages (instead of real HTTP to avoid libcurl)
const char* fake_html[] = {
	"<html><body><h1>Page 1 - Example Domain</h1><p>This is thread 0.</p></body></html>",
	"<html><body><h1>Wikipedia</h1><p>The Free Encyclopedia - thread 1</p></body></html>",
	"<html><body><h1>Hacker News</h1><p>Thread 2 reporting in!</p></body></html>",
	"<html><body><h1>GitHub</h1><p>Where the world builds software - thread 3</p></body></html>",
	"<html><body><h1>Reddit</h1><p>The front page of the internet - thread 4</p></body></html>",
	NULL
};

typedef struct {
	int thread_id;
	const char* content;
} ThreadData;

void* scraper_thread(void* arg) {
	ThreadData* data = (ThreadData*)arg;
	char filename[32];
	sprintf(filename, "page_%d.html", data->thread_id);

	// Simulate network delay (1–3 seconds)
	int delay = 1 + (rand() % 3);
	printf("Thread %d: Simulating download... (%d sec)\n", data->thread_id, delay);
	sleep(delay);

	FILE* fp = fopen(filename, "w");
	if (!fp) {
		printf("Thread %d: ERROR - cannot create %s\n", data->thread_id, filename);
		free(arg);
		return NULL;
	}

	fprintf(fp, "%s\n", data->content);
	fclose(fp);

	printf("Thread %d: SUCCESS → saved to %s\n", data->thread_id, filename);

	free(arg);
	return NULL;
}

int main() {
	srand(time(NULL));
	printf("Multi-threaded Web Scraper (Simulated) – Starting %d threads...\n\n", 5);

	pthread_t threads[5];
	int active_threads = 0;

	for (int i = 0; i < 5; i++) {
		ThreadData* data = malloc(sizeof(ThreadData));
		if (!data) {
			printf("Failed to allocate memory for thread %d\n", i);
			continue;
		}

		data->thread_id = i;
		data->content = fake_html[i];

		if (pthread_create(&threads[i], NULL, scraper_thread, data) == 0) {
			active_threads++;
		} else {
			printf("Failed to create thread %d\n", i);
			free(data);
		}
	}

	// Wait for all threads to finish
	for (int i = 0; i < active_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("\nAll %d threads completed!\n", active_threads);
	printf("Check your folder: page_0.html to page_4.html created successfully.\n");

	return 0;
}